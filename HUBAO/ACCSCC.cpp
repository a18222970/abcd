#include "pch.h"
#include "ACCSCC.h"

#include <TlHelp32.h>//获取进程列表
#include "HUBAO.h";
#include "SheZhi.h"
BOOL ACCSCC::zhuanChar(CString sj, char* shuzu, int len)
{
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
	if (len < ilen)//如果接受数组长度小于要转换的字符串长度,返回FALSE
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

ACCSCC::ACCSCC()
{
	
	lianJieKaiGuan = FALSE;

	/*accscc数据库*/
	yongHuId[0] = _T("zhangHao");//账号
	yongHuId[1] = _T("miMa");//密码
	yongHuId[2] = _T("leiXing");//类型
	yongHuId[3] = _T("suiJiMa1");//校验码
	yongHuId[4] = _T("suiJiMa2");//随机密码
	yongHuId[5] = _T("dengLuBiaoJi");//登陆标记
	yongHuId[6] = _T("daoQiShiJian");//到期时间
	yongHuId[7] = _T("dingShi");//int
	yongHuId[8] = _T("beiYong");// 0/1
	yongHuId[9] = _T("xuHao");// 序号


	yongHuJl[0] = _T("xuHao");  //记录序号 Int
	yongHuJl[1] = _T("zhangHao");//账号
	yongHuJl[2] = _T("yunJieCiShu");//越界执行程序的次数
	yongHuJl[3] = _T("yueJieZhiXing");//越界执行的程序名字
	yongHuJl[4] = _T("yueJieZhiXing");//越界执行的程序路径
	yongHuJl[5] = _T("yueJieShiJian"); //越界执行程序的时间
	yongHuJl[6] = _T("qiDongShiJian");//软件启动时间
	yongHuJl[7] = _T("sheDingShiJian");//设定运行时间
	yongHuJl[8] = _T("beiYong");//int
	yongHuJl[9] = _T("dingShiShiJian");//定时执行锁屏的开始时间
	yongHuJl[10] = _T("yunXunShiJian");// 程序运行总时间

	//除了文本,其他都是整数类型
	jinCheng2[0] = _T("xuHao");  //序号
	jinCheng2[1] = _T("th32ProcessID");  //进程标识符
	jinCheng2[2] = _T("cntThreads");  //进程启动的执行线程数
	jinCheng2[3] = _T("th32ParentProcessID");  //创建此进程的进程的标识符（其父进程）
	jinCheng2[4] = _T("pcPriClassBase");  //此进程创建的任何线程的基本优先级
	jinCheng2[5] = _T("szExeFile");  //进程的可执行文件的名称
	jinCheng2[6] = _T("modth32ProcessID");  //Module32First函数,要检查其模块的进程的标识符
	jinCheng2[7] = _T("modBaseAddr");  //拥有进程上下文中模块的基地址
	jinCheng2[8] = _T("modBaseSize");  //模块的大小，以字节为单位
	jinCheng2[9] = _T("hModule");  //拥有进程上下文中模块的句柄
	jinCheng2[10] = _T("szModule");  //模块名称; 短文本
	jinCheng2[11] = _T("modszExePath");  //模块路径; 长文本
	jinCheng2[12] = _T("bxuHao");  //序号
	jinCheng2[13] = _T("bth32ProcessID");  //进程标识符
	jinCheng2[14] = _T("bcntThreads");  //进程启动的执行线程数
	jinCheng2[15] = _T("bth32ParentProcessID");  //创建此进程的进程的标识符（其父进程）
	jinCheng2[16] = _T("bpcPriClassBase");  //此进程创建的任何线程的基本优先级
	jinCheng2[17] = _T("bszExeFile");  //进程的可执行文件的名称
	jinCheng2[18] = _T("bmodth32ProcessID");  //Module32First函数,要检查其模块的进程的标识符
	jinCheng2[19] = _T("bmodBaseAddr");  //拥有进程上下文中模块的基地址
	jinCheng2[20] = _T("bmodBaseSize");  //模块的大小，以字节为单位
	jinCheng2[21] = _T("bhModule");  //拥有进程上下文中模块的句柄;
	jinCheng2[22] = _T("bszModule");  //模块名称; 短文本
	jinCheng2[23] = _T("bmodszExePath");  //模块路径; 长文本

	fXjc[0] = _T("xuHao");  //序号
	fXjc[1] = _T("th32ProcessID");  //进程标识符
	fXjc[2] = _T("th32ParentProcessID");  //创建此进程的进程的标识符（其父进程）
	fXjc[3] = _T("szExeFile");  //进程的可执行文件的名称
	fXjc[4] = _T("modth32ProcessID");  //Module32First函数,要检查其模块的进程的标识符
	fXjc[5] = _T("modBaseAddr");  //拥有进程上下文中模块的基地址
	fXjc[6] = _T("modBaseSize");  //模块的大小，以字节为单位
	fXjc[7] = _T("hModule");  //拥有进程上下文中模块的句柄
	fXjc[8] = _T("szModule");  //模块名称; 短文本
	fXjc[9] = _T("modszExePath");  //模块路径; 长文本

	bMingDan[0] = _T("exeming");//exe名称
	bMingDan[1] = _T("exePath");//exe路径

	mingDanBiao = _T("bmd");//exe名称
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

		CoInitialize(NULL);//在当前线程上初始化 COM 库并将并发模型标识为单线程单元 (STA)。此参数是保留的，必须为NULL。
		m_pConnection = _ConnectionPtr(__uuidof(Connection));
		//CString strSQL=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=info.mdb;User ID=admin;Passward=;");
		// 使用JET数据库引擎实现对Acess2000类型的数据库info.mdb的连接
		//m_pConnection->ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\yidaoyun\\gongCheng\\SuoPing\\sjk\\HaoBao.accdb;";
		//m_pConnection->ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\yidaoyun\\gongCheng\\SuoPing\\sjk\\HaoBao.mdb;";
		m_pConnection->ConnectionString = pa;
		/*  Open
							 const _variant_t & Source,　　　　　　　　　//sql语句、表名、command对象
							 const _variant_t & ActiveConnection,　　　//已经建立好的连接　　
							 enum CursorTypeEnum CursorType,　　　　　　//用于设置在打开Recordset时提供者应使用的游标类型，默认值adOpenForwardOnly
							 enum LockTypeEnum LockType,　　　　　　　　//用于设置在打开Recordset时提供者应使用的锁定类型，默认值adLockReadOnly
							 long Options 　　　　　　　　　　　　　　//获取Source（即Open第一个参数）的方
		*/
		m_pConnection->Open("", "", "", adConnectUnspecified);
	}
	catch (_com_error e) {
		CString a;
		a.Format(L"连接数据库异常,代码: %s", e.ErrorMessage());
		AfxMessageBox(a);
		return FALSE;
	}
	lianJieKaiGuan = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

BOOL ACCSCC::lianJieAccscc(const char* luJing)
{
	try {

		CoInitialize(NULL);//在当前线程上初始化 COM 库并将并发模型标识为单线程单元 (STA)。此参数是保留的，必须为NULL。
		m_pConnection = _ConnectionPtr(__uuidof(Connection));
		//CString strSQL=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=info.mdb;User ID=admin;Passward=;");
		// 使用JET数据库引擎实现对Acess2000类型的数据库info.mdb的连接
		//m_pConnection->ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\yidaoyun\\gongCheng\\SuoPing\\sjk\\HaoBao.accdb;";
		m_pConnection->ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;";
		/*  Open
							 const _variant_t & Source,　　　　　　　　　//sql语句、表名、command对象
							 const _variant_t & ActiveConnection,　　　//已经建立好的连接　　
							 enum CursorTypeEnum CursorType,　　　　　　//用于设置在打开Recordset时提供者应使用的游标类型，默认值adOpenForwardOnly
							 enum LockTypeEnum LockType,　　　　　　　　//用于设置在打开Recordset时提供者应使用的锁定类型，默认值adLockReadOnly
							 long Options 　　　　　　　　　　　　　　//获取Source（即Open第一个参数）的方
		*/
		m_pConnection->Open("", "", "", adConnectUnspecified);
		lianJieKaiGuan = TRUE;
		return TRUE;  // return TRUE unless you set the focus to a control
	}
	catch (_com_error e) {
		CString a;
		a.Format(L"连接数据库异常,代码: %s", e.ErrorMessage());
		AfxMessageBox(a);
		return FALSE;
	}
	
	// 异常:  OCX 属性页应返回 FALSE
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
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT %s FROM %s",ziDuan, biao);
		/*函数: Execute
		* 作用:操作数据库
		* 参数1:sql语句
		* 参数2:转换后的指针
		* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);//这里返回的就是查找后符合条件的结果
		CString id;
		while (!m_pRecordset->adoEOF)
		{
			
			id = m_pRecordset->GetCollect((LPCTSTR)ziDuan).bstrVal;
			if (id!="")
			{
				if (id == shuJu)
				{
					return 1;//找到返回
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
		//AfxMessageBox(_T("搜索失败！"));
		printf("搜索失败 int！\n");
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
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT %s FROM %s", ziDuan, biao);
		/*函数: Execute
		* 作用:操作数据库
		* 参数1:sql语句
		* 参数2:转换后的指针
		* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
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
					return 1;//找到返回
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
		//AfxMessageBox(_T("搜索失败！"));
		printf("搜索失败！\n");
		lianJieKaiGuan = FALSE;
		return 3;
	}
}

BOOL ACCSCC::chaXunBMD(CString biao, CString ziDuan, CString shuJu)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		search_sql.Format(L"SELECT %s FROM %s", ziDuan, biao);
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);//这里返回的就是查找后符合条件的结果
		CString id;
		while (!m_pRecordset->adoEOF)
		{
			id = m_pRecordset->GetCollect((LPCTSTR)ziDuan).bstrVal;
			if (id == shuJu)
			{
				return TRUE;//找到返回
			}
			m_pRecordset->MoveNext();
		}
		return FALSE;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("搜索失败！"));
		printf("搜索失败 int！\n");
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

BOOL ACCSCC::chaXunBK(CString biao, CString ziDuan)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT %s FROM %s", ziDuan, biao);
		/*函数: Execute
		* 作用:操作数据库
		* 参数1:sql语句
		* 参数2:转换后的指针
		* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
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
		//AfxMessageBox(_T("搜索失败！"));
		printf("搜索失败 int！\n");
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

BOOL ACCSCC::chaXunK(CString biao, CString ziDuan)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT %s FROM %s", ziDuan, biao);
		/*函数: Execute
		* 作用:操作数据库
		* 参数1:sql语句
		* 参数2:转换后的指针
		* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		CString id;
		if (m_pRecordset->adoEOF)//如果没找到任何数据(空字段),记录集指针指向最后一条记录之后
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
		//AfxMessageBox(_T("搜索失败！"));
		printf("搜索失败 int！\n");
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
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		cmd.m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		search_sql.Format(L"SELECT %s FROM %s", ziDuan, biao);
		//search_sql.Format("SELECT * FROM WorkUser WHERE MemberID = '%s'" , m_StringNumber)
		/*函数: Execute
		* 作用:操作数据库
		* 参数1:sql语句
		* 参数2:转换后的指针
		* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
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
		std::cout <<" accscc chaXun(CString biao, CString ziDuan) 错误\n";
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
		cmd.lianJieAccscc();//打开数据库
	}
	if (chaXunK(biao, ziDuan))
	{
		AddSql.Format(L"INSERT INTO %s(%s) VALUES ('%s')", biao, ziDuan, shuJu);
		//AfxMessageBox(AddSql);
		try {
			/*
			* 函数: Execute
			* 作用:操作数据库
			* 参数1:sql语句
			* 参数2:转换后的指针
			* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
			*/
			//cmd.m_pConnection->Execute((_bstr_t)AddSql, &RecordsAffected, adCmdText);
			cmd.m_pConnection->Execute((_bstr_t)AddSql, 0, adCmdText);
			return TRUE;
		}
		catch (_com_error* e) {
			std::cout << e << "\n";
			lianJieKaiGuan = FALSE;
			printf(" accscc zengJia(CString biao, CString ziDuan, CString shuJu) 错误0\n");
			return FALSE;
		}
		
	}
	else
	{
		printf(" accscc zengJia(CString biao, CString ziDuan, CString shuJu) 错误1\n");
		return FALSE;
	}
}



