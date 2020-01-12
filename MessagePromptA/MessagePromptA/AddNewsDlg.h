#pragma once
#include "afxwin.h"
#include <vector>
using namespace std;
// CAddNewsDlg 对话框

class CAddNewsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddNewsDlg)

public:
	CAddNewsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddNewsDlg();

// 对话框数据
	enum { IDD = IDD_Add_DIALOG };

public:
	//存储新建消息名称的容器，全部的消息
	vector<CString> v_strNewMsgName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlNewName_EDIT;
	CString m_strNewName_EDIT;
	CEdit m_ctrlNewContent_EDIT;
	CString m_strNewContent_EDIT;
	afx_msg void OnBnClickedOk();
};
