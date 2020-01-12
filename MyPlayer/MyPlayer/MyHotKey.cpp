// MyHotKey.cpp : ʵ���ļ�
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



// CMyHotKey ��Ϣ�������



void CMyHotKey::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	NMHDR hdr;
	hdr.code = NM_CHANGE;
	hdr.hwndFrom = GetSafeHwnd();
	hdr.idFrom = GetDlgCtrlID();
	GetParent()->SendMessage( WM_NOTIFY, hdr.idFrom, (LPARAM)&hdr );

	CHotKeyCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}
