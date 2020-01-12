#pragma once
#include "AddNewsDlg.h"
#include <vector>
#include "afxwin.h"
using namespace std;

// CMessageManage 对话框

class CMessageManage : public CDialogEx
{
	DECLARE_DYNAMIC(CMessageManage)

public:
	CMessageManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMessageManage();

public:
	//存放添加新建消息
	vector<CString>v_strName;
	vector<CString>v_strContent;
	//容器中存储显示信息名称
	vector<CString>v_strShow;
	//保存初始记录
	vector<CString>v_strReName;
	vector<CString>v_strReContent;
	vector<int>::size_type v_nMsgNums;

// 对话框数据
	enum { IDD = IDD_MessageManage_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddButton();
public:
	CAddNewsDlg m_clsAddNewsDlg;

	afx_msg void OnBnClickedAllleftButton();
	CListBox m_ctrlNoticeList;
	CString m_strNoticeList;
	CListBox m_ctrlMsgList;
	CString m_strMsgList;
	afx_msg void OnBnClickedAllrightButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedLeftButton();
	afx_msg void OnBnClickedRightButton();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedDownupButton();
	afx_msg void OnBnClickedTurnupButton();
	afx_msg void OnBnClickedOk();
protected:
	afx_msg LRESULT OnNewMessage(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
};
