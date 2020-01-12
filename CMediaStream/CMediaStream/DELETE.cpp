// DELETE.cpp : 实现文件
//

#include "stdafx.h"
#include "CMediaStream.h"
#include "DELETE.h"
#include "afxdialogex.h"


// CDELETE 对话框

IMPLEMENT_DYNAMIC(CDELETE, CDialog)

CDELETE::CDELETE(CWnd* pParent /*=NULL*/)
	: CDialog(CDELETE::IDD, pParent)
{

}

CDELETE::~CDELETE()
{
}

void CDELETE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDELETE, CDialog)
	ON_BN_CLICKED(IDOK, &CDELETE::OnBnClickedOk)
END_MESSAGE_MAP()


// CDELETE 消息处理程序


void CDELETE::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnOK();
}
