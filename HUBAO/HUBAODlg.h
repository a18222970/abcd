
// HUBAODlg.h: 头文件
//

#pragma once
#include "DengLu.h"

/*******/
#include "shiJian.h"

// CHUBAODlg 对话框
class CHUBAODlg : public CDialogEx
{
// 构造
public:
	CHUBAODlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CHUBAODlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HUBAO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
protected:
	CString tuPianLuJing;//图片路径
public:
	DengLu dengLuL;//登陆页面

	void qidong();//初始化启动
	BOOL yanZhengQiDong();//验证是否记住账号,密码
	char yanZheng;//密码状态,1为记住密码,2为不记住密码
	/*隐藏窗口,桌面不可见,任务栏不可见,任务栏详细PID可见*/
	void yinChangChuangKou();//隐藏窗口
	BOOL daoQiPanDuan;//软件时间到期判断

	/*获取进程列表*/
	wchar_t** huoQuJinChengLieBiao();


	//static  LRESULT   CALLBACK SubClassMessage(HWND lHwnd, long lMessage, long lParentPID, long lParam);
	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public://时间
	shiJian shiJianL;
	unsigned jLshiJian;
	unsigned dQshiJian;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	BOOL OnCopyData(CWnd*, COPYDATASTRUCT* netData);//消息接收事件
	CEdit kongJian;
	CString kongJian1B;
	// 窗口
	CButton ck;
};
UINT _cdecl jianCeShiJian(LPVOID lpParam);//检测线程
UINT _cdecl jianCeChengXu(LPVOID lpParam);//检测线程

void __stdcall Func(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);//定时器回调函数