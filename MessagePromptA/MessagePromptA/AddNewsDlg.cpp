// AddNewsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MessagePromptA.h"
#include "AddNewsDlg.h"
#include "afxdialogex.h"

// CAddNewsDlg 对话框

IMPLEMENT_DYNAMIC(CAddNewsDlg, CDialogEx)

CAddNewsDlg::CAddNewsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddNewsDlg::IDD, pParent)
	, m_strNewName_EDIT(_T(""))
	, m_strNewContent_EDIT(_T(""))
{

}

CAddNewsDlg::~CAddNewsDlg()
{
}

void CAddNewsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NewName_EDIT, m_ctrlNewName_EDIT);
	DDX_Text(pDX, IDC_NewName_EDIT, m_strNewName_EDIT);
	DDX_Control(pDX, IDC_EDIT2, m_ctrlNewContent_EDIT);
	DDX_Text(pDX, IDC_EDIT2, m_strNewContent_EDIT);
}

BEGIN_MESSAGE_MAP(CAddNewsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddNewsDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAddNewsDlg 消息处理程序

/************************************************************************/
/* 功能：实现添加新消息然后添加到容器保存                               */
/************************************************************************/
void CAddNewsDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	bool IsAdd = true;       //设置变量做条件
	if (m_strNewName_EDIT == _T("") | m_strNewContent_EDIT == _T(""))
	{
		MessageBox(_T("请将信息填充完整！"));
	}
	else
	{
		//查找消息名是否重复，消息名重复则不会存储
		for (int i = 0; i < v_strNewMsgName.size(); i++)
		{

			if (m_strNewName_EDIT == v_strNewMsgName[i])
			{
				MessageBox(_T("消息名重复！"));
				m_ctrlNewName_EDIT.SetWindowText(_T(""));
				m_ctrlNewContent_EDIT.SetWindowText(_T(""));
				IsAdd = false;
			 }
		}
		if (IsAdd == true)
		{
			v_strNewMsgName.push_back(m_strNewName_EDIT);     //压给容器检验输入是否有重名情况
			this->GetParent()->SendMessage(WM_NEWMESSAGE, 1, 1);  //传递消息到父窗口进行相应消息处理
			m_ctrlNewName_EDIT.SetWindowText(_T(""));
			m_ctrlNewContent_EDIT.SetWindowText(_T(""));
			//添加成功后退出
			OnOK();
		}
	}
}
