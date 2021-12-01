#include "pch.h"
#include "TCPfuWu.h"
#include "HUBAO.h"

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

SOCKET hSock;//ȫ�ֱ���

UINT _cdecl TCPlianjie(LPVOID lpParam)
{
	/******************************* 1 **************************/
	//�����׽��ֿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	SOCKADDR_IN servAdr;
	HANDLE hRecvThread;
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
	servAdr.sin_addr.S_un.S_addr = inet_addr("192.168.1.12");
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
	//hSendThred = (HANDLE)_beginthreadex(NULL, 0, &TCPfaSong, (void*)&hSock, 0, NULL);//�������̷߳���Ϣ
	hRecvThread = (HANDLE)_beginthreadex(NULL, 0, &TCPjieShou, (void*)&hSock, 0, NULL);//�������߳�����Ϣ
	//�ȴ�hRecvThread��hSendThredִ�����
	WaitForSingleObject(hRecvThread, INFINITE);
	//WaitForSingleObject(hSendThred, INFINITE);
	/******************************* 4 **************************/
	//�ر��׽���
	closesocket(hSock);
	WSACleanup();
	theApp.tcpFuuWuKaiGuan = TRUE;//��tcp���񿪹�
	return 0;
}

unsigned WINAPI TCPfaSong()
{
// 	CSuoPingDlg* spLP;
// 	const char* u = cspLP->json_zuHe();
// 	const char* u = "hhha";
// 	//��ʱ���ӵ�socket�ı��hClntSock
// 	char szNameMsg[MAX_BUF_SIZE + NAME_SIZE] = { 0 };//��Ҫ�����ӵ�����,��Ҫ����Ϣ
// 	memset(szMsg, 0, MAX_BUF_SIZE);//����Ϣ����������
// 	sprintf(szNameMsg, "%s", u);
// 	send(hSock, szNameMsg, strlen(szNameMsg), 0);
 	return 0;
}

unsigned WINAPI TCPjieShou(void* arg)
{

//	CString shuJu;
	//��ʱ���ӵ�socket�ı��hClntSock
	TCPfuWu tcp;
	SOCKET hClntSock = *((SOCKET*)arg);//ǿ��ת����ȡ����
	char szNameMsg[600] = { 0 };//��Ҫ�����ӵ�����,��Ҫ����Ϣ
	int iLen = 0;
	while (theApp.tcpFuuWuKaiGuan)//ȫ�ֱ���
	{
		//memset(szNameMsg, 0, MAX_BUF_SIZE + NAME_SIZE);//����Ϣ����������
			//��������һ��,�ȴ������ڷ���˵���Ϣ
		iLen = recv(hClntSock, szNameMsg, sizeof(szNameMsg), 0);
		printf("szNameMsg1 = %s\n", szNameMsg);
		//��������Ƿ�Ͽ�
		if (iLen == -1)
		{
			return 2;//���ش���ֵ,�ͻ������ﲻ����-1
		}
		szNameMsg[iLen + 1] = 0;//Ҫ�����ַ���,��0��β
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
			/*  *****�����ַ�������**** ��ʼ */
			short lenth, lenthh;
			for (lenth = 0; gongNeng[lenth]; lenth++)
			{
			}
			lenth = (lenth + 1);//*2s ��Ϊwchar_t��˫�ֽ�,+1���ַ�����0��β,wchar_t��00��β
			for (lenthh = 0; jiaoYan[lenthh]; lenthh++)
			{
			}
			lenthh = (lenthh + 1);//*2s ��Ϊwchar_t��˫�ֽ�,+1���ַ�����0��β,wchar_t��00��β
			/*  *****�����ַ�������**** ���� */
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

			printf("������Ч��json\n");

		}
// 		sheZhiL.DLMM = szNameMsg;
// 		sheZhiL.UpdateData(FALSE);
		//fputs(szNameMsg, stdout);//����Ϣ���������̨
	}
	return 0;
}

