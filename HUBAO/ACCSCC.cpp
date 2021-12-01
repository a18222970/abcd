#include "pch.h"
#include "ACCSCC.h"

#include <TlHelp32.h>//��ȡ�����б�
#include "HUBAO.h";
#include "SheZhi.h"
BOOL ACCSCC::zhuanChar(CString sj, char* shuzu, int len)
{
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
	if (len < ilen)//����������鳤��С��Ҫת�����ַ�������,����FALSE
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

ACCSCC::ACCSCC()
{
	
	lianJieKaiGuan = FALSE;

	/*accscc���ݿ�*/
	yongHuId[0] = _T("zhangHao");//�˺�
	yongHuId[1] = _T("miMa");//����
	yongHuId[2] = _T("leiXing");//����
	yongHuId[3] = _T("suiJiMa1");//У����
	yongHuId[4] = _T("suiJiMa2");//�������
	yongHuId[5] = _T("dengLuBiaoJi");//��½���
	yongHuId[6] = _T("daoQiShiJian");//����ʱ��
	yongHuId[7] = _T("dingShi");//int
	yongHuId[8] = _T("beiYong");// 0/1
	yongHuId[9] = _T("xuHao");// ���


	yongHuJl[0] = _T("xuHao");  //��¼��� Int
	yongHuJl[1] = _T("zhangHao");//�˺�
	yongHuJl[2] = _T("yunJieCiShu");//Խ��ִ�г���Ĵ���
	yongHuJl[3] = _T("yueJieZhiXing");//Խ��ִ�еĳ�������
	yongHuJl[4] = _T("yueJieZhiXing");//Խ��ִ�еĳ���·��
	yongHuJl[5] = _T("yueJieShiJian"); //Խ��ִ�г����ʱ��
	yongHuJl[6] = _T("qiDongShiJian");//�������ʱ��
	yongHuJl[7] = _T("sheDingShiJian");//�趨����ʱ��
	yongHuJl[8] = _T("beiYong");//int
	yongHuJl[9] = _T("dingShiShiJian");//��ʱִ�������Ŀ�ʼʱ��
	yongHuJl[10] = _T("yunXunShiJian");// ����������ʱ��

	//�����ı�,����������������
	jinCheng2[0] = _T("xuHao");  //���
	jinCheng2[1] = _T("th32ProcessID");  //���̱�ʶ��
	jinCheng2[2] = _T("cntThreads");  //����������ִ���߳���
	jinCheng2[3] = _T("th32ParentProcessID");  //�����˽��̵Ľ��̵ı�ʶ�����丸���̣�
	jinCheng2[4] = _T("pcPriClassBase");  //�˽��̴������κ��̵߳Ļ������ȼ�
	jinCheng2[5] = _T("szExeFile");  //���̵Ŀ�ִ���ļ�������
	jinCheng2[6] = _T("modth32ProcessID");  //Module32First����,Ҫ�����ģ��Ľ��̵ı�ʶ��
	jinCheng2[7] = _T("modBaseAddr");  //ӵ�н�����������ģ��Ļ���ַ
	jinCheng2[8] = _T("modBaseSize");  //ģ��Ĵ�С�����ֽ�Ϊ��λ
	jinCheng2[9] = _T("hModule");  //ӵ�н�����������ģ��ľ��
	jinCheng2[10] = _T("szModule");  //ģ������; ���ı�
	jinCheng2[11] = _T("modszExePath");  //ģ��·��; ���ı�
	jinCheng2[12] = _T("bxuHao");  //���
	jinCheng2[13] = _T("bth32ProcessID");  //���̱�ʶ��
	jinCheng2[14] = _T("bcntThreads");  //����������ִ���߳���
	jinCheng2[15] = _T("bth32ParentProcessID");  //�����˽��̵Ľ��̵ı�ʶ�����丸���̣�
	jinCheng2[16] = _T("bpcPriClassBase");  //�˽��̴������κ��̵߳Ļ������ȼ�
	jinCheng2[17] = _T("bszExeFile");  //���̵Ŀ�ִ���ļ�������
	jinCheng2[18] = _T("bmodth32ProcessID");  //Module32First����,Ҫ�����ģ��Ľ��̵ı�ʶ��
	jinCheng2[19] = _T("bmodBaseAddr");  //ӵ�н�����������ģ��Ļ���ַ
	jinCheng2[20] = _T("bmodBaseSize");  //ģ��Ĵ�С�����ֽ�Ϊ��λ
	jinCheng2[21] = _T("bhModule");  //ӵ�н�����������ģ��ľ��;
	jinCheng2[22] = _T("bszModule");  //ģ������; ���ı�
	jinCheng2[23] = _T("bmodszExePath");  //ģ��·��; ���ı�

	fXjc[0] = _T("xuHao");  //���
	fXjc[1] = _T("th32ProcessID");  //���̱�ʶ��
	fXjc[2] = _T("th32ParentProcessID");  //�����˽��̵Ľ��̵ı�ʶ�����丸���̣�
	fXjc[3] = _T("szExeFile");  //���̵Ŀ�ִ���ļ�������
	fXjc[4] = _T("modth32ProcessID");  //Module32First����,Ҫ�����ģ��Ľ��̵ı�ʶ��
	fXjc[5] = _T("modBaseAddr");  //ӵ�н�����������ģ��Ļ���ַ
	fXjc[6] = _T("modBaseSize");  //ģ��Ĵ�С�����ֽ�Ϊ��λ
	fXjc[7] = _T("hModule");  //ӵ�н�����������ģ��ľ��
	fXjc[8] = _T("szModule");  //ģ������; ���ı�
	fXjc[9] = _T("modszExePath");  //ģ��·��; ���ı�

	bMingDan[0] = _T("exeming");//exe����
	bMingDan[1] = _T("exePath");//exe·��

	mingDanBiao = _T("bmd");//exe����
	idBiao = _T("id");
	jiLuBiao = _T("jiLu");
	jinCheng2Biao = _T("jinCheng2");
	jinCheng1Biao = _T("jinCheng1");
	jinChengBiao = _T("jinCheng");
	fXjinCheng = _T("fXjinCheng");
}

ACCSCC::~ACCSCC()
{
}

BOOL ACCSCC::lianJieAccscc()
{
	CString ku;
	ku.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;", theApp.kuPath);
	char pa[100] = { 0 };
	zhuanChar(ku, pa, 100);
	try {

		CoInitialize(NULL);//�ڵ�ǰ�߳��ϳ�ʼ�� COM �Ⲣ������ģ�ͱ�ʶΪ���̵߳�Ԫ (STA)���˲����Ǳ����ģ�����ΪNULL��
		m_pConnection = _ConnectionPtr(__uuidof(Connection));
		//CString strSQL=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=info.mdb;User ID=admin;Passward=;");
		// ʹ��JET���ݿ�����ʵ�ֶ�Acess2000���͵����ݿ�info.mdb������
		//m_pConnection->ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\yidaoyun\\gongCheng\\SuoPing\\sjk\\HaoBao.accdb;";
		//m_pConnection->ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\yidaoyun\\gongCheng\\SuoPing\\sjk\\HaoBao.mdb;";
		m_pConnection->ConnectionString = pa;
		/*  Open
							 const _variant_t & Source,������������������//sql��䡢������command����
							 const _variant_t & ActiveConnection,������//�Ѿ������õ����ӡ���
							 enum CursorTypeEnum CursorType,������������//���������ڴ�Recordsetʱ�ṩ��Ӧʹ�õ��α����ͣ�Ĭ��ֵadOpenForwardOnly
							 enum LockTypeEnum LockType,����������������//���������ڴ�Recordsetʱ�ṩ��Ӧʹ�õ��������ͣ�Ĭ��ֵadLockReadOnly
							 long Options ����������������������������//��ȡSource����Open��һ���������ķ�
		*/
		m_pConnection->Open("", "", "", adConnectUnspecified);
	}
	catch (_com_error e) {
		CString a;
		a.Format(L"�������ݿ��쳣,����: %s", e.ErrorMessage());
		AfxMessageBox(a);
		return FALSE;
	}
	lianJieKaiGuan = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

BOOL ACCSCC::lianJieAccscc(const char* luJing)
{
	try {

		CoInitialize(NULL);//�ڵ�ǰ�߳��ϳ�ʼ�� COM �Ⲣ������ģ�ͱ�ʶΪ���̵߳�Ԫ (STA)���˲����Ǳ����ģ�����ΪNULL��
		m_pConnection = _ConnectionPtr(__uuidof(Connection));
		//CString strSQL=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=info.mdb;User ID=admin;Passward=;");
		// ʹ��JET���ݿ�����ʵ�ֶ�Acess2000���͵����ݿ�info.mdb������
		//m_pConnection->ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\yidaoyun\\gongCheng\\SuoPing\\sjk\\HaoBao.accdb;";
		m_pConnection->ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;";
		/*  Open
							 const _variant_t & Source,������������������//sql��䡢������command����
							 const _variant_t & ActiveConnection,������//�Ѿ������õ����ӡ���
							 enum CursorTypeEnum CursorType,������������//���������ڴ�Recordsetʱ�ṩ��Ӧʹ�õ��α����ͣ�Ĭ��ֵadOpenForwardOnly
							 enum LockTypeEnum LockType,����������������//���������ڴ�Recordsetʱ�ṩ��Ӧʹ�õ��������ͣ�Ĭ��ֵadLockReadOnly
							 long Options ����������������������������//��ȡSource����Open��һ���������ķ�
		*/
		m_pConnection->Open("", "", "", adConnectUnspecified);
		lianJieKaiGuan = TRUE;
		return TRUE;  // return TRUE unless you set the focus to a control
	}
	catch (_com_error e) {
		CString a;
		a.Format(L"�������ݿ��쳣,����: %s", e.ErrorMessage());
		AfxMessageBox(a);
		return FALSE;
	}
	
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void ACCSCC::guanBiShuJuKu()
{
	if (lianJieKaiGuan)
	{
		m_pConnection->Close();
		m_pConnection = NULL;
		lianJieKaiGuan = FALSE;
	}	
}

unsigned ACCSCC::chaXun(CString biao, CString ziDuan, CString shuJu)
{
// 	char zDuan[30] = { 0 };
// 	zhuanChar(ziDuan, zDuan, 30);
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT %s FROM %s",ziDuan, biao);
		/*����: Execute
		* ����:�������ݿ�
		* ����1:sql���
		* ����2:ת�����ָ��
		* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);//���ﷵ�صľ��ǲ��Һ���������Ľ��
		CString id;
		while (!m_pRecordset->adoEOF)
		{
			
			id = m_pRecordset->GetCollect((LPCTSTR)ziDuan).bstrVal;
			if (id!="")
			{
				if (id == shuJu)
				{
					return 1;//�ҵ�����
				}
				return 2;
			}
			else
			{
				return 4;
			}
			m_pRecordset->MoveNext();
		}
		return 0;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("����ʧ�ܣ�"));
		printf("����ʧ�� int��\n");
		lianJieKaiGuan = FALSE;
		return 3;
	}
	
}

int ACCSCC::chaXun(CString biao, CString ziDuan, int shuJu)
{
	// 	char zDuan[30] = { 0 };
	// 	zhuanChar(ziDuan, zDuan, 30);
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT %s FROM %s", ziDuan, biao);
		/*����: Execute
		* ����:�������ݿ�
		* ����1:sql���
		* ����2:ת�����ָ��
		* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		int id;
		while (!m_pRecordset->adoEOF)
		{
			_variant_t var = m_pRecordset->GetCollect((LPCTSTR)ziDuan);
			//id = _ttoi(iid);
			var.ChangeType(VT_I4);
			id = var.lVal;
			if (id!= 0)
			{
				if (id == shuJu)
				{
					return 1;//�ҵ�����
				}
				return 2;
			} 
			else
			{
				return 4;
			}
			
			m_pRecordset->MoveNext();
		}
		return 0;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("����ʧ�ܣ�"));
		printf("����ʧ�ܣ�\n");
		lianJieKaiGuan = FALSE;
		return 3;
	}
}

BOOL ACCSCC::chaXunBMD(CString biao, CString ziDuan, CString shuJu)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
		CString search_sql;
		search_sql.Format(L"SELECT %s FROM %s", ziDuan, biao);
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);//���ﷵ�صľ��ǲ��Һ���������Ľ��
		CString id;
		while (!m_pRecordset->adoEOF)
		{
			id = m_pRecordset->GetCollect((LPCTSTR)ziDuan).bstrVal;
			if (id == shuJu)
			{
				return TRUE;//�ҵ�����
			}
			m_pRecordset->MoveNext();
		}
		return FALSE;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("����ʧ�ܣ�"));
		printf("����ʧ�� int��\n");
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

BOOL ACCSCC::chaXunBK(CString biao, CString ziDuan)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT %s FROM %s", ziDuan, biao);
		/*����: Execute
		* ����:�������ݿ�
		* ����1:sql���
		* ����2:ת�����ָ��
		* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		CString id;
		while (!m_pRecordset->adoEOF)
		{

			id = m_pRecordset->GetCollect((LPCTSTR)ziDuan).bstrVal;
			if (id!="")
			{
				return TRUE;
			}
			m_pRecordset->MoveNext();
		}
		return FALSE;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("����ʧ�ܣ�"));
		printf("����ʧ�� int��\n");
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

BOOL ACCSCC::chaXunK(CString biao, CString ziDuan)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT %s FROM %s", ziDuan, biao);
		/*����: Execute
		* ����:�������ݿ�
		* ����1:sql���
		* ����2:ת�����ָ��
		* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		CString id;
		if (m_pRecordset->adoEOF)//���û�ҵ��κ�����(���ֶ�),��¼��ָ��ָ�����һ����¼֮��
		{
			return TRUE;
		}
		while (!m_pRecordset->adoEOF)
		{

			id = m_pRecordset->GetCollect((LPCTSTR)ziDuan).bstrVal;
			if (id == "")
			{
				return TRUE;
			}
			m_pRecordset->MoveNext();
		}
		return FALSE;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("����ʧ�ܣ�"));
		printf("����ʧ�� int��\n");
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}





unsigned ACCSCC::chaXun(CString biao, CString ziDuan)
{
// 	char zDuan[30] = { 0 };
// 	zhuanChar(ziDuan, zDuan, 30);
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		cmd.m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
		CString search_sql;
		search_sql.Format(L"SELECT %s FROM %s", ziDuan, biao);
		//search_sql.Format("SELECT * FROM WorkUser WHERE MemberID = '%s'" , m_StringNumber)
		/*����: Execute
		* ����:�������ݿ�
		* ����1:sql���
		* ����2:ת�����ָ��
		* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
		*/
		cmd.m_pRecordset = cmd.m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		int i = 0;
		cmd.m_pRecordset->MoveFirst();
		//CString zHao;
		while (!cmd.m_pRecordset->adoEOF)
		{
			//zHao = cmd.m_pRecordset->GetCollect((LPCTSTR)ziDuan).bstrVal;
			i++;
			cmd.m_pRecordset->MoveNext();
		}
		return i;
		//std::cout << i << "     ksjdfskjdfskfjaaaaaaaaaaaa\n";
	}
	catch (_com_error e)
	{
		std::cout <<" accscc chaXun(CString biao, CString ziDuan) ����\n";
		lianJieKaiGuan = FALSE;
		return 0;
	}
	return 0;
}

BOOL ACCSCC::zengJia(CString biao, CString ziDuan, CString shuJu)
{
// 	char zDuan[30] = { 0 };
// 	zhuanChar(ziDuan, zDuan, 30);
	_variant_t RecordsAffected;
	CString AddSql;
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	if (chaXunK(biao, ziDuan))
	{
		AddSql.Format(L"INSERT INTO %s(%s) VALUES ('%s')", biao, ziDuan, shuJu);
		//AfxMessageBox(AddSql);
		try {
			/*
			* ����: Execute
			* ����:�������ݿ�
			* ����1:sql���
			* ����2:ת�����ָ��
			* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
			*/
			//cmd.m_pConnection->Execute((_bstr_t)AddSql, &RecordsAffected, adCmdText);
			cmd.m_pConnection->Execute((_bstr_t)AddSql, 0, adCmdText);
			return TRUE;
		}
		catch (_com_error* e) {
			std::cout << e << "\n";
			lianJieKaiGuan = FALSE;
			printf(" accscc zengJia(CString biao, CString ziDuan, CString shuJu) ����0\n");
			return FALSE;
		}
		
	}
	else
	{
		printf(" accscc zengJia(CString biao, CString ziDuan, CString shuJu) ����1\n");
		return FALSE;
	}
}



BOOL ACCSCC::xiuGai(CString biao, CString ziDuan, CString shuJu, CString xiuGaiZiDuan, CString zDshuJu)
{
	CString str;
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		//choosevalue = '%s'��chooseid = '%s Ҫ�޸ĵ��ֶ���ֵ,id = '%s Ҫ�޸ĵ��ֶζ�Ӧ����
		str.Format(_T("UPDATE %s SET %s = '%s' WHERE %s = '%s' "), biao, xiuGaiZiDuan, zDshuJu,ziDuan,shuJu);
		_variant_t RecordsAffected;
		cmd.m_pConnection->Execute((_bstr_t)str, &RecordsAffected, adCmdText);
		return TRUE;
	}
	catch (_com_error* e)
	{
		CString a;
		a.Format(L"�޸�ʧ��,�������: %s", e->ErrorMessage());
		AfxMessageBox(a);
		lianJieKaiGuan = FALSE;
		return TRUE;
	}
}

BOOL ACCSCC::xiuGai(CString biao, CString ziDuan, CString shuJu, CString xiuGaiShuJu)
{
	CString str;
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		//choosevalue = '%s'��chooseid = '%s Ҫ�޸ĵ��ֶ���ֵ,id = '%s Ҫ�޸ĵ��ֶζ�Ӧ����
		str.Format(_T("UPDATE %s SET %s = '%s' WHERE %s = '%s' "), biao, ziDuan, xiuGaiShuJu, ziDuan, shuJu);
		_variant_t RecordsAffected;
		cmd.m_pConnection->Execute((_bstr_t)str, &RecordsAffected, adCmdText);
		return TRUE;
	}
	catch (_com_error* e)
	{
		CString a;
		a.Format(L"�޸�ʧ��,�������: %s", e->ErrorMessage());
		AfxMessageBox(a);
		lianJieKaiGuan = FALSE;
		return TRUE;
	}
}

