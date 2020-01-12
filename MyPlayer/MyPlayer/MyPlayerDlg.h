// MyPlayerDlg.h : 头文件
//

#pragma once

#include "MyHotKey.h"
#include "afxwin.h"

// CMyPlayerDlg 对话框
class CMyPlayerDlg : public CDialog
{
	TCHAR m_strIniPath[MAX_PATH];
	struct ST_CONFIG
	{
		int iLanguage;	// 语言
		WORD wHotkey;	// 老板键
		UINT uiEnHot;	// 是否使能老板键

		int iPS;			// 点击播放、暂停
		int iOnlyEnable;		// 只列出可播放的
		int iAutoStop;		   // 自动暂停
		int iAutoFit;		       // 窗口适应视频
		int iStepTime;		// 步进时长

		int iUpdate;	// 升级选项
	}m_stConfig;
// 构造
public:
	CMyPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CMyHotKey m_ctrHotkey;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
public:
	// 加载配置
	BOOL LoadConfig();
	// 保存配置
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
	//自定义消息
	afx_msg void OnBosskeyChange(NMHDR* pHDR, LRESULT* lr);
	// 可能修改了 播放、升级选项
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
