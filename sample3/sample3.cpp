// ������ DLL �ļ���

#include "stdafx.h"

#include "sample3.h"
namespace sample3 {
Class1::Class1()
{
	m_gvoice = IGVoiceWraper::get_instance();
}
}