BOOL ACCSCC::shanChu(CString biao, CString ziDuan, CString shuJu)
{
	CString str;
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		//str.Format("DELETE from cmdchoose where id='" + choose_del + "'");
		//ɾ������ delete from car where ���� ����  //delete from ����  ����ɾ��ȫ������
		str.Format(L"DELETE from %s where %s='%s'", biao, ziDuan, shuJu);
		_variant_t RecordsAffected;
		cmd.m_pConnection->Execute((_bstr_t)str, &RecordsAffected, adCmdText);
		return TRUE;
	}
	catch (_com_error* e)
	{
		CString a;
		a.Format(L"ɾ��ʧ��,�������: %s", e->ErrorMessage());
		AfxMessageBox(a);
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

BOOL ACCSCC::shanChu(CString biao)
{
	CString str;
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		//str.Format("DELETE from cmdchoose where id='" + choose_del + "'");
		//ɾ������ delete from car where ���� ����  //delete from ����  ����ɾ��ȫ������
		str.Format(L"DELETE from %s", biao);
		//str.Format(L"TRUNCATE TABLE %s", biao);
		_variant_t RecordsAffected;
		cmd.m_pConnection->Execute((_bstr_t)str, &RecordsAffected, adCmdText);
		return TRUE;
	}
	catch (_com_error* e)
	{
		printf("shanChu(CString biao) �������: %s\n", e->ErrorMessage());
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

char** ACCSCC::getShuJu(CString biao, CString ziDuan, CString shuJu, CString muBiaoziDuan)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	unsigned a = chaXun(biao, muBiaoziDuan);
	//��ά����
	char** wu = new char* [30];
	if (a >= 1)
	{
		for (int i =0;i<a+1;i++)
		{
			wu[i] = new char[30];
		}
		wu[0][0] = a + 1;
		try
		{
			_variant_t RecordsAffected;
			m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
			CString search_sql;
			//CString a = L"xxx";
			//search_sql = "SELECT * FROM cmdchoose";
			//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
			search_sql.Format(L"SELECT %s,%s FROM %s WHERE %s = '%s'", muBiaoziDuan, ziDuan, biao, ziDuan, shuJu);
			/*����: Execute
			* ����:�������ݿ�
			* ����1:sql���
			* ����2:ת�����ָ��
			* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
			*/
			m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
			CString id;
			int len = 0;
			for (int ii = 1; !m_pRecordset->adoEOF; ii++)
			{
				id = m_pRecordset->GetCollect((LPCTSTR)muBiaoziDuan).bstrVal;//Ҫ��ȡ���ֶ�
				/***************************/
				len = id.GetLength();//���㳤��
				if (id== L"")
				{
					wu[ii][0] = '\0';
				}
				else
				{
					for (int iii = 0; iii < len; iii++)//�����鸳ֵ
					{
						wu[ii][iii] = id.GetAt(iii);//���ظ���λ�õ��ַ�
					}
				}
				/************************************/
				m_pRecordset->MoveNext();
			}
			return wu;
		}
		catch (_com_error e)
		{
			//AfxMessageBox(_T("����ʧ�ܣ�"));
			printf("\nchar** getShuJu �������: %s\n", e.ErrorMessage());
			lianJieKaiGuan = FALSE;
			/*�ͷ��ڴ�*/
			for (int i=0;i<a+1;i++)
			{
				delete[] wu[i];
			}
			delete[] wu;
			return wu;
		}
	}
	else
	{
		delete[] wu;
		wu = NULL;
		return wu;
	}
	
}

BOOL ACCSCC::getShuJu(CString biao, CString ziDuan, CString shuJu, CString muBiaoziDuan, wchar_t* shuzu)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
		CString search_sql;
		//L"SELECT Ҫ��ѯ���ֶ�,Ҫ��ѯ���ֶ� FROM �� WHERE ��λ���ֶ� = '��λ��ֵ'"
		search_sql.Format(L"SELECT %s,%s FROM %s WHERE %s = '%s'", muBiaoziDuan, ziDuan, biao, ziDuan, shuJu);
		//search_sql.Format(L"SELECT %s FROM %s", muBiaoziDuan, biao, muBiaoziDuan, shuJu);
		/*����: Execute
		* ����:�������ݿ�
		* ����1:sql���
		* ����2:ת�����ָ��
		* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		const wchar_t* aa = NULL;
		for (int i = 0;!m_pRecordset->adoEOF; i++)
		{
			aa = m_pRecordset->GetCollect((LPCTSTR)muBiaoziDuan).bstrVal;
			m_pRecordset->MoveNext();
		}

		wcscpy_s(shuzu, 30, aa);//���յ�����ָ��,����,Ҫ���Ƶ�����ָ��
		return TRUE;
	}
	catch (_com_error e)
	{
		printf("\nBOOL getShuJu �������: %s\n", e.ErrorMessage());
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

BOOL ACCSCC::getShuJu(CString biao, CString muBiaoziDuan, wchar_t* shuzu)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
		CString search_sql;
		//L"SELECT Ҫ ��ѯ���ֶ�,Ҫ��ѯ���ֶ� FROM �� WHERE ��λ���ֶ� = '��λ��ֵ'"
		search_sql.Format(L"SELECT %s FROM %s", muBiaoziDuan, biao);
		//search_sql.Format(L"SELECT %s FROM %s", muBiaoziDuan, biao, muBiaoziDuan, shuJu);
		/*����: Execute
		* ����:�������ݿ�
		* ����1:sql���
		* ����2:ת�����ָ��
		* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		const wchar_t* aa = NULL;
		for (int i = 0; !m_pRecordset->adoEOF; i++)
		{
			/*δ����������ݵı���*/
			aa = m_pRecordset->GetCollect((LPCTSTR)muBiaoziDuan).bstrVal;//�����ַ���
			m_pRecordset->MoveNext();
		}
		if (aa==NULL)
		{
// 			shuzu[0] = '\0';
// 			shuzu[1] = '\0';
			return FALSE;
		}
		wcscpy_s(shuzu, sizeof(aa), aa);//���յ�����ָ��,����,Ҫ���Ƶ�����ָ��
		return TRUE;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("����ʧ�ܣ�"));
		printf("\nBOOL getShuJu �������: %s\n", e.ErrorMessage());
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

