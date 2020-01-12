
// MessagePromptADlg.cpp : 实现文件
//
#include "stdafx.h"
#include "MessagePromptA.h"
#include "MessagePromptADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMessagePromptADlg 对话框



CMessagePromptADlg::CMessagePromptADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMessagePromptADlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMessagePromptADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlNotice_EDIT);
	DDX_Control(pDX, IDC_Notice_BUTTON, m_ctrlNotice_BUTTON);
	DDX_Control(pDX, IDC_Manage_BUTTON, m_ctrlManage_BUTTON);
	DDX_Control(pDX, IDC_Top_CHECK, m_ctrlTop);
	DDX_Control(pDX, IDCANCEL, m_ctrlExit_BUTTON);
}

BEGIN_MESSAGE_MAP(CMessagePromptADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Manage_BUTTON, &CMessagePromptADlg::OnBnClickedManageButton)
	ON_BN_CLICKED(IDC_Notice_BUTTON, &CMessagePromptADlg::OnBnClickedNoticeButton)
	ON_BN_CLICKED(IDC_Top_CHECK, &CMessagePromptADlg::OnBnClickedTopCheck)
	ON_WM_SIZE()
	ON_WM_TIMER()
//	ON_MESSAGE(WM_MESSAGEMANAGE, &CMessagePromptADlg::OnMessagemanage)
	ON_MESSAGE(WM_MESSAGEMANAGE, &CMessagePromptADlg::OnMsgManage)
END_MESSAGE_MAP()


// CMessagePromptADlg 消息处理程序
/************************************************************************/
/* 功能：初始化                                                         */
/************************************************************************/
BOOL CMessagePromptADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//获取窗口的大小
	CRect rcWnd;
	::GetWindowRect(this->m_hWnd, &rcWnd);
	//获取控件的大小
	m_ctrlTop.GetWindowRect(m_lpBtnRect);
	m_OldPoint[0].x = rcWnd.right - m_lpBtnRect[0].right;
	m_OldPoint[0].y = rcWnd.top - m_lpBtnRect[0].top;

	m_ctrlManage_BUTTON.GetWindowRect(m_lpBtnRect + 1);
	m_OldPoint[1].x = rcWnd.right - m_lpBtnRect[1].right;
	m_OldPoint[1].y = rcWnd.top - m_lpBtnRect[1].top;

	m_ctrlNotice_BUTTON.GetWindowRect(m_lpBtnRect + 2);
	m_OldPoint[2].x = rcWnd.right - m_lpBtnRect[2].right;
	m_OldPoint[2].y = rcWnd.top - m_lpBtnRect[2].top;

	m_ctrlExit_BUTTON.GetWindowRect(m_lpBtnRect + 3);
	m_OldPoint[3].x = rcWnd.right - m_lpBtnRect[3].right;
	m_OldPoint[3].y = rcWnd.top - m_lpBtnRect[3].top;


	m_ctrlNotice_EDIT.GetWindowRect(&m_rcEdit);
	m_rcEdit.left = rcWnd.left - m_rcEdit.left;
	m_rcEdit.top = rcWnd.top - m_rcEdit.top;
	m_rcEdit.right = rcWnd.right - m_rcEdit.right;
	m_rcEdit.bottom = rcWnd.bottom - m_rcEdit.bottom;
	//显示时间
	CTime time = CTime::GetCurrentTime();
	CString str;
	str.Format(_T("消息提示器    当前时间 %d年%d月%d日%d时%d分%d秒"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	SetWindowText(str);


	SetTimer(1, 1000, NULL);
	//判断列表消息中有没有消息,使开始提示按钮有没有作用
	int n = m_clsMessageManageDlg.v_strShow.size();
	if (n == 0)
	{
		m_ctrlNotice_BUTTON.EnableWindow(false);
	}

	m_bInitOk = TRUE;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
//命令响应
void CMessagePromptADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMessagePromptADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMessagePromptADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/************************************************************************/
/* 功能：实现消息管理功能，弹出消息管理窗口                             */
/************************************************************************/
void CMessagePromptADlg::OnBnClickedManageButton()
{
	// TODO:  在此添加控件通知处理程序代码
	vector<int>::size_type i = 0;       //定义vector的 size 的类型
	//编辑框中显示的内容
	for (i = 0; i < v_strShowContext.size(); i++)
	{
		CString str;
		str = v_strShowContext[i];
		m_clsMessageManageDlg.v_strShow.push_back(str);
	}
	v_strShowContext.clear();
	m_ctrlNotice_EDIT.SetWindowText(_T(""));
	m_clsMessageManageDlg.DoModal();
}

/************************************************************************/
/* 功能：实现主窗口进行消息提示                                          */
/************************************************************************/
void CMessagePromptADlg::OnBnClickedNoticeButton()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_bIsNotic == false)
	{
		m_ctrlNotice_BUTTON.SetWindowText(_T("取消提示"));
		m_bIsNotic = true;
		SetTimer(1, 1000, NULL);//m_clsMsgMngDlg.m_nEditTime
		//使消息管理按钮失效
		m_x = 0;
		//m_ctrlManage_BUTTON.EnableWindow(false);
	}
	else
	{
		m_ctrlNotice_BUTTON.SetWindowText(_T("开始提示"));
		m_bIsNotic = false;
		//使消息管理按钮有效
		m_ctrlNotice_EDIT.SetWindowText(_T(""));
		//m_ctrlManage_BUTTON.EnableWindow(true);
	
	}
}

