// MessageManage.cpp : 实现文件
//
#include "stdafx.h"
#include "MessagePromptA.h"
#include "MessageManage.h"
#include "afxdialogex.h"

// CMessageManage 对话框

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
	//自定消息
   ON_MESSAGE(WM_NEWMESSAGE, &CMessageManage::OnNewMessage)
END_MESSAGE_MAP()


// CMessageManage 消息处理程序


BOOL CMessageManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//容器中存储信息名称的总个数
	vector<int>::size_type i_NameNum = v_strName.size();
	//容器中存储显示信息名称的个数
	vector<int>::size_type i_ShowNum = v_strShow.size();
	CString str;
	if (i_NameNum == 0)
	{
		return 0;
	}
	else
	{
		//消息列表框中初始化
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
			//把要显示的数据传入提示列表中进行初始化
			static vector<int>::size_type j;
			for (j = 0; j < i_ShowNum; j++)
			{
				m_ctrlNoticeList.InsertString(j, v_strShow[j]);
				//保存初始提示框中消息
				//str = v_strShow[j];
				//v_strReShow.push_back(str);
			}
			//把其他消息传入消息列表中进行初始化
			static vector<int>::size_type m;
			static vector<int>::size_type n;
			int k = 0;
			for (m = 0; m < i_NameNum; m++)
			{
				//判断要显示的消息与消息名称是否相同，若不同则把消息名称添加到消息列表中
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
	//保存初始记录
	for (unsigned int m = 0; m < v_strName.size(); m++)
	{
		str = v_strName[m];
		v_strReName.push_back(str);
		str = v_strContent[m];
		v_strReContent.push_back(str);
	}
	//记录消息总数
	v_nMsgNums = v_strName.size();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

/************************************************************************/
/* 功能：添加消息按钮                                                   */
/************************************************************************/
void CMessageManage::OnBnClickedAddButton()
{
	// TODO:  在此添加控件通知处理程序代码
	m_clsAddNewsDlg.DoModal();
}

/************************************************************************/
/* 功能：将提示列表中项目全部左移到消息列表                             */
/************************************************************************/
void CMessageManage::OnBnClickedAllleftButton()
{
	// TODO:  在此添加控件通知处理程序代码
	int i;
	int nums = m_ctrlNoticeList.GetCount();//获取提示列表中项目个数
	for (i = 0; i < nums; nums--)
	{
		m_ctrlNoticeList.GetText(i, m_strNoticeList);//获取对应的消息名
		m_ctrlMsgList.AddString(m_strNoticeList);
		m_ctrlNoticeList.DeleteString(i);
	}
	m_strNoticeList = _T("");
}
/************************************************************************/
/*功能：将消息列表中项目全部右移到提示列表                              */
/************************************************************************/
void CMessageManage::OnBnClickedAllrightButton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	int i,nums;
	nums = m_ctrlMsgList.GetCount();
	for ( i = 0;i < nums; nums--)
	{
		int counts = m_ctrlNoticeList.GetCount();
		m_ctrlMsgList.GetText(i, m_strMsgList);//获取对应的消息名
		m_ctrlNoticeList.InsertString(counts, m_strMsgList);//将得到的消息依次排列到提示列表
		m_ctrlMsgList.DeleteString(i);
	}
	m_strMsgList = _T("");
}

/************************************************************************/
/*功能：删除消息列表中选中的消息                                        */
/************************************************************************/
void CMessageManage::OnBnClickedDeleteButton()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_ctrlMsgList.GetCurSel() >= 0)   //判断是否有选中消息
	{
		m_ctrlMsgList.GetText(m_ctrlMsgList.GetCurSel(), m_strMsgList);//获取当前选中项目值
		m_ctrlMsgList.DeleteString(m_ctrlMsgList.GetCurSel());
		//删除后重新存放消息
		vector<int>::size_type i;
		for (i = 0; i < v_strName.size(); i++)
		{
			if (m_strMsgList == v_strName[i]) //获取前面删除项目，然后在容器中做对应删除处理
			{
				//擦除存储容器的对应消息
				v_strName.erase(v_strName.begin() + i);
				v_strContent.erase(v_strContent.begin() + i);
				//擦除新建容器中对应的消息名
				m_clsAddNewsDlg.v_strNewMsgName.erase(m_clsAddNewsDlg.v_strNewMsgName.begin() + i);
			}
		}

	}
	else
	{
		MessageBox(_T("请选择删除项！"));
	}
	m_strMsgList = _T("");
}

