#pragma once
#include "afxwin.h"

// AddGroup �Ի���

class AddGroup : public CDialog
{
	DECLARE_DYNAMIC(AddGroup)

public:
	AddGroup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddGroup();

// �Ի�������
	enum { IDD = IDD_Add_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_ctrlAddGroupDlg_EDIT;
};
