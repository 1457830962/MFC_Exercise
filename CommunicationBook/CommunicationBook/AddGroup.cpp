// AddGroup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommunicationBook.h"
#include "AddGroup.h"
#include "afxdialogex.h"


// AddGroup �Ի���

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

// AddGroup ��Ϣ�������
/************************************************************************/
/* ���ܣ���ӷ���                                                       */
/************************************************************************/
void AddGroup::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
	CString strGroupName = L"";
	m_ctrlAddGroupDlg_EDIT.GetWindowText(strGroupName);
	if (strGroupName == L"")
	{
		MessageBox(L"�������������");
	}
	else
	{
		::SendMessage(this->GetParent()->GetSafeHwnd(), WM_GROUP_ADD, 1, 1);
		OnOK();
	}
}
