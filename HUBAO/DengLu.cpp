// DengLu.cpp: 实现文件
//

#include "pch.h"
#include "HUBAO.h"
#include "DengLu.h"
#include "afxdialogex.h"

#include "json/json.h"
using namespace Json;//声明Json命名空间


// DengLu 对话框

IMPLEMENT_DYNAMIC(DengLu, CDialogEx)

DengLu::DengLu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DENGLU, pParent)
	, zhangHao(_T(""))
	, zhangHaoMiMa(_T(""))
	, jiZhuMiMaD(TRUE)
{
	dengLuBiaoJi = FALSE;
}

DengLu::~DengLu()
{
	if (!jiZhuMiMaD)
	{
		zhangHao=_T("");
		zhangHaoMiMa=_T("");
	}
}

void DengLu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, zhangHao);
	DDX_Text(pDX, IDC_EDIT2, zhangHaoMiMa);
	DDX_Check(pDX, IDC_CHECK1, jiZhuMiMaD);
}

BOOL DengLu::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_STATIC_DL)->SetWindowText(L"");

	//duQuAccsccShuJu();
	return 0;
}

char* DengLu::zhuanChar(CString sj)
{
	//int nk;//字符个数
	int len;//字节个数
	char* a = NULL;
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
	len = WideCharToMultiByte(CP_ACP, 0, sj, -1, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的.此步是为了避免内存泄漏
	//std::cout << len << "\n";
	char* ls = new char[len]; //为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小,以字节为单位
	WideCharToMultiByte(CP_ACP, 0, sj, -1, ls, len, NULL, NULL);//宽字节编码转换成多字节编码
	/*捕获错误*/
	if (ERROR_INSUFFICIENT_BUFFER == GetLastError() || ERROR_INVALID_FLAGS == GetLastError() ||
		ERROR_INVALID_PARAMETER == GetLastError() || ERROR_NO_UNICODE_TRANSLATION == GetLastError())
	{
		printf("JSON char* 转换 errorNum = %d\n", GetLastError());
	}
	return ls;
}

void DengLu::dengLuYanZheng()
{
	CString z;
	CString zz = L"..";
	int i = 0;
	for (; i < 10; i++)
	{
		UpdateData(TRUE);
		z.Format(_T("登陆中..%s"), zz);
		GetDlgItem(IDC_STATIC_DL)->SetWindowText(z);
		UpdateData(FALSE);
		if (theApp.idYanZhe)
		{
			//AfxMessageBox(L"登陆成功!");
			//theApp.idYanZhe = FALSE;
			i = 10;
			GetDlgItem(IDC_STATIC_DL)->SetWindowText(_T("登陆成功!!"));
			UpdateData(FALSE);
			dengLuBiaoJi = TRUE;
			if (cmd.chaXun(theApp.idBiao, theApp.yongHuId[0], zhangHao) == 1)//如果有账号符合
			{
				if (jiZhuMiMaD)//是否记住密码
				{
					cmd.xiuGai(theApp.idBiao, theApp.yongHuId[0], zhangHao, theApp.yongHuId[1], zhangHaoMiMa);
					cmd.xiuGai(theApp.idBiao, theApp.yongHuId[0], zhangHao, theApp.yongHuId[5], _T("ok"));

					break;
				}
				else
				{
					cmd.xiuGai(theApp.idBiao, theApp.yongHuId[0], zhangHao, theApp.yongHuId[5], _T("no"));

					break;
				}

				break;
			}
			if (cmd.chaXunK(theApp.idBiao, theApp.yongHuId[0]))//如果账号为空
			{
				cmd.zengJia(theApp.idBiao, theApp.yongHuId[0], zhangHao);
				cmd.zengJia(theApp.jiLuBiao, theApp.yongHuJl[1], zhangHao);
				if (jiZhuMiMaD)
				{
					cmd.xiuGai(theApp.idBiao, theApp.yongHuId[0], zhangHao, theApp.yongHuId[1], zhangHaoMiMa);
					cmd.xiuGai(theApp.idBiao, theApp.yongHuId[0], zhangHao, theApp.yongHuId[5], _T("ok"));

					break;
				}
				else
				{
					cmd.xiuGai(theApp.idBiao, theApp.yongHuId[0], zhangHao, theApp.yongHuId[5], _T("no"));

					break;
				}
			}
		}
		Sleep(1000);
	}
	//cmd.guanBiShuJuKu();
	if (i>=10 && !theApp.idYanZhe && !dengLuBiaoJi)
	{
		AfxMessageBox(L"登陆失败,请重试");
	}
	
}



BEGIN_MESSAGE_MAP(DengLu, CDialogEx)
	ON_BN_CLICKED(IDOK, &DengLu::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DengLu::OnBnClickedCancel)
END_MESSAGE_MAP()


// DengLu 消息处理程序

/*登陆*/
void DengLu::OnBnClickedOk() //登陆
{
	UpdateData(TRUE);//将控件的值传递给变量
	if (zhangHao != _T("") && zhangHaoMiMa != _T(""))
	{
		

// 		char* zh = zhuanChar(id);
// 		char* zhmm = zhuanChar(zhangHaoMiMa);
// 		const char* s = zhmm;
// 		printf("这就是的话     %s\n", s);
// 		//必须所有指向这个地址的指针结束才能释放该指针内存
// 		delete[] zh;
// 		delete[] zhmm;
		char zz[600] = { 0 };
		char zh[30] = { 0 };
		char zhmm[30] = { 0 };
		tcpFuWuL.zhuanChar(zhangHao, zh);
		tcpFuWuL.zhuanChar(zhangHaoMiMa, zhmm);
		tcpFuWuL.zhuanJsonJ(zz, 1, zh, zhmm);
		tcpFuWuL.TCPfaSong(zz);
		printf("这就shuz     %s\n", zz);
		dengLuYanZheng();

	}
	else
	{
		AfxMessageBox(_T("请输入账号或密码"));
	}
}

/*退出*/
void DengLu::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
