// MyPlayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyPlayer.h"
#include "MyPlayerDlg.h"

#include <shlwapi.h>
#include <strsafe.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMyPlayerDlg 对话框




CMyPlayerDlg::CMyPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//清除文件路径
	ZeroMemory( m_strIniPath,sizeof( m_strIniPath ));
	//清除配置数据
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
	//自定义
	ON_NOTIFY(NM_CHANGE, IDC_HK_BOSS, &CMyPlayerDlg::OnBosskeyChange)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CK_PS, IDC_CK_AUTOFIT,&CMyPlayerDlg::OnClickItem )
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RD_AUTO_UPDATE, IDC_RD_NOT_UPDATE,&CMyPlayerDlg::OnClickItem )
	ON_EN_CHANGE(IDC_ED_STEPTIMER, &CMyPlayerDlg::OnEnChangeEdSteptimer)
	ON_EN_CHANGE(IDC_ED_VERSION, &CMyPlayerDlg::OnEnChangeEdVersion)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_HK_BOSS, &CMyPlayerDlg::OnNMOutofmemoryHkBoss)
END_MESSAGE_MAP()


// CMyPlayerDlg 消息处理程序

BOOL CMyPlayerDlg::OnInitDialog()
{
	//配置对话框初始化
	LoadConfig();


	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    
	//控件类与其父窗口关联
	m_ctrHotkey.SubclassDlgItem( IDC_HK_BOSS, this );

	GetDlgItem( IDC_CB_LANGUAGE)->SetFocus();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CMyPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
BOOL CMyPlayerDlg::LoadConfig()
{
	// 获取当前程序文件目录
	::GetModuleFileName( NULL, m_strIniPath, MAX_PATH );
	//删除以“\”结尾的文件名
	::PathRemoveFileSpec(m_strIniPath);
	//使字符串以“\”结尾
	::PathAddBackslash(m_strIniPath);
	//连接两字符串，设置配置文件名
	StringCbCat( m_strIniPath,MAX_PATH,_T("config.ini"));
	//是否存在该路径的配置文件 是 加载该配置文件
	if ( ::PathFileExists(m_strIniPath) == TRUE )
	{
		// 语言  获取有关控件的值
		m_stConfig.iLanguage = (int)::GetPrivateProfileInt( _T("BASE"), _T("Language"), 0, m_strIniPath );
		// 快捷键
		m_stConfig.wHotkey = (WORD)::GetPrivateProfileInt( _T("BASE"), _T("Hotkey"), 1, m_strIniPath );
		// 是否使能快捷键
		m_stConfig.uiEnHot = ::GetPrivateProfileInt( _T("BASE"), _T("EnHotkey"), 1, m_strIniPath );
		// 播放选项
		m_stConfig.iPS = (int)::GetPrivateProfileInt( _T("BASE"), _T("PS"), 1, m_strIniPath );
		m_stConfig.iOnlyEnable = (int)::GetPrivateProfileInt( _T("BASE"), _T("OnlyEnable"), 1, m_strIniPath );
		m_stConfig.iAutoStop = (int)::GetPrivateProfileInt( _T("BASE"), _T("AutoStop"), 0, m_strIniPath );
		m_stConfig.iAutoFit = (int)::GetPrivateProfileInt( _T("BASE"), _T("AutoFit"), 0, m_strIniPath );
		// 步进时长
		m_stConfig.iStepTime = (int)::GetPrivateProfileInt( _T("BASE"), _T("StepTime"), 5, m_strIniPath );
		if ( m_stConfig.iStepTime < 1 )
			m_stConfig.iStepTime = 1;
		else if ( m_stConfig.iStepTime > 60 )
			m_stConfig.iStepTime = 60;
		// 升级选项
		m_stConfig.iUpdate = (int)::GetPrivateProfileInt( _T("BASE"), _T("Update"), 0, m_strIniPath );

		// 应用按钮失效
		GetDlgItem( IDC_BTN_APPLY )->EnableWindow(FALSE);
	}
	//加载默认配置文件
	else
	{
		// 语言
		m_stConfig.iLanguage = 0u;
		// 快捷键
		m_stConfig.wHotkey = MAKEWORD( 'E', HOTKEYF_ALT );
		// 是否使能快捷键
		m_stConfig.uiEnHot = 1u;
		// 播放选项
		m_stConfig.iPS = 1;
		m_stConfig.iOnlyEnable = 1;
		m_stConfig.iAutoStop = 0;
		m_stConfig.iAutoFit = 0;
		// 步进时长
		m_stConfig.iStepTime = 5;
		// 升级选项
		m_stConfig.iUpdate = 0;

		// 应用按钮激活
		GetDlgItem( IDC_BTN_APPLY )->EnableWindow(TRUE);

	}
	//设置配置初始值
	// 语言
	CComboBox* pctrLanguage = (CComboBox*)GetDlgItem( IDC_CB_LANGUAGE );
	pctrLanguage->AddString( _T("简体中文") );
	pctrLanguage->AddString( _T("繁軆中文") );
	pctrLanguage->AddString( _T("English") );
	if ( m_stConfig.iLanguage < 0 )
		m_stConfig.iLanguage = 0;
	else if ( m_stConfig.iLanguage >= pctrLanguage->GetCount() )
		m_stConfig.iLanguage = pctrLanguage->GetCount() - 1;
	pctrLanguage->SetCurSel( m_stConfig.iLanguage );

	// 快捷键
	CHotKeyCtrl* pctrHotkey = (CHotKeyCtrl*)GetDlgItem( IDC_HK_BOSS );
	pctrHotkey->SetHotKey( LOBYTE(m_stConfig.wHotkey), HIBYTE(m_stConfig.wHotkey) );

	// 是否使能快捷键
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

	// 语言
	CComboBox* pctrLanguage = (CComboBox*)GetDlgItem( IDC_CB_LANGUAGE );
	int iSel= pctrLanguage->GetCurSel();
	if ( iSel >= 0 && iSel < pctrLanguage->GetCount() )
		m_stConfig.iLanguage = iSel;
	// 快捷键
	CHotKeyCtrl* pctrHotkey = (CHotKeyCtrl*)GetDlgItem( IDC_HK_BOSS );
	m_stConfig.wHotkey = (WORD)pctrHotkey->GetHotKey();
	// 使能快捷键
	CButton* pctrEnHot = (CButton*)GetDlgItem( IDC_CK_HOTKEY );
	if ( pctrEnHot->GetCheck() & BST_CHECKED )
		m_stConfig.uiEnHot = 1;
	else
		m_stConfig.uiEnHot = 0;

	// 写文件
	CString strConfig = _T("");
	// 语言
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iLanguage );
	::WritePrivateProfileString( _T("BASE"), _T("Language"), strConfig.GetString(), m_strIniPath );
	// 快捷键
	strConfig.Format( _T("0x%04x"), m_stConfig.wHotkey );
	::WritePrivateProfileString( _T("BASE"), _T("Hotkey"), strConfig.GetString(),m_strIniPath );
	// 使能快捷键
	strConfig.Format( _T("%u"), m_stConfig.uiEnHot );
	::WritePrivateProfileString( _T("BASE"), _T("EnHotkey"), strConfig.GetString(), m_strIniPath );
	// 播放选项
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iPS );
	::WritePrivateProfileString( _T("BASE"), _T("PS"), strConfig.GetString(), m_strIniPath);
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iOnlyEnable );
	::WritePrivateProfileString( _T("BASE"), _T("OnlyEnable"), strConfig.GetString(), m_strIniPath );
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iAutoStop );
	::WritePrivateProfileString( _T("BASE"), _T("AutoStop"), strConfig.GetString(), m_strIniPath );
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iAutoFit );
	::WritePrivateProfileString( _T("BASE"), _T("AutoFit"), strConfig.GetString(), m_strIniPath );
	// 步进时长
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iStepTime );
	::WritePrivateProfileString( _T("BASE"), _T("StepTime"), strConfig.GetString(), m_strIniPath );
	// 升级选项
	strConfig.Format( _T("%u"), (UINT)m_stConfig.iUpdate );
	::WritePrivateProfileString( _T("BASE"), _T("Update"), strConfig.GetString(), m_strIniPath );

	// 禁止应用按钮
	GetDlgItem( IDC_BTN_APPLY )->EnableWindow( FALSE );
	return TRUE;

}
void CMyPlayerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( GetDlgItem(IDC_BTN_APPLY)->IsWindowEnabled() == TRUE )
	{
		SaveConfig();
	}
	OnOK();
}

void CMyPlayerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( GetDlgItem(IDC_BTN_APPLY)->IsWindowEnabled() == TRUE )
	{
		if ( MessageBox( _T("配置内容已修改，确定不保存？"), _T("是否保存"), MB_ICONMASK|MB_YESNO ) == IDYES )
		{
			OnBnClickedBtnApply();
		}
	}
	OnCancel();
}

void CMyPlayerDlg::OnBnClickedBtnApply()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveConfig();
}

void CMyPlayerDlg::OnBnClickedBtnUpdateCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str = _T("查询版本信息...\r\n当前版本:4.06.11\r\n最新版本:4.07.01\r\n\r\n有可更新的版本！\r\n");
	SetDlgItemText( IDC_ED_VERSION, str.GetString() );
}
/************************************************************************/
/* 功能：                                                                     */
/************************************************************************/
void CMyPlayerDlg::OnCbnSelchangeCbLanguage()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);
}
/************************************************************************/
/* 功能：                                                                     */
/************************************************************************/
void CMyPlayerDlg::OnBnClickedCkHotkey()
{
	// TODO: 在此添加控件通知处理程序代码

	CButton* pctrEnHot = (CButton*)GetDlgItem( IDC_CK_HOTKEY );
	CHotKeyCtrl* pctrHotkey = (CHotKeyCtrl*)GetDlgItem( IDC_HK_BOSS );
	if ( pctrEnHot->GetCheck() & BST_CHECKED )
		pctrHotkey->EnableWindow( TRUE );
	else
		pctrHotkey->EnableWindow( FALSE );

	// 激活应用
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);
}
void CMyPlayerDlg::OnBosskeyChange(NMHDR* pHDR, LRESULT* lr)
{
	// 热键组合 可能修改，读取并判断
	CHotKeyCtrl* pctrHotkey = (CHotKeyCtrl*)GetDlgItem( IDC_HK_BOSS );
	WORD wHotkey = 0;
	wHotkey = (WORD)pctrHotkey->GetHotKey();
	if ( wHotkey != m_stConfig.wHotkey )
	{
		m_stConfig.wHotkey = wHotkey;
		// 激活应用
		GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);
	}
}
void CMyPlayerDlg::OnClickItem(UINT)
{
	// TODO:

	// 播放选项、升级选项 可能发生变化，激活应用
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);

}


void CMyPlayerDlg::OnEnChangeEdSteptimer()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	int iStepTime = GetDlgItemInt( IDC_ED_STEPTIMER );
	if( iStepTime < 1 )
		SetDlgItemInt( IDC_ED_STEPTIMER, 1u, FALSE );
	else if ( iStepTime > 60 )
		SetDlgItemInt( IDC_ED_STEPTIMER, 60u, FALSE );

	// 激活应用
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);
}

void CMyPlayerDlg::OnEnChangeEdVersion()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMyPlayerDlg::OnNMOutofmemoryHkBoss(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	// 激活应用
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(TRUE);
	*pResult = 0;
}
