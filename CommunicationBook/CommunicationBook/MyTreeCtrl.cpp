// MyTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "CommunicationBook.h"
#include "MyTreeCtrl.h"

// MyTreeCtrl

IMPLEMENT_DYNAMIC(MyTreeCtrl, CTreeCtrl)

MyTreeCtrl::MyTreeCtrl()
{
	ZeroMemory(&m_stTreeInfo, sizeof(TREE_DTAD_PARAM));
}

MyTreeCtrl::~MyTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(MyTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &MyTreeCtrl::OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// MyTreeCtrl 消息处理程序
/************************************************************************/
/* 功能：当开始拖拽时触发函数                                           */
/************************************************************************/
void MyTreeCtrl::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	//获取拖曳项句柄
	m_timeBeginDrag = 0;
	m_timeBeginDrag = CTime::GetCurrentTime();//获取时间
	m_stTreeInfo.hDragTreeDrag = pNMTreeView->itemNew.hItem;
	SelectItem(m_stTreeInfo.hDragTreeDrag);
	m_stTreeInfo.hScrParentItem = GetParentItem(pNMTreeView->itemNew.hItem);
	if (m_stTreeInfo.hScrParentItem == NULL)
	{
		return;
	}
	m_stTreeInfo.hDestParentItem = NULL;
	//创建拖曳时的句柄
	m_stTreeInfo.pImageList = CreateDragImage(m_stTreeInfo.hDragTreeDrag);
	if (!m_stTreeInfo.pImageList)
	{
		return;
	}
	//获取当前鼠标的位置
	CPoint pt = pNMTreeView->ptDrag;
	ClientToScreen(&pt);
	//开始拖曳图像，图像的索引值和开始能够拖曳的位置
	m_stTreeInfo.pImageList->BeginDrag(0, CPoint(0, 0));
	//显示拖曳的图形
	m_stTreeInfo.pImageList->DragEnter(this, pt);
	m_stTreeInfo.bIsDragging = TRUE;
	SetCapture();
}

/************************************************************************/
/* 功能：鼠标在树形空间中移动随即触发                                   */
/************************************************************************/
void MyTreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CTreeCtrl::OnMouseMove(nFlags, point);
	m_timeBeginMove = 0;
	if (m_stTreeInfo.bIsDragging == TRUE)
	{
		m_timeBeginMove = CTime::GetCurrentTime();
		m_stTreeInfo.pImageList->DragMove(point);
		//隐藏拖曳图像，避免拖曳时存在难看的痕迹
		m_stTreeInfo.pImageList->DragShowNolock(FALSE);
		UINT uFlags;
		//获取经过节点的句柄,若为父节点则展开
		HTREEITEM hItem = HitTest(point, &uFlags);//通过光标坐标位置来获得相应元素项
		if ((hItem != NULL) && ((TVHT_ONITEM | TVHT_ONITEMRIGHT) & uFlags))
		{
			HTREEITEM hParent = GetParentItem(hItem);
			//本身为父节点
			if (hParent == NULL)
			{
				hParent = hItem;
			}
			Expand(hParent, TVE_EXPAND);
			Select(hParent, TVGN_CARET);
			m_stTreeInfo.hDestParentItem = hParent;
		}
		else
		{
			m_stTreeInfo.hDestParentItem = NULL;
		}
		//显示拖曳图像
		m_stTreeInfo.pImageList->DragShowNolock(TRUE);
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}

/************************************************************************/
/* 功能：单击左键响应函数                                               */
/************************************************************************/
void MyTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_stTreeInfo.bIsDragging == TRUE)
	{
		m_stTreeInfo.bIsDragging = FALSE;  //赋值实现切换
		m_stTreeInfo.pImageList->DragLeave(this);
		m_stTreeInfo.pImageList->EndDrag();
		ReleaseCapture();    //鼠标消息释放掉
		delete m_stTreeInfo.pImageList;
		if (m_stTreeInfo.hDestParentItem != NULL && m_stTreeInfo.hDestParentItem != m_stTreeInfo.hScrParentItem)
		{
			HTREEITEM hItem = InsertItem(GetItemText(m_stTreeInfo.hDragTreeDrag), 3, 1, m_stTreeInfo.hDestParentItem);
			SelectItem(hItem);
			DeleteItem(m_stTreeInfo.hDragTreeDrag);
		}
	}
	CTreeCtrl::OnLButtonUp(nFlags, point);
}
