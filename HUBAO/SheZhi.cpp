// SheZhi.cpp: 实现文件
//

#include "pch.h"
#include "HUBAO.h"
#include "SheZhi.h"
#include "afxdialogex.h"

#include <TlHelp32.h>//获取进程列表

#include <fstream>  //读取文件
#include <wincrypt.h>//加密
// SheZhi 对话框

IMPLEMENT_DYNAMIC(SheZhi, CDialogEx)

SheZhi::SheZhi(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHEZHI, pParent)
	, shuliangB(_T(""))
{

}

SheZhi::~SheZhi()
{
}

void SheZhi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ProcessLst);
	DDX_Text(pDX, IDC_EDIT1, shuliangB);
}


BEGIN_MESSAGE_MAP(SheZhi, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &SheZhi::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDOK, &SheZhi::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &SheZhi::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK3, &SheZhi::OnBnClickedOk3)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &SheZhi::OnNMDblclkList1)
	ON_BN_CLICKED(IDOK4, &SheZhi::OnBnClickedOk4)
	ON_BN_CLICKED(IDOK5, &SheZhi::OnBnClickedOk5)
	ON_BN_CLICKED(IDOK6, &SheZhi::OnBnClickedOk6)
END_MESSAGE_MAP()


// SheZhi 消息处理程序

BOOL SheZhi::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*初始化*/
	/*设置列表*/
	LONG_PTR IStyle;
	IStyle = GetWindowLongPtr(ProcessLst.m_hWnd, GWL_STYLE);//ProcessLst.m_hWnd为控件句柄
	IStyle |= LVS_REPORT;
	SetWindowLongPtr(ProcessLst.m_hWnd, GWL_STYLE, IStyle);
	DWORD dStyle = ProcessLst.GetExtendedStyle();
	dStyle |= LVS_EX_FULLROWSELECT;
	dStyle |= LVS_EX_GRIDLINES;
	ProcessLst.SetExtendedStyle(dStyle);
	/*设置列表内容*/
	ProcessLst.InsertColumn(0, L"PID", 0, 50);//添加列
	ProcessLst.InsertColumn(1, L"exe名", 0, 60);
	ProcessLst.InsertColumn(2, L"父进程", 0, 60);
	ProcessLst.InsertColumn(3, L"进程标识", 0, 60);
	ProcessLst.InsertColumn(4, L"模块基地址", 0, 80);
	ProcessLst.InsertColumn(5, L"模块名称", 0, 60);
	ProcessLst.InsertColumn(6, L"模块路径", 0, 200);

	return TRUE;
}

//列表双击事件
void SheZhi::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	NM_LISTVIEW* View = (NM_LISTVIEW*)pNMHDR; //NM_LISTVIEW*就是NMHDR* 指针
	if (View->iItem != 1)
	{
		CString wPid = ProcessLst.GetItemText(View->iItem, 0);//得到PID
		//CString wExe = ProcessLst.GetItemText(View->iItem, 1);//得到文件名
		/*参数:wchar_t指针, 默认转换失败返回0 , 10进制*/
		DWORD dPid = wcstoul(wPid.GetBuffer(), 0, 10);//字符串转换为DWORD类型(整数)
		chaKanPidMoKuai(dPid);
	}
	//OnCancel();//退出页面

}

void SheZhi::chaKanPidMoKuai(DWORD pid)
{/*需要 #include <TlHelp32.h>//获取进程列表*/
	//GetCurrentProcessId() //检索调用进程的进程标识符PID
	MODULEENTRY32 me32;//使用Module32First函数
	HANDLE hSnap = INVALID_HANDLE_VALUE;//失败
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);//包括快照中PID中指定的进程的所有模块
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		return;
	}
	me32.dwSize = sizeof(MODULEENTRY32);
	BOOL BMORE = Module32First(hSnap, &me32);
	printf("\n\n     模块名称:     %S", me32.szModule);//
	printf("\n\n     模块路径     %S", me32.szExePath);
	printf("\n\n     要检查其模块的进程的标识符PID     %d", me32.th32ProcessID);
	CloseHandle(hSnap);//释放快照
}

/*列表*/
void SheZhi::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}




