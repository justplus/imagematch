// MatchView.cpp : implementation of the CMatchView class
//

#include "stdafx.h"
#include "Match.h"

#include "MatchDoc.h"
#include "MatchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatchView

IMPLEMENT_DYNCREATE(CMatchView, CScrollView)

BEGIN_MESSAGE_MAP(CMatchView, CScrollView)
	//{{AFX_MSG_MAP(CMatchView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatchView construction/destruction

CMatchView::CMatchView()
{
	// TODO: add construction code here
	bDraw=false;
	//m_rectBox=GetDocument()->m_rectTracker.m_rect;
}

CMatchView::~CMatchView()
{
}

BOOL CMatchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMatchView drawing

void CMatchView::OnDraw(CDC* pDC)
{
	CMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	m_frame1.Show(pDC->GetSafeHdc(),0,0,pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale,0,0);
	// 绘制橡皮筋
	if(pDoc->isdeletefeas)
	{
		//CRect rect=pDoc->m_rectTracker.m_rect; 
		pDoc->m_rectTracker.m_rect=pDoc->m_rect1;
		pDC->LPtoDP(&pDoc->m_rectTracker.m_rect);
		//pDoc->m_rectTracker.GetTrueRect(&rect);
		//pDC->LPtoDP(&rect);
		pDoc->m_rectTracker.Draw(pDC);
	}
	if(pDoc->isdeleteline)
	{
		//CRect rect=pDoc->m_rectTracker.m_rect; 
		pDoc->m_rectTracker2.m_rect=pDoc->m_rect3;
		pDC->LPtoDP(&pDoc->m_rectTracker2.m_rect);
		//pDoc->m_rectTracker.GetTrueRect(&rect);
		//pDC->LPtoDP(&rect);
		pDoc->m_rectTracker2.Draw(pDC);
	}
	ReleaseDC(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMatchView printing

BOOL CMatchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMatchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMatchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMatchView diagnostics

#ifdef _DEBUG
void CMatchView::AssertValid() const
{
	CView::AssertValid();
}

void CMatchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMatchDoc* CMatchView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMatchDoc)));
	return (CMatchDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMatchView message handlers

void CMatchView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


void CMatchView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CMatchDoc* pDoc = GetDocument();
	//使Scrollbar符合图像大小
	if(pDoc->IMG1OPEN)
		SetScrollSizes(MM_TEXT,CSize(pDoc->m_imgsize1.width,pDoc->m_imgsize1.height));
	//保证每次创建的显示图像内存大小与待打开图像大小一致
	m_frame1.Create(pDoc->m_imgsize1.width,pDoc->m_imgsize1.height,24);	
	//填充显示图像内存区域
	if(pDoc->IMG1OPEN)
	{
		ShownImage1=m_frame1.GetImage();
		cvSetImageROI(ShownImage1,cvRect(0,0,pDoc->m_imgsize1.width,pDoc->m_imgsize1.height));
		cvCopy(pDoc->showImg1,ShownImage1,NULL);
		cvResetImageROI(ShownImage1);
		Invalidate(false);
	}	
}

void CMatchView::OnMouseMove(UINT nFlags, CPoint point) 
{
	//设置鼠标手势
	HCURSOR hlcursor;
	if(GetDocument()->isenlarge)
	{
		hlcursor= LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR1));
		SetCursor(hlcursor);
		//GetCapture();
	}
	else if(GetDocument()->isreduce)
	{
		hlcursor= LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR2));
		SetCursor(hlcursor);
	}
	else if(GetDocument()->isview)
	{
		hlcursor= LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW));
		SetCursor(hlcursor);
	}
	else
	{
		hlcursor= LoadCursor(NULL,IDC_ARROW);
		SetCursor(hlcursor);
	}

 	CStatusBar*pFrame=(CStatusBar*)AfxGetMainWnd();   
 	CStatusBar*pStatusBar=(CStatusBar*)pFrame->GetDescendantWindow(AFX_IDW_STATUS_BAR);   
 	CString strMousePoint;   
 	strMousePoint.Format("%3d,%3d",point.x,point.y);   
 	pStatusBar->SetPaneText(pStatusBar->CommandToIndex(ID_INDICATOR_POS),strMousePoint);   
	
	Invalidate(false);
	CScrollView::OnMouseMove(nFlags, point);
}

