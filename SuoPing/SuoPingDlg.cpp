
// SuoPingDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SuoPing.h"
#include "SuoPingDlg.h"
#include "afxdialogex.h"
#include <windows.h>



//#include <winternl.h>
//#include < io.h>//判断文件是否存在

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSuoPingDlg 对话框



CSuoPingDlg::CSuoPingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SUOPING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bFullScreen = FALSE;
	//rectFullScreen = NULL;
}

void CSuoPingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSuoPingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSuoPingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CSuoPingDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDC_BUTTON1, &CSuoPingDlg::OnBnClickedButton1)
	ON_WM_GETMINMAXINFO()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDCANCEL, &CSuoPingDlg::OnBnClickedCancel)
	ON_WM_WINDOWPOSCHANGING()
	ON_BN_CLICKED(IDC_BUTTON2, &CSuoPingDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSuoPingDlg::OnBnClickedButton3)
END_MESSAGE_MAP()

// 唯一的 CSuoPingApp 对象,全局使用

CSuoPingDlg* cspLP;


// CSuoPingDlg 消息处理程序

BOOL CSuoPingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	/************************   获取程序自身根文件夹  开始  **********************************/
	TCHAR  FileModule[0x100]{};//保存路径缓冲区

	/*函数:GetModuleFileName
	* 作用: 检索包含指定模块的文件的完全限定路径。该模块必须已被当前进程加载。
	* 参数1:正在请求其路径的已加载模块的句柄。如果此参数为NULL，则 GetModuleFileName检索当前进程的可执行文件的路径。
	* 参数2:指向接收模块完全限定路径的缓冲区的指针,用来保存获取到的路径
	* 参数3:缓冲区(保存路径)的大小,以TCHARs 为单位。
	*/
	GetModuleFileName(NULL, FileModule, 0x100);

	/*计算字符串长度*/
	int ii = 0;
	for (int i = 0x100-1;FileModule[i] != L'\\'; i--)//字符串从后到前比较,如果不为'\\'就将它赋值为0,为'\\'时循环终止
	{
		FileModule[i] = 0;
		ii++;
	}
	//FileModule[0x100 - 1 - ii] = 0;//消除斜杠'\'
	wAppPath.Format(L"%s", FileModule);//将缓冲区数据保存到wAppPath里
	tuPianLuJing.Format(L"%s1.jpg", wAppPath);//图片完整路径
	/************************   获取程序自身根文件夹  结束  **********************************/

	//yinChangChuangKou(); //隐藏窗口函数
	lianWang();
	//sheZhiL.DoModal();//弹出设置页面
	//tuPianQuanPing();//图片全屏

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSuoPingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSuoPingDlg::OnPaint()
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
HCURSOR CSuoPingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSuoPingDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	system("rundll32.exe user32.dll, LockWorkStation");//进入系统锁屏
}


void CSuoPingDlg::OnBnClickedOk2()
{
	/*显示jpg类型的图片*/
	//UpdateData(TRUE);
	CImage image;
	image.Load(_T("E:\\1.jpg"));

	//获取图片客户区位置
	CRect imageRect;
	GetDlgItem(IDC_STATIC_2)->GetClientRect(&imageRect);

	//CDC类定义的是设备上下文对象的类，又称设备环境对象类。具体我也不懂，差了很多感觉就是画图时需要
	CDC* picDC = GetDC();
	image.Draw(picDC->m_hDC, imageRect);
	ReleaseDC(picDC);        //释放指针
	//UpdateData(FALSE);
}



void CSuoPingDlg::OnBnClickedButton1()
{
	//锁屏
	/**************窗口全屏 开始*************/
	if (!bFullScreen)
	{
		//获取系统屏幕宽高
		int g_iCurScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int g_iCurScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		//用m_struOldWndpl得到当前窗口的显示状态和窗体位置，以供退出全屏后使用
		GetWindowPlacement(&m_struOldWndpl);

		//计算出窗口全屏显示客户端所应该设置的窗口大小，主要为了将不需要显示的窗体边框等部分排除在屏幕外
		CRect rectWholeDlg;
		CRect rectClient;
		GetWindowRect(&rectWholeDlg);//得到当前窗体的总的相对于屏幕的坐标
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rectClient);//得到窗口客户区坐标
		ClientToScreen(&rectClient);//将客户区相对窗体的坐标转为相对屏幕坐标
		rectFullScreen.left = rectWholeDlg.left - rectClient.left;
		rectFullScreen.top = rectWholeDlg.top - rectClient.top;
		rectFullScreen.right = rectWholeDlg.right + g_iCurScreenWidth - rectClient.right;
		rectFullScreen.bottom = rectWholeDlg.bottom + g_iCurScreenHeight - rectClient.bottom;

		//设置窗口对象参数，为全屏做好准备并进入全屏状态
		WINDOWPLACEMENT struWndpl;
		struWndpl.length = sizeof(WINDOWPLACEMENT);
		struWndpl.flags = 0;
		struWndpl.showCmd = SW_SHOWNORMAL;
		struWndpl.rcNormalPosition = rectFullScreen;
		SetWindowPlacement(&struWndpl);//该函数设置指定窗口的显示状态和显示大小位置等，是我们该程序最为重要的函数
		bFullScreen = true;
	}
	else
	{
		SetWindowPlacement(&m_struOldWndpl);
		bFullScreen = false;
	}
	/**************窗口全屏 结束*************/
}




/* WM_GETMINMAXINFO消息的处理函数 */
void CSuoPingDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (bFullScreen)
	{
		lpMMI->ptMaxSize.x = rectFullScreen.Width();
		lpMMI->ptMaxSize.y = rectFullScreen.Height();
		lpMMI->ptMaxPosition.x = rectFullScreen.left;
		lpMMI->ptMaxPosition.y = rectFullScreen.top;
		lpMMI->ptMaxTrackSize.x = rectFullScreen.Width();
		lpMMI->ptMaxTrackSize.y = rectFullScreen.Height();
	}
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

