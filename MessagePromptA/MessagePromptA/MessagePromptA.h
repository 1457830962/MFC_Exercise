
// MessagePromptA.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMessagePromptAApp: 
// �йش����ʵ�֣������ MessagePromptA.cpp
//

class CMessagePromptAApp : public CWinApp
{
public:
	CMessagePromptAApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMessagePromptAApp theApp;