// MyPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyPlayer.h"
#include "MyPlayerDlg.h"

#include <shlwapi.h>
#include <strsafe.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMyPlayerDlg �Ի���




CMyPlayerDlg::CMyPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//����ļ�·��
	ZeroMemory( m_strIniPath,sizeof( m_strIniPath ));
	//�����������
	ZeroMemory( &m_stConfig,sizeof( m_stConfig ));
}

void CMyPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ED_STEPTIMER, m_stConfig.iStepTime);
	DDV_MinMaxInt(pDX, m_stConfig.iStepTime, 1, 60);
	DDX_Radio(pDX, IDC_RD_AUTO_UPDATE, m_stConfig.iUpdate);
	DDX_Check(pDX, IDC_CK_PS, m_stConfig.iPS);
	DDX_Check(pDX, IDC_CK_ONLYENABLE, m_stConfig.iOnlyEnable);
	DDX_Check(pDX, IDC_CK_AUTOSTOP, m_stConfig.iAutoStop);
	DDX_Check(pDX, IDC_CK_AUTOFIT, m_stConfig.iAutoFit);
}

BEGIN_MESSAGE_MAP(CMyPlayerDlg, CDialog)
	//ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMyPlayerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMyPlayerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_APPLY, &CMyPlayerDlg::OnBnClickedBtnApply)
	ON_BN_CLICKED(IDC_BTN_UPDATE_CHECK, &CMyPlayerDlg::OnBnClickedBtnUpdateCheck)
	ON_CBN_SELCHANGE(IDC_CB_LANGUAGE, &CMyPlayerDlg::OnCbnSelchangeCbLanguage)
	ON_BN_CLICKED(IDC_CK_HOTKEY, &CMyPlayerDlg::OnBnClickedCkHotkey)
	//�Զ���
	ON_NOTIFY(NM_CHANGE, IDC_HK_BOSS, &CMyPlayerDlg::OnBosskeyChange)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CK_PS, IDC_CK_AUTOFIT,&CMyPlayerDlg::OnClickItem )
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RD_AUTO_UPDATE, IDC_RD_NOT_UPDATE,&CMyPlayerDlg::OnClickItem )
	ON_EN_CHANGE(IDC_ED_STEPTIMER, &CMyPlayerDlg::OnEnChangeEdSteptimer)
	ON_EN_CHANGE(IDC_ED_VERSION, &CMyPlayerDlg::OnEnChangeEdVersion)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_HK_BOSS, &CMyPlayerDlg::OnNMOutofmemoryHkBoss)
END_MESSAGE_MAP()


// CMyPlayerDlg ��Ϣ�������

