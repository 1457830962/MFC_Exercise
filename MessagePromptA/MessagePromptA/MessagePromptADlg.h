
// MessagePromptADlg.h : ͷ�ļ�
//
#pragma once
#include "MessageManage.h"
#include "afxwin.h"
//����
#include <vector>
using namespace std;

// CMessagePromptADlg �Ի���
class CMessagePromptADlg : public CDialogEx
{
// ����
public:
	CMessagePromptADlg(CWnd* pParent = NULL);	// ��׼���캯��
	//�����Ϣ����
	vector<CString> v_strName;
	vector<CString> v_strContext;
    //��¼��ʾ����ѡ����ʾ��Ϣ
	vector<CString> v_strShowContext;
	BOOL m_bInitOk;
	//��ʱ����
	int m_x;
	CRect m_rcEdit;
	CRect m_lpBtnRect[4];
	CPoint m_OldPoint[4];

	CMessageManage m_clsMessageManageDlg;
public:
	bool m_bIsNotic;
public:
	bool m_bIsTop;

// �Ի�������
	enum { IDD = IDD_MESSAGEPROMPTA_DIALOG };

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
	afx_msg LRESULT OnMsgManage(WPARAM wParam, LPARAM lParam);//�Զ�����Ϣ��Ӧ����
};
