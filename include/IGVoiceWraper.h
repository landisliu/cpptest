#pragma once

#include "IGVoice.h"

class IGVoiceWraper
{
public:
	IGVoiceWraper(void);
	~IGVoiceWraper(void);
	static IGVoice* get_instance();
private:
	static IGVoice* m_instance;
};