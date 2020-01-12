// MySetBkDoc.cpp : CMySetBkDoc 类的实现
//

#include "stdafx.h"
#include "MySetBk.h"

#include "MySetBkDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMySetBkDoc

IMPLEMENT_DYNCREATE(CMySetBkDoc, CDocument)

BEGIN_MESSAGE_MAP(CMySetBkDoc, CDocument)
END_MESSAGE_MAP()


// CMySetBkDoc 构造/析构

CMySetBkDoc::CMySetBkDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMySetBkDoc::~CMySetBkDoc()
{
}

BOOL CMySetBkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMySetBkDoc 序列化

void CMySetBkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CMySetBkDoc 诊断

#ifdef _DEBUG
void CMySetBkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMySetBkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMySetBkDoc 命令