unsigned int ACCSCC::getShuJuRQ(CString biao, CString ziDuan, CString shuJu, CString muBiaoziDuan)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	unsigned int sj = 0;
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
		CString search_sql;
		//L"SELECT Ҫ��ѯ���ֶ�,Ҫ��ѯ���ֶ� FROM �� WHERE ��λ���ֶ� = '��λ��ֵ'"
		search_sql.Format(L"SELECT %s,%s FROM %s WHERE %s = '%s'", muBiaoziDuan, ziDuan, biao, ziDuan, shuJu);
		//search_sql.Format(L"SELECT %s FROM %s", muBiaoziDuan, biao, muBiaoziDuan, shuJu);
		/*����: Execute
		* ����:�������ݿ�
		* ����1:sql���
		* ����2:ת�����ָ��
		* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		for (int i = 0; !m_pRecordset->adoEOF; i++)
		{
			sj = m_pRecordset->GetCollect((LPCTSTR)muBiaoziDuan).uintVal;//��ȡ����
			m_pRecordset->MoveNext();
		}
		return sj;
	}
	catch (_com_error e)
	{
		printf("\nBOOL getShuJu �������: %s\n", e.ErrorMessage());
		lianJieKaiGuan = FALSE;
		return sj;
	}
}

void ACCSCC::bianLiMoKuai()
{/*��Ҫ #include <TlHelp32.h>//��ȡ�����б�*/
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//��ȡ���̿���;TH32CS_SNAPPROCESS �ڿ����а���ϵͳ�е����н��̡�
	if (hSnap == INVALID_HANDLE_VALUE)//���ʧ��
	{
		return;
	}

	PROCESSENTRY32 pe{ sizeof(pe) };//�ṹ��,����ʼ���ṹ���С


	BOOL BMORE = Process32First(hSnap, &pe);//��õ�һ������
	
	//QueryFullProcessImageNameA
	BMORE = Process32First(hSnap, &pe);//��õ�һ������
	while (BMORE)
	{
		//pe.th32ProcessID //PID
		CString txt;
		txt.Format(L"%d", pe.th32ProcessID);//���PID

		//pid[ci] =(int*)pe.th32ParentProcessID;
		//pidM[ci] = pe.szExeFile;
		//ProcessLst.InsertItem(0, txt);
		//ProcessLst.SetItemText(0, 1, pe.szExeFile);//����ļ���
		BMORE = Process32Next(hSnap, &pe);//�����һ������
		int a = pe.pcPriClassBase;
	}
	CloseHandle(hSnap);//�رտ���
}

