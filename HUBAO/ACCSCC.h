#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#import "msado15.dll" no_namespace rename("EOF", "adoEOF")
//#import "C:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF","adoEOF")


class ACCSCC
{
protected:
	
	/*
	*
	*����: ��Unicode->ANSI,���ֽ�ת���ֽ�
	* ����1: Unicode�ַ���
	* ����2: char����;
	* ����3: Ҫת���ĳ���
	*/
	BOOL zhuanChar(CString sj, char* shuzu, int len = 60);
public://��
	CString yongHuId[10];//���ݿ��ֶ�id��
	CString yongHuJl[11];//���ݿ��ֶ�JiLu��
	CString jinCheng2[24];
	CString fXjc[10];
	CString bMingDan[1];

	CString mingDanBiao;
	CString jinCheng1Biao;
	CString jinChengBiao;
	CString idBiao;
	CString jiLuBiao;
	CString jinCheng2Biao;
	CString fXjinCheng;
public:
	ACCSCC();
	~ACCSCC();
	//int ci;
	

	
public://���ݿ�����,�ر�
	/*���Ƶ���������ݿ⣬��Ҫ���غܶ��¼������ôӦ��ʹ��ȫ��_ConnectionPtr�ӿڴ���һ�����ݿ�����*/
	_ConnectionPtr m_pConnection; //���Ӷ���ָ��
	_RecordsetPtr  m_pRecordset;  //������¼��ָ��
	_CommandPtr    m_CommandPtr;  //�ýӿڷ���һ����¼��

	/*
	* �������ݿ�
	*/
	BOOL lianJieKaiGuan;//���ݿ��Ƿ�����
	BOOL lianJieAccscc();
	BOOL lianJieAccscc(const char* luJing);

	/*
	* ����: �ر����ݿ�����
	* ע��: ���ڳ�ʼ��COM����õ���AfxOleInit�����ַ�����ʼ��COM����ŵ��������Դ���ͷ�Ҳ���Զ����еģ����Բ��ص�����Դй©�����⡣
	*/
	void guanBiShuJuKu();

public://����
	/*���Ӳ�������*/
	BOOL zengJia(CString biao, CString ziDuan, CString shuJu);

	/*
	*/
	BOOL zegJia(CString biao);
public://�޸�
	/*�޸�����*/
	BOOL xiuGai(CString biao, CString ziDuan, CString shuJu, CString xiuGaiZiDuan, CString zDshuJu);

	/*δ��֤*/
	BOOL xiuGai(CString biao, CString ziDuan, CString shuJu, CString xiuGaiShuJu);
public://ɾ��
	/*ɾ��*/
	BOOL shanChu(CString biao, CString ziDuan, CString shuJu);
	BOOL shanChu(CString biao);
public://��ѯ

	/*
	* 
	* ����: ��ѯָ�������Ƿ��ڱ���ָ���ֶδ���
	* ����1: ��
	* ����2: ���ҵ��ֶ�
	* ����3: ���ҵ�����
	* ����ֵ:�ɹ�����1,ʧ�ܷ���0,���󷵻�3,�����ݵ�����Ҫ���ҵ����ݷ���2;��ѯ���ǿ�ֵ������4
	*/
	unsigned chaXun(CString biao, CString ziDuan, CString shuJu);
	int chaXun(CString biao, CString ziDuan, int shuJu);

	/*
	*
	* ����: ��ѯָ�������Ƿ��ڱ���ָ���ֶδ���
	* ����1: ��
	* ����2: ���ҵ��ֶ�
	* ����3: ���ҵ�����
	* ����ֵ:�ɹ�����TRUE,ʧ�ܷ���FALSE
	*/
	BOOL chaXunBMD(CString biao, CString ziDuan, CString shuJu);

	/*
	*
	* ����: ��ѯָ���ֶ��Ƿ��п�ֵ���ݴ���,һ�������±�
	* ����1: ��
	* ����2: �ֶ�
	* ����ֵ:�����û�����ݷ���FALSE,���ǿ�ֵ����TRUE
	*/
	BOOL chaXunBK(CString biao, CString ziDuan);