BOOL ACCSCC::xiuGai(CString biao, CString ziDuan, CString shuJu, CString xiuGaiZiDuan, CString zDshuJu)
{
	CString str;
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		//choosevalue = '%s'与chooseid = '%s 要修改的字段与值,id = '%s 要修改的字段对应的行
		str.Format(_T("UPDATE %s SET %s = '%s' WHERE %s = '%s' "), biao, xiuGaiZiDuan, zDshuJu,ziDuan,shuJu);
		_variant_t RecordsAffected;
		cmd.m_pConnection->Execute((_bstr_t)str, &RecordsAffected, adCmdText);
		return TRUE;
	}
	catch (_com_error* e)
	{
		CString a;
		a.Format(L"修改失败,错误代码: %s", e->ErrorMessage());
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
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		//choosevalue = '%s'与chooseid = '%s 要修改的字段与值,id = '%s 要修改的字段对应的行
		str.Format(_T("UPDATE %s SET %s = '%s' WHERE %s = '%s' "), biao, ziDuan, xiuGaiShuJu, ziDuan, shuJu);
		_variant_t RecordsAffected;
		cmd.m_pConnection->Execute((_bstr_t)str, &RecordsAffected, adCmdText);
		return TRUE;
	}
	catch (_com_error* e)
	{
		CString a;
		a.Format(L"修改失败,错误代码: %s", e->ErrorMessage());
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
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		//str.Format("DELETE from cmdchoose where id='" + choose_del + "'");
		//删除数据 delete from car where 表名 条件  //delete from 表名  ——删除全部数据
		str.Format(L"DELETE from %s where %s='%s'", biao, ziDuan, shuJu);
		_variant_t RecordsAffected;
		cmd.m_pConnection->Execute((_bstr_t)str, &RecordsAffected, adCmdText);
		return TRUE;
	}
	catch (_com_error* e)
	{
		CString a;
		a.Format(L"删除失败,错误代码: %s", e->ErrorMessage());
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
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		//str.Format("DELETE from cmdchoose where id='" + choose_del + "'");
		//删除数据 delete from car where 表名 条件  //delete from 表名  ——删除全部数据
		str.Format(L"DELETE from %s", biao);
		//str.Format(L"TRUNCATE TABLE %s", biao);
		_variant_t RecordsAffected;
		cmd.m_pConnection->Execute((_bstr_t)str, &RecordsAffected, adCmdText);
		return TRUE;
	}
	catch (_com_error* e)
	{
		printf("shanChu(CString biao) 错误代码: %s\n", e->ErrorMessage());
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

char** ACCSCC::getShuJu(CString biao, CString ziDuan, CString shuJu, CString muBiaoziDuan)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	unsigned a = chaXun(biao, muBiaoziDuan);
	//二维数组
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
			m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
			CString search_sql;
			//CString a = L"xxx";
			//search_sql = "SELECT * FROM cmdchoose";
			//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
			search_sql.Format(L"SELECT %s,%s FROM %s WHERE %s = '%s'", muBiaoziDuan, ziDuan, biao, ziDuan, shuJu);
			/*函数: Execute
			* 作用:操作数据库
			* 参数1:sql语句
			* 参数2:转换后的指针
			* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
			*/
			m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
			CString id;
			int len = 0;
			for (int ii = 1; !m_pRecordset->adoEOF; ii++)
			{
				id = m_pRecordset->GetCollect((LPCTSTR)muBiaoziDuan).bstrVal;//要读取的字段
				/***************************/
				len = id.GetLength();//计算长度
				if (id== L"")
				{
					wu[ii][0] = '\0';
				}
				else
				{
					for (int iii = 0; iii < len; iii++)//给数组赋值
					{
						wu[ii][iii] = id.GetAt(iii);//返回给定位置的字符
					}
				}
				/************************************/
				m_pRecordset->MoveNext();
			}
			return wu;
		}
		catch (_com_error e)
		{
			//AfxMessageBox(_T("搜索失败！"));
			printf("\nchar** getShuJu 错误代码: %s\n", e.ErrorMessage());
			lianJieKaiGuan = FALSE;
			/*释放内存*/
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
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		//L"SELECT 要查询的字段,要查询的字段 FROM 表 WHERE 定位的字段 = '定位的值'"
		search_sql.Format(L"SELECT %s,%s FROM %s WHERE %s = '%s'", muBiaoziDuan, ziDuan, biao, ziDuan, shuJu);
		//search_sql.Format(L"SELECT %s FROM %s", muBiaoziDuan, biao, muBiaoziDuan, shuJu);
		/*函数: Execute
		* 作用:操作数据库
		* 参数1:sql语句
		* 参数2:转换后的指针
		* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		const wchar_t* aa = NULL;
		for (int i = 0;!m_pRecordset->adoEOF; i++)
		{
			aa = m_pRecordset->GetCollect((LPCTSTR)muBiaoziDuan).bstrVal;
			m_pRecordset->MoveNext();
		}

		wcscpy_s(shuzu, 30, aa);//接收的数组指针,长度,要复制的数组指针
		return TRUE;
	}
	catch (_com_error e)
	{
		printf("\nBOOL getShuJu 错误代码: %s\n", e.ErrorMessage());
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

BOOL ACCSCC::getShuJu(CString biao, CString muBiaoziDuan, wchar_t* shuzu)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		//L"SELECT 要 查询的字段,要查询的字段 FROM 表 WHERE 定位的字段 = '定位的值'"
		search_sql.Format(L"SELECT %s FROM %s", muBiaoziDuan, biao);
		//search_sql.Format(L"SELECT %s FROM %s", muBiaoziDuan, biao, muBiaoziDuan, shuJu);
		/*函数: Execute
		* 作用:操作数据库
		* 参数1:sql语句
		* 参数2:转换后的指针
		* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		const wchar_t* aa = NULL;
		for (int i = 0; !m_pRecordset->adoEOF; i++)
		{
			/*未解决多条数据的保存*/
			aa = m_pRecordset->GetCollect((LPCTSTR)muBiaoziDuan).bstrVal;//返回字符串
			m_pRecordset->MoveNext();
		}
		if (aa==NULL)
		{
// 			shuzu[0] = '\0';
// 			shuzu[1] = '\0';
			return FALSE;
		}
		wcscpy_s(shuzu, sizeof(aa), aa);//接收的数组指针,长度,要复制的数组指针
		return TRUE;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("搜索失败！"));
		printf("\nBOOL getShuJu 错误代码: %s\n", e.ErrorMessage());
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

