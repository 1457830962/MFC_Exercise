
// CommunicationBookDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommunicationBook.h"
#include "CommunicationBookDlg.h"
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


// CCommunicationBookDlg �Ի���



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


// CCommunicationBookDlg ��Ϣ�������

// ���ܣ�������Ӧ�Ի�������ĳ�ʼ��     
BOOL CCommunicationBookDlg::OnInitDialog()
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
	// TODO: Add extra initialization here   
	  
	// ��������ͼ�꣬�������ǵľ�����浽����   
	hIcon[0] = theApp.LoadIcon(IDI_ICON1);
	hIcon[1] = theApp.LoadIcon(IDI_ICON2);

	// ����ͼ������CImageList����   
	m_imageList.Create(32, 32, ILC_COLOR32, 2, 2); //32X32ͼ��
	// ��2��ͼ����ӵ�ͼ������   
	for (int i = 0; i < 2; i++)
	{
	m_imageList.Add(hIcon[i]);
	}
	// Ϊ���οؼ�����ͼ������,���洢ͼ���б������οؼ�����   
	m_ctrlList_Tree.SetImageList(&m_imageList, TVSIL_NORMAL);
	// ������ڵ�   
	hRoot = m_ctrlList_Tree.InsertItem(_T("δ����"), 0, 0);
	// �ڸ��ڵ��²����ӽڵ�   
	hCataItem = m_ctrlList_Tree.InsertItem(_T("��С��"), 1, 1, hRoot, TVI_LAST);
	// Ϊ��δ���顱�ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_ctrlList_Tree.SetItemData(hCataItem, 1);
	// ������ڵ�   
    hSubItem = m_ctrlList_Tree.InsertItem(_T("��ѧͬѧ"), 0, 0);
	// �ڸ��ڵ��²����ӽڵ�
	hCataItem = m_ctrlList_Tree.InsertItem(_T("����"), 1, 1, hSubItem, TVI_LAST);
	// Ϊ����ѧͬѧ���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_ctrlList_Tree.SetItemData(hCataItem, 1);
	// �ڸ��ڵ��²����ӽڵ�
	hCataItem = m_ctrlList_Tree.InsertItem(_T("����"), 1, 1, hSubItem, TVI_LAST);
	// Ϊ����ѧͬѧ���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_ctrlList_Tree.SetItemData(hCataItem, 2);
	//��ʼ����ά����
	m_strMsg[0][0] = _T("��С��");
	m_strMsg[1][0] = _T("����");
	m_strMsg[2][0] = _T("����");

	m_ctrlDelete_BUTTON.EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//���ܣ�������Ҫ�ǽػ���������(�Դ�)                 
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

//���ܣ������ػ�                                            
void CCommunicationBookDlg::OnPaint()
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
HCURSOR CCommunicationBookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���ܣ�������Ӧ����                                                   
void CCommunicationBookDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CString strText; // ���ڵ�ı�ǩ�ı��ַ���   
	// ��ȡ��ǰѡ�нڵ�ľ��   
	HTREEITEM hItem = m_ctrlList_Tree.GetSelectedItem();
	// ��ȡѡ�нڵ�ı�ǩ�ı��ַ���   
	strText = m_ctrlList_Tree.GetItemText(hItem);
	// ���ַ�����ʾ���༭������ʾ   
	SetDlgItemText(IDC_name_EDIT, strText);
}

//���ܣ��������                                                     
void CCommunicationBookDlg::OnBnClickedAdd1Button()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_strname_EDIT == _T(""))
	{
		MessageBox(_T("��������Ϊ�գ�"),_T("��ʾ"),MB_OK);
	} 
	else
	{
		static int i;
		for (i = 0; i < 30; i++)
		{
			if (m_strMsg[i][0] == m_strname_EDIT)//�ж������Ƿ��Ѿ�����
			{
				MessageBox(_T(" �Ѵ��ڸ�������"));
				return;
			}
		}
		for (i = 0; m_strMsg[i][0] != _T("");)
		{
			i++;
		}
		UpdateData(TRUE);
		//ʵ�ֶԿռ�����ĸ�ֵ
		m_strMsg[i][0] = m_strname_EDIT ;
		//�����ϵ����Ϣ�Լ�ͼ���ʵ��
		m_ctrlList_Tree.InsertItem(m_strMsg[i][0], 1, 1, hRoot);
	}
}

//���ܣ�ʵ����տؼ��е�ֵ                                              
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

// ���ܣ�ʵ���޸���Ϣ���ұ��渴��                                  
void CCommunicationBookDlg::OnBnClickedAlterButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strname_EDIT == _T(""))
	{
		::MessageBox(NULL, _T("��ѡ���޸ĵ��"), _T("��ʾ"), MB_OK);
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

//���ܣ�ʵ��ɾ�����Ա                                             
void CCommunicationBookDlg::OnBnClickedDeleteButton()
{
	if (m_ctrlList_Tree.GetParentItem(hHandle) == NULL)
	{
		return;
	}
	m_ctrlList_Tree.DeleteItem(hHandle);

}
//���ܣ�                                                                    
void CCommunicationBookDlg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	//��ȡ�����Ϣ���������
	CPoint pt = GetCurrentMessage()->pt;//��ǰ������
	m_ctrlList_Tree.ScreenToClient(&pt);//��Ļ����ת��ΪTREE������
	UINT uFlags = 0;
	HTREEITEM hItem = m_ctrlList_Tree.HitTest(pt, &uFlags);//�����Ƿ���ITEM
	
	if (hItem == NULL)//��δѡ���򲻽���
	{
		m_ctrlGroupDelete_BUTTON.EnableWindow(FALSE);
		m_ctrlADD1_BUTTON.EnableWindow(TRUE);
		m_ctrlAlter_BUTTON.EnableWindow(FALSE);
		m_ctrlDelete_BUTTON.EnableWindow(FALSE);
		FreshMsg();
		
		//ѡ����Ǹ��ڵ�
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
	
	if (hItem != NULL && (TVHT_ONITEM & uFlags)) //�ж��Ƿ���HTREEITEM
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
		//��ȡǰѡ����ľ��Ϊ���ڵ�
		hPreHandle = hHandle;
		//���ý���
		m_ctrlList_Tree.PostMessage(WM_SETFOCUS, 0, 0);

		CString str = _T("");
		str = m_ctrlList_Tree.GetItemText(hHandle);
		//ѡ���˸��ڵ�
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

// ���ܣ��Զ�����ӷ�����Ϣ��Ӧ����                                   
afx_msg LRESULT CCommunicationBookDlg::OnGroupAdd(WPARAM wParam, LPARAM lParam)
{
	CString str;
	m_clsAddGroup.m_ctrlAddGroupDlg_EDIT.GetWindowText(str);
	HTREEITEM hSubItem = m_ctrlList_Tree.InsertItem(str, 0, 0);
	m_ctrlList_Tree.RedrawWindow();
	return (1);
}

// ���ܣ�ɾ������    
void CCommunicationBookDlg::OnBnClickedDelgroupButton()
{
	// ��ȡ��ǰѡ�нڵ�ľ��   
	HTREEITEM hItem = m_ctrlList_Tree.GetSelectedItem();
	m_ctrlList_Tree.DeleteItem(hItem);
}

//���ܣ�������ӷ���Ի��� 
void CCommunicationBookDlg::OnBnClickedAddgroupButton()
{
	m_clsAddGroup.DoModal();
}

//���ܣ���ȡ����
void CCommunicationBookDlg::OnDtnDatetimechangeBirthdayDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
