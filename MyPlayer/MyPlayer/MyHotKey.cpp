// MyHotKey.cpp : 实现文件
//

#include "stdafx.h"
#include "MyPlayer.h"
#include "MyHotKey.h"


// CMyHotKey

IMPLEMENT_DYNAMIC(CMyHotKey, CHotKeyCtrl)

CMyHotKey::CMyHotKey()
{

}

CMyHotKey::~CMyHotKey()
{
}


BEGIN_MESSAGE_MAP(CMyHotKey, CHotKeyCtrl)
	ON_WM_KEYUP()
END_MESSAGE_MAP()



// CMyHotKey 消息处理程序



void CMyHotKey::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	NMHDR hdr;
	hdr.code = NM_CHANGE;
	hdr.hwndFrom = GetSafeHwnd();
	hdr.idFrom = GetDlgCtrlID();
	GetParent()->SendMessage( WM_NOTIFY, hdr.idFrom, (LPARAM)&hdr );

	CHotKeyCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}
