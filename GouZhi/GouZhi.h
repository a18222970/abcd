// GouZhi.h: GouZhi DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
#include "SheZhi.h"

// CGouZhiApp
// 有关此类实现的信息，请参阅 GouZhi.cpp
//

class CGouZhiApp : public CWinApp
{
public:
	CGouZhiApp();
	
public://添加

	SheZhi* sheZhiL;

// 重写
public:
	
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

/*注入函数,截取键盘消息,钩子*/
LRESULT CALLBACK KeyCallBack(int nCode, WPARAM w, LPARAM l);