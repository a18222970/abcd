
// HUBAO.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "HUBAO.h"
#include "HUBAODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHUBAOApp

BEGIN_MESSAGE_MAP(CHUBAOApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHUBAOApp 构造

CHUBAOApp::CHUBAOApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	tcpFuuWuKaiGuan = TRUE;
	idYanZhe = FALSE;
	memset(tcpDengLUYanZheng, 0, 600);

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
	yongHuId[9] = _T("xuHao");// 序号 int
	

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
	fXjinCheng= _T("fXjinCheng");
	
	ci = 1;
}


// 唯一的 CHUBAOApp 对象

CHUBAOApp theApp;


// CHUBAOApp 初始化

BOOL CHUBAOApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CHUBAODlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

