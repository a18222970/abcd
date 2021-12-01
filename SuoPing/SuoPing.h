
// SuoPing.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号

// CSuoPingApp:
// 有关此类的实现，请参阅 SuoPing.cpp
//

class CSuoPingApp : public CWinApp
{
public:
	CSuoPingApp();
	BOOL tcpKaiGuan;//另类的全局变量
	struct XinXi_J
	{
		char* id;
		char* mima;
		const char* xiaoxi;
	};
	XinXi_J xinXiJ;
// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

//声明全局对象
extern CSuoPingApp theApp;

