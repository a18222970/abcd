#pragma once
class TCPfuWu
{



public:
	unsigned TCPfaSong(char* json);
	/*
	* ����: zhuanJsonJ
	* ����: ���ַ�ת��Ϊjson��ʽ�ַ���
	* ����1: char�����ָ��
	* ����2: ���߷�������������
	* ����3: ���߷�������������;Ҳ�ǵ�½���˺�
	* ����4: У����,��½������
	* ����5: ָ�����յ����鳤��,Ĭ��600�ֽ�
	* ����ֵ: �ɹ�����TRUE;ʧ�ܷ��� FALSE
	*/
	BOOL zhuanJsonJ(char* shuzu, int leiXing, char* gongNeng, char* jiaoYan, int len=600);

	/*
	* ����: ��json��ʽ�ַ���,תΪC��ʽ�ַ���
	*/
	int zhuanJsonC(char* shuzu, char* gongNeng, char* jiaoYan, int len = 600);

	/*
	* 
	*/
	BOOL shuZuBiJiao(char* a, char* b, int c);



	/*��Ҫ: ʹ�ô˺�������Ҫ�� delete[] ����ָ��  ���ͷ��ڴ�,��Ȼ���ڴ����
	*
	*����: ��Unicode->ANSI,���ֽ�ת���ֽ�
	*/
	char* zhuanChar(CString sj);

	/*
	*
	*����: ��Unicode->ANSI,���ֽ�ת���ֽ�
	* ����1: Unicode�ַ���
	* ����2: char����;
	* ����3: Ҫת���ĳ���
	*/
	BOOL zhuanChar(CString sj, char* shuzu, int len = 60);
};

UINT _cdecl TCPlianjie(LPVOID lpParam);//���߳�
unsigned WINAPI TCPfaSong();
unsigned WINAPI TCPjieShou(void* arg);