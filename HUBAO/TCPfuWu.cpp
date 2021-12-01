#include "pch.h"
#include "TCPfuWu.h"
#include "HUBAO.h"

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

SOCKET hSock;//全局变量

UINT _cdecl TCPlianjie(LPVOID lpParam)
{
	/******************************* 1 **************************/
	//加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	SOCKADDR_IN servAdr;
	HANDLE hRecvThread;
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
	servAdr.sin_addr.S_un.S_addr = inet_addr("192.168.1.12");
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
	//hSendThred = (HANDLE)_beginthreadex(NULL, 0, &TCPfaSong, (void*)&hSock, 0, NULL);//建立新线程发消息
	hRecvThread = (HANDLE)_beginthreadex(NULL, 0, &TCPjieShou, (void*)&hSock, 0, NULL);//建立新线程收消息
	//等待hRecvThread与hSendThred执行完毕
	WaitForSingleObject(hRecvThread, INFINITE);
	//WaitForSingleObject(hSendThred, INFINITE);
	/******************************* 4 **************************/
	//关闭套接字
	closesocket(hSock);
	WSACleanup();
	theApp.tcpFuuWuKaiGuan = TRUE;//打开tcp服务开关
	return 0;
}

unsigned WINAPI TCPfaSong()
{
// 	CSuoPingDlg* spLP;
// 	const char* u = cspLP->json_zuHe();
// 	const char* u = "hhha";
// 	//此时链接的socket的标记hClntSock
// 	char szNameMsg[MAX_BUF_SIZE + NAME_SIZE] = { 0 };//又要有连接的名称,又要有消息
// 	memset(szMsg, 0, MAX_BUF_SIZE);//将消息缓冲区清零
// 	sprintf(szNameMsg, "%s", u);
// 	send(hSock, szNameMsg, strlen(szNameMsg), 0);
 	return 0;
}

unsigned WINAPI TCPjieShou(void* arg)
{

//	CString shuJu;
	//此时链接的socket的标记hClntSock
	TCPfuWu tcp;
	SOCKET hClntSock = *((SOCKET*)arg);//强制转化并取数据
	char szNameMsg[600] = { 0 };//又要又连接的名称,又要有消息
	int iLen = 0;
	while (theApp.tcpFuuWuKaiGuan)//全局变量
	{
		//memset(szNameMsg, 0, MAX_BUF_SIZE + NAME_SIZE);//将消息缓冲区清零
			//阻塞在这一句,等待来自于服务端的消息
		iLen = recv(hClntSock, szNameMsg, sizeof(szNameMsg), 0);
		printf("szNameMsg1 = %s\n", szNameMsg);
		//检测服务端是否断开
		if (iLen == -1)
		{
			return 2;//返回错误值,客户端这里不能是-1
		}
		szNameMsg[iLen + 1] = 0;//要的是字符串,以0结尾
		printf("szNameMsg = %s\n", szNameMsg);
		Value zhi;
		Reader quzhi;
		if (quzhi.parse(szNameMsg, zhi))
		{
			char gongNeng[30];
			char jiaoYan[30];
			int len=0;
			len = tcp.zhuanJsonC(szNameMsg, gongNeng, jiaoYan);
			//CString gN = (CString)gongNeng;
			//AfxMessageBox(gN);
			//CString jY = (CString)jiaoYan;
			//AfxMessageBox(jY);
			/*  *****计算字符串长度**** 开始 */
			short lenth, lenthh;
			for (lenth = 0; gongNeng[lenth]; lenth++)
			{
			}
			lenth = (lenth + 1);//*2s 因为wchar_t是双字节,+1是字符串以0结尾,wchar_t是00结尾
			for (lenthh = 0; jiaoYan[lenthh]; lenthh++)
			{
			}
			lenthh = (lenthh + 1);//*2s 因为wchar_t是双字节,+1是字符串以0结尾,wchar_t是00结尾
			/*  *****计算字符串长度**** 结束 */
			switch (len)
			{
			case 1:
				
				
				if (tcp.shuZuBiJiao(gongNeng, "OK", lenth) && tcp.shuZuBiJiao(jiaoYan, "abcd", lenthh))
				{
					theApp.idYanZhe = TRUE;	
				}
				break;
			case 2:
				if (tcp.shuZuBiJiao(gongNeng, "souQuan", lenth) && tcp.shuZuBiJiao(jiaoYan, "abcd", lenthh))
				{
					theApp.idYanZhe = TRUE;
				}
				break;
			default:
				break;
			}

		}
		else
		{
			char buTongguo[600] = { "buTonggo" };
			char Tongguo[600] = { "Tonggo" };

			printf("不是有效的json\n");

		}
// 		sheZhiL.DLMM = szNameMsg;
// 		sheZhiL.UpdateData(FALSE);
		//fputs(szNameMsg, stdout);//将消息输出到控制台
	}
	return 0;
}

