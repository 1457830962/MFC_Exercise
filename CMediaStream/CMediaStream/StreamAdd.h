#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CStreamAdd 对话框

class CStreamAdd : public CDialog
{
	DECLARE_DYNAMIC(CStreamAdd)

public:
	CStreamAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStreamAdd();

// 对话框数据
	enum { IDD = IDD_ADD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlEDIT_name;
	CString m_strEDIT_name;
	CComboBox m_ctrlCOMBO_style;
	CEdit m_ctrlEDIT_remark;
	CString m_strEDIT_remark;
	CIPAddressCtrl m_ctrlIPadress;
	DWORD m_strIPadress;
	//指针变量
	CString *m_pStream1;

	HWND* m_pHwnd;
	CString m_strCOMBO_style;
public:
	afx_msg void OnCbnSelchangeCombostyle();
	afx_msg void OnBnClickedOk();
};
