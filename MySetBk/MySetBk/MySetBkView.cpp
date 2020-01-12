// MySetBkView.cpp : CMySetBkView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_PIC_SET, &CMySetBkView::OnPicSet)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMySetBkView 构造/析构

CMySetBkView::CMySetBkView()
{
	// TODO: 在此处添加构造代码
    //m_stBkPro.strTitle = _T("画面一");
	m_stBkPro.nBorderWidth = 5;
	m_stBkPro.clrBorder = RGB(0,0,255);
	//m_stBkPro.strPathName = _T("");
}

CMySetBkView::~CMySetBkView()
{
}

BOOL CMySetBkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMySetBkView 绘制

void CMySetBkView::OnDraw(CDC* pDC)
{
	CMySetBkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//画边框
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
	
	//显示指定路径图片
	if ( m_stBkPro.strPathName != _T(""))
	{
		CImage Image;
		Image.Load( m_stBkPro.strPathName);
		CRect rcBk = rcWnd;
		rcBk.DeflateRect( m_stBkPro.nBorderWidth,m_stBkPro.nBorderWidth);
		Image.Draw( pDC->m_hDC,rcBk);
	}
	//标题
	CFont *oldFont,newFont;
	LOGFONT lf;
	//获取原有字体参数，并进行修改
	pDC->GetCurrentFont()->GetLogFont(&lf);
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfHeight =-50;
	lf.lfWidth = 0;
	_tcscpy(lf.lfFaceName,_T("宋体"));
	newFont.CreateFontIndirect(&lf);
	oldFont = pDC->SelectObject(&newFont);

	pDC->SetBkMode( TRANSPARENT);
	pDC->SetBkColor( RGB( 0,0,0 ));
	pDC->DrawText( m_stBkPro.strTitle,&rcWnd,DT_CENTER);

	pDC->SelectObject(oldFont);
}


// CMySetBkView 打印

BOOL CMySetBkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMySetBkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMySetBkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CMySetBkView 诊断

#ifdef _DEBUG
void CMySetBkView::AssertValid() const
{
	CView::AssertValid();
}

void CMySetBkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMySetBkDoc* CMySetBkView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySetBkDoc)));
	return (CMySetBkDoc*)m_pDocument;
}
#endif //_DEBUG


// CMySetBkView 消息处理程序

void CMySetBkView::OnPicSet()
{
	// TODO: 在此添加命令处理程序代码
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
//使图片无失真显示
BOOL CMySetBkView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pDC->SetStretchBltMode( HALFTONE );

	return CView::OnEraseBkgnd(pDC);
}

void CMySetBkView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    //获取状态栏地址
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
