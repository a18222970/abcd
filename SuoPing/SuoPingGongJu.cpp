#include "pch.h"
#include "SuoPingGongJu.h"
#include "SuoPingDlg.h"
#include "SuoPing.h"
/*TCP服务*/
#include<WinSock2.h>//网咯连接
#include <wininet.h>//InternetAttemptConnect 检测网络
#pragma comment(lib,"ws2_32.lib") //使用ws2_32.lib库
#pragma comment(lib,"Wininet.lib")
#pragma warning(disable:4996) //屏蔽4996错误

#include "json/json.h"
using namespace Json;//声明Json命名空间

#define  NAME_SIZE 256 //
#define  MAX_BUF_SIZE 1024 //
char szName[NAME_SIZE] = "[DEFAULT]";//连接的客户端名字
char szMsg[MAX_BUF_SIZE];//收发的数据缓冲区


BOOL SuoPingGongJu::wangLuoJianCe()
{
	TCHAR tszDebugMsg[100] = { 0 };


	DWORD dwres = InternetAttemptConnect(0);


	if (dwres != ERROR_SUCCESS)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
	//OutputDebugString(tszDebugMsg);
	return FALSE;
}

SuoPingGongJu::SuoPingGongJu()
{
	//duoXianChenQiTing = FALSE;
}

void SuoPingGongJu::huoQuLuJing(CString path)
{
	TCHAR  FileModule[0x100]{};//保存路径缓冲区

	/*函数:GetModuleFileName
	* 作用: 检索包含指定模块的文件的完全限定路径。该模块必须已被当前进程加载。
	* 参数1:正在请求其路径的已加载模块的句柄。如果此参数为NULL，则 GetModuleFileName检索当前进程的可执行文件的路径。
	* 参数2:指向接收模块完全限定路径的缓冲区的指针,用来保存获取到的路径
	* 参数3:缓冲区(保存路径)的大小,以TCHARs 为单位。
	*/
	GetModuleFileName(NULL, FileModule, 0x100);

	/*比较字符串*/
	int ii = 0;
	for (int i = 0x100 - 1; FileModule[i] != L'\\'; i--)//字符串从后到前比较,如果不为'\\'就将它赋值为0,为'\\'时循环终止
	{
		FileModule[i] = 0;
		ii++;
	}
	//FileModule[0x100 - 1 - ii] = 0;//消除斜杠'\'
	path.Format(L"%s", FileModule);//将缓冲区数据保存到wAppPath里
}

void SuoPingGongJu::xianShiKongJian(CDialogEx a)
{
	
// 	a.GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);
// 	a.GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);
// 	a.GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
// 	a.GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
// 	a.GetDlgItem(IDOK2)->ShowWindow(SW_SHOW);
}

int SuoPingGongJu::ziFuChuanChangDu(const wchar_t* a)
{
	short lenth;
	for (lenth = 0; a[lenth]; lenth++)
	{
	}
	lenth = (lenth + 1) * 2;//*2s 因为wchar_t是双字节,+1是字符串以0结尾,wchar_t是00结尾
	return lenth;
}

BOOL SuoPingGongJu::lianJieFuWuQiDuan(const char* ip)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(//启动一个进程使用Winsock DLL
		wVersionRequested, //调用者可以使用的最高版本的 Windows Sockets 规范
		&wsaData);//指向WSADATA数据结构的指针 ，用于接收 Windows 套接字实现的详细信息。
	if (err != 0)
	{
		//printf("WSAStartup errorNum = %d\n", GetLastError());
		return err;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		//printf("LOBYTE errorNum = %d\n", GetLastError());
		WSACleanup();
		return -1;
	}

	//SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//IPV4,TCP连接,0 协议不指定
	sockSrv = socket(AF_INET, SOCK_STREAM, 0);//IPV4,TCP连接,0 协议不指定
	if (INVALID_SOCKET == sockSrv)
	{
		//printf("socket errorno = %d/n", GetLastError());//GetLastError()获取错误代码
		return -1;
	}

	/*配置*/
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(ip);
	addrSrv.sin_family = AF_INET;//IPV4
	addrSrv.sin_port = htons(6000);//端口

	/*连接*/
	if (SOCKET_ERROR == connect(//建立到指定IP的连接
		sockSrv, //标识未连接套接字的描述符
		(SOCKADDR*)&addrSrv, //指向应建立连接的sockaddr结构的指针 。
		sizeof(SOCKADDR)))//name参数指向的sockaddr结构的长度（以字节为单位）。
	{
		//printf("connect errorrno = %d\n", GetLastError());
		return -1;
	}

	/*收发*/
	char recvBuf[100] = { 0 };
	iLen = recv(sockSrv, recvBuf, 100, 0);
	return TRUE;
}

