#include "pch.h"
#include "SuoPingGongJu.h"
#include "SuoPingDlg.h"
#include "SuoPing.h"
/*TCP����*/
#include<WinSock2.h>//��������
#include <wininet.h>//InternetAttemptConnect �������
#pragma comment(lib,"ws2_32.lib") //ʹ��ws2_32.lib��
#pragma comment(lib,"Wininet.lib")
#pragma warning(disable:4996) //����4996����

#include "json/json.h"
using namespace Json;//����Json�����ռ�

#define  NAME_SIZE 256 //
#define  MAX_BUF_SIZE 1024 //
char szName[NAME_SIZE] = "[DEFAULT]";//���ӵĿͻ�������
char szMsg[MAX_BUF_SIZE];//�շ������ݻ�����


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
	TCHAR  FileModule[0x100]{};//����·��������

	/*����:GetModuleFileName
	* ����: ��������ָ��ģ����ļ�����ȫ�޶�·������ģ������ѱ���ǰ���̼��ء�
	* ����1:����������·�����Ѽ���ģ��ľ��������˲���ΪNULL���� GetModuleFileName������ǰ���̵Ŀ�ִ���ļ���·����
	* ����2:ָ�����ģ����ȫ�޶�·���Ļ�������ָ��,���������ȡ����·��
	* ����3:������(����·��)�Ĵ�С,��TCHARs Ϊ��λ��
	*/
	GetModuleFileName(NULL, FileModule, 0x100);

	/*�Ƚ��ַ���*/
	int ii = 0;
	for (int i = 0x100 - 1; FileModule[i] != L'\\'; i--)//�ַ����Ӻ�ǰ�Ƚ�,�����Ϊ'\\'�ͽ�����ֵΪ0,Ϊ'\\'ʱѭ����ֹ
	{
		FileModule[i] = 0;
		ii++;
	}
	//FileModule[0x100 - 1 - ii] = 0;//����б��'\'
	path.Format(L"%s", FileModule);//�����������ݱ��浽wAppPath��
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
	lenth = (lenth + 1) * 2;//*2s ��Ϊwchar_t��˫�ֽ�,+1���ַ�����0��β,wchar_t��00��β
	return lenth;
}

BOOL SuoPingGongJu::lianJieFuWuQiDuan(const char* ip)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(//����һ������ʹ��Winsock DLL
		wVersionRequested, //�����߿���ʹ�õ���߰汾�� Windows Sockets �淶
		&wsaData);//ָ��WSADATA���ݽṹ��ָ�� �����ڽ��� Windows �׽���ʵ�ֵ���ϸ��Ϣ��
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

	//SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//IPV4,TCP����,0 Э�鲻ָ��
	sockSrv = socket(AF_INET, SOCK_STREAM, 0);//IPV4,TCP����,0 Э�鲻ָ��
	if (INVALID_SOCKET == sockSrv)
	{
		//printf("socket errorno = %d/n", GetLastError());//GetLastError()��ȡ�������
		return -1;
	}

	/*����*/
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(ip);
	addrSrv.sin_family = AF_INET;//IPV4
	addrSrv.sin_port = htons(6000);//�˿�

	/*����*/
	if (SOCKET_ERROR == connect(//������ָ��IP������
		sockSrv, //��ʶδ�����׽��ֵ�������
		(SOCKADDR*)&addrSrv, //ָ��Ӧ�������ӵ�sockaddr�ṹ��ָ�� ��
		sizeof(SOCKADDR)))//name����ָ���sockaddr�ṹ�ĳ��ȣ����ֽ�Ϊ��λ����
	{
		//printf("connect errorrno = %d\n", GetLastError());
		return -1;
	}

	/*�շ�*/
	char recvBuf[100] = { 0 };
	iLen = recv(sockSrv, recvBuf, 100, 0);
	return TRUE;
}

void SuoPingGongJu::duanKaiFuWuDuan()
{
	/*�ر�*/
	closesocket(sockSrv);//�ر��׽���
	WSACleanup();//��ֹʹ��Winsock 2 DLL (Ws2_32.dll)
}

