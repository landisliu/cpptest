#include "GetData.h"


GetData::GetData(void)
{
	m_instance = IGVoiceWraper::get_instance();
}

GetData::~GetData(void)
{
}

__declspec(dllexport) GetData* ExportData()
{
	return new GetData();
}