void CMatchView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CvSize dstsize;
	IplImage* tempimg;
	CString outmsg;
	pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;//得到主窗口指针
	CMatchDoc* pDoc=GetDocument();
	if(pDoc->isenlarge)
	{
		if(pDoc->scale-2.8<1e-6)
		{
			pDoc->scale+=0.2;
			//使Scrollbar符合图像大小
			if(pDoc->IMG1OPEN)
				SetScrollSizes(MM_TEXT,CSize(pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale));
			
			//保证每次创建的显示图像内存大小与待打开图像大小一致
			m_frame1.Create(pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale,24);
			
			//填充显示图像内存区域
			if(pDoc->IMG1OPEN)
			{
				ShownImage1=m_frame1.GetImage();
			//	cvSetImageROI(ShownImage1,cvRect(0,0,pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale));
				dstsize.width=pDoc->m_imgsize1.width*pDoc->scale;
				dstsize.height=pDoc->m_imgsize1.height*pDoc->scale;
				tempimg=cvCreateImage(dstsize,pDoc->srcImg1->depth,pDoc->srcImg1->nChannels);
				cvResize(pDoc->showImg1,tempimg,0);
				cvCopy(tempimg,ShownImage1);
				outmsg.Format(">>图像1大小增大至%d*%d",tempimg->width,tempimg->height);	
			}
			else
				outmsg=">>没有打开图像1，不能增大";
		}
		else
			outmsg=">>图像1不能继续增大";
		pFrame->m_listbox.SetTextColor(pDoc->crTextColor1);
		pFrame->m_listbox.InsertItem(0,outmsg);
	}
	else if(pDoc->isreduce)
	{
		if(pDoc->scale-0.2>1e-6)
		{
			pDoc->scale-=0.2;
			//使Scrollbar符合图像大小
			if(pDoc->IMG1OPEN)
				SetScrollSizes(MM_TEXT,CSize(pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale));
			
			//保证每次创建的显示图像内存大小与待打开图像大小一致
			m_frame1.Create(pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale,24);
			
			//填充显示图像内存区域
			if(pDoc->IMG1OPEN)
			{
				ShownImage1=m_frame1.GetImage();
				//	cvSetImageROI(ShownImage1,cvRect(0,0,pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale));
				dstsize.width=pDoc->m_imgsize1.width*pDoc->scale;
				dstsize.height=pDoc->m_imgsize1.height*pDoc->scale;
				tempimg=cvCreateImage(dstsize,pDoc->srcImg1->depth,pDoc->srcImg1->nChannels);
				cvResize(pDoc->showImg1,tempimg,0);
				cvCopy(tempimg,ShownImage1);
				outmsg.Format(">>图像1大小减小至%d*%d",tempimg->width,tempimg->height);	
			}
			else
				outmsg=">>没有打开图像1，不能减小";
		}
		else
			outmsg=">>图像1不能继续减小";
		pFrame->m_listbox.SetTextColor(pDoc->crTextColor1);
		pFrame->m_listbox.InsertItem(0,outmsg);
	}
	else if(pDoc->isview)
	{
		
	}
	if(pDoc->isdeletefeas)
	{
		int nIn; //定义一个鼠标的点击值；
		nIn=GetDocument()->m_rectTracker.HitTest(point); //看看点到了哪了
		if(nIn<0)  //不在四边形区域内；
		{
		}
		else 
			//在四边形区域内：
		{
			// Track()是CRectTracker中最富魅力的函数。它时时的改变调用者的m_rect;
			GetDocument()->m_rectTracker.Track(this,point,TRUE);
			CClientDC dc(this);
			pDoc->m_rect1=pDoc->m_rectTracker.m_rect;
			OnPrepareDC(&dc);
			dc.DPtoLP(&pDoc->m_rect1);
			//GetDocument()->m_rectTracker.Draw(&dc);
			bDraw=TRUE;
		}
	}
	else if(pDoc->isdeleteline)
	{
		int nIn; //定义一个鼠标的点击值；
		nIn=GetDocument()->m_rectTracker2.HitTest(point); //看看点到了哪了
		if(nIn<0)  //不在四边形区域内；
		{
		}
		else 
			//在四边形区域内：
		{
			GetDocument()->m_rectTracker2.Track(this,point,TRUE);
			CClientDC dc(this);
			pDoc->m_rect3=pDoc->m_rectTracker2.m_rect;
			OnPrepareDC(&dc);
			dc.DPtoLP(&pDoc->m_rect3);
			//GetDocument()->m_rectTracker.Draw(&dc);
			bDraw=TRUE;
		}
	}
	Invalidate(true);
	CScrollView::OnLButtonDown(nFlags, point);
}

//删除选中的角点，清除“橡皮筋”的功能
void CMatchView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(GetDocument()->isdeletefeas)
	{
		int nIn; //定义一个鼠标的点击值；
		nIn=GetDocument()->m_rectTracker.HitTest(point); //看看点到了哪了
		if(nIn<0)  //不在四边形区域内；
		{
			GetDocument()->isdeletefeas=false;		 
		}
		else 
			//在四边形区域内：
		{
			CClientDC dc(this);
			GetDocument()->m_rect1=GetDocument()->m_rectTracker.m_rect;
			OnPrepareDC(&dc);
			dc.DPtoLP(&GetDocument()->m_rect1);
			GetDocument()->DeletePts(GetDocument()->m_rect1);
		}
	}
	else if(GetDocument()->isdeleteline)
	{
		int nIn1; //定义一个鼠标的点击值；
		nIn1=GetDocument()->m_rectTracker2.HitTest(point); //看看点到了哪了
		if(nIn1<0)  //不在四边形区域内；
		{
			GetDocument()->isdeleteline=false;		 
		}
		else 
			//在四边形区域内：
		{
			CClientDC dc(this);
			GetDocument()->m_rect3=GetDocument()->m_rectTracker2.m_rect;
			OnPrepareDC(&dc);
			dc.DPtoLP(&GetDocument()->m_rect3);
			//GetDocument()->DeletePts(GetDocument()->m_rect3);
			GetDocument()->DeleteLines(GetDocument()->matchpt,GetDocument()->m_rect3);
		}
	}
	Invalidate();
	CScrollView::OnRButtonDown(nFlags, point);
}

BOOL CMatchView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (pWnd == this && GetDocument()->m_rectTracker.SetCursor(this, nHitTest)) 
	return TRUE;
	if (pWnd == this && GetDocument()->m_rectTracker2.SetCursor(this, nHitTest)) 
	return TRUE;
}
