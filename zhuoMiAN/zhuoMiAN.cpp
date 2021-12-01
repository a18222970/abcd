#include<afxwin.h>
#include <Windows.h>
#include <string>
HINSTANCE hInst;                //当前实例
TCHAR szAppName[] = TEXT("VirtualDesk");      //程序名称
HWND  hwnd;                //主窗体句柄
HDESK hVirtualDesk;             //虚拟桌面句柄
HDESK hCurrent;             //当前桌面句柄
PROCESS_INFORMATION piExplor;           //Explorer进程的PROCESS_INFORMATION结构
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//每次运行首先检测注册表相关项，如果未发现，则设置开机自动运行
void SetStartup(HINSTANCE hInst)
{
	HKEY hKey;
	DWORD DataType = REG_SZ;
	PCSTR data_run = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	long ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR)data_run, 0, KEY_ALL_ACCESS, &hKey);
	if (ret != ERROR_SUCCESS)
	{
		MessageBox(NULL, L"无法打开注册表键", L"Error", 0);
		return;
	}
	CString ProcessName;
	//wchar_t* ProcessName;
	int len = GetModuleFileName(hInst, ProcessName.GetBuffer(256), 256);
	if (len == 0)
	{
		MessageBox(NULL, L"无法获取进程的当前目录", L"Error", 0);
		return;
	}
	ProcessName.ReleaseBuffer(len);
	DWORD direcLen = ProcessName.GetLength() + 1;
	LPBYTE direc = new BYTE[direcLen];
	ZeroMemory(direc, direcLen);
	ret = RegQueryValueEx(hKey, L"VirtualDesk", 0, 0, direc, &direcLen);
	//如果键不存在或者键长度与目前的值长度不匹配则添加新键
	if ((ret != ERROR_SUCCESS) || (direcLen != ProcessName.GetLength() + 1))
	{
	SetValue:
		DWORD KeyLength = ProcessName.GetLength() + 1;
		LPBYTE KeyValue = new BYTE[KeyLength];
		ZeroMemory(KeyValue, KeyLength);
		for (int i = 0; i < ProcessName.GetLength(); i++)
			KeyValue[i] = ProcessName[i];
		KeyValue[ProcessName.GetLength()] = 0;
		ret = RegSetValueEx(hKey, L"VirtualDesk", 0, REG_SZ, KeyValue, KeyLength);
		delete[]KeyValue;
	}
	else
	{
		//如果键的内容与当前值不匹配同样进行更改
		for (int i = 0; i < ProcessName.GetLength(); i++)
		{
			if (direc[i] != ProcessName[i])
				goto SetValue;
		}
	}
	delete[]direc;
	return;
}
//创建explorer进程的函数，如果创建了一个虚拟桌面，那么最好调用该函数

void StartExplorer()
{
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.lpDesktop = (LPWSTR)L"Virtual";
	ZeroMemory(&piExplor, sizeof(piExplor));
	if (!CreateProcess(NULL,                   // No module name (use command line).

		(LPWSTR)L"explorer",                                       // Command line.
		NULL,                       // Process handle not inheritable.
		NULL,                       // Thread handle not inheritable.
		FALSE,                      // Set handle inheritance to FALSE.
		0,                      // No creation flags.
		NULL,                       // Use parent's environment block.
		NULL,                       // Use parent's starting directory.
		&si,                        // Pointer to STARTUPINFO structure.
		&piExplor)                     // Pointer to PROCESS_INFORMATION structure.
		)
	{
		MessageBox(NULL, L"无法初始化Explorer", L"Error", 0);
		ExitProcess(1);
	}
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szAppName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_APPLICATION);
	return RegisterClassEx(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中
	hwnd = CreateWindow(szAppName, TEXT("SunBear"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInst, NULL);
	if (!hwnd)
	{
		return FALSE;
	}
	return TRUE;
}
int Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("SunBear");
	MSG          msg;
	SetStartup(hInstance);
	hVirtualDesk = CreateDesktop(
		(LPWSTR)L"Virtual",
		NULL,
		NULL,
		DF_ALLOWOTHERACCOUNTHOOK,
		GENERIC_ALL,
		NULL);
	hCurrent = GetThreadDesktop(GetCurrentThreadId());
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, iCmdShow))
	{
		return FALSE;
	}
	StartExplorer();            //启动Explorer进程
	if (!RegisterHotKey(hwnd, 0x0001, MOD_ALT, 'Q'))
	{
		//处理切换虚拟桌面
		return TRUE;
	}
	if (!RegisterHotKey(hwnd, 0x0002, 0, VK_F8))
	{
		//处理退出进程
		return TRUE;
	}
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	static HDESK hNow = hCurrent;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		//在关闭虚拟桌面前要切换回当前桌面
		SwitchDesktop(hCurrent);
		PostQuitMessage(0);
		return 0;
	case WM_HOTKEY:
		if (0x0001 == wParam)
		{
			if (hNow == hCurrent)
			{
				SwitchDesktop(hVirtualDesk);
				hNow = hVirtualDesk;
			}
			else
			{
				SwitchDesktop(hCurrent);
				hNow = hCurrent;
			}
		}
		if (0x0002 == wParam)
		{
			//用TerminateProcess终止explorer进程的时候，如果传递第二个参数为1
			//那么操作系统不会在终止后自动唤醒explorer,如果为0,会重新启动
			//explorer
			TerminateProcess(piExplor.hProcess, 1);
			//关闭虚拟桌面
			CloseDesktop(hVirtualDesk);
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

