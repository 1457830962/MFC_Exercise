// MySetBkDoc.cpp : CMySetBkDoc ���ʵ��
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


// CMySetBkDoc ����/����

CMySetBkDoc::CMySetBkDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMySetBkDoc::~CMySetBkDoc()
{
}

BOOL CMySetBkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMySetBkDoc ���л�

void CMySetBkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CMySetBkDoc ���

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


// CMySetBkDoc ����
