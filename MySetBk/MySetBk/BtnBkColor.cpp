// BtnBkColor.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "MySetBk.h"
#include "BtnBkColor.h"


// CBtnBkColor

//IMPLEMENT_DYNAMIC(CBtnBkColor, CButton)

CBtnBkColor::CBtnBkColor(void)
{

}

CBtnBkColor::~CBtnBkColor(void)
{
}


BEGIN_MESSAGE_MAP(CBtnBkColor, CButton)
END_MESSAGE_MAP()



// CBtnBkColor ��Ϣ�������


// BtnBkColor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MySetBk.h"
#include "BtnBkColor.h"


// CBtnBkColor

//IMPLEMENT_DYNAMIC(CBtnBkColor, CButton)

CBtnBkColor::CBtnBkColor(void)
{
}

CBtnBkColor::~CBtnBkColor(void)
{
}


BEGIN_MESSAGE_MAP(CBtnBkColor, CButton)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CBtnBkColor::OnBnClickedButtonColor)
END_MESSAGE_MAP()



// CBtnBkColor ��Ϣ�������



void CBtnBkColor::OnBnClickedButtonColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CBtnBkColor::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  ������Ĵ����Ի���ָ����
}
