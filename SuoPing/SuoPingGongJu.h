#pragma once
#if _SUO_PING_GONGGONG_
#define _SUO_PING_GONGGONG_
#else



class SuoPingGongJu
{
private://��ȫ˽�еģ��е�ǰ���еĳ�Ա�ܷ��ʵ���

protected://���ܱ����ģ�ֻ�е�ǰ��ĳ�Ա��̳и��������ܷ���

	//WORD wVersionRequested;
	//WSADATA wsaData;
	SOCKET sockSrv;
	int iLen;

	/*
	* ����: wangLuoJianCe
	* ����: ��������Ƿ���ͨ,���ֻ�Ǽ�������Ƿ�������
	* ����ֵ: FALSE �޷�����,TRUE ��������
	*/
	BOOL wangLuoJianCe();
public://���߳�
	CWinThread* pThread;
	
public://����
	SuoPingGongJu();
	/*
	* ����: huoQuLuJing
	* ����: ��ȡ����������ļ���
	* ����: ���ڱ���ȡ�õ�·��
	*/
	void huoQuLuJing(CString path);

	/*
	* 
	* ����: 
	* ����: ��
	*/
	void xianShiKongJian(CDialogEx a);


	/*
	* ����: ziFuChuanChangDu
	* ����: ����Unicode����(���ַ���,1���ַ�ռ2���ֽ�)�ַ����ĳ���,������β��00
	* ����: ��CString���Ͷ�����ַ���, CString a =L"husdhdkd";
	*/
	int ziFuChuanChangDu(const wchar_t* a);

	/*
	* ����: ���ӷ�������
	*/
	BOOL lianJieFuWuQiDuan(const char* ip);

	/*
	* ����: �Ͽ���TCP������������
	*/
	void duanKaiFuWuDuan();

	/*
	* ����: ��TCP������������Ϣ
	*/
	int faSong();

	/* ziFuZhuanHuan_K_A
	* ����: Unicode��CStringת��Ϊchar *
	* ����: CString�����ַ���
	* ����ֵ: �¿��ٵĶ�̬�ڴ�ָ���ַ
	* ע��: ʹ�ô˺�������Ҫ�� delete[] ����ָ��  ���ͷ��ڴ�,��Ȼ���ڴ����
	*/
	char* ziFuZhuanHuan_K_A(CString k);

	/*
	* ����:
	* ����: ���ַ���ת��Ϊjson��ʽ
	* ����1: const char*�����ַ���,����Ϊ���Ʒ�������ָ��
	* ����2: const char*�����ַ���,����Ϊ���Ʒ�������ָ���У����
	* ����3: int����,����Ϊ���Ʒ�����Ҫ�����ķ���,������֤��½����1,
	* ����ֵ: ת�����json��ʽ���ַ���
	*/
	const char* json_shengCheng(const char* zhiLing, const char* jiaoYan, int leiXing);

	BOOL tcpfaShuJU(const char* a);








};

//extern BOOL duoXianChenQiTing;//���߳���ͣ����
UINT _cdecl ThreadFunc_aa(LPVOID lpParam);//���߳�
UINT _cdecl TCPlianjie(LPVOID lpParam);//���߳�
unsigned WINAPI TCPjieShou(void* arg);//���߳�
unsigned WINAPI TCPfaSong(void* arg);//���߳�
#endif