UINT sDjC(LPVOID dwPID)
{/*��Ҫ #include <TlHelp32.h>//��ȡ�����б�*/
	//GetCurrentProcessId() //�������ý��̵Ľ��̱�ʶ��PID
	//����ȫ�ֱ���ʱ�ͼ���, ������
	SheZhi szL;
	WaitForSingleObject(szL.hMutex, INFINITE);
	SheZhi::jcCS* js = (SheZhi::jcCS*)dwPID;
	DWORD Pid = js->pid;
	printf("\n     �߳����� %d............ %d    \n", theApp.ci,Pid);
	theApp.ci++;
	//������ȫ�ֱ���ʱ�ͽ���, ������
	ReleaseMutex(szL.hMutex);

	MODULEENTRY32 me32;//ʹ��Module32First����
	HANDLE hSnap = INVALID_HANDLE_VALUE;//ʧ��
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Pid);//����������PID��ָ���Ľ��̵�����ģ��
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	me32.dwSize = sizeof(MODULEENTRY32);
	BOOL BMORE = Module32First(hSnap, &me32);
	CString lj;
	CString mz;
	DWORD pid;
	// 	while (BMORE)
	// 	{
	printf("\n     ģ������:     %S", me32.szModule);//
	mz = me32.szModule;
	printf("\n     ģ��·��     %S", me32.szExePath);
	lj = me32.szExePath;
	printf("\n     Ҫ�����ģ��Ľ��̵ı�ʶ��PID     %d\n", me32.th32ProcessID);
	pid = me32.th32ProcessID;
	CloseHandle(hSnap);//�ͷſ���
	BOOL pd = cmd.chaXunBMD(cmd.mingDanBiao, cmd.bMingDan[0], mz);
	if (0)
	{
		//�رս���
		HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION |   // Required by Alpha
			PROCESS_CREATE_THREAD |   // For CreateRemoteThread
			PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
			PROCESS_VM_WRITE,             // For WriteProcessMemory);
			FALSE, pid);
		if (killHandle == NULL)
		{
			return 0;
		}
		TerminateProcess(killHandle, 0);
		CloseHandle(killHandle);//�رվ��
		return 0;
	}
	return 0;
}

