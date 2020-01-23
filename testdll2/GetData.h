#pragma once
#include "IGVoiceWraper.h"
class GetData
{
public:
	GetData(void);
	~GetData(void);
private:
	IGVoice* m_instance;
};

__declspec(dllexport) GetData* ExportData();