unsigned int ACCSCC::getShuJuRQ(CString biao, CString ziDuan, CString shuJu, CString muBiaoziDuan)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	unsigned int sj = 0;
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		//L"SELECT 要查询的字段,要查询的字段 FROM 表 WHERE 定位的字段 = '定位的值'"
		search_sql.Format(L"SELECT %s,%s FROM %s WHERE %s = '%s'", muBiaoziDuan, ziDuan, biao, ziDuan, shuJu);
		//search_sql.Format(L"SELECT %s FROM %s", muBiaoziDuan, biao, muBiaoziDuan, shuJu);
		/*函数: Execute
		* 作用:操作数据库
		* 参数1:sql语句
		* 参数2:转换后的指针
		* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		for (int i = 0; !m_pRecordset->adoEOF; i++)
		{
			sj = m_pRecordset->GetCollect((LPCTSTR)muBiaoziDuan).uintVal;//获取整数
			m_pRecordset->MoveNext();
		}
		return sj;
	}
	catch (_com_error e)
	{
		printf("\nBOOL getShuJu 错误代码: %s\n", e.ErrorMessage());
		lianJieKaiGuan = FALSE;
		return sj;
	}
}

void ACCSCC::bianLiMoKuai()
{/*需要 #include <TlHelp32.h>//获取进程列表*/
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//获取进程快照;TH32CS_SNAPPROCESS 在快照中包括系统中的所有进程。
	if (hSnap == INVALID_HANDLE_VALUE)//如果失败
	{
		return;
	}

	PROCESSENTRY32 pe{ sizeof(pe) };//结构体,并初始化结构体大小


	BOOL BMORE = Process32First(hSnap, &pe);//获得第一个进程
	
	//QueryFullProcessImageNameA
	BMORE = Process32First(hSnap, &pe);//获得第一个进程
	while (BMORE)
	{
		//pe.th32ProcessID //PID
		CString txt;
		txt.Format(L"%d", pe.th32ProcessID);//获得PID

		//pid[ci] =(int*)pe.th32ParentProcessID;
		//pidM[ci] = pe.szExeFile;
		//ProcessLst.InsertItem(0, txt);
		//ProcessLst.SetItemText(0, 1, pe.szExeFile);//获得文件名
		BMORE = Process32Next(hSnap, &pe);//获得下一个进程
		int a = pe.pcPriClassBase;
	}
	CloseHandle(hSnap);//关闭快照
}