int SuoPingGongJu::faSong()
{
	CString ss = L"��ð���ʱ";
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
	int len;//�ֽڸ���
	char* a = NULL;

	/*
	* ����: WideCharToMultiByte
	* ����: �� UTF-16�����ַ����ַ���ӳ�䵽���ַ��������ַ�����һ�����Զ��ֽ��ַ�����
	* ����1: ����ִ��ת���Ĵ���ҳ��ת����ĸ�ʽ,CP_ACP=ϵͳĬ�ϵ� Windows ANSI ����ҳ
	* ����2: ָʾת�����͵ı�־����û��������Щ��־ʱ���ú���ִ�еø��졣
	* ����3: ָ��Ҫת���� Unicode �ַ�����ָ�롣
	* ����4: Ҫת����Դ�ַ����Ĵ�С�����ַ�Ϊ��λ�������ߣ�����ַ����Կ��ַ���β������Խ��˲�������Ϊ -1,Ϊ-1ʱ���صĳ��Ȱ��������Ŀ��ַ�
	* ����5: ת���󱣴����ݵĻ�����(ָ��)
	* ����6: �� ����4 ָʾ�Ļ������Ĵ�С�����ֽ�Ϊ��λ��������˲�������Ϊ 0����ú������� ����4 ����Ļ�������С
	* ����7: һ������ΪNULL
	* ����8: ��������NULL
	* ����ֵ: ����ɹ����򷵻�д�� ����5 ָ��Ļ��������ֽ�����
	*        ��������ɹ����� ����6 Ϊ 0���򷵻�ֵ�� ����5 ָʾ�Ļ���������Ĵ�С�����ֽ�Ϊ��λ��
	*/
	len = WideCharToMultiByte(CP_ACP, 0, k, -1, NULL, 0, NULL, NULL); //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����,�˲���Ϊ�˱����ڴ�й©
	a = new char[len]; //Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ŀ��ֽ��ֽڴ�С,���ֽ�Ϊ��λ
	mbstate_t ad;
	USES_CONVERSION;
	//GetBuffer����ָ�� ������ڲ��ַ��������� CSimpleStringT ָ��. 
	//GetLength �ַ������ַ��ļ���,���� null ��ֹ��
	const wchar_t* pBuf = T2W(k.GetBuffer(k.GetLength()));//��CStringת��Ϊ const wchar_t*
	/*
	* ����: wcsrtombs
	* ����: �����ַ��ַ���ת��Ϊ���ֽ��ַ�����ʾ��ʽ
	* ����1:ת���󱣳ֵĵ�ַ
	* ����2:Ҫת�����ַ���ַ
	* ����3:ת�����ַ�����,��λ�ֽ�
	* ����4: ָ��ת��״̬ mbstate_t �����ָ��
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
	//�����׽��ֿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	SOCKADDR_IN servAdr;
	HANDLE hSendThred, hRecvThread;
	wVersionRequested = MAKEWORD(1, 1);
	//��ʼ��
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
	//���ö˿�
	hSock = socket(PF_INET, SOCK_STREAM, 0);
	servAdr.sin_addr.S_un.S_addr = inet_addr("192.168.1.8");
	servAdr.sin_family = AF_INET;
	servAdr.sin_port = htons(6000);
	/******************************* 2 **************************/
	/******************************* 3 **************************/
	//���ӷ�����
	if (SOCKET_ERROR == connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)))
	{
		printf("connect errorrno = %d\n", GetLastError());
		return -1;
	}
	/******************************* 3 **************************/
	/******************************* 4 **************************/
	hSendThred = (HANDLE)_beginthreadex(NULL, 0, &TCPfaSong, (void*)&hSock, 0, NULL);//�������̷߳���Ϣ
	hRecvThread = (HANDLE)_beginthreadex(NULL, 0, &TCPjieShou, (void*)&hSock, 0, NULL);//�������߳�����Ϣ
	//�ȴ�hRecvThread��hSendThredִ�����
	if (hSendThred > 0)
	{
		WaitForSingleObject(hRecvThread, INFINITE);
	}
	if (hRecvThread > 0)
	{
		WaitForSingleObject(hSendThred, INFINITE);
	}
	/******************************* 4 **************************/
	//�ر��׽���
	closesocket(hSock);
	WSACleanup();
	theApp.tcpKaiGuan = TRUE;//��tcp���񿪹�
	return 0;
}

