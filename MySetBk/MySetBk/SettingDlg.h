#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "BtnBkClr.h"


// CSettingDlg �Ի���

class CSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_PICSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTitle;
public:
	CSliderCtrl m_ctrSlider;
public:
	int m_nSliderMark;
public:
	CBtnBkClr m_ctrBtnColor;
public:
	CString  m_strPathName;
	//������ʾ���ؼ�
public:
	CToolTipCtrl m_ctrTips;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	afx_msg void OnEnChangeEditWidth();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnBnClickedButtonScan();
	afx_msg void OnEnChangeEditTitle();
};
