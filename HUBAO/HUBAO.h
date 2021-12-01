
// HUBAO.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
/***************************/
#include <iostream>
#include "SheZhi.h"
//#include "ACCSCC.h"
// CHUBAOApp:
// 有关此类的实现，请参阅 HUBAO.cpp
//

class CHUBAOApp : public CWinApp
{
public:
	CHUBAOApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
public:
	BOOL tcpFuuWuKaiGuan;
	char tcpDengLUYanZheng[600];//TCP收到的消息
	BOOL idYanZhe; //登陆ID验证
	//SOCKET hSock;//tcp

	//HANDLE hMutex;//多线程互斥量
	// 
	//操作全局变量时就加锁, 互斥量
	//WaitForSingleObject(hMutex, INFINITE);
	//操作完全局变量时就解锁, 互斥量
	//ReleaseMutex(hMutex);

	/*accscc*/
	CString yongHuId[10];//数据库字段id表
	CString yongHuJl[11];//数据库字段JiLu表
	CString jinCheng2[24];
	CString fXjc[10];
	CString bMingDan[2];

	CString jinCheng1Biao;
	CString idBiao;
	CString jiLuBiao;
	CString jinCheng2Biao;
	CString jinChengBiao;
	CString fXjinCheng;
	CString mingDanBiao;

	SheZhi sheZhiL;

	CString kuPath;

	int ci;//线程数量
};

extern CHUBAOApp theApp;
