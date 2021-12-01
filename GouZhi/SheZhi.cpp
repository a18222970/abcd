// SheZhi.cpp: 实现文件
//

#include "pch.h"
#include "GouZhi.h"
#include "SheZhi.h"



// SheZhi 对话框

IMPLEMENT_DYNAMIC(SheZhi, CDialogEx)

SheZhi::SheZhi(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHE_ZHI, pParent)
{

}

SheZhi::~SheZhi()
{
}

void SheZhi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SheZhi, CDialogEx)
END_MESSAGE_MAP()


// SheZhi 消息处理程序
