#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPage1 �Ի���

class CPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage1();

// �Ի�������
	enum { IDD = IDD_Page1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlEDIT1_name;
	CComboBox m_ctrlProSheet1_style;
	CIPAddressCtrl m_ctrlIP1;
	CEdit m_ctrlEDIT1_remark;
};
