// Page1.cpp : 实现文件
//

#include "stdafx.h"
#include "CMediaStream.h"
#include "Page1.h"
#include "afxdialogex.h"


// CPage1 对话框

IMPLEMENT_DYNAMIC(CPage1, CDialogEx)

CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPage1::IDD, pParent)
{

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlEDIT1_name);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlProSheet1_style);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ctrlIP1);
	DDX_Control(pDX, IDC_EDIT2, m_ctrlEDIT1_remark);
}


BEGIN_MESSAGE_MAP(CPage1, CDialogEx)
END_MESSAGE_MAP()


// CPage1 消息处理程序
