#pragma once
#include "Page1.h"
#include "Page2.h"
#include "afxcmn.h"
//#include "afxcmn.h"


// CPropertSheet �Ի���

class CPropertSheet : public CDialog
{
	DECLARE_DYNAMIC(CPropertSheet)

public:
	CPropertSheet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPropertSheet();

// �Ի�������
	enum { IDD = IDD_PropertySheet_DIALOG };
public:
	int m_nCurSelTab;
	CTabCtrl m_tab;
	CPage1 m_clsPage1;
	CPage2 m_clsPage2;
	CString * m_pStream;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
