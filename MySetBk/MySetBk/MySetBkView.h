// MySetBkView.h : CMySetBkView ��Ľӿ�
//


#pragma once

#include "SettingDlg.h"


class CMySetBkView : public CView
{
protected: // �������л�����
	CMySetBkView();
	DECLARE_DYNCREATE(CMySetBkView)

// ����
public:
	CMySetBkDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMySetBkView();
	CSettingDlg m_clsPicSetDlg;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPicSet();
	struct ST_BK_PRO 
	{
		CString strTitle;
		int nBorderWidth;
		COLORREF clrBorder;
		CString strPathName;
	}m_stBkPro;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MySetBkView.cpp �еĵ��԰汾
inline CMySetBkDoc* CMySetBkView::GetDocument() const
   { return reinterpret_cast<CMySetBkDoc*>(m_pDocument); }
#endif

