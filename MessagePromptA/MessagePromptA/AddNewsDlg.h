#pragma once
#include "afxwin.h"
#include <vector>
using namespace std;
// CAddNewsDlg �Ի���

class CAddNewsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddNewsDlg)

public:
	CAddNewsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddNewsDlg();

// �Ի�������
	enum { IDD = IDD_Add_DIALOG };

public:
	//�洢�½���Ϣ���Ƶ�������ȫ������Ϣ
	vector<CString> v_strNewMsgName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlNewName_EDIT;
	CString m_strNewName_EDIT;
	CEdit m_ctrlNewContent_EDIT;
	CString m_strNewContent_EDIT;
	afx_msg void OnBnClickedOk();
};