DWORD WINAPI jingChengChuLi(void* a)
{
	ACCSCC::jCjingCheng* jc = (ACCSCC::jCjingCheng*)a;
	printf("\n�߳�pid  %d\n", jc->Pid);
	printf("\n�߳�exe����  %S\n", jc->exeMing);
	printf("\n�߳�exepath  %S\n", jc->exePath);

	//�Ա�exe���Ƿ������ݿ������
	//�Ա�exe·���Ƿ������ݿ������
	//���û��ƥ��,ɱ������
	BOOL pd = cmd.chaXunBMD(cmd.mingDanBiao, cmd.bMingDan[0], jc->exePath);
	if (0)
	{
		//�رս���
		HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION |   // Required by Alpha
			PROCESS_CREATE_THREAD |   // For CreateRemoteThread
			PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
			PROCESS_VM_WRITE,             // For WriteProcessMemory);
			FALSE, jc->Pid);
		if (killHandle == NULL)
		{
			delete a;//�ͷ��ڴ�
			a = NULL;
			return FALSE;
		}
		TerminateProcess(killHandle, 0);
		CloseHandle(killHandle);//�رվ��
		return TRUE;
	}
	delete a;//�ͷ��ڴ�
	a = NULL;
	printf("\n     xianc1............     \n");
	return FALSE;
}

