
// CMediaStreamView.cpp : CCMediaStreamView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CMediaStream.h"
#endif

#include "CMediaStreamDoc.h"
#include "CMediaStreamView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCMediaStreamView

IMPLEMENT_DYNCREATE(CCMediaStreamView, CFormView)

BEGIN_MESSAGE_MAP(CCMediaStreamView, CFormView)
	ON_COMMAND(ID_ADD, &CCMediaStreamView::OnAdd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CCMediaStreamView::OnLvnItemchangedList)
	ON_COMMAND(ID_DELETE, &CCMediaStreamView::OnDelete)
	ON_UPDATE_COMMAND_UI(ID_DELETE, &CCMediaStreamView::OnUpdateDelete)
	ON_COMMAND(ID_allDELETE, &CCMediaStreamView::Onalldelete)
	ON_UPDATE_COMMAND_UI(ID_allDELETE, &CCMediaStreamView::OnUpdatealldelete)
	ON_COMMAND(ID_PROPERTY, &CCMediaStreamView::OnProperty)
	ON_UPDATE_COMMAND_UI(ID_PROPERTY, &CCMediaStreamView::OnUpdateProperty)
	ON_WM_CONTEXTMENU()
  //�Զ�����Ϣ��Ӧ����
    ON_MESSAGE(WM_ADD_OK, &CCMediaStreamView::OnAddOk)
END_MESSAGE_MAP()

// CCMediaStreamView ����/����

CCMediaStreamView::CCMediaStreamView()
	: CFormView(CCMediaStreamView::IDD)
{
	// TODO:  �ڴ˴���ӹ������
	m_nStreamNum = 0;   //�����ý����������ֵ
	m_nSelRow = -1;
}

CCMediaStreamView::~CCMediaStreamView()
{
}

void CCMediaStreamView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_ctrl_list);
}

BOOL CCMediaStreamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CCMediaStreamView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//ʹ��ӶԻ������ý������������ʾ����ý�干һ���
	m_clsAddDlg.m_pStream1 = m_pStream;

	//ʹ����ҳ����������ʾ����ý�干һ���
	m_clsPropertySheetDlg.m_pStream = m_pStream;

	//ʹ�����ھ�����������ý��Ի��򣬱㷢����Ϣ��������
	m_hwnd = this->m_hWnd;//��ȡ���ھ��
	m_clsAddDlg.m_pHwnd = &m_hwnd;//�������ַ����ָ�����

	DWORD dwStyle = m_ctrl_list.GetExtendedStyle();                    //����б��������ߣ�����
	
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_ctrl_list.SetExtendedStyle(dwStyle);
	CRect rect;
	GetClientRect(&rect);
	m_ctrl_list.InsertColumn(0, _T("���"), LVCFMT_LEFT, rect.Width()/8);//����б��⣡������  �����80,40,90���������еĿ�ȡ�������LVCFMT_LEFT�������ö��뷽ʽ������
	m_ctrl_list.InsertColumn(1, _T("������"), LVCFMT_LEFT, rect.Width() / 8);
	m_ctrl_list.InsertColumn(2, _T("������"), LVCFMT_LEFT, rect.Width() / 8);
	m_ctrl_list.InsertColumn(3, _T("����ַ"), LVCFMT_LEFT, rect.Width() / 4);
	m_ctrl_list.InsertColumn(4, _T("��ע"), LVCFMT_LEFT, 3*rect.Width() / 8);

	//��������������(�Ʊ��)       ʹѡ�е��е���  
	m_ctrl_list.SetExtendedStyle(m_ctrl_list.GetStyle() | LVS_EX_FULLROWSELECT);
	
}


// CCMediaStreamView ���

#ifdef _DEBUG
void CCMediaStreamView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCMediaStreamView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
	
}

CCMediaStreamDoc* CCMediaStreamView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCMediaStreamDoc)));
	return (CCMediaStreamDoc*)m_pDocument;
}
#endif //_DEBUG

void CCMediaStreamView::OnAdd()
{
	// TODO:  �ڴ���������������
	m_clsAddDlg.DoModal();
		
}


