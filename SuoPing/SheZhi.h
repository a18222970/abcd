#pragma once
//#include "SuoPingDlg.h"

// SheZhi 对话框
#include "SuoPingGongJu.h"
#include "SuoPing.h"
class SheZhi : public CDialogEx
{
	DECLARE_DYNAMIC(SheZhi)

public:
	SheZhi(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SheZhi();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual BOOL OnInitDialog();//初始化 类
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	WINDOWPLACEMENT m_struOldWndpl;//结构中包含了有关窗口在屏幕上位置的信息
public:
	SuoPingGongJu spGongJuLP;

public:
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	// 登陆id编辑框
	CString dLuID;
	// 登陆密码_编辑框
	CString dLuMiMa;
	// 登陆密码
	CString DLMM;
	/*
	* 函数: ziFuZhuanHuan_K_A
	* 作用: 宽字符串转换成指定的新的字符串.CString转char char*
	* 参数: 宽字符
	* 返回值: 转换后的保存区动态内存指针,取值后要delete[]释放内存
	*/
	char* ziFuZhuanHuan_K_A(CString k);
	afx_msg void OnBnClickedButton1();
};
