// AddNewsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MessagePromptA.h"
#include "AddNewsDlg.h"
#include "afxdialogex.h"

// CAddNewsDlg �Ի���

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

// CAddNewsDlg ��Ϣ�������

/************************************************************************/
/* ���ܣ�ʵ���������ϢȻ����ӵ���������                               */
/************************************************************************/
void CAddNewsDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	bool IsAdd = true;       //���ñ���������
	if (m_strNewName_EDIT == _T("") | m_strNewContent_EDIT == _T(""))
	{
		MessageBox(_T("�뽫��Ϣ���������"));
	}
	else
	{
		//������Ϣ���Ƿ��ظ�����Ϣ���ظ��򲻻�洢
		for (int i = 0; i < v_strNewMsgName.size(); i++)
		{

			if (m_strNewName_EDIT == v_strNewMsgName[i])
			{
				MessageBox(_T("��Ϣ���ظ���"));
				m_ctrlNewName_EDIT.SetWindowText(_T(""));
				m_ctrlNewContent_EDIT.SetWindowText(_T(""));
				IsAdd = false;
			 }
		}
		if (IsAdd == true)
		{
			v_strNewMsgName.push_back(m_strNewName_EDIT);     //ѹ���������������Ƿ����������
			this->GetParent()->SendMessage(WM_NEWMESSAGE, 1, 1);  //������Ϣ�������ڽ�����Ӧ��Ϣ����
			m_ctrlNewName_EDIT.SetWindowText(_T(""));
			m_ctrlNewContent_EDIT.SetWindowText(_T(""));
			//��ӳɹ����˳�
			OnOK();
		}
	}
}