unsigned TCPfuWu::TCPfaSong(char* json)
{
	//const char* u = "hhha";
	//此时链接的socket的标记hClntSock
	char szNameMsg[MAX_BUF_SIZE + NAME_SIZE] = { 0 };//又要有连接的名称,又要有消息
	/*
	* 函数: memset
	* 作用: 将缓冲区设置为指定的字符
	* 参数1: 指向目标的指针  void *dest
	* 参数2: 要设置的字符 int c
	* 参数3: 字符数 size_t count
	*/
	memset(szMsg, 0, MAX_BUF_SIZE);//将消息缓冲区清零

	/*
	* 函数: sprintf
	* 作用: 将设置格式的数据(字符串)写入数组
	* 参数1:输出的存储位置  char *buffer
	* 参数2:格式控件字符串
	* 参数3:要转换的数据(字符串)
	* 返回值:写入的字符数;如果发生错误，则返回 -1;sprintf 返回 参数1 中存储的字节数 ，不包括终止null(\0)字符
	*/
	sprintf(szNameMsg, "%s", json);

	/*
	* 函数: send
	* 作用: 发送TCP数据
	* 参数1:标识已连接套接字的描述符       SOCKET     s
	* 参数2:指向包含要传输的数据的缓冲区的指针。\    const char *buf
	* 参数3:第二参数指向的缓冲区中数据的长度（以字节为单位）  int        len
	* 参数4:一组指定调用方式的标志        int        flags
	* 返回值:如果没有发生错误， send返回发送的总字节数,否则，返回 SOCKET_ERROR 的值,可以通过调用WSAGetLastError检索特定的错误代码
	* 
	* 函数: strlen
	* 作用: 通过使用当前区域设置或指定区域设置获取字符串的长度
	* 参数: const 类的 以 Null 结尾的字符串。
	* 返回值: 返回参数中的字符数 ，不包括0。
	*/
	send(hSock, szNameMsg, strlen(szNameMsg), 0);
	return 0;
}

BOOL TCPfuWu::zhuanJsonJ(char* shuzu, int leiXing, char* gongNeng, char* jiaoYan, int len)
{
	/*建立json字符串1*/
	Json::Value root;//Value能使用的类型 wchar_t*  const char*  char*  std::string
	root["gongNeng"] = gongNeng;
	root["jiaoYan"] = jiaoYan;
	root["leiXing"] = leiXing;
	Json::FastWriter sii;
	std::string sq = sii.write(root);//
	short lenth;
	for (lenth = 0; sq[lenth]; lenth++)
	{
	}
	lenth = (lenth + 1);//*2s 因为wchar_t是双字节,+1是字符串以0结尾,wchar_t是00结尾
	if (len > lenth)
	{
		len = sprintf(shuzu, "%s", sq.c_str());//c_str() 将字符串的内容转换为以 null 结尾的 C 样式字符串。 
		if (len == -1)
		{
			return FALSE;
		}
		shuzu[len + 1] = 0;
		return TRUE;
	}
	return FALSE;
}

int TCPfuWu::zhuanJsonC(char* shuzu, char* gongNeng, char* jiaoYan, int len)
{
	Value zhi;
	Reader quzhi;
	if (quzhi.parse(shuzu, zhi))
	{

		int lei = 0;
		const char* a = NULL;
		const char* m = NULL;
		char* yyy = "woshi2/\n";
		if (zhi.isMember("leiXing"))
		{
			lei = zhi["leiXing"].asInt();
			
			if (zhi.isMember("jiaoYan"))
			{
				m = zhi["jiaoYan"].asCString();
				sprintf(jiaoYan, "%s", m);
				if (zhi.isMember("gongNeng"))
				{
					a = zhi["gongNeng"].asCString();
					sprintf(gongNeng, "%s", a);
					return lei;
				}
			}
		}
	}
	else
	{
		printf("   **********json格式错误***********       \n");
		return 0;
	}
	return 0;
}

BOOL TCPfuWu::shuZuBiJiao(char* a, char* b, int c)
{
	for (int i = 0; i < c-1; i++)
	{
		if (a[i] != b[i])
		{
			printf("    03    \n");
			return FALSE;
		}
	}
	printf("    04    \n");
	return TRUE;
}

