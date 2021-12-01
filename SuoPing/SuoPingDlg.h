
// SuoPingDlg.h: 头文件
//

#pragma once
#include "SheZhi.h"
#include "SuoPingGongJu.h"

#include "json/json.h"
using namespace Json;//声明Json命名空间
// CSuoPingDlg 对话框
class CSuoPingDlg : public CDialogEx
{
// 构造
public:
	CSuoPingDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	//enum { IDD = IDD_SUOPING_DIALOG }; //IDD_SHEZHI
	enum { IDD = IDD_SHEZHI };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedButton1();

private:
	BOOL bFullScreen;
	CRect rectFullScreen;
	WINDOWPLACEMENT m_struOldWndpl;//结构中包含了有关窗口在屏幕上位置的信息
	WINDOWPLACEMENT m_struOldWndpPic;//PICTURE控件在屏幕上位置的信息

public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void xianShiKongJian();//显示控件
	void yinChangKongJian();//隐藏控件
	void yinChangChuangKou();//隐藏窗口
	void tuPianQuanPing();//隐藏执行

	CString wAppPath; //本程序自身路径根文件夹
	CString tuPianLuJing;//图片路径
	afx_msg void OnBnClickedCancel();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();


public:
	/*弹出页面*/
	SheZhi sheZhiL;
	

	/*TCP*/
	//CWinThread* zThread;
	void lianWang();

	/*json*/
	const char* json_zuHe();

	
	SuoPingGongJu suoPingGongJuL;
	
};

extern CSuoPingDlg* cspLP;