/*鼠标双击消息*/
void CSuoPingDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	tuPianQuanPing();

	CDialogEx::OnLButtonDblClk(nFlags, point);
}



void CSuoPingDlg::xianShiKongJian()
{
	GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDOK2)->ShowWindow(SW_SHOW);
}

void CSuoPingDlg::yinChangKongJian()
{
	GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDOK2)->ShowWindow(SW_HIDE);
}
/*************************      隐藏窗口开始      *****************************************/
/*隐藏窗口,桌面不可见,任务栏不可见,任务栏详细PID可见*/
void CSuoPingDlg::yinChangChuangKou()
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

/*隐藏执行*/
void CSuoPingDlg::tuPianQuanPing()
{
	if (!bFullScreen)
	{
		bFullScreen = true;
		//获取系统屏幕宽高
		yinChangKongJian();
		int g_iCurScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int g_iCurScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		//用m_struOldWndpl得到当前窗口的显示状态和窗体位置，以供退出全屏后使用
		GetWindowPlacement(&m_struOldWndpl);
		GetDlgItem(IDC_STATIC_2)->GetWindowPlacement(&m_struOldWndpPic);
		//计算出窗口全屏显示客户端所应该设置的窗口大小，主要为了将不需要显示的窗体边框等部分排除在屏幕外
		CRect rectWholeDlg;
		CRect rectClient;
		GetWindowRect(&rectWholeDlg);//得到当前窗体的总的相对于屏幕的坐标
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rectClient);//得到客户区窗口坐标
		ClientToScreen(&rectClient);//将客户区相对窗体的坐标转为相对屏幕坐标
		//GetDlgItem(IDC_STATIC_PICSHOW)->GetWindowRect(rectClient);//得到PICTURE控件坐标
		rectFullScreen.left = rectWholeDlg.left - rectClient.left;
		rectFullScreen.top = rectWholeDlg.top - rectClient.top;
		rectFullScreen.right = rectWholeDlg.right + g_iCurScreenWidth - rectClient.right;
		rectFullScreen.bottom = rectWholeDlg.bottom + g_iCurScreenHeight - rectClient.bottom;

		//设置窗口对象参数，为全屏做好准备并进入全屏状态
		WINDOWPLACEMENT struWndpl;
		struWndpl.length = sizeof(WINDOWPLACEMENT);
		struWndpl.flags = 0;
		struWndpl.showCmd = SW_SHOWNORMAL;
		struWndpl.rcNormalPosition = rectFullScreen;
		SetWindowPlacement(&struWndpl);//该函数设置指定窗口的显示状态和显示大小位置等，是我们该程序最为重要的函数

		//将PICTURE控件的坐标设为全屏大小
		GetDlgItem(IDC_STATIC_2)->MoveWindow(CRect(0, 0, g_iCurScreenWidth, g_iCurScreenHeight));

		/*判断图片文件是否存在*/
		//BOOL rec = PathFileExists(tuPianLuJing);
		if (!PathFileExists(tuPianLuJing))
		{
			AfxMessageBox(L"程序出现错误,请重新安装!");
			CDialogEx::OnCancel();
		}
		/*显示图片*/
		CImage image;
		//image.Load(L"E:\\1.jpg");
		image.Load(tuPianLuJing);
		//获取图片客户区位置
		CRect imageRect;
		GetDlgItem(IDC_STATIC_2)->GetClientRect(&imageRect);
		//CDC类定义的是设备上下文对象的类，又称设备环境对象类。具体我也不懂，差了很多感觉就是画图时需要
		CDC* picDC = GetDC();
		image.Draw(picDC->m_hDC, imageRect);
		ReleaseDC(picDC);        //释放指针
	}
	else
	{
		xianShiKongJian();
		GetDlgItem(IDC_STATIC_2)->SetWindowPlacement(&m_struOldWndpPic);
		SetWindowPlacement(&m_struOldWndpl);
		bFullScreen = false;
	}
}

/*WM_WINDOWPOSCHANGING消息的响应函数*/
void CSuoPingDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanging(lpwndpos);

	// TODO: 在此处添加消息处理程序代码
	//lpwndpos->flags &= ~SWP_SHOWWINDOW;//隐藏窗口;功能即为将flags 中 SWP_SHOWWINDOW 属性去掉。

}
/*************************      隐藏窗口结束      *****************************************/

void CSuoPingDlg::lianWang()
{
	AfxBeginThread(TCPlianjie, this);
}

const char* CSuoPingDlg::json_zuHe()
{
	/*建立json字符串1*/
	Json::Value root;
	root["id"] = "cx";
	root["mima"] = "cx1231";
	root["gongneng"] = 2;
	Json::FastWriter sii;
	std::string sq = sii.write(root);//

	/*std::string 与 char* 转换的2种方法*/
	//const char* a = sq.data();
	const char* a = sq.c_str();
// 	std::cout << sq << "\n";
// 	std::cout << a << "\n";
	return a;
}

void CSuoPingDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

LRESULT __stdcall KeyCallBack(int nCode, WPARAM w, LPARAM l)
{
	return LRESULT();
}


void CSuoPingDlg::OnBnClickedButton2()
{
	const char* a = "192.168.1.12";
	suoPingGongJuL.lianJieFuWuQiDuan(a);
	suoPingGongJuL.pThread = AfxBeginThread(ThreadFunc_aa, this);
}


void CSuoPingDlg::OnBnClickedButton3()
{
	sheZhiL.DoModal();
}
