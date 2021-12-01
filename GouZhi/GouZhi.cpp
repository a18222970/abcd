// GouZhi.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "GouZhi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CGouZhiApp

BEGIN_MESSAGE_MAP(CGouZhiApp, CWinApp)
END_MESSAGE_MAP()


// CGouZhiApp 构造

CGouZhiApp::CGouZhiApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CGouZhiApp 对象
HHOOK KeyHook;
HHOOK KeyHook64;
CGouZhiApp theApp;

CGouZhiApp* PtheApp;


// CGouZhiApp 初始化

BOOL CGouZhiApp::InitInstance()
{
	CWinApp::InitInstance();
	PtheApp = this;
	KeyHook = SetWindowsHook(WH_KEYBOARD, KeyCallBack);
	//KeyHook64 = SetWindowsHookEx(WH_KEYBOARD,)

	return TRUE;
}

LRESULT __stdcall KeyCallBack(int nCode, WPARAM w, LPARAM l)
{
	if ((l & (1 << 31)) == 0)
	{
		switch (w)
		{
		case VK_HOME:
			/*显示页面*/
			if (PtheApp->sheZhiL == NULL)
			{
				PtheApp->sheZhiL = new SheZhi;
				PtheApp->sheZhiL->Create(IDD_SHE_ZHI);
			}
			PtheApp->sheZhiL->ShowWindow(TRUE);
			break;
		default:
			break;
		}
		return CallNextHookEx(KeyHook, nCode, w, l);
	}
}