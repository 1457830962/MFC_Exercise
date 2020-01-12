// BtnBkColor.cpp : 实现文件
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



// CBtnBkColor 消息处理程序


// BtnBkColor.cpp : 实现文件
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



// CBtnBkColor 消息处理程序



void CBtnBkColor::OnBnClickedButtonColor()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CBtnBkColor::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
}