UINT sDjC(LPVOID dwPID)
{/*需要 #include <TlHelp32.h>//获取进程列表*/
	//GetCurrentProcessId() //检索调用进程的进程标识符PID
	//操作全局变量时就加锁, 互斥量
	SheZhi szL;
	WaitForSingleObject(szL.hMutex, INFINITE);
	SheZhi::jcCS* js = (SheZhi::jcCS*)dwPID;
	DWORD Pid = js->pid;
	printf("\n     线程数量 %d............ %d    \n", theApp.ci,Pid);
	theApp.ci++;
	//操作完全局变量时就解锁, 互斥量
	ReleaseMutex(szL.hMutex);

	MODULEENTRY32 me32;//使用Module32First函数
	HANDLE hSnap = INVALID_HANDLE_VALUE;//失败
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Pid);//包括快照中PID中指定的进程的所有模块
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
	printf("\n     模块名称:     %S", me32.szModule);//
	mz = me32.szModule;
	printf("\n     模块路径     %S", me32.szExePath);
	lj = me32.szExePath;
	printf("\n     要检查其模块的进程的标识符PID     %d\n", me32.th32ProcessID);
	pid = me32.th32ProcessID;
	CloseHandle(hSnap);//释放快照
	BOOL pd = cmd.chaXunBMD(cmd.mingDanBiao, cmd.bMingDan[0], mz);
	if (0)
	{
		//关闭进程
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
		CloseHandle(killHandle);//关闭句柄
		return 0;
	}
	return 0;
}

