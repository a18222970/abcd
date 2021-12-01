// SheZhi.cpp: 实现文件
//

#include "pch.h"
#include "SuoPing.h"
#include "SheZhi.h"
#include "afxdialogex.h"

#include "SuoPingDlg.h"
#pragma warning(disable:4996) //屏蔽4996错误
CSuoPingDlg cSuoPingDlgL;

// SheZhi 对话框

IMPLEMENT_DYNAMIC(SheZhi, CDialogEx)

SheZhi::SheZhi(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, dLuID(_T(""))
	, dLuMiMa(_T(""))
	, DLMM(_T(""))
{
// 	dLuID = L"请输入你的ID";
// 	dLuMiMa = L"请输入你的登陆密码";
// 	DLMM = _T("请输入密码");
}

SheZhi::~SheZhi()
{
}

/*类的初始化*/
BOOL SheZhi::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*从这里开始写入初始化*/

	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);//从任务栏中去掉窗口显示.但是进程PID还是可见

	return 0;
}

void SheZhi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, dLuID);
	DDX_Text(pDX, IDC_EDIT2, dLuMiMa);
	DDX_Text(pDX, IDC_EDIT3, DLMM);
}


BEGIN_MESSAGE_MAP(SheZhi, CDialogEx)
	ON_BN_CLICKED(IDOK, &SheZhi::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &SheZhi::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &SheZhi::OnBnClickedButton1)
END_MESSAGE_MAP()


// SheZhi 消息处理程序


void SheZhi::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void SheZhi::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}





char* SheZhi::ziFuZhuanHuan_K_A(CString k)
{
	int len;//字节个数
	char* a = NULL;

	/*
	* 函数: WideCharToMultiByte
	* 作用: 将 UTF-16（宽字符）字符串映射到新字符串。新字符串不一定来自多字节字符集。
	* 参数1: 用于执行转换的代码页。转换后的格式,CP_ACP=系统默认的 Windows ANSI 代码页
	* 参数2: 指示转换类型的标志。当没有设置这些标志时，该函数执行得更快。
	* 参数3: 指向要转换的 Unicode 字符串的指针。
	* 参数4: 要转换的源字符串的大小（以字符为单位）。或者，如果字符串以空字符结尾，则可以将此参数设置为 -1,为-1时返回的长度包括结束的空字符
	* 参数5: 转换后保存数据的缓冲区(指针)
	* 参数6: 由 参数4 指示的缓冲区的大小（以字节为单位）。如果此参数设置为 0，则该函数返回 参数4 所需的缓冲区大小
	* 参数7: 一般设置为NULL
	* 参数8: 可以设置NULL
	* 返回值: 如果成功，则返回写入 参数5 指向的缓冲区的字节数。
	*        如果函数成功并且 参数6 为 0，则返回值是 参数5 指示的缓冲区所需的大小（以字节为单位）
	*/
	len = WideCharToMultiByte(CP_ACP, 0, k, -1, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的
	a = new char[len]; //为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小,以字节为单位
	mbstate_t ad;
	USES_CONVERSION;
	//GetBuffer返回指向 对象的内部字符缓冲区的 CSimpleStringT 指针. 
	//GetLength 字符串中字符的计数,包括 null 终止符
	const wchar_t* pBuf = T2W(k.GetBuffer(k.GetLength()));//将CString转换为 const wchar_t*
	/*
	* 函数: wcsrtombs
	* 作用: 将宽字符字符串转换为多字节字符串表示形式
	* 参数1:转换后保持的地址
	* 参数2:要转换的字符地址
	* 参数3:转换的字符长度,单位字节
	* 参数4: 指向转换状态 mbstate_t 对象的指针
	*/
	wcsrtombs(a, &pBuf, len + 1, &ad);
	//wcsrtombs_s(len + 1,a, len + 1 ,&pBuf, len + 1, &ad);
	return a;
}

void SheZhi::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	char* id=NULL;
	const char* mima=NULL;
	id = ziFuZhuanHuan_K_A(dLuID);
	mima= spGongJuLP.ziFuZhuanHuan_K_A(dLuMiMa);
	CString v;
	//v.Format(L"%s", id);
	v = id;
	AfxMessageBox(v);
	const char* ss = spGongJuLP.json_shengCheng(id, mima, 1);
	delete[] id;
	delete[] mima;
	
	
	BOOL a = spGongJuLP.tcpfaShuJU(ss);
// 	if (a)
// 	{
// 		UpdateData(TRUE);
// 		DLMM = L"登陆成功";
// 		UpdateData(FALSE);
// 	} 
// 	else
// 	{
// 		UpdateData(TRUE);
// 		DLMM = L"登陆失败";
// 		UpdateData(FALSE);
// 	}
	

	//_CrtDumpMemoryLeaks();//检测内存泄漏,运行到此就检测之前有无泄漏
}
