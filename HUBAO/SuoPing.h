#pragma once


// SuoPing 对话框

class SuoPing : public CDialogEx
{
	DECLARE_DYNAMIC(SuoPing)

public:
	SuoPing(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SuoPing();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUOPING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
