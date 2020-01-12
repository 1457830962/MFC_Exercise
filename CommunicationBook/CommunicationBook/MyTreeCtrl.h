#pragma once


// MyTreeCtrl

class MyTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(MyTreeCtrl)

public:
	MyTreeCtrl();
	virtual ~MyTreeCtrl();
	struct TREE_DTAD_PARAM
	{
		BOOL bIsDragging;
		HTREEITEM hDragTreeDrag;
		CImageList* pImageList;
		HTREEITEM hScrParentItem;
		HTREEITEM hDestParentItem;
	}m_stTreeInfo;

protected:
	DECLARE_MESSAGE_MAP()
	CTime m_timeBeginDrag;
	CTime m_timeBeginMove;
public:
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


