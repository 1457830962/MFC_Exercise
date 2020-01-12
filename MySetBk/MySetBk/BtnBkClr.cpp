// BtnBkClr.cpp : ʵ���ļ�
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
	//ע��ؼ��봴�������
	ON_CONTROL_REFLECT( BN_CLICKED, &CBtnBkClr::OnBnClickedButtonColor)
END_MESSAGE_MAP()



// CBtnBkClr ��Ϣ�������


//�麯�� ʵ�ֿؼ����Ի�
void CBtnBkClr::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  ������Ĵ����Ի���ָ����
	//HDC& hDC = lpDrawItemStruct->hDC;
	//RECT& rc = lpDrawItemStruct->rcItem;
	////������Сָ�����εĿ�͸�
	//::InflateRect(&rc,-1,-1);
	//::FillRect( hDC,&rc,::CBrush(m_clrBtnBk));
	//if ( m_hWnd == ::GetFocus())
	//{
	//	::DrawFocusRect(hDC,&rc);
	//}
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	// ����ť����ɫ
	CBrush cb;
	cb.CreateSolidBrush(GetBtnColor());
	CRect rc= lpDrawItemStruct->rcItem;
	pDC->FillRect(&rc, &cb); 
	cb.DeleteObject();
}

void CBtnBkClr::OnBnClickedButtonColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;  //ʹ��ɫ�Ի�����ȫ�򿪣�������ɫ�Ի����ʼ��
	dlg.m_cc.rgbResult = m_clrBtnBk;             //����֮ǰѡ�е���ɫ����ɫ�Ի��� 
	if (IDOK == dlg.DoModal())
	{
		m_clrBtnBk = dlg.m_cc.rgbResult;     //������ɫ�Ի���ѡ�е���ɫ  
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
