#include "stdio.h"

int charToInt(char c)
{
	switch(c)
	{
	case 'I':
		return 1;
	case 'V':
		return 5;
	case 'X':
		return 10;
	case 'L':
		return 50;
	case 'C':
		return 100;
	case 'D':
		return 500;
	case 'M':
		return 1000;
	default:
		return 0;
	}
}
int romanToInt(char * s){
	char* cur = s;
	char* next = NULL;
	int total = 0;
	while(*cur != '\0')
	{
		int cur_num = charToInt(*cur);
		next = cur + 1;
		if(next == '\0')
		{
			total += cur_num;
			return total;
		}

		int next_num = charToInt(*next);

		if(cur_num >= next_num)
		{
			total += cur_num;
			cur = next;
		}
		else
		{
			total += (next_num - cur_num);
			cur = next + 1;
		}
	}
	return total;
}