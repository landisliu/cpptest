#pragma once

#include "IGVoiceWraper.h"
class GetSample
{
public:
	GetSample(void);
	~GetSample(void);
private:
	IGVoice* m_instance;
};

__declspec(dllexport) GetSample* ExportSample();