char* TCPfuWu::zhuanChar(CString sj)
{
	//int nk;//字符个数
	int len;//字节个数
	char* a = NULL;
	//nk = sj.GetLength();//调用此方法可返回对象中的字符数。 计数不包括 null 终止符。
	/*
	* 函数: WideCharToMultiByte
	* 作用: 将 UTF-16（宽字符）字符串映射到新字符串。新字符串不一定来自多字节字符集。此函数容易造成内存泄漏和转换后的数据丢失
	* 参数1: 用于执行转换的代码页。转换后的格式,CP_ACP=系统默认的 Windows ANSI 代码页
	* 参数2: 指示转换类型的标志。当没有设置这些标志时，该函数执行得更快。
	* 参数3: 指向要转换的 Unicode 字符串的指针。
	* 参数4: 要转换的源字符串的大小（以字符为单位）。或者，如果字符串以空字符结尾，则可以将此参数设置为 -1,为-1时返回的长度包括结束的空字符
	* 参数5: 转换后保存数据的缓冲区(指针)
	* 参数6: 由 参数4 指示的缓冲区的大小（以字节为单位）。如果此参数设置为 0，则该函数返回 参数4 所需的缓冲区大小,此参数为正数时才能转换成功
	* 参数7: 一般设置为NULL
	* 参数8: 可以设置NULL
	* 返回值: 如果成功，则返回写入 参数5 指向的缓冲区的字节数。
	*        如果函数成功并且 参数6 为 0，则返回值是 参数5 指示的缓冲区所需的大小（以字节为单位）
	*/
	len = WideCharToMultiByte(CP_ACP, 0, sj, -1, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的.此步是为了避免内存泄漏
	//std::cout << len << "\n";
	char* ls = new char[len]; //为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小,以字节为单位
	WideCharToMultiByte(CP_ACP, 0, sj, -1, ls, len, NULL, NULL);//宽字节编码转换成多字节编码
	/*捕获错误*/
	if (ERROR_INSUFFICIENT_BUFFER == GetLastError() || ERROR_INVALID_FLAGS == GetLastError() ||
		ERROR_INVALID_PARAMETER == GetLastError() || ERROR_NO_UNICODE_TRANSLATION == GetLastError())
	{
		printf("JSON char* 转换 errorNum = %d\n", GetLastError());
	}
	return ls;
}

BOOL TCPfuWu::zhuanChar(CString sj, char* shuzu, int len)
{
	//int nk;//字符个数
	int ilen;//字节个数
	//nk = sj.GetLength();//调用此方法可返回对象中的字符数。 计数不包括 null 终止符。
	/*
	* 函数: WideCharToMultiByte
	* 作用: 将 UTF-16（宽字符）字符串映射到新字符串。新字符串不一定来自多字节字符集。此函数容易造成内存泄漏和转换后的数据丢失
	* 参数1: 用于执行转换的代码页。转换后的格式,CP_ACP=系统默认的 Windows ANSI 代码页
	* 参数2: 指示转换类型的标志。当没有设置这些标志时，该函数执行得更快。
	* 参数3: 指向要转换的 Unicode 字符串的指针。
	* 参数4: 要转换的源字符串的大小（以字符为单位）。或者，如果字符串以空字符结尾，则可以将此参数设置为 -1,为-1时返回的长度包括结束的空字符
	* 参数5: 转换后保存数据的缓冲区(指针)
	* 参数6: 由 参数4 指示的缓冲区的大小（以字节为单位）。如果此参数设置为 0，则该函数返回 参数4 所需的缓冲区大小,此参数为正数时才能转换成功
	* 参数7: 一般设置为NULL
	* 参数8: 可以设置NULL
	* 返回值: 如果成功，则返回写入 参数5 指向的缓冲区的字节数。
	*        如果函数成功并且 参数6 为 0，则返回值是 参数5 指示的缓冲区所需的大小（以字节为单位）
	*/
	ilen = WideCharToMultiByte(CP_ACP, 0, sj, -1, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的.此步是为了避免内存泄漏
	if (len<ilen)//如果接受数组长度小于要转换的字符串长度,返回FALSE
	{
		return FALSE;
	}
	WideCharToMultiByte(CP_ACP, 0, sj, -1, shuzu, ilen, NULL, NULL);//宽字节编码转换成多字节编码
	/*捕获错误*/
	if (ERROR_INSUFFICIENT_BUFFER == GetLastError() || ERROR_INVALID_FLAGS == GetLastError() ||
		ERROR_INVALID_PARAMETER == GetLastError() || ERROR_NO_UNICODE_TRANSLATION == GetLastError())
	{
		printf("JSON char* 转换 errorNum = %d\n", GetLastError());//获取错误代码
		return FALSE;
	}
	return TRUE;
}
