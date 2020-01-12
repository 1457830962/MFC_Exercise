
// MessagePromptADlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "MessagePromptA.h"
#include "MessagePromptADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMessagePromptADlg �Ի���



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


// CMessagePromptADlg ��Ϣ�������
/************************************************************************/
/* ���ܣ���ʼ��                                                         */
/************************************************************************/
BOOL CMessagePromptADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//��ȡ���ڵĴ�С
	CRect rcWnd;
	::GetWindowRect(this->m_hWnd, &rcWnd);
	//��ȡ�ؼ��Ĵ�С
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
	//��ʾʱ��
	CTime time = CTime::GetCurrentTime();
	CString str;
	str.Format(_T("��Ϣ��ʾ��    ��ǰʱ�� %d��%d��%d��%dʱ%d��%d��"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	SetWindowText(str);


	SetTimer(1, 1000, NULL);
	//�ж��б���Ϣ����û����Ϣ,ʹ��ʼ��ʾ��ť��û������
	int n = m_clsMessageManageDlg.v_strShow.size();
	if (n == 0)
	{
		m_ctrlNotice_BUTTON.EnableWindow(false);
	}

	m_bInitOk = TRUE;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
//������Ӧ
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMessagePromptADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMessagePromptADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/************************************************************************/
/* ���ܣ�ʵ����Ϣ�����ܣ�������Ϣ������                             */
/************************************************************************/
void CMessagePromptADlg::OnBnClickedManageButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	vector<int>::size_type i = 0;       //����vector�� size ������
	//�༭������ʾ������
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
/* ���ܣ�ʵ�������ڽ�����Ϣ��ʾ                                          */
/************************************************************************/
void CMessagePromptADlg::OnBnClickedNoticeButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_bIsNotic == false)
	{
		m_ctrlNotice_BUTTON.SetWindowText(_T("ȡ����ʾ"));
		m_bIsNotic = true;
		SetTimer(1, 1000, NULL);//m_clsMsgMngDlg.m_nEditTime
		//ʹ��Ϣ����ťʧЧ
		m_x = 0;
		//m_ctrlManage_BUTTON.EnableWindow(false);
	}
	else
	{
		m_ctrlNotice_BUTTON.SetWindowText(_T("��ʼ��ʾ"));
		m_bIsNotic = false;
		//ʹ��Ϣ����ť��Ч
		m_ctrlNotice_EDIT.SetWindowText(_T(""));
		//m_ctrlManage_BUTTON.EnableWindow(true);
	
	}
}

/************************************************************************/
/* ���ܣ�ʵ���ö�������Ϣ                                               */
/************************************************************************/
void CMessagePromptADlg::OnBnClickedTopCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (false == m_bIsTop)
	{
		this->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		m_ctrlTop.SetWindowText(_T("ȡ������"));
		m_bIsTop = true;
	}
	else
	{
		this->SetWindowPos(&wndNoTopMost, 0, 0, 100, 100, SWP_NOMOVE | SWP_NOSIZE);
		m_ctrlTop.SetWindowText(_T("����"));
		m_bIsTop = false;
	}
}
/************************************************************************/
/* ���ܣ�ʵ�ֶԻ����С�ı�                                             */
/************************************************************************/
void CMessagePromptADlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
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
/* ���ܣ�ʵ��ʵʱ��ʾϵͳʱ��                                           */
/************************************************************************/
void CMessagePromptADlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ʾϵͳʱ��
	CTime time = CTime::GetCurrentTime();
	CString str;
	str.Format(_T("��Ϣ��ʾ��    ��ǰʱ�� %d��%d��%d��%dʱ%d��%d��"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	SetWindowText(str);

	//��ʾ��ʾ��Ϣ
	if (m_bIsNotic == true)
	{
		CString strName, strContent;
		strName = _T("��Ϣ����:\r\n");
		strContent = _T(" \r\n��Ϣ����:\r\n");
		int ShowNums = v_strShowContext.size();
		static vector<int>::size_type i = 0;
		//�ظ���ʾ
		if (m_x == ShowNums)
			//ȫ�ֱ���
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
/* �Զ�����Ϣ��Ӧ������ʵ�ֽ���Ҫ��ʾ��Ϣ��ʾ�����Ի�����               */
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
		//ʹ��ʼ��ʾ��ť�ָ�
		if (ShowNums != 0)
		{
			m_ctrlNotice_BUTTON.EnableWindow(true);
		}
		return 0;
}