/************************************************************************/
/*功能：将选中项目从提示列表左移到消息列表                              */
/************************************************************************/
void CMessageManage::OnBnClickedLeftButton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_strNoticeList == _T(""))
	{
		MessageBox(_T("请选择转移项！"));
	}
	else
	{
		m_ctrlMsgList.AddString(m_strNoticeList);
		m_ctrlNoticeList.DeleteString(m_ctrlNoticeList.GetCurSel());
		
	}
	m_strNoticeList = _T("");

}
/************************************************************************/
/* 功能：实现将选中项目右移                                             */
/************************************************************************/
void CMessageManage::OnBnClickedRightButton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_strMsgList == _T(""))
	{
		MessageBox(_T("请选择转移项！"));
	}
	else
	{
		m_ctrlNoticeList.AddString(m_strMsgList);
		m_ctrlMsgList.DeleteString(m_ctrlMsgList.GetCurSel());
	 }
	m_strMsgList = _T("");
}
/************************************************************************/
/* 功能：界面取消编辑显示消息，并清空对话框                            */
/************************************************************************/
void CMessageManage::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	unsigned int i;
	//消息数是否变化
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
	//消息位子是否变化
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
/* 功能：实现将显示列表中项目向下移动                                   */
/************************************************************************/
void CMessageManage::OnBnClickedDownupButton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_strNoticeList == _T(""))
	{
		MessageBox(_T("请选择需要移动的项！"));
	}
	else
	{
		if (m_ctrlNoticeList.GetCurSel() == m_ctrlNoticeList.GetCount() - 1)
		{
			MessageBox(_T("该项为底层，不能下移！"));
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
/* 功能：实现将显示列表中项目向上移动                                   */
/************************************************************************/
void CMessageManage::OnBnClickedTurnupButton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	int index = m_ctrlNoticeList.GetCurSel();
	if (m_strNoticeList == _T(""))
	{
		MessageBox(_T("请选择某项！"));
	}
	else
	{
		if (m_ctrlNoticeList.GetCurSel() == 0)
		{
			MessageBox(_T("该项为顶层，不能上移！"));
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
/* 功能：将修改内容实现保存                                             */
/************************************************************************/
void CMessageManage::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	v_strShow.clear();
	CString str;
	int ShowNums = m_ctrlNoticeList.GetCount();
	for (int i = 0; i < ShowNums; ShowNums--)   //当有需要提示消息时进入循环
	{
		m_ctrlNoticeList.GetText(i, str);
		v_strShow.push_back(str);  //将需要在主界面显示的消息传入v_strShow
		m_ctrlNoticeList.DeleteString(i);  //实现将传完的消息删除
	}
	UpdateData(true);
	this->GetParent()->SendMessage(WM_MESSAGEMANAGE, 1, 1);
	v_strReName.clear();
	v_strReContent.clear();
	v_strShow.clear();
	CDialogEx::OnOK();
}

/************************************************************************/
/* 自定义消息函数功能：实现添加新建消息传值给消息管理窗口               */
/************************************************************************/
afx_msg LRESULT CMessageManage::OnNewMessage(WPARAM wParam, LPARAM lParam)
{
	m_ctrlMsgList.AddString(m_clsAddNewsDlg.m_strNewName_EDIT);
	v_strName.push_back(m_clsAddNewsDlg.m_strNewName_EDIT);//将新添加消息名压入容器
	v_strContent.push_back(m_clsAddNewsDlg.m_strNewContent_EDIT);//将新添加消息内容压入容器
	return 0;
}


