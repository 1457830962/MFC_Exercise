// SettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MySetBk.h"
#include "SettingDlg.h"


// CSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CSettingDlg, CDialog)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
	, m_nSliderMark(0)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	//DDV_MaxChars(pDX, m_strTitle, 30);
	DDX_Control(pDX, IDC_SLIDER_WIDTH, m_ctrSlider);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nSliderMark);
	//DDV_MinMaxInt(pDX, m_nSliderMark, 0, 30);
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_ctrBtnColor);
	DDX_Text(pDX, IDC_EDIT_PATHNAME, m_strPathName);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_WIDTH, &CSettingDlg::OnEnChangeEditWidth)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CSettingDlg::OnBnClickedButtonScan)
	ON_EN_CHANGE(IDC_EDIT_TITLE , &CSettingDlg::OnEnChangeEditTitle)
END_MESSAGE_MAP()


// CSettingDlg ��Ϣ�������

BOOL CSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//������ʾ
	EnableToolTips( true);
	m_ctrTips.Create(this);
    m_ctrTips.Activate(true);
	m_ctrTips.AddTool( GetDlgItem(IDC_EDIT_TITLE),L"���ⲻҪ����16����");
	m_ctrTips.AddTool( GetDlgItem(IDC_BUTTON_COLOR),L"���ѡ��߿���ɫ");
	m_ctrTips.AddTool( GetDlgItem(IDC_EDIT_PATHNAME),L"������������ťѡ�񱳾�ͼƬ·����");
	m_ctrTips.AddTool( GetDlgItem(IDC_BUTTON_SCAN),L"ѡ�񱳾�ͼƬ");
	m_ctrTips.AddTool( GetDlgItem(IDC_SLIDER_WIDTH),L"��ΧΪ1~30");

	//���û���
	m_ctrSlider.SetRange(1,30);
	m_ctrSlider.SetPos(m_nSliderMark);
	SetDlgItemInt(IDC_EDIT_WIDTH,m_nSliderMark,true);
	//����Ĭ�ϱ���
	SetDlgItemText( IDC_EDIT_TITLE,_T("����һ"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
//ͨ���������ñ༭���ֵ
void CSettingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    nPos = m_ctrSlider.GetPos();
	SetDlgItemInt(IDC_EDIT_WIDTH,nPos,true);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
//ͨ���༭���ֵ���û����λ��
void CSettingDlg::OnEnChangeEditWidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	int nPos = GetDlgItemInt( IDC_EDIT_WIDTH);
	if ( nPos > 30 )
	{
		nPos = 30;
		SetDlgItemInt( IDC_EDIT_WIDTH,nPos,true );
		m_ctrSlider.SetPos( nPos );
	}
	if ( nPos < 1 )
	{
		nPos = 1;
		SetDlgItemInt( IDC_EDIT_WIDTH,nPos,true );
		m_ctrSlider.SetPos( nPos );
	}
	m_ctrSlider.SetPos( nPos );
	//UpdateData( false);
	m_nSliderMark = nPos;

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
//�ػ���Ϣ��ʵ����ʾ��
BOOL CSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
    m_ctrTips.RelayEvent( pMsg );
	return CDialog::PreTranslateMessage(pMsg);
}
//���ͼƬ·��
void CSettingDlg::OnBnClickedButtonScan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg( true,NULL,NULL,OFN_ENABLESIZING|OFN_EXPLORER,_T("λͼ�ļ�(*.bmp)|*.bmp|PNG�ļ���ʽ(*.png)|*.png|JPG�ļ���ʽ(*.jpg)|*.jpg||"),this);
	if ( dlg.DoModal() == IDOK )
	{
		SetDlgItemText( IDC_EDIT_PATHNAME,dlg.GetPathName());
	}
}


void CSettingDlg::OnEnChangeEditTitle()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
