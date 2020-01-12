#pragma once

#define	NM_CHANGE  (WM_USER + 100) 

// CMyHotKey

class CMyHotKey : public CHotKeyCtrl
{
	DECLARE_DYNAMIC(CMyHotKey)

public:
	CMyHotKey();
	virtual ~CMyHotKey();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};
