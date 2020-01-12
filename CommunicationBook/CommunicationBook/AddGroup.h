#pragma once
#include "afxwin.h"

// AddGroup 对话框

class AddGroup : public CDialog
{
	DECLARE_DYNAMIC(AddGroup)

public:
	AddGroup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddGroup();

// 对话框数据
	enum { IDD = IDD_Add_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_ctrlAddGroupDlg_EDIT;
};
