
// MessagePromptADlg.h : 头文件
//
#pragma once
#include "MessageManage.h"
#include "afxwin.h"
//容器
#include <vector>
using namespace std;

// CMessagePromptADlg 对话框
class CMessagePromptADlg : public CDialogEx
{
// 构造
public:
	CMessagePromptADlg(CWnd* pParent = NULL);	// 标准构造函数
	//存放消息名称
	vector<CString> v_strName;
	vector<CString> v_strContext;
    //记录提示框中选中提示消息
	vector<CString> v_strShowContext;
	BOOL m_bInitOk;
	//临时变量
	int m_x;
	CRect m_rcEdit;
	CRect m_lpBtnRect[4];
	CPoint m_OldPoint[4];

	CMessageManage m_clsMessageManageDlg;
public:
	bool m_bIsNotic;
public:
	bool m_bIsTop;

// 对话框数据
	enum { IDD = IDD_MESSAGEPROMPTA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedManageButton();
	CEdit m_ctrlNotice_EDIT;
	afx_msg void OnBnClickedNoticeButton();
	CButton m_ctrlNotice_BUTTON;
	CButton m_ctrlManage_BUTTON;
	afx_msg void OnBnClickedTopCheck();
	CButton m_ctrlTop;
	CButton m_ctrlExit_BUTTON;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	void ReSize(LPRECT rect, LPRECT x, LPRECT y);
	void ReSize(CPoint *point, CPoint *x, LPRECT y);
protected:
	afx_msg LRESULT OnMsgManage(WPARAM wParam, LPARAM lParam);//自定义消息响应函数
};
