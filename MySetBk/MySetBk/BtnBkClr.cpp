// BtnBkClr.cpp : 实现文件
//

#include "stdafx.h"
#include "MySetBk.h"
#include "BtnBkClr.h"




// CBtnBkClr

IMPLEMENT_DYNAMIC(CBtnBkClr, CButton)

CBtnBkClr::CBtnBkClr()
{
	m_clrBtnBk = RGB( 0,0,255);

}

CBtnBkClr::~CBtnBkClr()
{
}


BEGIN_MESSAGE_MAP(CBtnBkClr, CButton)
	//ON_BN_CLICKED(IDC_BUTTON_COLOR, &CBtnBkClr::OnBnClickedButtonColor)
	//注意控件与创建类关联
	ON_CONTROL_REFLECT( BN_CLICKED, &CBtnBkClr::OnBnClickedButtonColor)
END_MESSAGE_MAP()



// CBtnBkClr 消息处理程序


//虚函数 实现控件的自绘
void CBtnBkClr::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	//HDC& hDC = lpDrawItemStruct->hDC;
	//RECT& rc = lpDrawItemStruct->rcItem;
	////增大或减小指定矩形的宽和高
	//::InflateRect(&rc,-1,-1);
	//::FillRect( hDC,&rc,::CBrush(m_clrBtnBk));
	//if ( m_hWnd == ::GetFocus())
	//{
	//	::DrawFocusRect(hDC,&rc);
	//}
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	// 画按钮背景色
	CBrush cb;
	cb.CreateSolidBrush(GetBtnColor());
	CRect rc= lpDrawItemStruct->rcItem;
	pDC->FillRect(&rc, &cb); 
	cb.DeleteObject();
}

void CBtnBkClr::OnBnClickedButtonColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;  //使颜色对话框完全打开，并对颜色对话框初始化
	dlg.m_cc.rgbResult = m_clrBtnBk;             //返回之前选中的颜色到颜色对话框 
	if (IDOK == dlg.DoModal())
	{
		m_clrBtnBk = dlg.m_cc.rgbResult;     //返回颜色对话框选中的颜色  
		//Invalidate();
		SetBtnClr( m_clrBtnBk );
	} 		
}
COLORREF CBtnBkClr::GetBtnColor()
{
	return m_clrBtnBk;
}
BOOL CBtnBkClr::SetBtnClr(COLORREF color)
{
	m_clrBtnBk = color;
	InvalidateRect(NULL);
	//Invalidate( true);
	return true;
}