DWORD __stdcall sDjingCheng(LPVOID dwPID)//LPVOID������,
{/*��Ҫ #include <TlHelp32.h>//��ȡ�����б�*/
	//GetCurrentProcessId() //�������ý��̵Ľ��̱�ʶ��PID
	DWORD Pid = *((DWORD*)dwPID);//ǿ��ת��
	printf("\n     xianc1............ %d    \n",Pid);
	MODULEENTRY32 me32;//ʹ��Module32First����
	HANDLE hSnap = INVALID_HANDLE_VALUE;//ʧ��
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Pid);//����������PID��ָ���Ľ��̵�����ģ��
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	me32.dwSize = sizeof(MODULEENTRY32);
	BOOL BMORE = Module32First(hSnap, &me32);
	CString lj;
	CString mz;
	DWORD pid;
	// 	while (BMORE)
	// 	{
	printf("\n     ģ������:     %S", me32.szModule);//
	mz = me32.szModule;
	printf("\n     ģ��·��     %S", me32.szExePath);
	lj = me32.szExePath;
	printf("\n     Ҫ�����ģ��Ľ��̵ı�ʶ��PID     %d\n", me32.th32ProcessID);
	pid = me32.th32ProcessID;
	CloseHandle(hSnap);//�ͷſ���
	BOOL pd = cmd.chaXunBMD(cmd.mingDanBiao, cmd.bMingDan[0], mz);
	if (0)
	{
		//�رս���
		HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION |   // Required by Alpha
			PROCESS_CREATE_THREAD |   // For CreateRemoteThread
			PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
			PROCESS_VM_WRITE,             // For WriteProcessMemory);
			FALSE, pid);
		if (killHandle == NULL)
		{
			return 0;
		}
		TerminateProcess(killHandle, 0);
		CloseHandle(killHandle);//�رվ��
		return 0;
	}
	return 0;
}



