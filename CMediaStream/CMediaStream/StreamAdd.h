#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CStreamAdd �Ի���

class CStreamAdd : public CDialog
{
	DECLARE_DYNAMIC(CStreamAdd)

public:
	CStreamAdd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStreamAdd();

// �Ի�������
	enum { IDD = IDD_ADD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlEDIT_name;
	CString m_strEDIT_name;
	CComboBox m_ctrlCOMBO_style;
	CEdit m_ctrlEDIT_remark;
	CString m_strEDIT_remark;
	CIPAddressCtrl m_ctrlIPadress;
	DWORD m_strIPadress;
	//ָ�����
	CString *m_pStream1;

	HWND* m_pHwnd;
	CString m_strCOMBO_style;
public:
	afx_msg void OnCbnSelchangeCombostyle();
	afx_msg void OnBnClickedOk();
};
