#include "IGVoiceWraper.h"
#include "GVoiceImpl.h"

IGVoiceWraper::IGVoiceWraper(void)
{
}


IGVoiceWraper::~IGVoiceWraper(void)
{
}

IGVoice* IGVoiceWraper::m_instance;
IGVoice* IGVoiceWraper::get_instance()
{
	if(!m_instance)
	{
		m_instance = new GVoiceImpl;
	}
	return m_instance;
}