unsigned TCPfuWu::TCPfaSong(char* json)
{
	//const char* u = "hhha";
	//��ʱ���ӵ�socket�ı��hClntSock
	char szNameMsg[MAX_BUF_SIZE + NAME_SIZE] = { 0 };//��Ҫ�����ӵ�����,��Ҫ����Ϣ
	/*
	* ����: memset
	* ����: ������������Ϊָ�����ַ�
	* ����1: ָ��Ŀ���ָ��  void *dest
	* ����2: Ҫ���õ��ַ� int c
	* ����3: �ַ��� size_t count
	*/
	memset(szMsg, 0, MAX_BUF_SIZE);//����Ϣ����������

	/*
	* ����: sprintf
	* ����: �����ø�ʽ������(�ַ���)д������
	* ����1:����Ĵ洢λ��  char *buffer
	* ����2:��ʽ�ؼ��ַ���
	* ����3:Ҫת��������(�ַ���)
	* ����ֵ:д����ַ���;������������򷵻� -1;sprintf ���� ����1 �д洢���ֽ��� ����������ֹnull(\0)�ַ�
	*/
	sprintf(szNameMsg, "%s", json);

	/*
	* ����: send
	* ����: ����TCP����
	* ����1:��ʶ�������׽��ֵ�������       SOCKET     s
	* ����2:ָ�����Ҫ��������ݵĻ�������ָ�롣\    const char *buf
	* ����3:�ڶ�����ָ��Ļ����������ݵĳ��ȣ����ֽ�Ϊ��λ��  int        len
	* ����4:һ��ָ�����÷�ʽ�ı�־        int        flags
	* ����ֵ:���û�з������� send���ط��͵����ֽ���,���򣬷��� SOCKET_ERROR ��ֵ,����ͨ������WSAGetLastError�����ض��Ĵ������
	* 
	* ����: strlen
	* ����: ͨ��ʹ�õ�ǰ�������û�ָ���������û�ȡ�ַ����ĳ���
	* ����: const ��� �� Null ��β���ַ�����
	* ����ֵ: ���ز����е��ַ��� ��������0��
	*/
	send(hSock, szNameMsg, strlen(szNameMsg), 0);
	return 0;
}

