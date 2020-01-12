
// CMediaStreamView.h : CCMediaStreamView 类的接口

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "StreamAdd.h"
#include "DELETE.h"
#include "PropertSheet.h"

class CCMediaStreamView : public CFormView
{
protected: // 仅从序列化创建
	CCMediaStreamView();
	DECLARE_DYNCREATE(CCMediaStreamView)

public:
	enum{ IDD = IDD_CMEDIASTREAM_FORM };

// 特性
public:
	CCMediaStreamDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CCMediaStreamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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
	// 添加流媒体的数量
	int m_nStreamNum;
public:
	// 在表内选中的行
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

#ifndef _DEBUG  // CMediaStreamView.cpp 中的调试版本
inline CCMediaStreamDoc* CCMediaStreamView::GetDocument() const
   { return reinterpret_cast<CCMediaStreamDoc*>(m_pDocument); }
#endif

