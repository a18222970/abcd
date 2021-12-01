
// HUBAODlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "HUBAO.h"
#include "HUBAODlg.h"
#include "afxdialogex.h"
/*********************/
#include "TCPfuWu.h"
#include <TlHelp32.h>//获取进程列表


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHUBAODlg 对话框



CHUBAODlg::CHUBAODlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HUBAO_DIALOG, pParent)
	, kongJian1B(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	yanZheng = 0;
	daoQiPanDuan = FALSE;
	dQshiJian = 0;
	jLshiJian = 0;
}

CHUBAODlg::~CHUBAODlg()
{
	//daoQiPanDuan = FALSE;
}

void CHUBAODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, kongJian);
	DDX_Text(pDX, IDC_EDIT1, kongJian1B);
	DDX_Control(pDX, IDCANCEL, ck);
}


void CHUBAODlg::qidong()
{
	if (cmd.chaXunBK(theApp.idBiao, theApp.yongHuId[0]))
	{
		//printf("    ddddddddddddddddddd        ");
		dQshiJian = shiJianL.getDangQianShiJianCuo();//获取当前时间
	    //unsigned sj1 = hBao->shiJianL.setShiJianCuo("2021:12:31 00:00:00");
		wchar_t sj[30]{ 0 };
		if (cmd.getShuJu(theApp.idBiao, theApp.yongHuId[6], sj))//获取数据库中的到期时间
		{
			jLshiJian = _ttoi(sj);
			if (jLshiJian > dQshiJian)//检查是否软件到期
			{
				daoQiPanDuan = TRUE;
				AfxBeginThread(jianCeShiJian, this);
				AfxBeginThread(jianCeChengXu, this);
			}
			else
			{
				//关闭检测线程 处理
				AfxMessageBox(_T("你的软件已经到期!"));
			}
		}
		unsigned a = cmd.getShuJuRQ(theApp.idBiao, theApp.yongHuId[0], L"cx", theApp.yongHuId[7]);
		std::cout << a << "         aaaaaaa\n";
	}
	
}

BOOL CHUBAODlg::yanZhengQiDong()
{
	cmd.bianLiJinCheng(16992);
	theApp.sheZhiL.DoModal();
	//cmd.huoQuJinChengLieBiao(theApp.jinCheng1Biao,TRUE);
	//cmd.quChongAccScc(theApp.jiLuBiao, theApp.jinCheng1Biao, theApp.jinCheng2[3], theApp.jinCheng2[3]);
	/*是否记住密码*/
	int zdok = cmd.chaXun(theApp.idBiao, theApp.yongHuId[5], _T("ok"));
	int zdno = cmd.chaXun(theApp.idBiao, theApp.yongHuId[5], _T("no"));
	//启动程序
	if (zdok == 1)
	{
		yanZheng = 1;
		//qidong();
		return TRUE;
	}
	if (zdno == 1)
	{
		yanZheng = 2;
	}
	return 0;
}

void CHUBAODlg::yinChangChuangKou()
{
	//GetWindowPlacement(&m_struOldWndpl); //恢复时用
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);//从任务栏中去掉.但是进程PID还是可见
	WINDOWPLACEMENT wp;
	wp.length = sizeof(WINDOWPLACEMENT);
	wp.flags = WPF_RESTORETOMAXIMIZED;
	wp.showCmd = SW_HIDE;
	SetWindowPlacement(&wp);
	//SetWindowPos(&wndTop, 0, 0, 0, 0, NULL);  //另一种隐藏方法,不能完全隐藏
}



BEGIN_MESSAGE_MAP(CHUBAODlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHUBAODlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CHUBAODlg::OnBnClickedCancel)
END_MESSAGE_MAP()

    // second message parameter);
// CHUBAODlg 消息处理程序

BOOL CHUBAODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	/************************   获取程序自身根文件夹  开始  **********************************/
	TCHAR  FileModule[0x100]{};//保存程序自身路径缓冲区

	/*函数:GetModuleFileName
	* 作用: 检索包含指定模块的文件的完全限定路径。该模块必须已被当前进程加载。
	* 参数1:正在请求其路径的已加载模块的句柄。如果此参数为NULL，则 GetModuleFileName检索当前进程的可执行文件的路径。
	* 参数2:指向接收模块完全限定路径的缓冲区的指针,用来保存获取到的路径
	* 参数3:缓冲区(保存路径)的大小,以TCHARs 为单位。
	*/
	GetModuleFileName(NULL, FileModule, 0x100);

	/*计算字符串长度*/
	int ii = 0;
	for (int i = 0x100 - 1; FileModule[i] != L'\\'; i--)//字符串从后到前比较,如果不为'\\'就将FileModule[i]赋值为0,为'\\'时循环终止
	{
		FileModule[i] = 0;
		ii++;
	}
	//FileModule[0x100 - 1 - ii] = 0;//消除斜杠'\'
	tuPianLuJing.Format(L"%s1.jpg", FileModule);//图片完整路径
	/************************   获取程序自身根文件夹  结束  **********************************/
	CString kuP;
	kuP.Format(L"%sHaoBao.mdb", FileModule);
	theApp.kuPath = kuP;//获取数据库地址
	AfxBeginThread(TCPlianjie, this);//建立TCP服务线程
	//yinChangChuangKou();//隐藏当前类指向的窗口
	yanZhengQiDong();
	//cmd.huoQuShiJian();
	qidong();



	//SetWindowLong (hWnd, -4, AddressOf SubClassMessage)
	//HWND hExe = FindWindowA(NULL, "护宝");
	//HWND hExe = GetSafeHwnd();
	//SetWindowLong(hExe, GWL_WNDPROC, (LONG)SubClassMessage);//接收DLL消息

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHUBAODlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHUBAODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHUBAODlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	dengLuL.DoModal();//弹出登陆窗口
}


