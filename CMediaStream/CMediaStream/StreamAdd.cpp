// StreamAdd.cpp : 实现文件
//
#include "stdafx.h"
#include "CMediaStream.h"
#include "StreamAdd.h"
#include "afxdialogex.h"


// CStreamAdd 对话框

IMPLEMENT_DYNAMIC(CStreamAdd, CDialog)

CStreamAdd::CStreamAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CStreamAdd::IDD, pParent)
	, m_strEDIT_name(_T(""))
	, m_strEDIT_remark(_T(""))
	, m_strIPadress(0)
	, m_strCOMBO_style(_T(""))
{

}

CStreamAdd::~CStreamAdd()
{
}

void CStreamAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_name, m_ctrlEDIT_name);
	DDX_Text(pDX, IDC_EDIT_name, m_strEDIT_name);
	DDV_MaxChars(pDX, m_strEDIT_name, 16);
	DDX_Control(pDX, IDC_COMBO_style, m_ctrlCOMBO_style);
	DDX_Control(pDX, IDC_EDIT_remark, m_ctrlEDIT_remark);
	DDX_Text(pDX, IDC_EDIT_remark, m_strEDIT_remark);
	DDV_MaxChars(pDX, m_strEDIT_remark, 128);
	DDX_Control(pDX, IDC_IPADDRESS, m_ctrlIPadress);
	DDX_IPAddress(pDX, IDC_IPADDRESS, m_strIPadress);
	DDX_CBString(pDX, IDC_COMBO_style, m_strCOMBO_style);
}


BEGIN_MESSAGE_MAP(CStreamAdd, CDialog)
	ON_BN_CLICKED(IDOK, &CStreamAdd::OnBnClickedOk)
	//ON_EN_CHANGE(IDC_EDIT_name, &CStreamAdd::OnEnChangeEditname)
END_MESSAGE_MAP()

// CStreamAdd 消息处理程序

/************************************************************************
*函数名称：OnBnClickedOk
*摘要：实现添加流媒体信息保存
*全局影响：public
*参    数：无
*返 回 值：void
*修改记录：
*[日期]   [作者/修改者]   [修改原因]
*2017.09.02   zxm  
************************************************************************/
void CStreamAdd::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_strEDIT_name == _T("") || m_strIPadress == 0 || m_strEDIT_remark == _T("") || m_strCOMBO_style == _T(""))
	{
		AfxMessageBox(_T("请将信息填充完整！"));
	}
	else
	{
		m_ctrlEDIT_name.GetWindowText(m_pStream1[0]);
		m_ctrlCOMBO_style.GetWindowText(m_pStream1[1]);
		m_ctrlIPadress.GetWindowText(m_pStream1[2]);
		m_ctrlEDIT_remark.GetWindowText(m_pStream1[3]);
		//向父窗口传递消息
		::SendMessage(*m_pHwnd, WM_ADD_OK, 1, 1);
		//添加成功后，清除添加对话框的记录
		m_ctrlEDIT_name.SetWindowText(_T(""));
		m_ctrlCOMBO_style.SetWindowText(_T(""));
		m_ctrlIPadress.SetWindowText(_T(""));
		m_ctrlEDIT_remark.SetWindowText(_T(""));
		CDialog::OnOK();
	}
		
}