unsigned WINAPI TCPjieShou(void* arg)
{
	SheZhi sheZhiL;
	CString shuJu;
	//��ʱ���ӵ�socket�ı��hClntSock
	SOCKET hClntSock = *((SOCKET*)arg);//ǿ��ת����ȡ����
	char szNameMsg[MAX_BUF_SIZE + NAME_SIZE] = { 0 };//��Ҫ�����ӵ�����,��Ҫ����Ϣ
	int iLen = 0;
	while (theApp.tcpKaiGuan)//ȫ�ֱ���
	{
		memset(szNameMsg, 0, MAX_BUF_SIZE + NAME_SIZE);//����Ϣ����������
			//��������һ��,�ȴ������ڷ���˵���Ϣ
		iLen = recv(hClntSock, szNameMsg, sizeof(szNameMsg), 0);
		//��������Ƿ�Ͽ�
		if (iLen == -1)
		{
			return 2;//���ش���ֵ,�ͻ������ﲻ����-1
		}
		if (iLen < MAX_BUF_SIZE + NAME_SIZE + 1)
		{
			szNameMsg[iLen] = 0;//Ҫ�����ַ���,��0��β
		}
		sheZhiL.DLMM = szNameMsg;
		sheZhiL.UpdateData(FALSE);
		//fputs(szNameMsg, stdout);//����Ϣ���������̨
	}
}

unsigned WINAPI TCPfaSong(void* arg)
{
	CSuoPingDlg* spLP;
	const char* u = cspLP->json_zuHe();
	//��ʱ���ӵ�socket�ı��hClntSock
	SOCKET hClntSock = *((SOCKET*)arg);//ǿ��ת����ȡ����
	char szNameMsg[MAX_BUF_SIZE + NAME_SIZE] = { 0 };//��Ҫ�����ӵ�����,��Ҫ����Ϣ
	while (theApp.tcpKaiGuan)
	{
		memset(szMsg, 0, MAX_BUF_SIZE);//����Ϣ����������
			//��������һ��,�ȴ�����̨������Ϣ
		fgets(szMsg, MAX_BUF_SIZE, stdin);
		if (!strcmp(szMsg, "Q\n") || !strcmp(szMsg, "q\n"))//����������Q����q���˳�
		{
			closesocket(hClntSock);//�ͻ�������(�Ͽ�����)
			exit(0);//�˳�����
		}
		//ƴ����Ϣ
		//sprintf(szNameMsg, "%s%s", szName, szMsg);
		sprintf(szNameMsg, "%s", u);
		//printf(u);
		//jsonjx();
		//sprintf(szNameMsg, "%s%s", szName, s);
		//������Ϣ
		send(hClntSock, szNameMsg, strlen(szNameMsg), 0);

	}
}




BOOL SuoPingGongJu::tcpfaShuJU(const char* a)
{
	//��ʱ���ӵ�socket�ı��hClntSock
	SOCKET hClntSock = *((SOCKET*)hSock);//ǿ��ת����ȡ����
	char szNameMsg[MAX_BUF_SIZE + NAME_SIZE] = { 0 };//��Ҫ�����ӵ�����,��Ҫ����Ϣ
	sprintf(szNameMsg, "%s", a);
	//������Ϣ
	int zijie = send(hClntSock, szNameMsg, strlen(szNameMsg), 0);
	if (zijie<=0)
	{
		return FALSE;
	}
	return TRUE;
}

const char* SuoPingGongJu::json_shengCheng(const char* zhiLing, const char* jiaoYan, int leiXing)
{
	/*����json�ַ���1*/
	Json::Value root;
	root["id"] = zhiLing;
	root["mima"] = jiaoYan;
	root["gongneng"] = leiXing;
	Json::FastWriter sii;
	std::string sq = sii.write(root);
	const char* a = sq.c_str();
	return a;
}