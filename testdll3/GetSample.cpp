#include "GetSample.h"

GetSample::GetSample(void)
{
	m_instance = IGVoiceWraper::get_instance();
}


GetSample::~GetSample(void)
{
}

__declspec(dllexport) GetSample* ExportSample()
{
	return new GetSample();
}