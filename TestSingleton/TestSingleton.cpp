// TestSingleton.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Singleton.hpp"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{

	coco::Singleton<int>::GetInstance(5);

	std::cout << *coco::Singleton<int>::GetInstance() << std::endl;

	getchar();
	return 0;
}