DWORD WINAPI jingChengChuLi(void* a)
{
	ACCSCC::jCjingCheng* jc = (ACCSCC::jCjingCheng*)a;
	printf("\n线程pid  %d\n", jc->Pid);
	printf("\n线程exe名字  %S\n", jc->exeMing);
	printf("\n线程exepath  %S\n", jc->exePath);

	//对比exe名是否在数据库白名单
	//对比exe路径是否在数据库白名单
	//如果没有匹配,杀掉进程
	BOOL pd = cmd.chaXunBMD(cmd.mingDanBiao, cmd.bMingDan[0], jc->exePath);
	if (0)
	{
		//关闭进程
		HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION |   // Required by Alpha
			PROCESS_CREATE_THREAD |   // For CreateRemoteThread
			PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
			PROCESS_VM_WRITE,             // For WriteProcessMemory);
			FALSE, jc->Pid);
		if (killHandle == NULL)
		{
			delete a;//释放内存
			a = NULL;
			return FALSE;
		}
		TerminateProcess(killHandle, 0);
		CloseHandle(killHandle);//关闭句柄
		return TRUE;
	}
	delete a;//释放内存
	a = NULL;
	printf("\n     xianc1............     \n");
	return FALSE;
}

DWORD __stdcall sDjingCheng(LPVOID dwPID)//LPVOID无类型,
{/*需要 #include <TlHelp32.h>//获取进程列表*/
	//GetCurrentProcessId() //检索调用进程的进程标识符PID
	DWORD Pid = *((DWORD*)dwPID);//强制转换
	printf("\n     xianc1............ %d    \n",Pid);
	MODULEENTRY32 me32;//使用Module32First函数
	HANDLE hSnap = INVALID_HANDLE_VALUE;//失败
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Pid);//包括快照中PID中指定的进程的所有模块
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
	printf("\n     模块名称:     %S", me32.szModule);//
	mz = me32.szModule;
	printf("\n     模块路径     %S", me32.szExePath);
	lj = me32.szExePath;
	printf("\n     要检查其模块的进程的标识符PID     %d\n", me32.th32ProcessID);
	pid = me32.th32ProcessID;
	CloseHandle(hSnap);//释放快照
	BOOL pd = cmd.chaXunBMD(cmd.mingDanBiao, cmd.bMingDan[0], mz);
	if (0)
	{
		//关闭进程
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
		CloseHandle(killHandle);//关闭句柄
		return 0;
	}
	return 0;
}



