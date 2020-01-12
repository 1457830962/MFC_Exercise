#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPage1 对话框

class CPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPage1();

// 对话框数据
	enum { IDD = IDD_Page1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlEDIT1_name;
	CComboBox m_ctrlProSheet1_style;
	CIPAddressCtrl m_ctrlIP1;
	CEdit m_ctrlEDIT1_remark;
};
