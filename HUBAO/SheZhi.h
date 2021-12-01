#pragma once
#include "ACCSCC.h"

// SheZhi 对话框

class SheZhi : public CDialogEx
{
	DECLARE_DYNAMIC(SheZhi)

public:
	SheZhi(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SheZhi();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHEZHI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	BOOL OnInitDialog();
public:
	// 列表	// 列表
	CListCtrl ProcessLst;

	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);//列表事件
	afx_msg void OnBnClickedOk();

	void xianShi(CString biao, BOOL a = FALSE);

	afx_msg void OnBnClickedOk2();
	/*表1与表2不相同的字段数据,返回的是表1现有的数据中查找出来的不相同的结果*/
	void quChong(CString biao1, CString b1ziDuan, CString biao2, CString biao2ziduan);

	void biJiao();
	void biJiao1();
	afx_msg void OnBnClickedOk3();
	// 编辑框
	CString shuliangB;
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);

	void chaKanPidMoKuai(DWORD pid);

	typedef struct jcCS
	{
		DWORD pid;
		CString ming;
		CString path;
		int ci;
	}JC;
	HANDLE hMutex;//互斥量

	/*PE表 结构*/
	IMAGE_DOS_HEADER* dosHeader;//DOS头结构指针
	IMAGE_NT_HEADERS* ntHeader;//PE头结构指针
	IMAGE_FILE_HEADER* file_HEADER;//标准PE头
	IMAGE_OPTIONAL_HEADER* optIONAL32; //可选PE头
	IMAGE_DATA_DIRECTORY* data_DIRECTORY;//数据目录表
	IMAGE_SECTION_HEADER* sectION_HEADER;//区块表,节表

	/*获得哈希值,哈希算法*/
	BOOL GetHash(int hash_type, CString& hash_result, static CString hash_message);
	void teZhenMa(CString ptahb, CString& fanHui);

	afx_msg void OnBnClickedOk4();

	typedef int(*ah)(int a, int b);//测试
	typedef BOOL(__stdcall* kaiShi)(void);
	typedef BOOL(WINAPI* jieSu)(void);
	afx_msg void OnBnClickedOk5();
	afx_msg void OnBnClickedOk6();
};