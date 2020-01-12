
// CMediaStreamView.cpp : CCMediaStreamView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
  //自定义消息响应函数
    ON_MESSAGE(WM_ADD_OK, &CCMediaStreamView::OnAddOk)
END_MESSAGE_MAP()

// CCMediaStreamView 构造/析构

CCMediaStreamView::CCMediaStreamView()
	: CFormView(CCMediaStreamView::IDD)
{
	// TODO:  在此处添加构造代码
	m_nStreamNum = 0;   //添加流媒体条数赋初值
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
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CCMediaStreamView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//使添加对话框的流媒体与主界面显示的流媒体共一类存
	m_clsAddDlg.m_pStream1 = m_pStream;

	//使属性页与主界面显示的流媒体共一类存
	m_clsPropertySheetDlg.m_pStream = m_pStream;

	//使主窗口句柄赋予添加流媒体对话框，便发送消息到主界面
	m_hwnd = this->m_hWnd;//获取窗口句柄
	m_clsAddDlg.m_pHwnd = &m_hwnd;//将句柄地址赋给指针变量

	DWORD dwStyle = m_ctrl_list.GetExtendedStyle();                    //添加列表框的网格线！！！
	
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_ctrl_list.SetExtendedStyle(dwStyle);
	CRect rect;
	GetClientRect(&rect);
	m_ctrl_list.InsertColumn(0, _T("序号"), LVCFMT_LEFT, rect.Width()/8);//添加列标题！！！！  这里的80,40,90用以设置列的宽度。！！！LVCFMT_LEFT用来设置对齐方式！！！
	m_ctrl_list.InsertColumn(1, _T("流名称"), LVCFMT_LEFT, rect.Width() / 8);
	m_ctrl_list.InsertColumn(2, _T("流类型"), LVCFMT_LEFT, rect.Width() / 8);
	m_ctrl_list.InsertColumn(3, _T("流地址"), LVCFMT_LEFT, rect.Width() / 4);
	m_ctrl_list.InsertColumn(4, _T("备注"), LVCFMT_LEFT, 3*rect.Width() / 8);

	//设置行数和列数(制表格)       使选中的行点亮  
	m_ctrl_list.SetExtendedStyle(m_ctrl_list.GetStyle() | LVS_EX_FULLROWSELECT);
	
}


// CCMediaStreamView 诊断

#ifdef _DEBUG
void CCMediaStreamView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCMediaStreamView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
	
}

CCMediaStreamDoc* CCMediaStreamView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCMediaStreamDoc)));
	return (CCMediaStreamDoc*)m_pDocument;
}
#endif //_DEBUG

void CCMediaStreamView::OnAdd()
{
	// TODO:  在此添加命令处理程序代码
	m_clsAddDlg.DoModal();
		
}


void CCMediaStreamView::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}

//删除按钮
void CCMediaStreamView::OnDelete()
{
	// TODO:  在此添加命令处理程序代码
	m_nSelRow = m_ctrl_list.GetSelectionMark();
	if (m_nSelRow < 0)
	{
		MessageBox(_T("请选中删除的项!"));
	}
	else
	{
		//删除选中的项
		if (IDOK == m_clsDelDlg.DoModal())
		{
			m_ctrl_list.DeleteItem(m_nSelRow);
			//删除后进行排序
			for (int i = m_nSelRow; i < m_nStreamNum; i++)//只需对序号排序
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

//菜单项中删除响应是否激活
void CCMediaStreamView::OnUpdateDelete(CCmdUI *pCmdUI)
{
	m_nSelRow = -1;
	m_nSelRow = m_ctrl_list.GetSelectionMark();   //鼠标选中删除项
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

//全部删除响应函数
void CCMediaStreamView::Onalldelete()
{
	// TODO:  在此添加命令处理程序代码
	m_ctrl_list.DeleteAllItems();
	m_nStreamNum = 0;
	m_nSelRow = -1;
}

//菜单项中全部删除响应是否激活
void CCMediaStreamView::OnUpdatealldelete(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
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
//属性显示
void CCMediaStreamView::OnProperty()
{
	m_nSelRow = m_ctrl_list.GetSelectionMark();
	m_pStream[0] = m_ctrl_list.GetItemText(m_nSelRow, 1);
	m_pStream[1] = m_ctrl_list.GetItemText(m_nSelRow, 2);
	m_pStream[2] = m_ctrl_list.GetItemText(m_nSelRow, 3);
	m_pStream[3] = m_ctrl_list.GetItemText(m_nSelRow, 4);
	m_clsPropertySheetDlg.DoModal();
}
//菜单项中属性响应是否激活
void CCMediaStreamView::OnUpdateProperty(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	m_nSelRow = -1;
	m_nSelRow = m_ctrl_list.GetSelectionMark();
	if (m_nSelRow == -1)
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);    //属性选项激活
	}
	m_nSelRow = -1;
}
// 右键菜单
void CCMediaStreamView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu *pPopMenu, Menu;
	Menu.LoadMenu(IDR_MENU1);
	pPopMenu = Menu.GetSubMenu(0);
	pPopMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, GetParent());
}

/************************************************************************
*函数名称：OnAddOk
*摘要：实现流媒体相关信息在主窗口列表中显示出来    
*全局影响：protected
*参    数：无
*返 回 值：void
*修改记录：
*[日期]    [作者/修改者]   [修改原因]
*2017.09.02    zxm
************************************************************************/
afx_msg LRESULT CCMediaStreamView::OnAddOk(WPARAM wParam, LPARAM lParam)
{
	CString str;
	str.Format(_T("%d"), m_nStreamNum + 1);                //将数据格式转换为CString类型
	m_ctrl_list.InsertItem(m_nStreamNum, str);             //插入对应序号
	m_ctrl_list.SetItemText(m_nStreamNum, 1, m_pStream[0]);//实现逐个传值
	m_ctrl_list.SetItemText(m_nStreamNum, 2, m_pStream[1]);
	m_ctrl_list.SetItemText(m_nStreamNum, 3, m_pStream[2]);
	m_ctrl_list.SetItemText(m_nStreamNum, 4, m_pStream[3]);
	m_nStreamNum++;//记录流媒体数量
	return 0;
}