void SuoPingGongJu::duanKaiFuWuDuan()
{
	/*关闭*/
	closesocket(sockSrv);//关闭套接字
	WSACleanup();//终止使用Winsock 2 DLL (Ws2_32.dll)
}

int SuoPingGongJu::faSong()
{
	CString ss = L"你好爱爱时";
	char* sd = NULL;
	//ziFuZhuanHuan_K_A(ss, sd);
	int iSize;
	iSize = WideCharToMultiByte(CP_ACP, 0, ss, -1, NULL, 0, NULL, NULL);
	sd = (char*)malloc(iSize * sizeof(char));
	WideCharToMultiByte(CP_ACP, 0, ss, -1, sd, iSize, NULL, NULL);

	char sendBuf[100] = "heolw";
	iLen = send(sockSrv, sd, 100, MSG_OOB);
	return 1;
}

char* SuoPingGongJu::ziFuZhuanHuan_K_A(CString k)
{
	int len;//字节个数
	char* a = NULL;

	/*
	* 函数: WideCharToMultiByte
	* 作用: 将 UTF-16（宽字符）字符串映射到新字符串。新字符串不一定来自多字节字符集。
	* 参数1: 用于执行转换的代码页。转换后的格式,CP_ACP=系统默认的 Windows ANSI 代码页
	* 参数2: 指示转换类型的标志。当没有设置这些标志时，该函数执行得更快。
	* 参数3: 指向要转换的 Unicode 字符串的指针。
	* 参数4: 要转换的源字符串的大小（以字符为单位）。或者，如果字符串以空字符结尾，则可以将此参数设置为 -1,为-1时返回的长度包括结束的空字符
	* 参数5: 转换后保存数据的缓冲区(指针)
	* 参数6: 由 参数4 指示的缓冲区的大小（以字节为单位）。如果此参数设置为 0，则该函数返回 参数4 所需的缓冲区大小
	* 参数7: 一般设置为NULL
	* 参数8: 可以设置NULL
	* 返回值: 如果成功，则返回写入 参数5 指向的缓冲区的字节数。
	*        如果函数成功并且 参数6 为 0，则返回值是 参数5 指示的缓冲区所需的大小（以字节为单位）
	*/
	len = WideCharToMultiByte(CP_ACP, 0, k, -1, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的,此步是为了避免内存泄漏
	a = new char[len]; //为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小,以字节为单位
	mbstate_t ad;
	USES_CONVERSION;
	//GetBuffer返回指向 对象的内部字符缓冲区的 CSimpleStringT 指针. 
	//GetLength 字符串中字符的计数,包括 null 终止符
	const wchar_t* pBuf = T2W(k.GetBuffer(k.GetLength()));//将CString转换为 const wchar_t*
	/*
	* 函数: wcsrtombs
	* 作用: 将宽字符字符串转换为多字节字符串表示形式
	* 参数1:转换后保持的地址
	* 参数2:要转换的字符地址
	* 参数3:转换的字符长度,单位字节
	* 参数4: 指向转换状态 mbstate_t 对象的指针
	*/
	wcsrtombs(a, &pBuf, len + 1, &ad);
	return a;
	 
}






UINT _cdecl ThreadFunc_aa(LPVOID lpParam)
{

	char bufRecv[0x100] = { 0 };
	
	

	return 0;
}

SOCKET hSock;
UINT _cdecl TCPlianjie(LPVOID lpParam)
{
	/******************************* 1 **************************/
	//加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	SOCKADDR_IN servAdr;
	HANDLE hSendThred, hRecvThread;
	wVersionRequested = MAKEWORD(1, 1);
	//初始化
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return err;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return -1;
	}
	/******************************* 1 **************************/
	/******************************* 2 **************************/
	//配置端口
	hSock = socket(PF_INET, SOCK_STREAM, 0);
	servAdr.sin_addr.S_un.S_addr = inet_addr("192.168.1.8");
	servAdr.sin_family = AF_INET;
	servAdr.sin_port = htons(6000);
	/******************************* 2 **************************/
	/******************************* 3 **************************/
	//连接服务器
	if (SOCKET_ERROR == connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)))
	{
		printf("connect errorrno = %d\n", GetLastError());
		return -1;
	}
	/******************************* 3 **************************/
	/******************************* 4 **************************/
	hSendThred = (HANDLE)_beginthreadex(NULL, 0, &TCPfaSong, (void*)&hSock, 0, NULL);//建立新线程发消息
	hRecvThread = (HANDLE)_beginthreadex(NULL, 0, &TCPjieShou, (void*)&hSock, 0, NULL);//建立新线程收消息
	//等待hRecvThread与hSendThred执行完毕
	if (hSendThred > 0)
	{
		WaitForSingleObject(hRecvThread, INFINITE);
	}
	if (hRecvThread > 0)
	{
		WaitForSingleObject(hSendThred, INFINITE);
	}
	/******************************* 4 **************************/
	//关闭套接字
	closesocket(hSock);
	WSACleanup();
	theApp.tcpKaiGuan = TRUE;//打开tcp服务开关
	return 0;
}

