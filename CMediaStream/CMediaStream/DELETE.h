#pragma once


// CDELETE 对话框

class CDELETE : public CDialog
{
	DECLARE_DYNAMIC(CDELETE)

public:
	CDELETE(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDELETE();

// 对话框数据
	enum { IDD = IDD_DELETE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
