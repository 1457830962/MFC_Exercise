#pragma once


// CPage2 �Ի���

class CPage2 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage2();

// �Ի�������
	enum { IDD = IDD_Page2_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};