/*表1与表2不相同的字段数据,返回的是表1现有的数据中查找出来的不相同的结果*/
void SheZhi::quChong(CString biao1, CString b1ziDuan, CString biao2, CString biao2ziduan)
{
	ProcessLst.DeleteAllItems();//清空列表内容
	if (FALSE == cmd.lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		cmd.m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		/*比较2张表的字段中不一样的数据*/
		//search_sql.Format(L"select distinct jinCheng.th32ParentProcessID from  jinCheng where jinCheng.th32ParentProcessID not in (select th32ParentProcessID from jinCheng1)");
		//search_sql.Format(L"select jinCheng.th32ParentProcessID from jinCheng left join jinCheng1 on jinCheng.th32ParentProcessID=jinCheng1.th32ParentProcessID where jinCheng1.th32ParentProcessID is null");//去重
		search_sql.Format(L"select distinct %s.%s from  %s where %s.%s not in (select %s from %s)",
			biao1, b1ziDuan, biao1, biao1, b1ziDuan, biao2ziduan, biao2);
		cmd.m_pRecordset = cmd.m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		CString a;
		int sj = 0;
		while (!cmd.m_pRecordset->adoEOF)
		{
			sj = cmd.m_pRecordset->GetCollect((LPCTSTR)theApp.jinCheng2[3]).uintVal;//获取整数
			a.Format(L"%d", sj);//获得PID
			ProcessLst.InsertItem(0, a);

			cmd.m_pRecordset->MoveNext();

	
		}
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("搜索失败！"));
		printf("错误: huoQuJinChengLieBiao(CString biao)！ 错误代码:%s\n", e.ErrorMessage());
		cmd.lianJieKaiGuan = FALSE;
	}
}

void SheZhi::biJiao()
{
	jcCS jjcc;
	int sz[50] = { 0 };
	int* aa = &sz[0];//指针操作数组
	int ci = 0;
	ProcessLst.DeleteAllItems();//清空列表内容
	if (FALSE == cmd.lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		cmd.m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		/*比较2张表的字段中不一样的数据*/
		//search_sql.Format(L"select distinct jinCheng.th32ParentProcessID from  jinCheng where jinCheng.th32ParentProcessID not in (select th32ParentProcessID from jinCheng1)");
		//search_sql.Format(L"select jinCheng.th32ParentProcessID from jinCheng left join jinCheng1 on jinCheng.th32ParentProcessID=jinCheng1.th32ParentProcessID where jinCheng1.th32ParentProcessID is null");//去重
		//search_sql.Format(L"select distinct %s.%s from  %s where %s.%s not in (select %s from %s)",theApp.jinChengBiao, theApp.jinCheng2[1], theApp.jinChengBiao, theApp.jinChengBiao, theApp.jinCheng2[1], theApp.jinCheng2[1], theApp.jinCheng1Biao);
// 		search_sql.Format(L"select distinct jinCheng.th32ProcessID ,jinCheng.th32ParentProcessID from  jinCheng where \
//           jinCheng.th32ProcessID not in (select th32ProcessID from jinCheng1) \
//           order by jinCheng.th32ProcessID desc");//asc/desc
		//L"select distinct jinCheng.th32ProcessID from  jinCheng where jinCheng.th32ProcessID not in (select th32ProcessID from jinCheng1)"
		search_sql.Format(L"select distinct jinCheng1.th32ProcessID from  jinCheng1 where \
          jinCheng1.th32ProcessID not in (select th32ProcessID from jinCheng) \
           order by jinCheng1.th32ProcessID desc");//asc/desc
		cmd.m_pRecordset = cmd.m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		CString a;
		int sj = 0;
		while (!cmd.m_pRecordset->adoEOF)
		{
			sj = cmd.m_pRecordset->GetCollect((LPCTSTR)theApp.jinCheng2[1]).uintVal;//获取整数
			printf("PID %d\n", sj);
			a.Format(L"%d", sj);//获得PID
			//cmd.bianLiJinCheng((DWORD)sj);
			
			//操作全局变量时就加锁, 互斥量
			WaitForSingleObject(hMutex, INFINITE);
			jjcc.pid = sj;
			aa[ci] = sj;
			ci++;
			//操作完全局变量时就解锁, 互斥量
			ReleaseMutex(hMutex);

			ProcessLst.InsertItem(0, a);
			cmd.m_pRecordset->MoveNext();
			//CreateThread(NULL, 0, sDjingCheng, &sj, 0, NULL);//新建线程
			//AfxBeginThread(sDjC, &jjcc);
			//Sleep(10);
		}
		//Sleep(100);
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("搜索失败！"));
		printf("错误:biJiao()！ 错误代码:%s\n", e.ErrorMessage());
		cmd.lianJieKaiGuan = FALSE;
	}
	int sj = 0;
	while (sj < ci)
	{
		jjcc.pid = sz[sj];
		AfxBeginThread(sDjC, &jjcc);//新建线程
		Sleep(120);
		sj++;
	}
	theApp.ci = 1;
}

