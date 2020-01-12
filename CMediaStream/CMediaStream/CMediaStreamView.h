
// CMediaStreamView.h : CCMediaStreamView ��Ľӿ�

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "StreamAdd.h"
#include "DELETE.h"
#include "PropertSheet.h"

class CCMediaStreamView : public CFormView
{
protected: // �������л�����
	CCMediaStreamView();
	DECLARE_DYNCREATE(CCMediaStreamView)

public:
	enum{ IDD = IDD_CMEDIASTREAM_FORM };

// ����
public:
	CCMediaStreamDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CCMediaStreamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CStreamAdd m_clsAddDlg;
	HWND m_hwnd;
	CListCtrl m_ctrl_list;
	afx_msg void OnAdd();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelete();
public:
	// �����ý�������
	int m_nStreamNum;
public:
	// �ڱ���ѡ�е���
	int m_nSelRow;
	CDELETE m_clsDelDlg;
	CPropertSheet m_clsPropertySheetDlg;
	afx_msg void OnUpdateDelete(CCmdUI *pCmdUI);
	afx_msg void Onalldelete();
	afx_msg void OnUpdatealldelete(CCmdUI *pCmdUI);
	afx_msg void OnProperty();
	afx_msg void OnUpdateProperty(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
private:
	CString m_pStream[4];
protected:
	afx_msg LRESULT OnAddOk(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // CMediaStreamView.cpp �еĵ��԰汾
inline CCMediaStreamDoc* CCMediaStreamView::GetDocument() const
   { return reinterpret_cast<CCMediaStreamDoc*>(m_pDocument); }
#endif

