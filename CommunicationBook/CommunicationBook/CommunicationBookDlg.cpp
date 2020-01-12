
// CommunicationBookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CommunicationBook.h"
#include "CommunicationBookDlg.h"
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


// CCommunicationBookDlg 对话框



CCommunicationBookDlg::CCommunicationBookDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommunicationBookDlg::IDD, pParent)
	, m_strname_EDIT(_T(""))
	, m_strname1_EDIT(_T(""))
	, m_strtelNumber1_EDIT(_T(""))
	, m_strtelNumber2_EDIT(_T(""))
	, m_strEmail_EDIT(_T(""))
	, m_strAddress_EDIT(_T(""))
	, m_strPrepare_EDIT(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCommunicationBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADD1_BUTTON, m_ctrlADD1_BUTTON);
	DDX_Text(pDX, IDC_name_EDIT, m_strname_EDIT);
	DDX_Text(pDX, IDC_name1_EDIT, m_strname1_EDIT);
	DDV_MaxChars(pDX, m_strname1_EDIT, 16);
	DDV_MaxChars(pDX, m_strname_EDIT, 16);
	DDX_Text(pDX, IDC_telNumber1_EDIT, m_strtelNumber1_EDIT);
	DDV_MaxChars(pDX, m_strtelNumber1_EDIT, 16);
	DDX_Text(pDX, IDC_telNumber2_EDIT, m_strtelNumber2_EDIT);
	DDV_MaxChars(pDX, m_strtelNumber2_EDIT, 16);
	DDX_Text(pDX, IDC_email_EDIT, m_strEmail_EDIT);
	DDV_MaxChars(pDX, m_strEmail_EDIT, 128);
	DDX_Text(pDX, IDC_Address_EDIT, m_strAddress_EDIT);
	DDV_MaxChars(pDX, m_strAddress_EDIT, 128);
	DDX_Text(pDX, IDC_prepare_EDIT, m_strPrepare_EDIT);
	DDV_MaxChars(pDX, m_strPrepare_EDIT, 256);
	DDX_Control(pDX, IDC_name_EDIT, m_ctrlname_EDIT);
	DDX_Control(pDX, IDC_name1_EDIT, m_ctrlname1_EDIT);
	DDX_Control(pDX, IDC_telNumber1_EDIT, m_ctrlTEI_EDIT);
	DDX_Control(pDX, IDC_telNumber2_EDIT, m_ctrlofficTEL_EDIT);
	DDX_Control(pDX, IDC_email_EDIT, m_ctrlemail_EDIT);
	DDX_Control(pDX, IDC_Address_EDIT, m_ctrlAddress_EDIT);
	DDX_Control(pDX, IDC_prepare_EDIT, m_ctrlAppendix_EDIT);
	DDX_Control(pDX, IDC_Birthday_DATETIMEPICKER, m_ctrlBirthday);
	DDX_Control(pDX, IDC_Delete_BUTTON, m_ctrlDelete_BUTTON);
	DDX_Control(pDX, IDC_AddGroup_BUTTON, m_ctrlGroupAdd_BUTTON);
	DDX_Control(pDX, IDC_DelGroup_BUTTON, m_ctrlGroupDelete_BUTTON);
	DDX_Control(pDX, IDC_Alter_BUTTON, m_ctrlAlter_BUTTON);
	DDX_Control(pDX, IDC_TREE1, m_ctrlList_Tree);
}

