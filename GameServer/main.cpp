#include <iostream>
#include <vector>

extern "C"
{
#include "event2/event.h"
#include "event2/event_compat.h"
#include "event2/listener.h"

#include <winsock2.h>
};

struct TimeoutData
{
	struct event** timeout_event;
	timeval tv;
};

std::vector<evutil_socket_t> sockets;

static void echo_cb(evutil_socket_t newsock, short events, void * additional_data)
{
	if(events & EV_READ)
	{
		char recv_buffer[256];
		memset(recv_buffer, 0, 256);

		int len = recv(newsock, recv_buffer, 256, 0);
		std::cout<<"recv:"<<recv_buffer<<std::endl;

		char* send_buffer = "byebye";
		send(newsock, send_buffer, strlen(send_buffer), 0);
	}
}

static void timeout_cb(evutil_socket_t newsock, short events, void * additional_data)
{
	TimeoutData* td = (TimeoutData*)additional_data; 
	if(events & EV_TIMEOUT)
	{
		char* buf = "let me go";
		for(std::vector<evutil_socket_t>::iterator itr = sockets.begin(); itr != sockets.end(); ++itr)
		{
			send(*itr, buf, strlen(buf), 0);
		}

		evtimer_add((*(td->timeout_event)), &td->tv);
	}
}

static void	listenercb(struct evconnlistener *listener, evutil_socket_t newsock,
struct sockaddr *sourceaddr, int socklen, void *ctx)
{
	//拿到 event base
	struct event_base* base_ptr = (struct event_base*)ctx;
	
	//添加读监听
	struct event* read_event;
	read_event = event_new(base_ptr, newsock, EV_READ|EV_PERSIST, echo_cb, base_ptr);
	event_add(read_event, NULL);
	sockets.push_back(newsock);
	
	std::cout<<"new connection sock:"<< newsock <<std::endl;
}

//处理三种情况
//1. 请求和回复
//2. 定时通知
//3. 广播

int main()
{
#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);
	//WSAStartup必须是应用程序或DLL调用的第一个Windows Sockets函数
	(void) WSAStartup(wVersionRequested, &wsaData);
#endif

	event_base* base;
	base = event_base_new();
	if(base == NULL)
	{
		std::cout<<"init base failed"<<std::endl;
		return -1;
	}

	//监听请求
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	//inet_addr不需要再转换一次字节序了，也就是不需要再调用 htonl
	sin.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("127.0.0.1");
	sin.sin_port = htons(9875);

	struct evconnlistener* listener;
	listener = evconnlistener_new_bind(base,listenercb, base, LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1,(const sockaddr*)&sin, sizeof(sin));
	if(listener == NULL)
	{
		std::cout<<"init listener failed."<<std::endl;
		return -1;
	}

	//定时消息处理
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	struct event* timeout_event;

	TimeoutData td;
	td.timeout_event = &timeout_event;
	td.tv = tv;

	timeout_event = evtimer_new(base, timeout_cb, &td);

	evtimer_add(timeout_event, &tv);

	event_base_dispatch(base);
	evconnlistener_free(listener);
	event_base_free(base);

	int c;
	std::cin>>c;

	return 0;
}