// MySetBkView.cpp : CMySetBkView ���ʵ��
//

#include "stdafx.h"
#include "MySetBk.h"

#include "MySetBkDoc.h"
#include "MySetBkView.h"

#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMySetBkView

IMPLEMENT_DYNCREATE(CMySetBkView, CView)

BEGIN_MESSAGE_MAP(CMySetBkView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_PIC_SET, &CMySetBkView::OnPicSet)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMySetBkView ����/����

CMySetBkView::CMySetBkView()
{
	// TODO: �ڴ˴���ӹ������
    //m_stBkPro.strTitle = _T("����һ");
	m_stBkPro.nBorderWidth = 5;
	m_stBkPro.clrBorder = RGB(0,0,255);
	//m_stBkPro.strPathName = _T("");
}

CMySetBkView::~CMySetBkView()
{
}

BOOL CMySetBkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMySetBkView ����

void CMySetBkView::OnDraw(CDC* pDC)
{
	CMySetBkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//���߿�
	CRect rcWnd;
	GetClientRect(&rcWnd);
	CPen *OldPen,NewPen;
	NewPen.CreatePen(PS_SOLID,m_stBkPro.nBorderWidth,m_stBkPro.clrBorder);
	OldPen = pDC->SelectObject(&NewPen);
	pDC->MoveTo(0,0);
	pDC->LineTo(rcWnd.right,0);
	pDC->LineTo(rcWnd.right,rcWnd.bottom);
	pDC->LineTo(0,rcWnd.bottom);
	pDC->LineTo(0,0);
	pDC->SelectObject(OldPen);
	NewPen.DeleteObject();
	
	//��ʾָ��·��ͼƬ
	if ( m_stBkPro.strPathName != _T(""))
	{
		CImage Image;
		Image.Load( m_stBkPro.strPathName);
		CRect rcBk = rcWnd;
		rcBk.DeflateRect( m_stBkPro.nBorderWidth,m_stBkPro.nBorderWidth);
		Image.Draw( pDC->m_hDC,rcBk);
	}
	//����
	CFont *oldFont,newFont;
	LOGFONT lf;
	//��ȡԭ������������������޸�
	pDC->GetCurrentFont()->GetLogFont(&lf);
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfHeight =-50;
	lf.lfWidth = 0;
	_tcscpy(lf.lfFaceName,_T("����"));
	newFont.CreateFontIndirect(&lf);
	oldFont = pDC->SelectObject(&newFont);

	pDC->SetBkMode( TRANSPARENT);
	pDC->SetBkColor( RGB( 0,0,0 ));
	pDC->DrawText( m_stBkPro.strTitle,&rcWnd,DT_CENTER);

	pDC->SelectObject(oldFont);
}


// CMySetBkView ��ӡ

BOOL CMySetBkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMySetBkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMySetBkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMySetBkView ���

#ifdef _DEBUG
void CMySetBkView::AssertValid() const
{
	CView::AssertValid();
}

void CMySetBkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMySetBkDoc* CMySetBkView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySetBkDoc)));
	return (CMySetBkDoc*)m_pDocument;
}
#endif //_DEBUG


// CMySetBkView ��Ϣ�������

void CMySetBkView::OnPicSet()
{
	// TODO: �ڴ���������������
	//m_clsPicSetDlg.m_strTitle = m_stBkPro.strTitle;
	m_clsPicSetDlg.m_nSliderMark = m_stBkPro.nBorderWidth;
	//m_clsPicSetDlg.m_ctrBtnColor.SetBtnClr( m_stBkPro.clrBorder );
	if ( m_clsPicSetDlg.DoModal() == IDOK )
	{
		m_stBkPro.strTitle = m_clsPicSetDlg.m_strTitle;
		m_stBkPro.nBorderWidth = m_clsPicSetDlg.m_nSliderMark;
		m_stBkPro.clrBorder = m_clsPicSetDlg.m_ctrBtnColor.GetBtnColor();
		m_stBkPro.strPathName = m_clsPicSetDlg.m_strPathName;
		Invalidate( true );
	}
}
//ʹͼƬ��ʧ����ʾ
BOOL CMySetBkView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	pDC->SetStretchBltMode( HALFTONE );

	return CView::OnEraseBkgnd(pDC);
}

void CMySetBkView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    //��ȡ״̬����ַ
	CStatusBar* pStatus = (CStatusBar*)GetParentFrame()->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	if ( pStatus )
	{
		CString str;
		str.Format(_T("X = %d,Y = %d  "),point.x,point.y);
		CClientDC dc(this);
		CSize sz=dc.GetTextExtent(str);
		pStatus->SetPaneInfo( 0,IDS_STRING_LOCATE,SBPS_NORMAL,sz.cx);
		pStatus->SetPaneText( 0,str );
	}
	CView::OnMouseMove(nFlags, point);
}
