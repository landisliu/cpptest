// 这是主 DLL 文件。

#include "stdafx.h"

#include "sample2.h"
namespace sample2 {
Class1::Class1()
{
	m_gvoice = IGVoiceWraper::get_instance();
}
}

