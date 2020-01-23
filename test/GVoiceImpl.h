#pragma once
#include "IGVoice.h"

class GVoiceImpl:public IGVoice
{
public:
	GVoiceImpl(void);
	~GVoiceImpl(void);

	virtual void init();

};

