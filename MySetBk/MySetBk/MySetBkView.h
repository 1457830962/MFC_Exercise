// MySetBkView.h : CMySetBkView 类的接口
//


#pragma once

#include "SettingDlg.h"


class CMySetBkView : public CView
{
protected: // 仅从序列化创建
	CMySetBkView();
	DECLARE_DYNCREATE(CMySetBkView)

// 属性
public:
	CMySetBkDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMySetBkView();
	CSettingDlg m_clsPicSetDlg;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // MySetBkView.cpp 中的调试版本
inline CMySetBkDoc* CMySetBkView::GetDocument() const
   { return reinterpret_cast<CMySetBkDoc*>(m_pDocument); }
#endif