unsigned WINAPI TCPjieShou(void* arg)
{
	SheZhi sheZhiL;
	CString shuJu;
	//此时链接的socket的标记hClntSock
	SOCKET hClntSock = *((SOCKET*)arg);//强制转化并取数据
	char szNameMsg[MAX_BUF_SIZE + NAME_SIZE] = { 0 };//又要又连接的名称,又要有消息
	int iLen = 0;
	while (theApp.tcpKaiGuan)//全局变量
	{
		memset(szNameMsg, 0, MAX_BUF_SIZE + NAME_SIZE);//将消息缓冲区清零
			//阻塞在这一句,等待来自于服务端的消息
		iLen = recv(hClntSock, szNameMsg, sizeof(szNameMsg), 0);
		//检测服务端是否断开
		if (iLen == -1)
		{
			return 2;//返回错误值,客户端这里不能是-1
		}
		if (iLen < MAX_BUF_SIZE + NAME_SIZE + 1)
		{
			szNameMsg[iLen] = 0;//要的是字符串,以0结尾
		}
		sheZhiL.DLMM = szNameMsg;
		sheZhiL.UpdateData(FALSE);
		//fputs(szNameMsg, stdout);//将消息输出到控制台
	}
}

unsigned WINAPI TCPfaSong(void* arg)
{
	CSuoPingDlg* spLP;
	const char* u = cspLP->json_zuHe();
	//此时链接的socket的标记hClntSock
	SOCKET hClntSock = *((SOCKET*)arg);//强制转化并取数据
	char szNameMsg[MAX_BUF_SIZE + NAME_SIZE] = { 0 };//又要有连接的名称,又要有消息
	while (theApp.tcpKaiGuan)
	{
		memset(szMsg, 0, MAX_BUF_SIZE);//将消息缓冲区清零
			//阻塞在这一句,等待控制台输入消息
		fgets(szMsg, MAX_BUF_SIZE, stdin);
		if (!strcmp(szMsg, "Q\n") || !strcmp(szMsg, "q\n"))//如果输入的是Q或者q就退出
		{
			closesocket(hClntSock);//客户端下线(断开连接)
			exit(0);//退出程序
		}
		//拼包消息
		//sprintf(szNameMsg, "%s%s", szName, szMsg);
		sprintf(szNameMsg, "%s", u);
		//printf(u);
		//jsonjx();
		//sprintf(szNameMsg, "%s%s", szName, s);
		//发送消息
		send(hClntSock, szNameMsg, strlen(szNameMsg), 0);

	}
}




BOOL SuoPingGongJu::tcpfaShuJU(const char* a)
{
	//此时链接的socket的标记hClntSock
	SOCKET hClntSock = *((SOCKET*)hSock);//强制转化并取数据
	char szNameMsg[MAX_BUF_SIZE + NAME_SIZE] = { 0 };//又要有连接的名称,又要有消息
	sprintf(szNameMsg, "%s", a);
	//发送消息
	int zijie = send(hClntSock, szNameMsg, strlen(szNameMsg), 0);
	if (zijie<=0)
	{
		return FALSE;
	}
	return TRUE;
}

const char* SuoPingGongJu::json_shengCheng(const char* zhiLing, const char* jiaoYan, int leiXing)
{
	/*建立json字符串1*/
	Json::Value root;
	root["id"] = zhiLing;
	root["mima"] = jiaoYan;
	root["gongneng"] = leiXing;
	Json::FastWriter sii;
	std::string sq = sii.write(root);
	const char* a = sq.c_str();
	return a;
}