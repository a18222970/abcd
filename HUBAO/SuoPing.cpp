// SuoPing.cpp: 实现文件
//

#include "pch.h"
#include "HUBAO.h"
#include "SuoPing.h"
#include "afxdialogex.h"


// SuoPing 对话框

IMPLEMENT_DYNAMIC(SuoPing, CDialogEx)

SuoPing::SuoPing(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SUOPING, pParent)
{

}

SuoPing::~SuoPing()
{
}

void SuoPing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SuoPing, CDialogEx)
END_MESSAGE_MAP()


// SuoPing 消息处理程序