void ACCSCC::bianLiJinCheng(DWORD dwPID)
{/*需要 #include <TlHelp32.h>//获取进程列表*/
	//GetCurrentProcessId() //检索调用进程的进程标识符PID
	MODULEENTRY32 me32;//使用Module32First函数
	HANDLE hSnap = INVALID_HANDLE_VALUE;//失败
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);//包括快照中PID中指定的进程的所有模块
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
		printf("\n     模块名称:     %S", me32.szModule);//
		jc->exeMing = me32.szModule;
		printf("\n     模块路径     %S", me32.szExePath);
		jc->exePath = me32.szExePath;
		printf("\n     要检查其模块的进程的标识符PID     %d", me32.th32ProcessID);
		jc->Pid = me32.th32ProcessID;
		CloseHandle(hSnap);//释放快照
		HANDLE jcTherad = CreateThread(NULL, 0, jingChengChuLi, jc, 0, NULL);//新建线程
		//printf("\n     进程上下文中模块的基地址   = 0x%08X", (DWORD)me32.modBaseAddr);
		//printf("\n     模块的大小      = %d", me32.modBaseSize);
		//printf("\n     进程上下文中模块的句柄      = %d\n", me32.modBaseSize);
		//BMORE = Module32Next(hSnap, &me32);
	//} 
}

