// MyPlayerDlg.h : ͷ�ļ�
//

#pragma once

#include "MyHotKey.h"
#include "afxwin.h"

// CMyPlayerDlg �Ի���
class CMyPlayerDlg : public CDialog
{
	TCHAR m_strIniPath[MAX_PATH];
	struct ST_CONFIG
	{
		int iLanguage;	// ����
		WORD wHotkey;	// �ϰ��
		UINT uiEnHot;	// �Ƿ�ʹ���ϰ��

		int iPS;			// ������š���ͣ
		int iOnlyEnable;		// ֻ�г��ɲ��ŵ�
		int iAutoStop;		   // �Զ���ͣ
		int iAutoFit;		       // ������Ӧ��Ƶ
		int iStepTime;		// ����ʱ��

		int iUpdate;	// ����ѡ��
	}m_stConfig;
// ����
public:
	CMyPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CMyHotKey m_ctrHotkey;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
public:
	// ��������
	BOOL LoadConfig();
	// ��������
	BOOL SaveConfig();


public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedBtnApply();
public:
	afx_msg void OnBnClickedBtnUpdateCheck();
public:
	afx_msg void OnCbnSelchangeCbLanguage();
public:
	afx_msg void OnBnClickedCkHotkey();
	//�Զ�����Ϣ
	afx_msg void OnBosskeyChange(NMHDR* pHDR, LRESULT* lr);
	// �����޸��� ���š�����ѡ��
	afx_msg void OnClickItem(UINT);				
public:
	afx_msg void OnEnChangeEdSteptimer();

public:
	afx_msg void OnEnChangeEdVersion();
public:
	afx_msg void OnNMOutofmemoryHkBoss(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedRdAutoUpdate();
};