	/*
	*
	* ����: ��ѯָ���ֶ��Ƿ��п�ֵ���ݴ���,һ�������±�
	* ����1: ��
	* ����2: �ֶ�
	* ����ֵ:�����û�����ݷ���FALSE,�ǿ�ֵ����TRUE
	*/
	BOOL chaXunK(CString biao, CString ziDuan);

	/*
	*
	* ����: ��ѯָ�������Ƿ��Ϊ��,��Ϊ���м���
	* ����1: ��
	* ����2: �ֶ�
	* ����ֵ:�ɹ����ز鵽������,ʧ�ܷ���0
	*/
	unsigned chaXun(CString biao, CString ziDuan);


	/*
	* ����: getShuJu
	* ����: ��ȡָ���ֶ��µ���������
	* ����1: ��
	* ����2: �ֶ�
	* ����3: ��λ���ֶ�
	* ����4: Ҫ��ȡ���ݵ��ֶ�
	* ����ֵ: һ��2��ָ��,ָ��1����άchar����,wu[][];����wu[0][0]�����Ǽ�¼�����˼���2���ڴ�,��wu[1]��ʼ���Ƿ��ص�ֵ;û�����ݷ��ؿ�ָ��
	* ��Ҫ: �˺������ú���Ҫ�ͷ��ڴ�
	* ��ʽ����;  char** wu;
	        for (int i=0;i<a;i++)//a=wu[0][0]��ֵ;
			{
				delete[] wu[i];
			}
			delete[] wu;
	*/
	char** getShuJu(CString biao, CString ziDuan, CString shuJu, CString muBiaoziDuan);

	/*
	* ����: getShuJu
	* ����: ��ȡa�ֶ��µ�aֵ���ж�Ӧ��b�ֶε�ֵ
	* ����1: ��
	* ����2: ��λa�ֶ�
	* ����3: ��λ��aֵ
	* ����4: Ҫ��ȡ���ݵ��ֶ�
	* ����5: ���շ���ֵ��wchar_t����
	* ����ֵ: BOOL����,�ɹ�����TRUE
	* ע��:�������ж��,�������е�һ��
	*/
	BOOL   getShuJu(CString biao, CString ziDuan, CString shuJu, CString muBiaoziDuan, wchar_t* shuzu);///*δ����������ݵı���*/
	/*δ����������ݵı���*/
	BOOL   getShuJu(CString biao, CString muBiaoziDuan, wchar_t* shuzu);

	/*
	* ����: getShuJu
	* ����: ��ȡa�ֶ��µ�aֵ���ж�Ӧ��b�ֶε�ֵ
	* ����1: ��
	* ����2: ��λa�ֶ�
	* ����3: ��λ��aֵ
	* ����4: Ҫ��ȡ���ݵ�b�ֶ�
	* ����ֵ: ���ػ�ȡ����intֵ
	*/
	unsigned int getShuJuRQ(CString biao, CString ziDuan, CString shuJu, CString muBiaoziDuan);

	/*��ȡ����ģ���б���Ϣ*/
	void bianLiMoKuai();
	/*��ȡ����ģ����ϸ��Ϣ���������̱߳ȶ�,��ɱ������*/
	void bianLiJinCheng(DWORD dwPID);
	/*��ȡ�����б�*/
	BOOL huoQuJinChengLieBiao(CString biao, BOOL s = FALSE);
	BOOL huoQuJinChengLieBiao_lieBiao(CString biao, LPVOID IPtr, BOOL s = FALSE);//����
	wchar_t** huoQuJinChengLieBiao(int** a);

	void quChongAccScc(CString ba, CString bb, CString zda, CString zdb);

	/*���̴߳���*/
	typedef struct jCjingCheng
	{
		DWORD Pid;
		CString exeMing;
		CString exePath;

		char    ming[266];
		char    path[MAX_PATH];//260
   }JC;
public://����
	BOOL shaSiJinCheng(DWORD pid);
	BOOL qiDongJinCheng(CString exePath);


};

DWORD WINAPI jingChengChuLi(void* a);//�鵽��PID��Ĵ����߳�,����߳�Ϊ���ܻ�ͬʱ���еĶ��߳�
DWORD WINAPI sDjingCheng(LPVOID dwPID);
UINT sDjC(LPVOID pParam);