BOOL ACCSCC::zegJia(CString biao)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT * FROM %s",  biao);
		/*函数: Execute
		* 作用:操作数据库
		* 参数1:sql语句
		* 参数2:转换后的指针
		* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		CString id;
		if (m_pRecordset->adoEOF)//如果没找到任何数据(空字段),记录集指针指向最后一条记录之后
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
		//AfxMessageBox(_T("搜索失败！"));
		printf("搜索失败 int！\n");
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
}

BOOL ACCSCC::huoQuJinChengLieBiao(CString biao, BOOL s)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	if (s)
	{
		shanChu(biao);//清空表
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
	CString search_sql;
	search_sql.Format(L"SELECT   *   FROM   %s", biao);
	m_pRecordset->Open((LPCTSTR)search_sql, _variant_t((IDispatch*)m_pConnection, true), 
		adOpenStatic, adLockOptimistic, adCmdText);
	int ci = 1;
	try
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//获取进程快照
		if (hSnap == INVALID_HANDLE_VALUE)//如果失败
		{
			return 0;
		}
		PROCESSENTRY32 pe{ sizeof(pe) };//结构体,并初始化结构体大小
		BOOL BMORE = Process32First(hSnap, &pe);//获得第一个进程
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
			//txt.Format(L"%d", pe.th32ProcessID);//获得PID
			//ProcessLst.SetItemText(0, 1, pe.szExeFile);//获得文件名
			BMORE = Process32Next(hSnap, &pe);//获得下一个进程
			ci++;
		}
		CloseHandle(hSnap);//释放快照
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("搜索失败！"));
		printf("错误: huoQuJinChengLieBiao(CString biao)！ 错误代码:%s\n",e.ErrorMessage());
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
		cmd.lianJieAccscc();//打开数据库
	}
	if (s)
	{
		shanChu(biao);//清空表
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
	CString search_sql;
	search_sql.Format(L"SELECT   *   FROM   %s", biao);
	m_pRecordset->Open((LPCTSTR)search_sql, _variant_t((IDispatch*)m_pConnection, true), 
		adOpenStatic, adLockOptimistic, adCmdText);
	int ci = 1;
	try
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//获取进程快照
		if (hSnap == INVALID_HANDLE_VALUE)//如果失败
		{
			return 0;
		}
		PROCESSENTRY32 pe{ sizeof(pe) };//结构体,并初始化结构体大小
		BOOL BMORE = Process32First(hSnap, &pe);//获得第一个进程
		CString a;
		//SheZhi* lb = (SheZhi*)AfxGetMainWnd();
		while (BMORE)
		{
			m_pRecordset->AddNew();
			//m_pRecordset->PutCollect((LPCTSTR)jinCheng2[0], _variant_t((long)ci));
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[0], ci);
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[1], pe.th32ProcessID);

			a.Format(L"%d", pe.th32ProcessID);//获得PID
			lb->ProcessLst.InsertItem(0, a);
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[2], pe.cntThreads);
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[3], pe.th32ParentProcessID);

			a.Format(L"%d", pe.th32ParentProcessID);//获得PID
			lb->ProcessLst.SetItemText(0, 2, a);//获得文件名
			m_pRecordset->PutCollect((LPCTSTR)jinCheng2[5], _variant_t(pe.szExeFile));

			lb->ProcessLst.SetItemText(0, 1, pe.szExeFile);//获得文件名
			m_pRecordset->Update();
			//txt.Format(L"%d", pe.th32ProcessID);//获得PID
			//ProcessLst.SetItemText(0, 1, pe.szExeFile);//获得文件名
			BMORE = Process32Next(hSnap, &pe);//获得下一个进程
			ci++;
			if (ci==234)
			{
				int d = 3;
			}
		}
		lb->DoModal();//显示列表
		return TRUE;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("搜索失败！"));
		printf("错误: huoQuJinChengLieBiao(CString biao)！ 错误代码:%s\n",e.ErrorMessage());
		lianJieKaiGuan = FALSE;
		return FALSE;
	}
	
	return 0;
}

wchar_t** ACCSCC::huoQuJinChengLieBiao(int** a)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//获取进程快照
	if (hSnap == INVALID_HANDLE_VALUE)//如果失败
	{
		return 0;
	}

	PROCESSENTRY32 pe{ sizeof(pe) };//结构体,并初始化结构体大小


	BOOL BMORE = Process32First(hSnap, &pe);//获得第一个进程
	int i = 0;
	for (; BMORE; i++)//检测有多少进程
	{
		i++;
		BMORE = Process32Next(hSnap, &pe);//获得下一个进程
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
	pidM[0][1] = cc << 16;//低位
	pidM[0][2] = cc >> 16;//高位
	pidM[0][3] = (int)&b;
	
	//QueryFullProcessImageNameA
	BMORE = Process32First(hSnap, &pe);//获得第一个进程
	int ci = 0;
	int ci2 = 1;
	while (BMORE)
	{
		//pe.th32ProcessID //PID
		CString txt;
		txt.Format(L"%d", pe.th32ProcessID);//获得PID

		b[ci] = (int*)pe.th32ProcessID;
		pidM[ci2] = pe.szExeFile;
		//ProcessLst.InsertItem(0, txt);
		//ProcessLst.SetItemText(0, 1, pe.szExeFile);//获得文件名
		BMORE = Process32Next(hSnap, &pe);//获得下一个进程
		ci++;
		ci2++;
	}
	return pidM;
}


void ACCSCC::quChongAccScc(CString ba, CString bb, CString zda, CString zdb)
{
	if (FALSE == lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	CString search_sql;
	try
	{
		_variant_t RecordsAffected;
		m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		//CString a = L"xxx";
		//search_sql = "SELECT * FROM cmdchoose";
		//search_sql.Format(L"SELECT * FROM cmdchoose WHERE id = '%s'", a);
		search_sql.Format(L"SELECT %s FROM %s,%s groub by %s", zda, ba, bb,zda);
		/*函数: Execute
		* 作用:操作数据库
		* 参数1:sql语句
		* 参数2:转换后的指针
		* 参数3:如果第一个参数是sql语句则选择adCmdText,如果第一个参数是表名则选择adCmdTable
		*/
		m_pRecordset = m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		int id;
		CString iid;
		while (!m_pRecordset->adoEOF)
		{
			id = m_pRecordset->GetCollect((LPCTSTR)zda).uintVal;//获取整数
			iid.Format(L"%d", id);
			theApp.sheZhiL.ProcessLst.InsertItem(0, iid);
			m_pRecordset->MoveNext();
		}
		theApp.sheZhiL.DoModal();
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("搜索失败！"));
		printf("错误: huoQuJinChengLieBiao(CString biao)！ 错误代码:%s\n", e.ErrorMessage());
		lianJieKaiGuan = FALSE;
	}
}