void ACCSCC::bianLiJinCheng(DWORD dwPID)
{/*��Ҫ #include <TlHelp32.h>//��ȡ�����б�*/
	//GetCurrentProcessId() //�������ý��̵Ľ��̱�ʶ��PID
	MODULEENTRY32 me32;//ʹ��Module32First����
	HANDLE hSnap = INVALID_HANDLE_VALUE;//ʧ��
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);//����������PID��ָ���Ľ��̵�����ģ��
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		return;
	}
	
	me32.dwSize = sizeof(MODULEENTRY32);
	BOOL BMORE = Module32First(hSnap, &me32);
	CString lj;
	CString mz;
	struct jCjingCheng* jc = new jCjingCheng;

// 	while (BMORE)
// 	{
		printf("\n     ģ������:     %S", me32.szModule);//
		jc->exeMing = me32.szModule;
		printf("\n     ģ��·��     %S", me32.szExePath);
		jc->exePath = me32.szExePath;
		printf("\n     Ҫ�����ģ��Ľ��̵ı�ʶ��PID     %d", me32.th32ProcessID);
		jc->Pid = me32.th32ProcessID;
		CloseHandle(hSnap);//�ͷſ���
		HANDLE jcTherad = CreateThread(NULL, 0, jingChengChuLi, jc, 0, NULL);//�½��߳�
		//printf("\n     ������������ģ��Ļ���ַ   = 0x%08X", (DWORD)me32.modBaseAddr);
		//printf("\n     ģ��Ĵ�С      = %d", me32.modBaseSize);
		//printf("\n     ������������ģ��ľ��      = %d\n", me32.modBaseSize);
		//BMORE = Module32Next(hSnap, &me32);
	//} 
}