BEGIN_MESSAGE_MAP(CCommunicationBookDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CCommunicationBookDlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_ADD1_BUTTON, &CCommunicationBookDlg::OnBnClickedAdd1Button)
	ON_BN_CLICKED(IDC_Alter_BUTTON, &CCommunicationBookDlg::OnBnClickedAlterButton)
	ON_BN_CLICKED(IDC_Delete_BUTTON, &CCommunicationBookDlg::OnBnClickedDeleteButton)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CCommunicationBookDlg::OnNMClickTree1)
	ON_MESSAGE(WM_GROUP_ADD, &CCommunicationBookDlg::OnGroupAdd)
    ON_BN_CLICKED(IDC_DelGroup_BUTTON, &CCommunicationBookDlg::OnBnClickedDelgroupButton)
	ON_BN_CLICKED(IDC_AddGroup_BUTTON, &CCommunicationBookDlg::OnBnClickedAddgroupButton)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_Birthday_DATETIMEPICKER, &CCommunicationBookDlg::OnDtnDatetimechangeBirthdayDatetimepicker)
END_MESSAGE_MAP()


// CCommunicationBookDlg 消息处理程序

// 功能：进行相应对话框变量的初始化     
BOOL CCommunicationBookDlg::OnInitDialog()
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
	// TODO: Add extra initialization here   
	  
	// 加载两个图标，并将它们的句柄保存到数组   
	hIcon[0] = theApp.LoadIcon(IDI_ICON1);
	hIcon[1] = theApp.LoadIcon(IDI_ICON2);

	// 创建图像序列CImageList对象   
	m_imageList.Create(32, 32, ILC_COLOR32, 2, 2); //32X32图标
	// 将2个图标添加到图像序列   
	for (int i = 0; i < 2; i++)
	{
	m_imageList.Add(hIcon[i]);
	}
	// 为树形控件设置图像序列,将存储图像列表与树形控件关联   
	m_ctrlList_Tree.SetImageList(&m_imageList, TVSIL_NORMAL);
	// 插入根节点   
	hRoot = m_ctrlList_Tree.InsertItem(_T("未分组"), 0, 0);
	// 在根节点下插入子节点   
	hCataItem = m_ctrlList_Tree.InsertItem(_T("曾小明"), 1, 1, hRoot, TVI_LAST);
	// 为“未分组”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_ctrlList_Tree.SetItemData(hCataItem, 1);
	// 插入根节点   
    hSubItem = m_ctrlList_Tree.InsertItem(_T("大学同学"), 0, 0);
	// 在根节点下插入子节点
	hCataItem = m_ctrlList_Tree.InsertItem(_T("刘松"), 1, 1, hSubItem, TVI_LAST);
	// 为“大学同学”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_ctrlList_Tree.SetItemData(hCataItem, 1);
	// 在根节点下插入子节点
	hCataItem = m_ctrlList_Tree.InsertItem(_T("张三"), 1, 1, hSubItem, TVI_LAST);
	// 为“大学同学”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_ctrlList_Tree.SetItemData(hCataItem, 2);
	//初始化二维数组
	m_strMsg[0][0] = _T("曾小明");
	m_strMsg[1][0] = _T("刘松");
	m_strMsg[2][0] = _T("张三");

	m_ctrlDelete_BUTTON.EnableWindow(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//功能：函数主要是截获控制命令的(自带)                 
void CCommunicationBookDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

//功能：窗口重绘                                            
void CCommunicationBookDlg::OnPaint()
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
HCURSOR CCommunicationBookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 功能：单击响应函数                                                   
void CCommunicationBookDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	CString strText; // 树节点的标签文本字符串   
	// 获取当前选中节点的句柄   
	HTREEITEM hItem = m_ctrlList_Tree.GetSelectedItem();
	// 获取选中节点的标签文本字符串   
	strText = m_ctrlList_Tree.GetItemText(hItem);
	// 将字符串显示到编辑框中显示   
	SetDlgItemText(IDC_name_EDIT, strText);
}