void CCMediaStreamView::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

//ɾ����ť
void CCMediaStreamView::OnDelete()
{
	// TODO:  �ڴ���������������
	m_nSelRow = m_ctrl_list.GetSelectionMark();
	if (m_nSelRow < 0)
	{
		MessageBox(_T("��ѡ��ɾ������!"));
	}
	else
	{
		//ɾ��ѡ�е���
		if (IDOK == m_clsDelDlg.DoModal())
		{
			m_ctrl_list.DeleteItem(m_nSelRow);
			//ɾ�����������
			for (int i = m_nSelRow; i < m_nStreamNum; i++)//ֻ����������
			{
				CString str;
				str.Format(_T("%d"), i);
				m_ctrl_list.SetItemText(i, 0, str);
			 }
		}
		m_nSelRow = -1;
		m_nStreamNum--;
		return;
	}
}

//�˵�����ɾ����Ӧ�Ƿ񼤻�
void CCMediaStreamView::OnUpdateDelete(CCmdUI *pCmdUI)
{
	m_nSelRow = -1;
	m_nSelRow = m_ctrl_list.GetSelectionMark();   //���ѡ��ɾ����
	if (m_nSelRow == -1)
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);
		
	}
	m_nSelRow = -1;
}

//ȫ��ɾ����Ӧ����
void CCMediaStreamView::Onalldelete()
{
	// TODO:  �ڴ���������������
	m_ctrl_list.DeleteAllItems();
	m_nStreamNum = 0;
	m_nSelRow = -1;
}

//�˵�����ȫ��ɾ����Ӧ�Ƿ񼤻�
void CCMediaStreamView::OnUpdatealldelete(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	if (m_nStreamNum > 0)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
	//m_nSelRow = -1;
}
//������ʾ
void CCMediaStreamView::OnProperty()
{
	m_nSelRow = m_ctrl_list.GetSelectionMark();
	m_pStream[0] = m_ctrl_list.GetItemText(m_nSelRow, 1);
	m_pStream[1] = m_ctrl_list.GetItemText(m_nSelRow, 2);
	m_pStream[2] = m_ctrl_list.GetItemText(m_nSelRow, 3);
	m_pStream[3] = m_ctrl_list.GetItemText(m_nSelRow, 4);
	m_clsPropertySheetDlg.DoModal();
}
//�˵�����������Ӧ�Ƿ񼤻�
void CCMediaStreamView::OnUpdateProperty(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	m_nSelRow = -1;
	m_nSelRow = m_ctrl_list.GetSelectionMark();
	if (m_nSelRow == -1)
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);    //����ѡ���
	}
	m_nSelRow = -1;
}
// �Ҽ��˵�
void CCMediaStreamView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu *pPopMenu, Menu;
	Menu.LoadMenu(IDR_MENU1);
	pPopMenu = Menu.GetSubMenu(0);
	pPopMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, GetParent());
}

/************************************************************************
*�������ƣ�OnAddOk
*ժҪ��ʵ����ý�������Ϣ���������б�����ʾ����    
*ȫ��Ӱ�죺protected
*��    ������
*�� �� ֵ��void
*�޸ļ�¼��
*[����]    [����/�޸���]   [�޸�ԭ��]
*2017.09.02    zxm
************************************************************************/
afx_msg LRESULT CCMediaStreamView::OnAddOk(WPARAM wParam, LPARAM lParam)
{
	CString str;
	str.Format(_T("%d"), m_nStreamNum + 1);                //�����ݸ�ʽת��ΪCString����
	m_ctrl_list.InsertItem(m_nStreamNum, str);             //�����Ӧ���
	m_ctrl_list.SetItemText(m_nStreamNum, 1, m_pStream[0]);//ʵ�������ֵ
	m_ctrl_list.SetItemText(m_nStreamNum, 2, m_pStream[1]);
	m_ctrl_list.SetItemText(m_nStreamNum, 3, m_pStream[2]);
	m_ctrl_list.SetItemText(m_nStreamNum, 4, m_pStream[3]);
	m_nStreamNum++;//��¼��ý������
	return 0;
}
