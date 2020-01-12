// SettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MySetBk.h"
#include "SettingDlg.h"


// CSettingDlg 对话框

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


// CSettingDlg 消息处理程序

BOOL CSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置提示
	EnableToolTips( true);
	m_ctrTips.Create(this);
    m_ctrTips.Activate(true);
	m_ctrTips.AddTool( GetDlgItem(IDC_EDIT_TITLE),L"标题不要超过16个字");
	m_ctrTips.AddTool( GetDlgItem(IDC_BUTTON_COLOR),L"点击选择边框颜色");
	m_ctrTips.AddTool( GetDlgItem(IDC_EDIT_PATHNAME),L"点击“浏览”按钮选择背景图片路径名");
	m_ctrTips.AddTool( GetDlgItem(IDC_BUTTON_SCAN),L"选择背景图片");
	m_ctrTips.AddTool( GetDlgItem(IDC_SLIDER_WIDTH),L"范围为1~30");

	//设置滑块
	m_ctrSlider.SetRange(1,30);
	m_ctrSlider.SetPos(m_nSliderMark);
	SetDlgItemInt(IDC_EDIT_WIDTH,m_nSliderMark,true);
	//设置默认标题
	SetDlgItemText( IDC_EDIT_TITLE,_T("画面一"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
//通过滑块设置编辑框的值
void CSettingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    nPos = m_ctrSlider.GetPos();
	SetDlgItemInt(IDC_EDIT_WIDTH,nPos,true);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
//通过编辑框的值设置滑块的位置
void CSettingDlg::OnEnChangeEditWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
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

	// TODO:  在此添加控件通知处理程序代码
}
//截获消息，实现提示条
BOOL CSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
    m_ctrTips.RelayEvent( pMsg );
	return CDialog::PreTranslateMessage(pMsg);
}
//浏览图片路径
void CSettingDlg::OnBnClickedButtonScan()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg( true,NULL,NULL,OFN_ENABLESIZING|OFN_EXPLORER,_T("位图文件(*.bmp)|*.bmp|PNG文件格式(*.png)|*.png|JPG文件格式(*.jpg)|*.jpg||"),this);
	if ( dlg.DoModal() == IDOK )
	{
		SetDlgItemText( IDC_EDIT_PATHNAME,dlg.GetPathName());
	}
}


void CSettingDlg::OnEnChangeEditTitle()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