void SheZhi::biJiao1()
{
	ProcessLst.DeleteAllItems();//清空列表内容
	if (FALSE == cmd.lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	try
	{
		cmd.m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
		CString search_sql;
		/*比较2张表的字段中不一样的数据*/
		//search_sql.Format(L"select distinct jinCheng.th32ParentProcessID from  jinCheng where jinCheng.th32ParentProcessID not in (select th32ParentProcessID from jinCheng1)");
		//search_sql.Format(L"select jinCheng.th32ParentProcessID from jinCheng left join jinCheng1 on jinCheng.th32ParentProcessID=jinCheng1.th32ParentProcessID where jinCheng1.th32ParentProcessID is null");//去重
		//search_sql.Format(L"select distinct %s.%s from  %s where %s.%s not in (select %s from %s)",theApp.jinChengBiao, theApp.jinCheng2[1], theApp.jinChengBiao, theApp.jinChengBiao, theApp.jinCheng2[1], theApp.jinCheng2[1], theApp.jinCheng1Biao);
// 		search_sql.Format(L"select distinct jinCheng.th32ProcessID ,jinCheng.th32ParentProcessID from  jinCheng where \
//           jinCheng.th32ProcessID not in (select th32ProcessID from jinCheng1) \
//           order by jinCheng.th32ProcessID desc");//asc/desc
		//L"select distinct jinCheng.th32ProcessID from  jinCheng where jinCheng.th32ProcessID not in (select th32ProcessID from jinCheng1)"
		search_sql.Format(L"select distinct jinCheng1.th32ProcessID ,jinCheng1.th32ParentProcessID from  jinCheng1 where \
          jinCheng1.th32ProcessID not in (select th32ProcessID from jinCheng) \
           order by jinCheng1.th32ProcessID desc");//asc/desc
		cmd.m_pRecordset = cmd.m_pConnection->Execute(search_sql.AllocSysString(), NULL, adCmdText);
		CString a;
		int sj = 0;
		int sjj = 0;
		int icount = ProcessLst.GetItemCount();//获取当前列表行数
		while (!cmd.m_pRecordset->adoEOF)
		{
			sj = cmd.m_pRecordset->GetCollect((LPCTSTR)theApp.jinCheng2[1]).uintVal;//获取整数
			sjj = cmd.m_pRecordset->GetCollect((LPCTSTR)theApp.jinCheng2[3]).uintVal;//获取整数
			printf("新的 PID: %d\n", sj);
			a.Format(L"%d", sj);//获得PID
			//cmd.bianLiJinCheng(sj);
			ProcessLst.InsertItem(icount, a);
			ProcessLst.SetItemText(icount, 3, a);//获得文件名
			a.Format(L"%d", sjj);//获得PID
			ProcessLst.SetItemText(icount, 4, a);//获得文件名
			cmd.m_pRecordset->MoveNext();
			icount++;

		}
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("搜索失败！"));
		printf("错误: huoQuJinChengLieBiao(CString biao)！ 错误代码:%s\n", e.ErrorMessage());
		cmd.lianJieKaiGuan = FALSE;
	}
}

