
// CommunicationBookDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "AddGroup.h"
#include "MyTreeCtrl.h"

/*class AddGroup;*/
// CCommunicationBookDlg 对话框
class CCommunicationBookDlg : public CDialogEx
{
// 构造
public:
	CCommunicationBookDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMMUNICATIONBOOK_DIALOG };

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

	CImageList m_imageList;    //创建图标列表

public:
	CButton m_ctrlADD1_BUTTON;
	CString m_strname_EDIT;
	CString m_strname1_EDIT;
	CString m_strtelNumber1_EDIT;
	CString m_strtelNumber2_EDIT;
	CString m_strEmail_EDIT;
	CString m_strAddress_EDIT;
	CString m_strPrepare_EDIT;
	CEdit m_ctrlname_EDIT;
	HICON hIcon[2];      // 图标句柄数组   
	HTREEITEM hRoot;     // 树的根节点的句柄一
	HTREEITEM hSubItem;   // 树的根节点的句柄二
	HTREEITEM hCataItem;  // 可表示任一分类节点的句柄   
	//存储个人信息
	CString m_strMsg[30][8];
	CTime pTime[30];
	//所选项句柄
	HTREEITEM hHandle;
	//之前选中项的句柄
	HTREEITEM hPreHandle;
	CEdit m_ctrlname1_EDIT;
	CEdit m_ctrlTEI_EDIT;
	CEdit m_ctrlofficTEL_EDIT;
	CEdit m_ctrlemail_EDIT;
	CEdit m_ctrlAddress_EDIT;
	CEdit m_ctrlAppendix_EDIT;
	CDateTimeCtrl m_ctrlBirthday;
	CButton m_ctrlDelete_BUTTON;
	CButton m_ctrlGroupAdd_BUTTON;
	CButton m_ctrlGroupDelete_BUTTON;
	CButton m_ctrlAlter_BUTTON;
    AddGroup m_clsAddGroup;
	CTime m_time;
protected:
	afx_msg LRESULT OnGroupAdd(WPARAM wParam, LPARAM lParam);
public:
	MyTreeCtrl m_ctrlList_Tree;
	afx_msg void OnBnClickedDelgroupButton();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAdd1Button();
	afx_msg void OnBnClickedAlterButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedAddgroupButton();
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	//自定义函数
	void FreshMsg();
		
	afx_msg void OnDtnDatetimechangeBirthdayDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult);
};
