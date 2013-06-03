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
	// ������Ƥ��
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
	//ʹScrollbar����ͼ���С
	if(pDoc->IMG1OPEN)
		SetScrollSizes(MM_TEXT,CSize(pDoc->m_imgsize1.width,pDoc->m_imgsize1.height));
	//��֤ÿ�δ�������ʾͼ���ڴ��С�����ͼ���Сһ��
	m_frame1.Create(pDoc->m_imgsize1.width,pDoc->m_imgsize1.height,24);	
	//�����ʾͼ���ڴ�����
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
	//�����������
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
	pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;//�õ�������ָ��
	CMatchDoc* pDoc=GetDocument();
	if(pDoc->isenlarge)
	{
		if(pDoc->scale-2.8<1e-6)
		{
			pDoc->scale+=0.2;
			//ʹScrollbar����ͼ���С
			if(pDoc->IMG1OPEN)
				SetScrollSizes(MM_TEXT,CSize(pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale));
			
			//��֤ÿ�δ�������ʾͼ���ڴ��С�����ͼ���Сһ��
			m_frame1.Create(pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale,24);
			
			//�����ʾͼ���ڴ�����
			if(pDoc->IMG1OPEN)
			{
				ShownImage1=m_frame1.GetImage();
			//	cvSetImageROI(ShownImage1,cvRect(0,0,pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale));
				dstsize.width=pDoc->m_imgsize1.width*pDoc->scale;
				dstsize.height=pDoc->m_imgsize1.height*pDoc->scale;
				tempimg=cvCreateImage(dstsize,pDoc->srcImg1->depth,pDoc->srcImg1->nChannels);
				cvResize(pDoc->showImg1,tempimg,0);
				cvCopy(tempimg,ShownImage1);
				outmsg.Format(">>ͼ��1��С������%d*%d",tempimg->width,tempimg->height);	
			}
			else
				outmsg=">>û�д�ͼ��1����������";
		}
		else
			outmsg=">>ͼ��1���ܼ�������";
		pFrame->m_listbox.SetTextColor(pDoc->crTextColor1);
		pFrame->m_listbox.InsertItem(0,outmsg);
	}
	else if(pDoc->isreduce)
	{
		if(pDoc->scale-0.2>1e-6)
		{
			pDoc->scale-=0.2;
			//ʹScrollbar����ͼ���С
			if(pDoc->IMG1OPEN)
				SetScrollSizes(MM_TEXT,CSize(pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale));
			
			//��֤ÿ�δ�������ʾͼ���ڴ��С�����ͼ���Сһ��
			m_frame1.Create(pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale,24);
			
			//�����ʾͼ���ڴ�����
			if(pDoc->IMG1OPEN)
			{
				ShownImage1=m_frame1.GetImage();
				//	cvSetImageROI(ShownImage1,cvRect(0,0,pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale));
				dstsize.width=pDoc->m_imgsize1.width*pDoc->scale;
				dstsize.height=pDoc->m_imgsize1.height*pDoc->scale;
				tempimg=cvCreateImage(dstsize,pDoc->srcImg1->depth,pDoc->srcImg1->nChannels);
				cvResize(pDoc->showImg1,tempimg,0);
				cvCopy(tempimg,ShownImage1);
				outmsg.Format(">>ͼ��1��С��С��%d*%d",tempimg->width,tempimg->height);	
			}
			else
				outmsg=">>û�д�ͼ��1�����ܼ�С";
		}
		else
			outmsg=">>ͼ��1���ܼ�����С";
		pFrame->m_listbox.SetTextColor(pDoc->crTextColor1);
		pFrame->m_listbox.InsertItem(0,outmsg);
	}
	else if(pDoc->isview)
	{
		
	}
	if(pDoc->isdeletefeas)
	{
		int nIn; //����һ�����ĵ��ֵ��
		nIn=GetDocument()->m_rectTracker.HitTest(point); //�����㵽������
		if(nIn<0)  //�����ı��������ڣ�
		{
		}
		else 
			//���ı��������ڣ�
		{
			// Track()��CRectTracker��������ĺ�������ʱʱ�ĸı�����ߵ�m_rect;
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
		int nIn; //����һ�����ĵ��ֵ��
		nIn=GetDocument()->m_rectTracker2.HitTest(point); //�����㵽������
		if(nIn<0)  //�����ı��������ڣ�
		{
		}
		else 
			//���ı��������ڣ�
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

//ɾ��ѡ�еĽǵ㣬�������Ƥ��Ĺ���
void CMatchView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(GetDocument()->isdeletefeas)
	{
		int nIn; //����һ�����ĵ��ֵ��
		nIn=GetDocument()->m_rectTracker.HitTest(point); //�����㵽������
		if(nIn<0)  //�����ı��������ڣ�
		{
			GetDocument()->isdeletefeas=false;		 
		}
		else 
			//���ı��������ڣ�
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
		int nIn1; //����һ�����ĵ��ֵ��
		nIn1=GetDocument()->m_rectTracker2.HitTest(point); //�����㵽������
		if(nIn1<0)  //�����ı��������ڣ�
		{
			GetDocument()->isdeleteline=false;		 
		}
		else 
			//���ı��������ڣ�
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