void SheZhi::xianShi(CString biao, BOOL a)
{
	ProcessLst.DeleteAllItems();//清空列表内容
	if (FALSE == cmd.lianJieKaiGuan)
	{
		cmd.lianJieAccscc();//打开数据库
	}
	if (a)
	{
		cmd.shanChu(biao);//清空表
	}
	cmd.m_pRecordset.CreateInstance(__uuidof(Recordset));//创建实例
	CString search_sql;
	search_sql.Format(L"SELECT   *   FROM   %s", biao);
	//search_sql.Format(L"SELECT   *   FROM   %s order by th32ProcessID desc", biao);
	cmd.m_pRecordset->Open((LPCTSTR)search_sql, _variant_t((IDispatch*)cmd.m_pConnection, true),
		adOpenStatic, adLockOptimistic, adCmdText);
	int ci = 1;
	try
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//获取进程快照
		if (hSnap == INVALID_HANDLE_VALUE)//如果失败
		{
			return ;
		}
		PROCESSENTRY32 pe{ sizeof(pe) };//结构体,并初始化结构体大小
		BOOL BMORE = Process32First(hSnap, &pe);//获得第一个进程
		CString a;
		while (BMORE)
		{
			cmd.m_pRecordset->AddNew();
			//m_pRecordset->PutCollect((LPCTSTR)jinCheng2[0], _variant_t((long)ci));
			cmd.m_pRecordset->PutCollect((LPCTSTR)cmd.jinCheng2[0], ci);
			cmd.m_pRecordset->PutCollect((LPCTSTR)cmd.jinCheng2[1], pe.th32ProcessID);

			a.Format(L"%d", pe.th32ProcessID);//获得PID
			ProcessLst.InsertItem(0, a);
			cmd.m_pRecordset->PutCollect((LPCTSTR)cmd.jinCheng2[2], pe.cntThreads);
			cmd.m_pRecordset->PutCollect((LPCTSTR)cmd.jinCheng2[3], pe.th32ParentProcessID);

			a.Format(L"%d", pe.th32ParentProcessID);//获得PID
			ProcessLst.SetItemText(0, 2, a);//获得文件名
			cmd.m_pRecordset->PutCollect((LPCTSTR)cmd.jinCheng2[5], _variant_t(pe.szExeFile));

			ProcessLst.SetItemText(0, 1, pe.szExeFile);//获得文件名
			cmd.m_pRecordset->Update();
			//txt.Format(L"%d", pe.th32ProcessID);//获得PID
			//ProcessLst.SetItemText(0, 1, pe.szExeFile);//获得文件名
			BMORE = Process32Next(hSnap, &pe);//获得下一个进程
			ci++;
		}
		CloseHandle(hSnap);//释放快照
		a.Format(L"%d", ci);
		shuliangB = a;
		UpdateData(FALSE);
	}
	catch (_com_error e)
	{
		//AfxMessageBox(_T("搜索失败！"));
		printf("错误: huoQuJinChengLieBiao(CString biao)！ 错误代码:%s\n", e.ErrorMessage());
		cmd.lianJieKaiGuan = FALSE;
	}
}




void SheZhi::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//cmd.huoQuJinChengLieBiao_lieBiao(theApp.jinCheng1Biao,this, TRUE);
	xianShi(theApp.jinCheng1Biao,TRUE);
	//biJiao1();
}
void SheZhi::OnBnClickedOk2()
{
	//cmd.huoQuJinChengLieBiao_lieBiao(theApp.jinCheng1Biao, this, TRUE);
	//quChong(theApp.jinCheng1Biao,L"dhfhhf");
	biJiao();
	//cmd.shanChu(theApp.jinChengBiao);
	//cmd.shanChu(theApp.jinCheng1Biao);
}

void SheZhi::OnBnClickedOk3()
{
	xianShi(theApp.jinChengBiao,TRUE);
}




//修改链接设置，使运行时不出现命令行窗口
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  

/*标识要使用的哈希算法的ALG_ID值,返回的哈希值,传入的值*/
BOOL SheZhi::GetHash(int hash_type, CString& hash_result, CString hash_message)
{
	HCRYPTPROV hCryptProv;

	HCRYPTHASH hCryptHash;

	if (!CryptAcquireContext(&hCryptProv, NULL, MS_DEF_PROV,

		PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))

	{
		int e = GetLastError();

		CString str;

		str.Format(L"创建CSP容器出错！错误代码为:%d！",

			e);

		MessageBox(str, L"出错啦!",

			MB_OK | MB_ICONERROR);

		return false;

	}

	if (!CryptCreateHash(hCryptProv, hash_type, 0, 0,

		&hCryptHash))

	{
		int e = GetLastError();

		CString str;

		str.Format(L"创建哈希句柄出错！错误代码为:%d！",

			e);

		MessageBox(str, L"出错啦!",

			MB_OK | MB_ICONERROR);

		return false;

	}

	if (!CryptHashData(hCryptHash, (BYTE*)hash_message.GetBuffer(), hash_message.GetLength(), 0))

	{
		int e = GetLastError();

		CString str;

		str.Format(L"计算哈希值出错！错误代码为:%d！",

			e);

		MessageBox(str, L"出错啦!",

			MB_OK | MB_ICONERROR);

		return false;

	}

	char hash_data[512];

	DWORD hash_len = 512;

	if (!CryptGetHashParam(hCryptHash, HP_HASHVAL, (BYTE*)hash_data,

		&hash_len, 0))

	{
		int e = GetLastError();

		CString str;

		str.Format(L"获取哈希值出错！错误代码为:%d！",

			e);

		MessageBox(str, L"出错啦!",

			MB_OK | MB_ICONERROR);

		return false;

	}

	char hash_hex[512];
	int hash_bit;
	int first;
	int second;
	char tmp[2];
	/*32位哈希为例，如果直接以字符串形式或者%x输出都会有问题。因为是4bit对应一个Hex码，所以要进行一下转换*/
	for (int i = 0; i <= hash_len - 1; i++)

	{
		hash_bit = hash_data[i];

		first = (hash_bit & 0xf0) >> 4;//取前4位

		second = hash_bit & 0x0f;//取后4位

		_itoa_s(first, tmp, 16);//将整数转为字符

		hash_hex[i * 2] = tmp[0];//乘2是因为要把前4位放在前面,也就是从0开始双数的位置

		_itoa_s(second, tmp, 16);

		hash_hex[i * 2 + 1] = tmp[0];//这里+1是要把数据放在单数位置

	}

	hash_hex[hash_len * 2] = '\0';
	hash_result = (CString)hash_hex;
	//hash_result.Format(L"%s", hash_hex);
	//hash_result.Format(L"aaaaaaaaaaaaaaaaaaaaaaaaaa");

	CryptDestroyHash(hCryptHash);

	CryptReleaseContext(hCryptProv, NULL);

	return true;
}

