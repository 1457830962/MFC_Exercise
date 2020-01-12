// PropertSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "CMediaStream.h"
#include "PropertSheet.h"
#include "afxdialogex.h"


// CPropertSheet 对话框

IMPLEMENT_DYNAMIC(CPropertSheet, CDialog)

CPropertSheet::CPropertSheet(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertSheet::IDD, pParent)
{
	m_nCurSelTab = 0;
}

CPropertSheet::~CPropertSheet()
{
}

void CPropertSheet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CPropertSheet, CDialog)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB1, &CPropertSheet::OnTcnSelchangingTab1)
	ON_BN_CLICKED(IDOK, &CPropertSheet::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPropertSheet::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPropertSheet 消息处理程序

//界面初始化
BOOL CPropertSheet::OnInitDialog()
{
	CDialog::OnInitDialog();
	//为Tab Control增加两个页面
	m_tab.InsertItem(0, _T("常规"));
	m_tab.InsertItem(1, _T("网络"));
	//创建两个对话框
	m_clsPage1.Create(IDD_Page1_DIALOG, &m_tab);
	m_clsPage2.Create(IDD_Page2_DIALOG, &m_tab);
	//设置属性页显示的范围
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_clsPage1.MoveWindow(&rc);
	m_clsPage2.MoveWindow(&rc);
	//显示页面
	m_clsPage1.ShowWindow(SW_SHOW);
	m_clsPage2.ShowWindow(SW_HIDE);

	//初始化默认页面1并设置页面的值
	m_clsPage1.m_ctrlEDIT1_name.SetWindowText(m_pStream[0]);
	m_clsPage1.m_ctrlProSheet1_style.SetWindowText(m_pStream[1]);
	m_clsPage1.m_ctrlIP1.SetWindowText(m_pStream[2]);
	m_clsPage1.m_ctrlEDIT1_remark.SetWindowText(m_pStream[3]);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


// 功能：选项卡的单击实现page1和page2切换（通知父窗口控件的标签选择项正在改变）
void CPropertSheet::OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	m_nCurSelTab = m_tab.GetCurSel();
	switch (m_nCurSelTab)
	{
	case 0:
		m_clsPage1.ShowWindow(SW_HIDE);
		m_clsPage2.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_clsPage1.ShowWindow(SW_SHOW);
		m_clsPage2.ShowWindow(SW_HIDE);
		break;
	default:
		break;
	}
	*pResult = 0;
}


void CPropertSheet::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnOK();
}

void CPropertSheet::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
