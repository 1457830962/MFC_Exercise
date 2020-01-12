#pragma once

#include "afxwin.h"


// CBtnBkClr

class CBtnBkClr : public CButton
{
	DECLARE_DYNAMIC(CBtnBkClr)

public:
	CBtnBkClr();
	virtual ~CBtnBkClr();
public:
	COLORREF m_clrBtnBk;
	COLORREF GetBtnColor();
	BOOL SetBtnClr(COLORREF color);

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	afx_msg void OnBnClickedButtonColor();
};