//功能：添加姓名                                                     
void CCommunicationBookDlg::OnBnClickedAdd1Button()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_strname_EDIT == _T(""))
	{
		MessageBox(_T("姓名不能为空！"),_T("提示"),MB_OK);
	} 
	else
	{
		static int i;
		for (i = 0; i < 30; i++)
		{
			if (m_strMsg[i][0] == m_strname_EDIT)//判断人名是否已经存在
			{
				MessageBox(_T(" 已存在该人名！"));
				return;
			}
		}
		for (i = 0; m_strMsg[i][0] != _T("");)
		{
			i++;
		}
		UpdateData(TRUE);
		//实现对空间变量的赋值
		m_strMsg[i][0] = m_strname_EDIT ;
		//添加联系人信息以及图标的实现
		m_ctrlList_Tree.InsertItem(m_strMsg[i][0], 1, 1, hRoot);
	}
}

//功能：实现清空控件中的值                                              
void CCommunicationBookDlg::FreshMsg()
{
	m_ctrlname_EDIT.SetWindowText(_T(""));
	m_strname_EDIT = _T("");
	m_ctrlname1_EDIT.SetWindowText(_T(""));
	CTime time = CTime::GetCurrentTime();
	CString str;
	str.Format(_T("%d-%d-%d"), time.GetYear(), time.GetMonth(), time.GetDay());
	m_ctrlBirthday.SetWindowText(str);
	m_ctrlTEI_EDIT.SetWindowText(_T(""));
	m_ctrlofficTEL_EDIT.SetWindowText(_T(""));
	m_ctrlemail_EDIT.SetWindowText(_T(""));
	m_ctrlAddress_EDIT.SetWindowText(_T(""));
	m_ctrlAppendix_EDIT.SetWindowText(_T(""));
}

// 功能：实现修改信息并且保存复现                                  
void CCommunicationBookDlg::OnBnClickedAlterButton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strname_EDIT == _T(""))
	{
		::MessageBox(NULL, _T("请选择修改的项！"), _T("提示"), MB_OK);
	}
	else
	{
		static int i;
		for (i = 0; i < 30; i++)
		{
			if (m_strname_EDIT == m_strMsg[i][0])
			{
				UpdateData(TRUE);
				m_ctrlname_EDIT.GetWindowText(m_strMsg[i][0]);
				m_strname_EDIT = m_strMsg[i][0];
				m_ctrlname1_EDIT.GetWindowText(m_strMsg[i][1]);
				m_ctrlTEI_EDIT.GetWindowText(m_strMsg[i][2]);
				m_ctrlofficTEL_EDIT.GetWindowText(m_strMsg[i][3]);
				m_ctrlemail_EDIT.GetWindowText(m_strMsg[i][4]);
				m_ctrlAddress_EDIT.GetWindowText(m_strMsg[i][5]);
				m_ctrlAppendix_EDIT.GetWindowText(m_strMsg[i][6]);
				FreshMsg();

				break;
			}
		}
	}
}

