#pragma once

#include "TCPfuWu.h"

#include "ACCSCC.h"
// DengLu 对话框

class DengLu : public CDialogEx
{
	DECLARE_DYNAMIC(DengLu)

public:
	DengLu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DengLu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DENGLU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();//类初始化
	DECLARE_MESSAGE_MAP()
	BOOL dengLuBiaoJi;//登陆成功或失败时的标记
public:
	/*重要: 使用此函数后需要用 delete[] 接受指针  来释放内存,不然会内存溢出
	* 
	* 
	*/
	char* zhuanChar(CString sj);

	/*
	* 作用: 登陆过程
	*/
	void dengLuYanZheng();

	TCPfuWu tcpFuWuL;

	/*accscc*/
	

public:
	// 账号id
	CString zhangHao;
	// 账号密码
	CString zhangHaoMiMa;
	// 记住密码
	BOOL jiZhuMiMaD;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
