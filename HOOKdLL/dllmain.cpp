// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <Windows.h>
#include <string>

#pragma warning(disable:4996)

HHOOK hHook = 0;
HINSTANCE hMod = 0;
HWND hExe = 0;
HANDLE hProcess;
DWORD dizhi;
DWORD dizhi1;
ULONG FunAddr;
ULONG JmpAddr = 0;
char OldCode[5] = {0};
char NewCode[5] = {0};
int a = 0;
char code[1] = { 0 };
BOOL WINAPI CreateProcessWCallBack(
	LPCWSTR lpApplicationName,
	LPWSTR lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles,
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCWSTR lpCurrentDirectory,
	LPSTARTUPINFOW lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation);
BOOL WINAPI ActiveDefenseON();
BOOL WINAPI ActiveDefenseOFF();
LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);
BOOL HookStatus(BOOL Status);
BOOL HookCreateProcess();

/*cs*/
int ava(int a, int b)
{
	return a + b;
}

/*这是输出函数，用于在应用程序中调用，启用API HOOK:*/
BOOL WINAPI ActiveDefenseON()
{
	/*设置系统钩子，向各活动进程注入此DLL*/
	hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)HookProc, hMod, 0);
	if (hHook)
	{
		printf("            hook  ok            \n");
		return TRUE;
	}
	else 
	{
		printf("            hook     no        \n");
		return FALSE; 
	}
}

/*这是输出函数，用于在应用程序中调用，关闭API HOOK:*/
BOOL WINAPI ActiveDefenseOFF() 
{ 
	return(UnhookWindowsHookEx(hHook)); 
}


LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	//printf("     HookProc       hook  ok            \n");
	return(CallNextHookEx(hHook, nCode, wParam, lParam)); //将钩子信息传递给当前钩子链中的下一个钩子过程
}

/*设置API Hook启用状态状态：*/
BOOL HookStatus(BOOL Status)
{
	BOOL ret = FALSE;
	if (Status)
	{
		printf("     HookStatus       hook  WriteProcessMemory            \n");
		/*将CreateProcessW入口地址写为我们自己定义的函数，使API Hook启用:*/
		ret = WriteProcessMemory(hProcess, (void*)FunAddr, NewCode, 5, 0);
		if (ret) return TRUE;
	}
	else
	{
		printf("     HookStatus       hook  WriteProcessMemory            \n");
		/*将CreateProcessW入口地址写为原始函数CreateProcessW的地址，API Hook停止*/
		ret = WriteProcessMemory(hProcess, (void*)FunAddr, OldCode, 5, 0);
		if (ret)
		{
			return TRUE;
		}
		return FALSE;
	}
	
}

/*CreateProcessW的替代函数，拥有与CreateProcessW相同的参数：*/
BOOL WINAPI CreateProcessWCallBack(
	LPCWSTR lpApplicationName,
	LPWSTR lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles,
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCWSTR lpCurrentDirectory,
	LPSTARTUPINFOW lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation)
{
	printf("     CreateProcessWCallBack       hook              \n");
	BOOL b = FALSE;
	char AppName[256] = { 0 };
	//const char* AppName = "";
	//获取要启动的进程：
	WideCharToMultiByte(CP_ACP, 0, lpApplicationName, -1, AppName, 256, NULL, NULL);

	char* CopyData = NULL;
	//构造字符串，内容是：进程和命令行。用于发送给上层杀毒软件
	strcat(CopyData, AppName);
	strcat(CopyData, "$");

	char* s = new char[1024];
	//s = { 0 };
	strcpy_s(s, 1024, "");
	//s[0] = AppName[0];
		
	//构造字符串，内容是：进程和命令行。用于发送给上层杀毒软件
	strcat(s, AppName);
	strcat(s, "$"); 
	COPYDATASTRUCT cds = { 0 }; 
	//cds.lpData = CopyData; //要传递给接收应用程序的数据。该成员可以是NULL。  PVOID
	cds.lpData = s; //要传递给接收应用程序的数据。该成员可以是NULL。  PVOID
	cds.cbData = 1024;//lpData成员指向的数据的大小（以字节为单位）  DWORD
	//取得dll所在进程pid：
	DWORD dwProcessId; 
	dwProcessId = GetCurrentProcessId();
	DWORD ret;
	//向杀毒软件发送消息
	
	COPYDATASTRUCT netDataPacket;
	netDataPacket.dwData = 0;
	const wchar_t* aa = L"DDDOOO";
	netDataPacket.cbData = wcslen(aa)+2;//* sizeof(TCHAR);
	netDataPacket.lpData = (PVOID)aa;

// 	const char* strInfo = "abcdef";
// 	netDataPacket.cbData = strlen(strInfo) + 1;
// 	netDataPacket.lpData = &strInfo;

	ret = SendMessage(hExe, WM_COPYDATA, dwProcessId, (LPARAM)&netDataPacket);
	if (ret == 915)
	{
		HookStatus(FALSE);
		b = CreateProcessW(
			lpApplicationName, 
			lpCommandLine, 
			lpProcessAttributes, 
			lpThreadAttributes, 
			bInheritHandles, 
			dwCreationFlags, 
			lpEnvironment, 
			lpCurrentDirectory, 
			lpStartupInfo, 
			lpProcessInformation);
		HookStatus(TRUE);
		printf("     SendMessage       hook       0       \n");
		delete s;
		s = NULL;
		return b;
	} 
	else
	{
		printf("     SendMessage       hook      1        \n");
		delete s;
		s = NULL;
		return FALSE;
	}
	return FALSE;
}

/*进行Hook*/
BOOL HookCreateProcess()
{
	printf("    HookCreateProcess       hook              \n");
	
	/*获取CreateProcessW函数地址*/
	FunAddr = (DWORD)GetProcAddress(LoadLibrary(L"Kernel32.dll"), "CreateProcessW");
	/*保存CreateProcessW函数原始地址*/
	memcpy(OldCode, (void*)FunAddr, 5);
	/*构造汇编跳转指令:*/
	NewCode[0] = 0xE9;
	/*用我们自定义的CreateProcessWCallBack函数取代CreateProcessW函数的地址，*/
	JmpAddr = (ULONG)CreateProcessWCallBack - FunAddr - 5;//计算除我们的函数在GetProcAddress位置的跳转地址
	memcpy(&NewCode[1], &JmpAddr, 4);
	/*启用HOOK*/
	HookStatus(TRUE);
	return TRUE;
}

/*入口函数*/
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	hMod = (HINSTANCE)hModule; 
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) 
	{ hProcess = OpenProcess(
		PROCESS_ALL_ACCESS, 
		0,
		GetCurrentProcessId());//要打开的本地进程的标识符
	 /*获取我们设计的杀毒软件的标题，以便发送消息进行通迅：*/
	    hExe = FindWindow(NULL, L"护宝");
		//DLL被加载时对createprocess函数进行Hook：

		printf("    DllMain       hook       1       \n");
	    HookCreateProcess();
	}
	if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		printf("    DllMain       hook       2       \n");
		HookStatus(FALSE);
	}
	return TRUE;
}

