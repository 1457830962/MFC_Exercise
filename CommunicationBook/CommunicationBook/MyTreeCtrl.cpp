// MyTreeCtrl.cpp : ʵ���ļ�
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

// MyTreeCtrl ��Ϣ�������
/************************************************************************/
/* ���ܣ�����ʼ��קʱ��������                                           */
/************************************************************************/
void MyTreeCtrl::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//��ȡ��ҷ����
	m_timeBeginDrag = 0;
	m_timeBeginDrag = CTime::GetCurrentTime();//��ȡʱ��
	m_stTreeInfo.hDragTreeDrag = pNMTreeView->itemNew.hItem;
	SelectItem(m_stTreeInfo.hDragTreeDrag);
	m_stTreeInfo.hScrParentItem = GetParentItem(pNMTreeView->itemNew.hItem);
	if (m_stTreeInfo.hScrParentItem == NULL)
	{
		return;
	}
	m_stTreeInfo.hDestParentItem = NULL;
	//������ҷʱ�ľ��
	m_stTreeInfo.pImageList = CreateDragImage(m_stTreeInfo.hDragTreeDrag);
	if (!m_stTreeInfo.pImageList)
	{
		return;
	}
	//��ȡ��ǰ����λ��
	CPoint pt = pNMTreeView->ptDrag;
	ClientToScreen(&pt);
	//��ʼ��ҷͼ��ͼ�������ֵ�Ϳ�ʼ�ܹ���ҷ��λ��
	m_stTreeInfo.pImageList->BeginDrag(0, CPoint(0, 0));
	//��ʾ��ҷ��ͼ��
	m_stTreeInfo.pImageList->DragEnter(this, pt);
	m_stTreeInfo.bIsDragging = TRUE;
	SetCapture();
}

/************************************************************************/
/* ���ܣ���������οռ����ƶ��漴����                                   */
/************************************************************************/
void MyTreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTreeCtrl::OnMouseMove(nFlags, point);
	m_timeBeginMove = 0;
	if (m_stTreeInfo.bIsDragging == TRUE)
	{
		m_timeBeginMove = CTime::GetCurrentTime();
		m_stTreeInfo.pImageList->DragMove(point);
		//������ҷͼ�񣬱�����ҷʱ�����ѿ��ĺۼ�
		m_stTreeInfo.pImageList->DragShowNolock(FALSE);
		UINT uFlags;
		//��ȡ�����ڵ�ľ��,��Ϊ���ڵ���չ��
		HTREEITEM hItem = HitTest(point, &uFlags);//ͨ���������λ���������ӦԪ����
		if ((hItem != NULL) && ((TVHT_ONITEM | TVHT_ONITEMRIGHT) & uFlags))
		{
			HTREEITEM hParent = GetParentItem(hItem);
			//����Ϊ���ڵ�
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
		//��ʾ��ҷͼ��
		m_stTreeInfo.pImageList->DragShowNolock(TRUE);
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}

/************************************************************************/
/* ���ܣ����������Ӧ����                                               */
/************************************************************************/
void MyTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_stTreeInfo.bIsDragging == TRUE)
	{
		m_stTreeInfo.bIsDragging = FALSE;  //��ֵʵ���л�
		m_stTreeInfo.pImageList->DragLeave(this);
		m_stTreeInfo.pImageList->EndDrag();
		ReleaseCapture();    //�����Ϣ�ͷŵ�
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
