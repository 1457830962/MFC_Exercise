// MySetBk.h : MySetBk Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMySetBkApp:
// �йش����ʵ�֣������ MySetBk.cpp
//

class CMySetBkApp : public CWinApp
{
public:
	CMySetBkApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMySetBkApp theApp;