BOOL ACCSCC::shaSiJinCheng(DWORD pid)
{
	//关闭进程
	HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION |   // Required by Alpha
		PROCESS_CREATE_THREAD |   // For CreateRemoteThread
		PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
		PROCESS_VM_WRITE,             // For WriteProcessMemory);
		FALSE, pid);
	if (killHandle == NULL)
		return false;
	TerminateProcess(killHandle, 0);//杀死进程
	CloseHandle(killHandle);//关闭句柄
	return true;
}

BOOL ACCSCC::qiDongJinCheng(CString exePath)
{
	TCHAR tszProcess[260] = { 0 };
	lstrcpy(tszProcess, exePath);
	//启动程序配置
	SHELLEXECUTEINFO shellInfo;
	memset(&shellInfo, 0, sizeof(SHELLEXECUTEINFO));
	shellInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	shellInfo.fMask = NULL;
	shellInfo.hwnd = NULL;
	shellInfo.lpVerb = NULL;
	shellInfo.lpFile = tszProcess;                      // 执行的程序名(绝对路径)
	shellInfo.lpParameters = NULL;
	shellInfo.lpDirectory = NULL;
	shellInfo.nShow = SW_MINIMIZE;                      //SW_SHOWNORMAL 全屏显示这个程序
	shellInfo.hInstApp = NULL;

	ShellExecuteEx(&shellInfo);//启动

	return true;
}