//功能：实现删除组成员                                             
void CCommunicationBookDlg::OnBnClickedDeleteButton()
{
	if (m_ctrlList_Tree.GetParentItem(hHandle) == NULL)
	{
		return;
	}
	m_ctrlList_Tree.DeleteItem(hHandle);

}
//功能：                                                                    
void CCommunicationBookDlg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	//获取鼠标消息点击的坐标
	CPoint pt = GetCurrentMessage()->pt;//当前点坐标
	m_ctrlList_Tree.ScreenToClient(&pt);//屏幕坐标转换为TREE内坐标
	UINT uFlags = 0;
	HTREEITEM hItem = m_ctrlList_Tree.HitTest(pt, &uFlags);//坐标是否有ITEM
	
	if (hItem == NULL)//若未选中则不进入
	{
		m_ctrlGroupDelete_BUTTON.EnableWindow(FALSE);
		m_ctrlADD1_BUTTON.EnableWindow(TRUE);
		m_ctrlAlter_BUTTON.EnableWindow(FALSE);
		m_ctrlDelete_BUTTON.EnableWindow(FALSE);
		FreshMsg();
		
		//选择的是父节点
		if (m_ctrlList_Tree.GetParentItem(hPreHandle) == NULL)
		{
			m_ctrlList_Tree.SetItemImage(hPreHandle,1,1);
			
		}
		else
		{
			m_ctrlList_Tree.SetItemImage(hPreHandle,0,0);
		}
		m_ctrlList_Tree.PostMessage(WM_KILLFOCUS, 0, 0);
		m_ctrlList_Tree.RedrawWindow();
		return;
      }
	
	if (hItem != NULL && (TVHT_ONITEM & uFlags)) //判断是否有HTREEITEM
	{
		m_ctrlList_Tree.SelectItem(hItem);

		hHandle = m_ctrlList_Tree.GetSelectedItem();
	
		if (m_ctrlList_Tree.GetParentItem(hPreHandle) == NULL)
		{
			m_ctrlList_Tree.SetItemImage(hPreHandle, 0, 0);
			
		}
		else
		{
			m_ctrlList_Tree.SetItemImage(hPreHandle, 1, 1);

		}
		//获取前选中项的句柄为父节点
		hPreHandle = hHandle;
		//设置焦点
		m_ctrlList_Tree.PostMessage(WM_SETFOCUS, 0, 0);

		CString str = _T("");
		str = m_ctrlList_Tree.GetItemText(hHandle);
		//选中了父节点
		if (m_ctrlList_Tree.GetParentItem(hHandle) == NULL)
		{
			m_ctrlGroupDelete_BUTTON.EnableWindow(TRUE);
			m_ctrlADD1_BUTTON.EnableWindow(FALSE);
			m_ctrlAlter_BUTTON.EnableWindow(FALSE);
			m_ctrlDelete_BUTTON.EnableWindow(FALSE);
			FreshMsg();
			return;
		}
		else
		{
			m_ctrlGroupDelete_BUTTON.EnableWindow(FALSE);
			m_ctrlADD1_BUTTON.EnableWindow(TRUE);
			m_ctrlAlter_BUTTON.EnableWindow(TRUE);
			m_ctrlDelete_BUTTON.EnableWindow(TRUE);
			int i;
			for (i = 0; i < 30; i++)
			{
				if (str == m_strMsg[i][0])
				{
					UpdateData(FALSE);
					m_ctrlname_EDIT.SetWindowText(m_strMsg[i][0]);
					m_strname_EDIT = m_strMsg[i][0];
					m_ctrlname1_EDIT.SetWindowText(m_strMsg[i][1]);
					m_ctrlofficTEL_EDIT.SetWindowText(m_strMsg[i][2]);
					m_ctrlofficTEL_EDIT.SetWindowText(m_strMsg[i][3]);
					m_ctrlemail_EDIT.SetWindowText(m_strMsg[i][4]);
					m_ctrlAddress_EDIT.SetWindowText(m_strMsg[i][5]);
					m_ctrlAppendix_EDIT.SetWindowText(m_strMsg[i][6]);
					break;
				}
			}
			
		}
	}

}

// 功能：自定义添加分组消息响应函数                                   
afx_msg LRESULT CCommunicationBookDlg::OnGroupAdd(WPARAM wParam, LPARAM lParam)
{
	CString str;
	m_clsAddGroup.m_ctrlAddGroupDlg_EDIT.GetWindowText(str);
	HTREEITEM hSubItem = m_ctrlList_Tree.InsertItem(str, 0, 0);
	m_ctrlList_Tree.RedrawWindow();
	return (1);
}

// 功能：删除分组    
void CCommunicationBookDlg::OnBnClickedDelgroupButton()
{
	// 获取当前选中节点的句柄   
	HTREEITEM hItem = m_ctrlList_Tree.GetSelectedItem();
	m_ctrlList_Tree.DeleteItem(hItem);
}

//功能：弹出添加分组对话框 
void CCommunicationBookDlg::OnBnClickedAddgroupButton()
{
	m_clsAddGroup.DoModal();
}

//功能：获取日期
void CCommunicationBookDlg::OnDtnDatetimechangeBirthdayDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}
