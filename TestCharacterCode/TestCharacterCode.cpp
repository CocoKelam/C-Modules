// TestCharacterCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "StrCodeUtil.h"
#include "GSStrCodeUtil.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{

	std::string strUtf8;
	GSStrCodeUtil::GB2312ToUTF_8(strUtf8,"中国",sizeof("中国"));


	//**test this function has memory leak?
	std::string strAnsi;
	for (int i = 0; i < 1000000; i++)
	{
		strAnsi = StrCodeUtil::UTF8ToANSI(strUtf8);
		strUtf8 = StrCodeUtil::ANSIToUTF8(strAnsi);
	}
	
	std::cout << "end" << std::endl;
	getchar();
	return 0;
}