UINT _cdecl jianCeShiJian(LPVOID lpParam)
{
	printf("线程1\n");
	/*获取当前时间戳
	* 循环查询比较数据库剩余时间戳
	* 没到时间无动作
	* 到时间执行锁屏
	*/
	CHUBAODlg* hBao = (CHUBAODlg*)lpParam;
	/*记录软件运行总时间 && 比较软件运行时间与数据库中设定的时间*/
	hBao->SetTimer(1, 10000, Func);//建立ID为1,间隔10秒,带回调函数的定时器
	
	//检查有无ID记录
	while (hBao->daoQiPanDuan)
	{
		//记录软件启动时间
		// 判断日期,如果是同1天,就不是第一次启动,如果比数据库的日期后1天或以上,就是第一次启动
		
		//如果开启了定时执行,检查是否在定时区间内,并关闭定时器1,
		// 
		//锁屏
		//随机连接网络验证信息
		
		/*定时10秒写入一次软件运行时间*/

	}
	hBao->KillTimer(1);//销毁ID为1的定时器
	return 0;
}


UINT _cdecl jianCeChengXu(LPVOID lpParam)
{
	printf("线程2\n");
	/*获取进程列表
	* 获取进程地址
	* 对比进程名,进程地址
	* 杀死进程,并上报服务端
	*/
	CHUBAODlg* hBao = (CHUBAODlg*)lpParam;
	while (hBao->daoQiPanDuan)//软件到期,结束检测线程
	{
		//hBao->huoQuJinChengLieBiao();
		



	}
	return 0;
}

void __stdcall Func(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	//读取软件运行时间
	//在读取的结果上+10秒并保存到数据库
}


void CHUBAODlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	daoQiPanDuan = FALSE;
	CDialogEx::OnCancel();
}

wchar_t** CHUBAODlg::huoQuJinChengLieBiao()
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
	int** pid = new int* [cdPid];
	for (int ii = 0; ii < i + 1; ii++)
	{
		pid[ii] = new int[cdPid];
	}

	wchar_t** pidM = new wchar_t* [cdPidM];
	int ii = 2;
	for (; ii < i+2 + 1; ii++)
	{
		pidM[ii] = new wchar_t[cdPidM];
	}
	*pidM[0] = (ii + 2);
	*pidM[1] =(int)&pid;
	//QueryFullProcessImageNameA
	BMORE = Process32First(hSnap, &pe);//获得第一个进程
	int ci = 0;
	while (BMORE)
	{
		//pe.th32ProcessID //PID
		CString txt;
		txt.Format(L"%d", pe.th32ProcessID);//获得PID

		//pid[ci] =(int*)pe.th32ParentProcessID;
		pidM[ci] = pe.szExeFile;
		//ProcessLst.InsertItem(0, txt);
		//ProcessLst.SetItemText(0, 1, pe.szExeFile);//获得文件名
		BMORE = Process32Next(hSnap, &pe);//获得下一个进程
		int a = pe.pcPriClassBase;
	}
	return pidM;
}



// LRESULT  CALLBACK CHUBAODlg::SubClassMessage(HWND lHwnd, long lMessage, long lParentPID, LPARAM lParam)
// {
// 	CHUBAODlg* pMainWnd = (CHUBAODlg*)GetWindowLong(lHwnd, GWL_USERDATA);
// 	CString sTemp;
// 	COPYDATASTRUCT uCDS;
// 	if (lMessage == WM_COPYDATA)
// 	{
// 		char* cs = (char*)lParam;
// 		printf("DLL的PID为: %d\n", lParentPID);
// 		printf("   shoudao    %s\n", cs);
// 		//sTemp= Space
// 	}
// 	//::CallWindowProc((int(__stdcall*)())old, hWnd, message, wParam, lParam);
// 	return 0;
// }


BOOL CHUBAODlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* netData)//消息接收事件
{
	CDialogEx::OnCopyData(pWnd, netData);//回交给系统处理
	if (netData->lpData)
	{
		LPWSTR jieShou = (LPWSTR)netData->lpData;
		DWORD cd = (DWORD)netData->cbData;
		wchar_t xinXi[1024] = { 0 };
		memcpy(xinXi, jieShou, cd);
		printf("收到信息:  %S  \n", xinXi);

		return 915;
	}

	return 0;

	//return CDialogEx::OnCopyData(pWnd, netData);
}