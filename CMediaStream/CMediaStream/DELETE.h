#pragma once


// CDELETE �Ի���

class CDELETE : public CDialog
{
	DECLARE_DYNAMIC(CDELETE)

public:
	CDELETE(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDELETE();

// �Ի�������
	enum { IDD = IDD_DELETE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