BOOL CMyPlayerDlg::OnInitDialog()
{
	//���öԻ����ʼ��
	LoadConfig();


	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	/*ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}*/

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    
	//�ؼ������丸���ڹ���
	m_ctrHotkey.SubclassDlgItem( IDC_HK_BOSS, this );

	GetDlgItem( IDC_CB_LANGUAGE)->SetFocus();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//void CMyPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
//{
//	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
//	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
//	}
//	else
//	{
//		CDialog::OnSysCommand(nID, lParam);
//	}
//}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CMyPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
BOOL CMyPlayerDlg::LoadConfig()
{
	// ��ȡ��ǰ�����ļ�Ŀ¼
	::GetModuleFileName( NULL, m_strIniPath, MAX_PATH );
	//ɾ���ԡ�\����β���ļ���
	::PathRemoveFileSpec(m_strIniPath);
	//ʹ�ַ����ԡ�\����β
	::PathAddBackslash(m_strIniPath);
	//�������ַ��������������ļ���
	StringCbCat( m_strIniPath,MAX_PATH,_T("config.ini"));
	//�Ƿ���ڸ�·���������ļ� �� ���ظ������ļ�
	if ( ::PathFileExists(m_strIniPath) == TRUE )
	{
		// ����  ��ȡ�йؿؼ���ֵ
		m_stConfig.iLanguage = (int)::GetPrivateProfileInt( _T("BASE"), _T("Language"), 0, m_strIniPath );
		// ��ݼ�
		m_stConfig.wHotkey = (WORD)::GetPrivateProfileInt( _T("BASE"), _T("Hotkey"), 1, m_strIniPath );
		// �Ƿ�ʹ�ܿ�ݼ�
		m_stConfig.uiEnHot = ::GetPrivateProfileInt( _T("BASE"), _T("EnHotkey"), 1, m_strIniPath );
		// ����ѡ��
		m_stConfig.iPS = (int)::GetPrivateProfileInt( _T("BASE"), _T("PS"), 1, m_strIniPath );
		m_stConfig.iOnlyEnable = (int)::GetPrivateProfileInt( _T("BASE"), _T("OnlyEnable"), 1, m_strIniPath );
		m_stConfig.iAutoStop = (int)::GetPrivateProfileInt( _T("BASE"), _T("AutoStop"), 0, m_strIniPath );
		m_stConfig.iAutoFit = (int)::GetPrivateProfileInt( _T("BASE"), _T("AutoFit"), 0, m_strIniPath );
		// ����ʱ��
		m_stConfig.iStepTime = (int)::GetPrivateProfileInt( _T("BASE"), _T("StepTime"), 5, m_strIniPath );
		if ( m_stConfig.iStepTime < 1 )
			m_stConfig.iStepTime = 1;
		else if ( m_stConfig.iStepTime > 60 )
			m_stConfig.iStepTime = 60;
		// ����ѡ��
		m_stConfig.iUpdate = (int)::GetPrivateProfileInt( _T("BASE"), _T("Update"), 0, m_strIniPath );

		// Ӧ�ð�ťʧЧ
		GetDlgItem( IDC_BTN_APPLY )->EnableWindow(FALSE);
	}
	//����Ĭ�������ļ�
	else
	{
		// ����
		m_stConfig.iLanguage = 0u;
		// ��ݼ�
		m_stConfig.wHotkey = MAKEWORD( 'E', HOTKEYF_ALT );
		// �Ƿ�ʹ�ܿ�ݼ�
		m_stConfig.uiEnHot = 1u;
		// ����ѡ��
		m_stConfig.iPS = 1;
		m_stConfig.iOnlyEnable = 1;
		m_stConfig.iAutoStop = 0;
		m_stConfig.iAutoFit = 0;
		// ����ʱ��
		m_stConfig.iStepTime = 5;
		// ����ѡ��
		m_stConfig.iUpdate = 0;

		// Ӧ�ð�ť����
		GetDlgItem( IDC_BTN_APPLY )->EnableWindow(TRUE);

	}
	//�������ó�ʼֵ
	// ����
	CComboBox* pctrLanguage = (CComboBox*)GetDlgItem( IDC_CB_LANGUAGE );
	pctrLanguage->AddString( _T("��������") );
	pctrLanguage->AddString( _T("��܃����") );
	pctrLanguage->AddString( _T("English") );
	if ( m_stConfig.iLanguage < 0 )
		m_stConfig.iLanguage = 0;
	else if ( m_stConfig.iLanguage >= pctrLanguage->GetCount() )
		m_stConfig.iLanguage = pctrLanguage->GetCount() - 1;
	pctrLanguage->SetCurSel( m_stConfig.iLanguage );

	// ��ݼ�
	CHotKeyCtrl* pctrHotkey = (CHotKeyCtrl*)GetDlgItem( IDC_HK_BOSS );
	pctrHotkey->SetHotKey( LOBYTE(m_stConfig.wHotkey), HIBYTE(m_stConfig.wHotkey) );

	// �Ƿ�ʹ�ܿ�ݼ�
	CButton* pctrEnHot = (CButton*)GetDlgItem( IDC_CK_HOTKEY );
	if ( m_stConfig.uiEnHot != 0 )
	{
		pctrEnHot->SetCheck( BST_CHECKED );
		pctrHotkey->EnableWindow( TRUE );
	}
	else
	{
		pctrEnHot->SetCheck( BST_UNCHECKED );
		pctrHotkey->EnableWindow( FALSE );
	}

	return TRUE;
}
BOOL CMyPlayerDlg:: SaveConfig()
{
	if( UpdateData() == FALSE )
		return FALSE;

	// ����
	CComboBox* pctrLanguage = (CComboBox*)GetDlgItem( IDC_CB_LANGUAGE );
	int iSel= pctrLanguage->GetCurSel();
	if ( iSel >= 0 && iSel < pctrLanguage->GetCount() )
		m_stConfig.iLanguage = iSel;
	// ��ݼ�
	CHotKeyCtrl* pctrHotkey = (CHotKeyCtrl*)GetDlgItem( IDC_HK_BOSS );
	m_stConfig.wHotkey = (WORD)pctrHotkey->GetHotKey();
	// ʹ�ܿ�ݼ�
	CButton* pctrEnHot = (CButton*)GetDlgItem( IDC_CK_HOTKEY );
	if ( pctrEnHot->GetCheck() & BST_CHECKED )
		m_stConfig.uiEnHot = 1;
	else
		m_stConfig.uiEnHot = 0;

	// д�ļ�
	CString strConfig = _T("");
	// ����
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iLanguage );
	::WritePrivateProfileString( _T("BASE"), _T("Language"), strConfig.GetString(), m_strIniPath );
	// ��ݼ�
	strConfig.Format( _T("0x%04x"), m_stConfig.wHotkey );
	::WritePrivateProfileString( _T("BASE"), _T("Hotkey"), strConfig.GetString(),m_strIniPath );
	// ʹ�ܿ�ݼ�
	strConfig.Format( _T("%u"), m_stConfig.uiEnHot );
	::WritePrivateProfileString( _T("BASE"), _T("EnHotkey"), strConfig.GetString(), m_strIniPath );
	// ����ѡ��
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iPS );
	::WritePrivateProfileString( _T("BASE"), _T("PS"), strConfig.GetString(), m_strIniPath);
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iOnlyEnable );
	::WritePrivateProfileString( _T("BASE"), _T("OnlyEnable"), strConfig.GetString(), m_strIniPath );
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iAutoStop );
	::WritePrivateProfileString( _T("BASE"), _T("AutoStop"), strConfig.GetString(), m_strIniPath );
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iAutoFit );
	::WritePrivateProfileString( _T("BASE"), _T("AutoFit"), strConfig.GetString(), m_strIniPath );
	// ����ʱ��
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iStepTime );
	::WritePrivateProfileString( _T("BASE"), _T("StepTime"), strConfig.GetString(), m_strIniPath );
	// ����ѡ��
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iUpdate );
	::WritePrivateProfileString( _T("BASE"), _T("Update"), strConfig.GetString(), m_strIniPath );

	// ��ֹӦ�ð�ť
	GetDlgItem( IDC_BTN_APPLY )->EnableWindow( FALSE );
	return TRUE;

}
void CMyPlayerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ( GetDlgItem(IDC_BTN_APPLY)->IsWindowEnabled() == TRUE )
	{
		SaveConfig();
	}
	OnOK();
}

void CMyPlayerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ( GetDlgItem(IDC_BTN_APPLY)->IsWindowEnabled() == TRUE )
	{
		if ( MessageBox( _T("�����������޸ģ�ȷ�������棿"), _T("�Ƿ񱣴�"), MB_ICONMASK|MB_YESNO ) == IDYES )
		{
			OnBnClickedBtnApply();
		}
	}
	OnCancel();
}

void CMyPlayerDlg::OnBnClickedBtnApply()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SaveConfig();
}

void CMyPlayerDlg::OnBnClickedBtnUpdateCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("��ѯ�汾��Ϣ...\r\n��ǰ�汾:4.06.11\r\n���°汾:4.07.01\r\n\r\n�пɸ��µİ汾��\r\n");
	SetDlgItemText( IDC_ED_VERSION, str.GetString() );
}
/************************************************************************/
/* ���ܣ�                                                                     */
/************************************************************************/
void CMyPlayerDlg::OnCbnSelchangeCbLanguage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);
}
/************************************************************************/
/* ���ܣ�                                                                     */
/************************************************************************/
void CMyPlayerDlg::OnBnClickedCkHotkey()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CButton* pctrEnHot = (CButton*)GetDlgItem( IDC_CK_HOTKEY );
	CHotKeyCtrl* pctrHotkey = (CHotKeyCtrl*)GetDlgItem( IDC_HK_BOSS );
	if ( pctrEnHot->GetCheck() & BST_CHECKED )
		pctrHotkey->EnableWindow( TRUE );
	else
		pctrHotkey->EnableWindow( FALSE );

	// ����Ӧ��
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);
}
void CMyPlayerDlg::OnBosskeyChange(NMHDR* pHDR, LRESULT* lr)
{
	// �ȼ���� �����޸ģ���ȡ���ж�
	CHotKeyCtrl* pctrHotkey = (CHotKeyCtrl*)GetDlgItem( IDC_HK_BOSS );
	WORD wHotkey = 0;
	wHotkey = (WORD)pctrHotkey->GetHotKey();
	if ( wHotkey != m_stConfig.wHotkey )
	{
		m_stConfig.wHotkey = wHotkey;
		// ����Ӧ��
		GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);
	}
}
void CMyPlayerDlg::OnClickItem(UINT)
{
	// TODO:

	// ����ѡ�����ѡ�� ���ܷ����仯������Ӧ��
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);

}


void CMyPlayerDlg::OnEnChangeEdSteptimer()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int iStepTime = GetDlgItemInt( IDC_ED_STEPTIMER );
	if( iStepTime < 1 )
		SetDlgItemInt( IDC_ED_STEPTIMER, 1u, FALSE );
	else if ( iStepTime > 60 )
		SetDlgItemInt( IDC_ED_STEPTIMER, 60u, FALSE );

	// ����Ӧ��
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);
}

void CMyPlayerDlg::OnEnChangeEdVersion()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMyPlayerDlg::OnNMOutofmemoryHkBoss(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ����Ӧ��
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);
	*pResult = 0;
}