/************************************************************************/
/* 功能：实现置顶推送消息                                               */
/************************************************************************/
void CMessagePromptADlg::OnBnClickedTopCheck()
{
	// TODO:  在此添加控件通知处理程序代码
	if (false == m_bIsTop)
	{
		this->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		m_ctrlTop.SetWindowText(_T("取消顶置"));
		m_bIsTop = true;
	}
	else
	{
		this->SetWindowPos(&wndNoTopMost, 0, 0, 100, 100, SWP_NOMOVE | SWP_NOSIZE);
		m_ctrlTop.SetWindowText(_T("顶置"));
		m_bIsTop = false;
	}
}
/************************************************************************/
/* 功能：实现对话框大小改变                                             */
/************************************************************************/
void CMessagePromptADlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (m_bInitOk == TRUE)
	{
		CPoint point[4];
		CRect rcWnd, rect;
		::GetClientRect(this->m_hWnd, &rcWnd);
		ReSize(&rect, &m_rcEdit, &rcWnd);
		m_ctrlNotice_EDIT.MoveWindow(&rect);
		/*for(int i = 1;i < 3;i++)
		{
		ReSize((point+i),(m_OldPoint + i),&rcWnd);
		}*/
		m_lpBtnRect[0].left = cx - m_lpBtnRect[0].right + m_lpBtnRect[0].left - 20;
		m_lpBtnRect[0].right = cx - 20;
		m_ctrlTop.MoveWindow((m_lpBtnRect + 0));

		m_lpBtnRect[1].top = cy - m_lpBtnRect[1].bottom + m_lpBtnRect[1].top - 30;
		m_lpBtnRect[1].bottom = cy - 30;
		m_ctrlManage_BUTTON.MoveWindow((m_lpBtnRect + 1));

		m_lpBtnRect[2].top = cy - m_lpBtnRect[2].bottom + m_lpBtnRect[2].top - 30;
		m_lpBtnRect[2].bottom = cy - 30;
		m_ctrlNotice_BUTTON.MoveWindow((m_lpBtnRect + 2));

		m_lpBtnRect[3].left = cx - m_lpBtnRect[3].right + m_lpBtnRect[3].left - 20;
		m_lpBtnRect[3].right = cx - 20;
		m_lpBtnRect[3].top = cy - m_lpBtnRect[3].bottom + m_lpBtnRect[3].top - 30;
		m_lpBtnRect[3].bottom = cy - 30;
		m_ctrlExit_BUTTON.MoveWindow((m_lpBtnRect + 3));
	}
}

/************************************************************************/
/* 功能：实现实时显示系统时间                                           */
/************************************************************************/
void CMessagePromptADlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//显示系统时间
	CTime time = CTime::GetCurrentTime();
	CString str;
	str.Format(_T("消息提示器    当前时间 %d年%d月%d日%d时%d分%d秒"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	SetWindowText(str);

	//显示提示消息
	if (m_bIsNotic == true)
	{
		CString strName, strContent;
		strName = _T("消息名称:\r\n");
		strContent = _T(" \r\n消息内容:\r\n");
		int ShowNums = v_strShowContext.size();
		static vector<int>::size_type i = 0;
		//重复显示
		if (m_x == ShowNums)
			//全局变量
			m_x = 0;
		for (i = 0; i < v_strName.size();)
		{
			if (v_strShowContext[m_x] == v_strName[i])
			{
				break;
			}
			i++;

		}
		strName = strName + v_strShowContext[m_x++];
		strName = strName + strContent + v_strContext[i];
		m_ctrlNotice_EDIT.SetWindowText(strName);

	}
	CDialogEx::OnTimer(nIDEvent);
}

void CMessagePromptADlg::ReSize(LPRECT rect, LPRECT x, LPRECT y)
{
	rect->left = y->left - x->left;
	rect->top = y->top - x->top;
	rect->right = y->right - x->right;
	rect->bottom = y->bottom - x->bottom;
}

void CMessagePromptADlg::ReSize(CPoint *point, CPoint *x, LPRECT y)
{
	point->x = y->left - x->x;
	point->y = y->top - x->y;
}
/************************************************************************/
/* 自定义消息响应函数：实现将需要显示消息显示到主对话款中               */
/************************************************************************/
afx_msg LRESULT CMessagePromptADlg::OnMsgManage(WPARAM wParam, LPARAM lParam)
{
	int NameNums, ShowNums;
		NameNums = m_clsMessageManageDlg.v_strName.size();
		CString str;
		if (NameNums == 0)
		{
			return 0;
		}
		vector<int>::size_type i;
		for (i = 0; i < NameNums; i++)
		{
			str = m_clsMessageManageDlg.v_strName[i];
			v_strName.push_back(str);
			str = m_clsMessageManageDlg.v_strContent[i];
			v_strContext.push_back(str);
		}
	
		ShowNums = m_clsMessageManageDlg.v_strShow.size();
		vector<int>::size_type j;
		for (j = 0; j < ShowNums; j++)
		{
			str = m_clsMessageManageDlg.v_strShow[j];
			v_strShowContext.push_back(str);
		}
		//使开始提示按钮恢复
		if (ShowNums != 0)
		{
			m_ctrlNotice_BUTTON.EnableWindow(true);
		}
		return 0;
}
