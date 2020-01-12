// MessageManage.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "MessagePromptA.h"
#include "MessageManage.h"
#include "afxdialogex.h"

// CMessageManage �Ի���

IMPLEMENT_DYNAMIC(CMessageManage, CDialogEx)

CMessageManage::CMessageManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMessageManage::IDD, pParent)
	, m_strNoticeList(_T(""))
	, m_strMsgList(_T(""))
{

}

CMessageManage::~CMessageManage()
{
}

void CMessageManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ctrlNoticeList);
	DDX_LBString(pDX, IDC_LIST2, m_strNoticeList);
	DDX_Control(pDX, IDC_LIST1, m_ctrlMsgList);
	DDX_LBString(pDX, IDC_LIST1, m_strMsgList);
}

BEGIN_MESSAGE_MAP(CMessageManage, CDialogEx)
	ON_BN_CLICKED(IDC_Add_BUTTON, &CMessageManage::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_AllLeft_BUTTON, &CMessageManage::OnBnClickedAllleftButton)
	ON_BN_CLICKED(IDC_AllRight_BUTTON, &CMessageManage::OnBnClickedAllrightButton)
	ON_BN_CLICKED(IDC_Delete_BUTTON, &CMessageManage::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_Left_BUTTON, &CMessageManage::OnBnClickedLeftButton)
	ON_BN_CLICKED(IDC_Right_BUTTON, &CMessageManage::OnBnClickedRightButton)
	ON_BN_CLICKED(IDCANCEL, &CMessageManage::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_DownUp_BUTTON, &CMessageManage::OnBnClickedDownupButton)
	ON_BN_CLICKED(IDC_TurnUp_BUTTON, &CMessageManage::OnBnClickedTurnupButton)
	ON_BN_CLICKED(IDOK, &CMessageManage::OnBnClickedOk)
	//�Զ���Ϣ
   ON_MESSAGE(WM_NEWMESSAGE, &CMessageManage::OnNewMessage)
END_MESSAGE_MAP()


// CMessageManage ��Ϣ�������


BOOL CMessageManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//�����д洢��Ϣ���Ƶ��ܸ���
	vector<int>::size_type i_NameNum = v_strName.size();
	//�����д洢��ʾ��Ϣ���Ƶĸ���
	vector<int>::size_type i_ShowNum = v_strShow.size();
	CString str;
	if (i_NameNum == 0)
	{
		return 0;
	}
	else
	{
		//��Ϣ�б���г�ʼ��
	   if (i_ShowNum == 0)
		{
			static vector<int>::size_type i;
			for (i = 0; i < i_NameNum; i++)
			{
				m_ctrlMsgList.InsertString(i, v_strName[i]);
			}
		}
		else
		{
			//��Ҫ��ʾ�����ݴ�����ʾ�б��н��г�ʼ��
			static vector<int>::size_type j;
			for (j = 0; j < i_ShowNum; j++)
			{
				m_ctrlNoticeList.InsertString(j, v_strShow[j]);
				//�����ʼ��ʾ������Ϣ
				//str = v_strShow[j];
				//v_strReShow.push_back(str);
			}
			//��������Ϣ������Ϣ�б��н��г�ʼ��
			static vector<int>::size_type m;
			static vector<int>::size_type n;
			int k = 0;
			for (m = 0; m < i_NameNum; m++)
			{
				//�ж�Ҫ��ʾ����Ϣ����Ϣ�����Ƿ���ͬ������ͬ�����Ϣ������ӵ���Ϣ�б���
				bool flats = true;
				for (n = 0; n < i_ShowNum; n++)
				{
					if (v_strName[m] == v_strShow[n])
					{
						flats = false;
					}
				}
				if (flats == true)
				{
					m_ctrlMsgList.InsertString(k++, v_strName[m]);
				}

			}
		}
	}
	//�����ʼ��¼
	for (unsigned int m = 0; m < v_strName.size(); m++)
	{
		str = v_strName[m];
		v_strReName.push_back(str);
		str = v_strContent[m];
		v_strReContent.push_back(str);
	}
	//��¼��Ϣ����
	v_nMsgNums = v_strName.size();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

/************************************************************************/
/* ���ܣ������Ϣ��ť                                                   */
/************************************************************************/
void CMessageManage::OnBnClickedAddButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_clsAddNewsDlg.DoModal();
}

