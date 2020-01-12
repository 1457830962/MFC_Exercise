// AddGroup.cpp : 实现文件
//

#include "stdafx.h"
#include "CommunicationBook.h"
#include "AddGroup.h"
#include "afxdialogex.h"


// AddGroup 对话框

IMPLEMENT_DYNAMIC(AddGroup, CDialog)

AddGroup::AddGroup(CWnd* pParent /*=NULL*/)
	: CDialog(AddGroup::IDD, pParent)
{

}

AddGroup::~AddGroup()
{
}

void AddGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlAddGroupDlg_EDIT);
}

BEGIN_MESSAGE_MAP(AddGroup, CDialog)
	ON_BN_CLICKED(IDOK, &AddGroup::OnBnClickedOk)
END_MESSAGE_MAP()

// AddGroup 消息处理程序
/************************************************************************/
/* 功能：添加分组                                                       */
/************************************************************************/
void AddGroup::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnOK();
	CString strGroupName = L"";
	m_ctrlAddGroupDlg_EDIT.GetWindowText(strGroupName);
	if (strGroupName == L"")
	{
		MessageBox(L"请输入分组名！");
	}
	else
	{
		::SendMessage(this->GetParent()->GetSafeHwnd(), WM_GROUP_ADD, 1, 1);
		OnOK();
	}
}
