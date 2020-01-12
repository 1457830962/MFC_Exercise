#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "BtnBkClr.h"


// CSettingDlg 对话框

class CSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PICSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	//定义提示条控件
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