/************************************************************************/
/* ���ܣ�����ʾ�б�����Ŀȫ�����Ƶ���Ϣ�б�                             */
/************************************************************************/
void CMessageManage::OnBnClickedAllleftButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i;
	int nums = m_ctrlNoticeList.GetCount();//��ȡ��ʾ�б�����Ŀ����
	for (i = 0; i < nums; nums--)
	{
		m_ctrlNoticeList.GetText(i, m_strNoticeList);//��ȡ��Ӧ����Ϣ��
		m_ctrlMsgList.AddString(m_strNoticeList);
		m_ctrlNoticeList.DeleteString(i);
	}
	m_strNoticeList = _T("");
}
/************************************************************************/
/*���ܣ�����Ϣ�б�����Ŀȫ�����Ƶ���ʾ�б�                              */
/************************************************************************/
void CMessageManage::OnBnClickedAllrightButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	int i,nums;
	nums = m_ctrlMsgList.GetCount();
	for ( i = 0;i < nums; nums--)
	{
		int counts = m_ctrlNoticeList.GetCount();
		m_ctrlMsgList.GetText(i, m_strMsgList);//��ȡ��Ӧ����Ϣ��
		m_ctrlNoticeList.InsertString(counts, m_strMsgList);//���õ�����Ϣ�������е���ʾ�б�
		m_ctrlMsgList.DeleteString(i);
	}
	m_strMsgList = _T("");
}

/************************************************************************/
/*���ܣ�ɾ����Ϣ�б���ѡ�е���Ϣ                                        */
/************************************************************************/
void CMessageManage::OnBnClickedDeleteButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_ctrlMsgList.GetCurSel() >= 0)   //�ж��Ƿ���ѡ����Ϣ
	{
		m_ctrlMsgList.GetText(m_ctrlMsgList.GetCurSel(), m_strMsgList);//��ȡ��ǰѡ����Ŀֵ
		m_ctrlMsgList.DeleteString(m_ctrlMsgList.GetCurSel());
		//ɾ�������´����Ϣ
		vector<int>::size_type i;
		for (i = 0; i < v_strName.size(); i++)
		{
			if (m_strMsgList == v_strName[i]) //��ȡǰ��ɾ����Ŀ��Ȼ��������������Ӧɾ������
			{
				//�����洢�����Ķ�Ӧ��Ϣ
				v_strName.erase(v_strName.begin() + i);
				v_strContent.erase(v_strContent.begin() + i);
				//�����½������ж�Ӧ����Ϣ��
				m_clsAddNewsDlg.v_strNewMsgName.erase(m_clsAddNewsDlg.v_strNewMsgName.begin() + i);
			}
		}

	}
	else
	{
		MessageBox(_T("��ѡ��ɾ���"));
	}
	m_strMsgList = _T("");
}

