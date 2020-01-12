
// CommunicationBookDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "AddGroup.h"
#include "MyTreeCtrl.h"

/*class AddGroup;*/
// CCommunicationBookDlg �Ի���
class CCommunicationBookDlg : public CDialogEx
{
// ����
public:
	CCommunicationBookDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COMMUNICATIONBOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CImageList m_imageList;    //����ͼ���б�

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
	HICON hIcon[2];      // ͼ��������   
	HTREEITEM hRoot;     // ���ĸ��ڵ�ľ��һ
	HTREEITEM hSubItem;   // ���ĸ��ڵ�ľ����
	HTREEITEM hCataItem;  // �ɱ�ʾ��һ����ڵ�ľ��   
	//�洢������Ϣ
	CString m_strMsg[30][8];
	CTime pTime[30];
	//��ѡ����
	HTREEITEM hHandle;
	//֮ǰѡ����ľ��
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
	//�Զ��庯��
	void FreshMsg();
		
	afx_msg void OnDtnDatetimechangeBirthdayDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult);
};