BOOL TCPfuWu::zhuanJsonJ(char* shuzu, int leiXing, char* gongNeng, char* jiaoYan, int len)
{
	/*����json�ַ���1*/
	Json::Value root;//Value��ʹ�õ����� wchar_t*  const char*  char*  std::string
	root["gongNeng"] = gongNeng;
	root["jiaoYan"] = jiaoYan;
	root["leiXing"] = leiXing;
	Json::FastWriter sii;
	std::string sq = sii.write(root);//
	short lenth;
	for (lenth = 0; sq[lenth]; lenth++)
	{
	}
	lenth = (lenth + 1);//*2s ��Ϊwchar_t��˫�ֽ�,+1���ַ�����0��β,wchar_t��00��β
	if (len > lenth)
	{
		len = sprintf(shuzu, "%s", sq.c_str());//c_str() ���ַ���������ת��Ϊ�� null ��β�� C ��ʽ�ַ����� 
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
		printf("   **********json��ʽ����***********       \n");
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
	//int nk;//�ַ�����
	int len;//�ֽڸ���
	char* a = NULL;
	//nk = sj.GetLength();//���ô˷����ɷ��ض����е��ַ����� ���������� null ��ֹ����
	/*
	* ����: WideCharToMultiByte
	* ����: �� UTF-16�����ַ����ַ���ӳ�䵽���ַ��������ַ�����һ�����Զ��ֽ��ַ������˺�����������ڴ�й©��ת��������ݶ�ʧ
	* ����1: ����ִ��ת���Ĵ���ҳ��ת����ĸ�ʽ,CP_ACP=ϵͳĬ�ϵ� Windows ANSI ����ҳ
	* ����2: ָʾת�����͵ı�־����û��������Щ��־ʱ���ú���ִ�еø��졣
	* ����3: ָ��Ҫת���� Unicode �ַ�����ָ�롣
	* ����4: Ҫת����Դ�ַ����Ĵ�С�����ַ�Ϊ��λ�������ߣ�����ַ����Կ��ַ���β������Խ��˲�������Ϊ -1,Ϊ-1ʱ���صĳ��Ȱ��������Ŀ��ַ�
	* ����5: ת���󱣴����ݵĻ�����(ָ��)
	* ����6: �� ����4 ָʾ�Ļ������Ĵ�С�����ֽ�Ϊ��λ��������˲�������Ϊ 0����ú������� ����4 ����Ļ�������С,�˲���Ϊ����ʱ����ת���ɹ�
	* ����7: һ������ΪNULL
	* ����8: ��������NULL
	* ����ֵ: ����ɹ����򷵻�д�� ����5 ָ��Ļ��������ֽ�����
	*        ��������ɹ����� ����6 Ϊ 0���򷵻�ֵ�� ����5 ָʾ�Ļ���������Ĵ�С�����ֽ�Ϊ��λ��
	*/
	len = WideCharToMultiByte(CP_ACP, 0, sj, -1, NULL, 0, NULL, NULL); //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����.�˲���Ϊ�˱����ڴ�й©
	//std::cout << len << "\n";
	char* ls = new char[len]; //Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ŀ��ֽ��ֽڴ�С,���ֽ�Ϊ��λ
	WideCharToMultiByte(CP_ACP, 0, sj, -1, ls, len, NULL, NULL);//���ֽڱ���ת���ɶ��ֽڱ���
	/*�������*/
	if (ERROR_INSUFFICIENT_BUFFER == GetLastError() || ERROR_INVALID_FLAGS == GetLastError() ||
		ERROR_INVALID_PARAMETER == GetLastError() || ERROR_NO_UNICODE_TRANSLATION == GetLastError())
	{
		printf("JSON char* ת�� errorNum = %d\n", GetLastError());
	}
	return ls;
}

BOOL TCPfuWu::zhuanChar(CString sj, char* shuzu, int len)
{
	//int nk;//�ַ�����
	int ilen;//�ֽڸ���
	//nk = sj.GetLength();//���ô˷����ɷ��ض����е��ַ����� ���������� null ��ֹ����
	/*
	* ����: WideCharToMultiByte
	* ����: �� UTF-16�����ַ����ַ���ӳ�䵽���ַ��������ַ�����һ�����Զ��ֽ��ַ������˺�����������ڴ�й©��ת��������ݶ�ʧ
	* ����1: ����ִ��ת���Ĵ���ҳ��ת����ĸ�ʽ,CP_ACP=ϵͳĬ�ϵ� Windows ANSI ����ҳ
	* ����2: ָʾת�����͵ı�־����û��������Щ��־ʱ���ú���ִ�еø��졣
	* ����3: ָ��Ҫת���� Unicode �ַ�����ָ�롣
	* ����4: Ҫת����Դ�ַ����Ĵ�С�����ַ�Ϊ��λ�������ߣ�����ַ����Կ��ַ���β������Խ��˲�������Ϊ -1,Ϊ-1ʱ���صĳ��Ȱ��������Ŀ��ַ�
	* ����5: ת���󱣴����ݵĻ�����(ָ��)
	* ����6: �� ����4 ָʾ�Ļ������Ĵ�С�����ֽ�Ϊ��λ��������˲�������Ϊ 0����ú������� ����4 ����Ļ�������С,�˲���Ϊ����ʱ����ת���ɹ�
	* ����7: һ������ΪNULL
	* ����8: ��������NULL
	* ����ֵ: ����ɹ����򷵻�д�� ����5 ָ��Ļ��������ֽ�����
	*        ��������ɹ����� ����6 Ϊ 0���򷵻�ֵ�� ����5 ָʾ�Ļ���������Ĵ�С�����ֽ�Ϊ��λ��
	*/
	ilen = WideCharToMultiByte(CP_ACP, 0, sj, -1, NULL, 0, NULL, NULL); //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����.�˲���Ϊ�˱����ڴ�й©
	if (len<ilen)//����������鳤��С��Ҫת�����ַ�������,����FALSE
	{
		return FALSE;
	}
	WideCharToMultiByte(CP_ACP, 0, sj, -1, shuzu, ilen, NULL, NULL);//���ֽڱ���ת���ɶ��ֽڱ���
	/*�������*/
	if (ERROR_INSUFFICIENT_BUFFER == GetLastError() || ERROR_INVALID_FLAGS == GetLastError() ||
		ERROR_INVALID_PARAMETER == GetLastError() || ERROR_NO_UNICODE_TRANSLATION == GetLastError())
	{
		printf("JSON char* ת�� errorNum = %d\n", GetLastError());//��ȡ�������
		return FALSE;
	}
	return TRUE;
}