void SheZhi::teZhenMa(CString ptahb, CString& fanHui)
{
	const wchar_t* filename;
	filename = ptahb.GetBuffer();//将CString转换为const wchar_t*
	/*读取硬盘里的文件到内存里*/
	std::ifstream streamReader(filename, std::ios::binary);//以二进制方式读取文件
	streamReader.seekg(0, std::ios::end);//将读取文件的指针,跳到尾部
	unsigned filesize = streamReader.tellg();//得到需要读取文件从头部到尾部的大小
	//char* _data = new char[filesize];//分配内存
	char* _data = new char[0x500];//分配内存,因为PE头文件在模块的最前面,而PE头不大.0x500足够
	streamReader.seekg(0, std::ios::beg);//将读取文件的指针,跳到开始
	//streamReader.read(_data, filesize);//读取文件到内存
	streamReader.read(_data, 0x500);//读取文件到内存
	streamReader.close();//关闭打开的文件
	/*分析文件,DOS头*/
	dosHeader = (IMAGE_DOS_HEADER*)_data; //定义DOS部分,DOS共0x40=64字节
	if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		AfxMessageBox(L"这不是DOS文件!!");
		return;
	}
	//dosHeader->e_lfanew就是DOS头里指向PE头的偏移
	unsigned PEAddress = dosHeader->e_lfanew + (unsigned)_data;//得到PE头地址,DOS->LONG e_lfanew + dos头地址(exe文件起始地址)
	/*PE头*/
	ntHeader = (IMAGE_NT_HEADERS*)PEAddress;//定义PE部分指针,PE总大小F8h
	if (ntHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		AfxMessageBox(L"这不是PE文件!!");
		return;
	}
	WORD NumberOfSections = ntHeader->FileHeader.NumberOfSections;//得到PE文件中区块数量,返回几个就有几个节表
	unsigned qkTable = PEAddress + sizeof(IMAGE_NT_HEADERS);//第1个节表地址
	BYTE jBming[9] = { 0 };
	int jieLen = 0;
	CString as1;
	CString as2;
	DWORD VirtualSize;//节表没有对齐前的真实尺寸,可改,不一定准确
	DWORD SizeOfRawData;//在磁盘中对齐后的大小
	for (int i = 0; i < NumberOfSections; i++)
	{
		BYTE* ls = (BYTE*)qkTable + jieLen;
		for (int i = 0; i < 8; i++)
		{
			jBming[i] = ls[i];
			if (jBming[i] == 0)
			{
				break;
			}
		}
		as2 = (CString)jBming;
		as1 += as2;

		sectION_HEADER = (IMAGE_SECTION_HEADER*)(qkTable + jieLen);//区块表指针,1个区块大小28h
		VirtualSize = sectION_HEADER->Misc.VirtualSize;//节表没有对齐前的真实尺寸,可改,不一定准确
		SizeOfRawData = sectION_HEADER->SizeOfRawData;//节表在磁盘上的大小
		VirtualSize += SizeOfRawData;
		as2.Format(_T("|%u|"), VirtualSize);
		as1 += as2;
		jieLen += 40;
	}

	GetHash(CALG_MD5, fanHui, as1);
}

