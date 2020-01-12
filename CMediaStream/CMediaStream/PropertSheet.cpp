// PropertSheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMediaStream.h"
#include "PropertSheet.h"
#include "afxdialogex.h"


// CPropertSheet �Ի���

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


// CPropertSheet ��Ϣ�������

//�����ʼ��
BOOL CPropertSheet::OnInitDialog()
{
	CDialog::OnInitDialog();
	//ΪTab Control��������ҳ��
	m_tab.InsertItem(0, _T("����"));
	m_tab.InsertItem(1, _T("����"));
	//���������Ի���
	m_clsPage1.Create(IDD_Page1_DIALOG, &m_tab);
	m_clsPage2.Create(IDD_Page2_DIALOG, &m_tab);
	//��������ҳ��ʾ�ķ�Χ
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_clsPage1.MoveWindow(&rc);
	m_clsPage2.MoveWindow(&rc);
	//��ʾҳ��
	m_clsPage1.ShowWindow(SW_SHOW);
	m_clsPage2.ShowWindow(SW_HIDE);

	//��ʼ��Ĭ��ҳ��1������ҳ���ֵ
	m_clsPage1.m_ctrlEDIT1_name.SetWindowText(m_pStream[0]);
	m_clsPage1.m_ctrlProSheet1_style.SetWindowText(m_pStream[1]);
	m_clsPage1.m_ctrlIP1.SetWindowText(m_pStream[2]);
	m_clsPage1.m_ctrlEDIT1_remark.SetWindowText(m_pStream[3]);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


// ���ܣ�ѡ��ĵ���ʵ��page1��page2�л���֪ͨ�����ڿؼ��ı�ǩѡ�������ڸı䣩
void CPropertSheet::OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}

void CPropertSheet::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