BOOL ACCSCC::zegJia(CString biao)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT * FROM %s",  biao);
		/*����: Execute
		* ����:�������ݿ�
		* ����1:sql���
		* ����2:ת�����ָ��
		* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		CString id;
		if (m_pRecordset->adoEOF)//���û�ҵ��κ�����(���ֶ�),��¼��ָ��ָ�����һ����¼֮��
		{
			return TRUE;
		}
		while (!m_pRecordset->adoEOF)
		{

			//id = m_pRecordset->GetCollect((LPCTSTR)ziDuan).bstrVal;
			if (id == "")
			{
				return TRUE;
			}
			m_pRecordset->MoveNext();
		}
		return FALSE;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("����ʧ�ܣ�"));
		printf("����ʧ�� int��\n");
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

BOOL ACCSCC::huoQuJinChengLieBiao(CString biao, BOOL s)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	if (s)
	{
		shanChu(biao);//��ձ�
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
	CString search_sql;
	search_sql.Format(L"SELECT   *   FROM   %s", biao);
	m_pRecordset->Open((LPCTSTR)search_sql, _variant_t((IDispatch*)m_pConnection, true), 
		adOpenStatic, adLockOptimistic, adCmdText);
	int ci = 1;
	try
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//��ȡ���̿���
		if (hSnap == INVALID_HANDLE_VALUE)//���ʧ��
		{
			return 0;
		}
		PROCESSENTRY32 pe{ sizeof(pe) };//�ṹ��,����ʼ���ṹ���С
		BOOL BMORE = Process32First(hSnap, &pe);//��õ�һ������
		while (BMORE)
		{
			m_pRecordset->AddNew();
			//m_pRecordset->PutCollect((LPCTSTR)jinCheng2[0], _variant_t((long)ci));
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[0], ci);
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[1], pe.th32ProcessID);
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[2], pe.cntThreads);
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[3], pe.th32ParentProcessID);
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[5], _variant_t(pe.szExeFile));
			m_pRecordset->Update();
			//txt.Format(L"%d", pe.th32ProcessID);//���PID
			//ProcessLst.SetItemText(0, 1, pe.szExeFile);//����ļ���
			BMORE = Process32Next(hSnap, &pe);//�����һ������
			ci++;
		}
		CloseHandle(hSnap);//�ͷſ���
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("����ʧ�ܣ�"));
		printf("����: huoQuJinChengLieBiao(CString biao)�� �������:%s\n",e.ErrorMessage());
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
	
	return 0;
}

BOOL ACCSCC::huoQuJinChengLieBiao_lieBiao(CString biao, LPVOID IPtr, BOOL s)
{
	SheZhi* lb = (SheZhi*)IPtr;
	//SheZhi lb;
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	if (s)
	{
		shanChu(biao);//��ձ�
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
	CString search_sql;
	search_sql.Format(L"SELECT   *   FROM   %s", biao);
	m_pRecordset->Open((LPCTSTR)search_sql, _variant_t((IDispatch*)m_pConnection, true), 
		adOpenStatic, adLockOptimistic, adCmdText);
	int ci = 1;
	try
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//��ȡ���̿���
		if (hSnap == INVALID_HANDLE_VALUE)//���ʧ��
		{
			return 0;
		}
		PROCESSENTRY32 pe{ sizeof(pe) };//�ṹ��,����ʼ���ṹ���С
		BOOL BMORE = Process32First(hSnap, &pe);//��õ�һ������
		CString a;
		//SheZhi* lb = (SheZhi*)AfxGetMainWnd();
		while (BMORE)
		{
			m_pRecordset->AddNew();
			//m_pRecordset->PutCollect((LPCTSTR)jinCheng2[0], _variant_t((long)ci));
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[0], ci);
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[1], pe.th32ProcessID);

			a.Format(L"%d", pe.th32ProcessID);//���PID
			lb->ProcessLst.InsertItem(0, a);
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[2], pe.cntThreads);
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[3], pe.th32ParentProcessID);

			a.Format(L"%d", pe.th32ParentProcessID);//���PID
			lb->ProcessLst.SetItemText(0, 2, a);//����ļ���
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[5], _variant_t(pe.szExeFile));

			lb->ProcessLst.SetItemText(0, 1, pe.szExeFile);//����ļ���
			m_pRecordset->Update();
			//txt.Format(L"%d", pe.th32ProcessID);//���PID
			//ProcessLst.SetItemText(0, 1, pe.szExeFile);//����ļ���
			BMORE = Process32Next(hSnap, &pe);//�����һ������
			ci++;
			if (ci==234)
			{
				int d = 3;
			}
		}
		lb->DoModal();//��ʾ�б�
		return TRUE;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("����ʧ�ܣ�"));
		printf("����: huoQuJinChengLieBiao(CString biao)�� �������:%s\n",e.ErrorMessage());
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
	
	return 0;
}

wchar_t** ACCSCC::huoQuJinChengLieBiao(int** a)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//��ȡ���̿���
	if (hSnap == INVALID_HANDLE_VALUE)//���ʧ��
	{
		return 0;
	}

	PROCESSENTRY32 pe{ sizeof(pe) };//�ṹ��,����ʼ���ṹ���С


	BOOL BMORE = Process32First(hSnap, &pe);//��õ�һ������
	int i = 0;
	for (; BMORE; i++)//����ж��ٽ���
	{
		i++;
		BMORE = Process32Next(hSnap, &pe);//�����һ������
	}
	int cdPid = 1;
	int cdPidM = 150;
	int** b = new int* [cdPid];
	for (int ii = 0; ii < i + 1; ii++)
	{
		b[ii] = new int[cdPid];
	}

	wchar_t** pidM = new wchar_t* [cdPidM];
	int ii = 0;
	for (; ii < i + 1; ii++)
	{
		pidM[ii] = new wchar_t[cdPidM];
	}
	pidM[0][0] = ii + 2;
	int cc =(int) &b;
	pidM[0][1] = cc << 16;//��λ
	pidM[0][2] = cc >> 16;//��λ
	pidM[0][3] = (int)&b;
	
	//QueryFullProcessImageNameA
	BMORE = Process32First(hSnap, &pe);//��õ�һ������
	int ci = 0;
	int ci2 = 1;
	while (BMORE)
	{
		//pe.th32ProcessID //PID
		CString txt;
		txt.Format(L"%d", pe.th32ProcessID);//���PID

		b[ci] = (int*)pe.th32ProcessID;
		pidM[ci2] = pe.szExeFile;
		//ProcessLst.InsertItem(0, txt);
		//ProcessLst.SetItemText(0, 1, pe.szExeFile);//����ļ���
		BMORE = Process32Next(hSnap, &pe);//�����һ������
		ci++;
		ci2++;
	}
	return pidM;
}


void ACCSCC::quChongAccScc(CString ba, CString bb, CString zda, CString zdb)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//�����ݿ�
	}
	CString search_sql;
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//����ʵ��
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT %s FROM %s,%s groub by %s", zda, ba, bb,zda);
		/*����: Execute
		* ����:�������ݿ�
		* ����1:sql���
		* ����2:ת�����ָ��
		* ����3:�����һ��������sql�����ѡ��adCmdText,�����һ�������Ǳ�����ѡ��adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		int id;
		CString iid;
		while (!m_pRecordset->adoEOF)
		{
			id = m_pRecordset->GetCollect((LPCTSTR)zda).uintVal;//��ȡ����
			iid.Format(L"%d", id);
			theApp.sheZhiL.ProcessLst.InsertItem(0, iid);
			m_pRecordset->MoveNext();
		}
		theApp.sheZhiL.DoModal();
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("����ʧ�ܣ�"));
		printf("����: huoQuJinChengLieBiao(CString biao)�� �������:%s\n", e.ErrorMessage());
		lianJieKaiGuan = FALSE;
	}
}

BOOL ACCSCC::shaSiJinCheng(DWORD pid)
{
	//�رս���
	HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION |   // Required by Alpha
		PROCESS_CREATE_THREAD |   // For CreateRemoteThread
		PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
		PROCESS_VM_WRITE,             // For WriteProcessMemory);
		FALSE, pid);
	if (killHandle == NULL)
		return false;
	TerminateProcess(killHandle, 0);//ɱ������
	CloseHandle(killHandle);//�رվ��
	return true;
}

BOOL ACCSCC::qiDongJinCheng(CString exePath)
{
	TCHAR tszProcess[260] = { 0 };
	lstrcpy(tszProcess, exePath);
	//������������
	SHELLEXECUTEINFO shellInfo;
	memset(&shellInfo, 0, sizeof(SHELLEXECUTEINFO));
	shellInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	shellInfo.fMask = NULL;
	shellInfo.hwnd = NULL;
	shellInfo.lpVerb = NULL;
	shellInfo.lpFile = tszProcess;                      // ִ�еĳ�����(����·��)
	shellInfo.lpParameters = NULL;
	shellInfo.lpDirectory = NULL;
	shellInfo.nShow = SW_MINIMIZE;                      //SW_SHOWNORMAL ȫ����ʾ�������
	shellInfo.hInstApp = NULL;

	ShellExecuteEx(&shellInfo);//����

	return true;
}