void SheZhi::OnBnClickedOk4()
{
	TCHAR  FileModule[0x100]{};//保存程序自身路径缓冲区
	GetModuleFileName(NULL, FileModule, 0x100);
	/*计算字符串长度*/
	int ii = 0;
	for (int i = 0x100 - 1; FileModule[i] != L'\\'; i--)//字符串从后到前比较,如果不为'\\'就将它赋值为0,为'\\'时循环终止
	{
		FileModule[i] = 0;
		ii++;
	}
	CString lj;
	lj.Format(L"%sHOOKdLL.dll", FileModule);
	// TODO: 在此添加控件通知处理程序代码
	//加载dll,检测是多少位的系统
#if defined _M_X64
	HINSTANCE hInstLibrary = LoadLibrary(_T("HOOKdLL.dll"));
#elif defined _M_IX86
	HINSTANCE hInstLibrary = LoadLibrary(lj);
	//HINSTANCE hInstLibrary = AfxLoadLibrary(TEXT("dll_hook.dll"));
#endif
	//HINSTANCE hInstLibrary = LoadLibrary(lj);
	//SetDllDirectory
	//HINSTANCE hInstLibrary = LoadLibraryEx(lj,NULL, LOAD_WITH_ALTERED_SEARCH_PATH);//从DLL位置搜索DLL依赖
	if (hInstLibrary == NULL)
	{
		printf("dll加载失败\n");
		printf("错误代码 : %d\n", GetLastError());
		FreeLibrary(hInstLibrary);//释放加载的动态链接库 (DLL) 模块
		return;
	}
	else
	{
		printf("dll加载成功\n");
		ah a = (ah)GetProcAddress(hInstLibrary, "ava");
		if (a)
		{
			//MessageBox(NULL, L"OnTimeProtectON函数调用失败！", L"错误", MB_ICONERROR);
			printf("函数加载成功\n");
			int b = a(1, 7);//调用DLL函数
			printf("调用DLL函数,返回的结果为%d \n",b);
		}

		kaiShi b = (kaiShi)(GetProcAddress(hInstLibrary, "ActiveDefenseON"));
		//kaiShi a = (kaiShi)(GetProcAddress(hInstLibrary, "ActiveDefenseOFF"));
		if (b)
		{
			printf("ActiveDefenseON 函数加载成功\n");
			BOOL dizhi = b();
			if (dizhi==FALSE)
			{
				//MessageBox(NULL, L"OnTimeProtectON函数调用失败！", L"错误", MB_ICONERROR);
				printf("调用ActiveDefenseON函数失败 错误代码: %d \n", GetLastError());
				return;
			}
			
		}
		else
		{
			printf("获取ActiveDefenseON函数地址失败 错误代码: %d \n", GetLastError());
		}
	}

}


void SheZhi::OnBnClickedOk5()
{
	//加载dll
#if defined _M_X64
	HINSTANCE hInstLibrary = LoadLibrary(TEXT("HOOKdLL.dll"));
#elif defined _M_IX86
	HINSTANCE hInstLibrary = LoadLibrary(_T("HOOKdLL.dll"));
#endif

	if (hInstLibrary == NULL)
	{
		printf("DLL加载失败 错误代码 : %d\n", GetLastError());
		FreeLibrary(hInstLibrary);
		return;
	}
	else {

		//获取API函数地址
		jieSu MyOnTimeProtectOFF = (jieSu)GetProcAddress(hInstLibrary, "ActiveDefenseOFF");
		if (MyOnTimeProtectOFF)
		{
			//停止API HOOK
			bool bHook = MyOnTimeProtectOFF();
			if (bHook = false)
			{
				printf("调用ActiveDefenseOFF函数失败 错误代码: %d \n", GetLastError());
				return;
			}
		}
		else {
			MessageBox(L"获取ActiveDefenseOFF函数地址失败！", NULL, MB_OKCANCEL);//使用MFC函数
			//MessageBox(NULL, NULL, NULL);//使用MFC函数
			//::MessageBoxW(NULL,NULL,NULL,NULL);//使用API
			return;
		}
	}
}


void SheZhi::OnBnClickedOk6()
{
	// TODO: 在此添加控件通知处理程序代码
}