/************************************************************************/
/*���ܣ���ѡ����Ŀ����ʾ�б����Ƶ���Ϣ�б�                              */
/************************************************************************/
void CMessageManage::OnBnClickedLeftButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_strNoticeList == _T(""))
	{
		MessageBox(_T("��ѡ��ת���"));
	}
	else
	{
		m_ctrlMsgList.AddString(m_strNoticeList);
		m_ctrlNoticeList.DeleteString(m_ctrlNoticeList.GetCurSel());
		
	}
	m_strNoticeList = _T("");

}
/************************************************************************/
/* ���ܣ�ʵ�ֽ�ѡ����Ŀ����                                             */
/************************************************************************/
void CMessageManage::OnBnClickedRightButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_strMsgList == _T(""))
	{
		MessageBox(_T("��ѡ��ת���"));
	}
	else
	{
		m_ctrlNoticeList.AddString(m_strMsgList);
		m_ctrlMsgList.DeleteString(m_ctrlMsgList.GetCurSel());
	 }
	m_strMsgList = _T("");
}
/************************************************************************/
/* ���ܣ�����ȡ���༭��ʾ��Ϣ������նԻ���                            */
/************************************************************************/
void CMessageManage::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	unsigned int i;
	//��Ϣ���Ƿ�仯
	if (v_nMsgNums != v_strName.size())
	{
		v_strName.clear();
		v_strContent.clear();
		m_clsAddNewsDlg .v_strNewMsgName.clear();

		for (i = 0; i < v_strReName.size(); i++)
		{
			str = v_strReName[i];
			v_strName.push_back(str);
			m_clsAddNewsDlg.v_strNewMsgName.push_back(str);
			str = v_strReContent[i];
			v_strContent.push_back(str);

		}
	}
	//��Ϣλ���Ƿ�仯
	else
	{
		bool flats = 0;
		for (i = 0; i < v_strName.size(); i++)
		{
			if (v_strName[i] != v_strReName[i])
			{
				flats = 1;
				break;
			}
		}
		if (flats == 1)
		{
			v_strName.clear();
			v_strContent.clear();
			m_clsAddNewsDlg.v_strNewMsgName.clear();
			for (i = 0; i < v_strReName.size(); i++)
			{
				str = v_strReName[i];
				v_strName.push_back(str);
				m_clsAddNewsDlg.v_strNewMsgName.push_back(str);
				str = v_strReContent[i];
				v_strContent.push_back(str);

			}

		}
	}
	UpdateData(true);
	this->GetParent()->SendMessage(WM_MESSAGEMANAGE, 1, 1);
	v_strReName.clear();
	v_strReContent.clear();
	v_strShow.clear();
	CDialogEx::OnCancel();
}
/************************************************************************/
/* ���ܣ�ʵ�ֽ���ʾ�б�����Ŀ�����ƶ�                                   */
/************************************************************************/
void CMessageManage::OnBnClickedDownupButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_strNoticeList == _T(""))
	{
		MessageBox(_T("��ѡ����Ҫ�ƶ����"));
	}
	else
	{
		if (m_ctrlNoticeList.GetCurSel() == m_ctrlNoticeList.GetCount() - 1)
		{
			MessageBox(_T("����Ϊ�ײ㣬�������ƣ�"));
			//return;
		}
		else
		{
			m_ctrlNoticeList.InsertString(m_ctrlNoticeList.GetCurSel() + 2, m_strNoticeList);
			m_ctrlNoticeList.DeleteString(m_ctrlNoticeList.GetCurSel());
		}
	}
}
/************************************************************************/
/* ���ܣ�ʵ�ֽ���ʾ�б�����Ŀ�����ƶ�                                   */
/************************************************************************/
void CMessageManage::OnBnClickedTurnupButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	int index = m_ctrlNoticeList.GetCurSel();
	if (m_strNoticeList == _T(""))
	{
		MessageBox(_T("��ѡ��ĳ�"));
	}
	else
	{
		if (m_ctrlNoticeList.GetCurSel() == 0)
		{
			MessageBox(_T("����Ϊ���㣬�������ƣ�"));
		}
		else
		{
		    m_ctrlNoticeList.InsertString(m_ctrlNoticeList.GetCurSel() - 1, m_strNoticeList);
			m_ctrlNoticeList.DeleteString(index + 1);
		}
	}
	m_strNoticeList = _T("");
}
/************************************************************************/
/* ���ܣ����޸�����ʵ�ֱ���                                             */
/************************************************************************/
void CMessageManage::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	v_strShow.clear();
	CString str;
	int ShowNums = m_ctrlNoticeList.GetCount();
	for (int i = 0; i < ShowNums; ShowNums--)   //������Ҫ��ʾ��Ϣʱ����ѭ��
	{
		m_ctrlNoticeList.GetText(i, str);
		v_strShow.push_back(str);  //����Ҫ����������ʾ����Ϣ����v_strShow
		m_ctrlNoticeList.DeleteString(i);  //ʵ�ֽ��������Ϣɾ��
	}
	UpdateData(true);
	this->GetParent()->SendMessage(WM_MESSAGEMANAGE, 1, 1);
	v_strReName.clear();
	v_strReContent.clear();
	v_strShow.clear();
	CDialogEx::OnOK();
}

/************************************************************************/
/* �Զ�����Ϣ�������ܣ�ʵ������½���Ϣ��ֵ����Ϣ������               */
/************************************************************************/
afx_msg LRESULT CMessageManage::OnNewMessage(WPARAM wParam, LPARAM lParam)
{
	m_ctrlMsgList.AddString(m_clsAddNewsDlg.m_strNewName_EDIT);
	v_strName.push_back(m_clsAddNewsDlg.m_strNewName_EDIT);//���������Ϣ��ѹ������
	v_strContent.push_back(m_clsAddNewsDlg.m_strNewContent_EDIT);//���������Ϣ����ѹ������
	return 0;
}


