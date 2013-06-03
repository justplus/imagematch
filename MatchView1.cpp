// MatchView1.cpp : implementation file
//

#include "stdafx.h"
#include "Match.h"
#include "MatchView1.h"
#include "MatchDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatchView1

IMPLEMENT_DYNCREATE(CMatchView1, CScrollView)

CMatchView1::CMatchView1()
{
	bDraw=false;
}

CMatchView1::~CMatchView1()
{
}


BEGIN_MESSAGE_MAP(CMatchView1, CScrollView)
	//{{AFX_MSG_MAP(CMatchView1)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CANCELMODE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatchView1 drawing
CMatchDoc* CMatchView1::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMatchDoc)));
	return (CMatchDoc*)m_pDocument;
}

void CMatchView1::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CMatchView1::OnDraw(CDC* pDC)
{
	CMatchDoc* pDoc = GetDocument();
	m_frame2.Show(pDC->GetSafeHdc(),0,0,pDoc->m_imgsize2.width*pDoc->scale1,pDoc->m_imgsize2.height*pDoc->scale1,0,0);
	if(pDoc->isdeletefeas1)
	{
		//CRect rect=pDoc->m_rectTracker.m_rect; 
		pDoc->m_rectTracker1.m_rect=pDoc->m_rect2;
		pDC->LPtoDP(&pDoc->m_rectTracker1.m_rect);
		//pDoc->m_rectTracker.GetTrueRect(&rect);
		//pDC->LPtoDP(&rect);
		pDoc->m_rectTracker1.Draw(pDC);
	}
	ReleaseDC(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMatchView1 diagnostics

#ifdef _DEBUG
void CMatchView1::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMatchView1::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMatchView1 message handlers

void CMatchView1::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMatchDoc* pDoc = GetDocument();
	
	//ʹScrollbar����ͼ���С
	if(pDoc->IMG2OPEN)
		SetScrollSizes(MM_TEXT,CSize(pDoc->m_imgsize2.width,pDoc->m_imgsize2.height));
	
	//��֤ÿ�δ�������ʾͼ���ڴ��С�����ͼ���Сһ��
	m_frame2.Create(pDoc->m_imgsize2.width,pDoc->m_imgsize2.height,24);
	
	//�����ʾͼ���ڴ�����
	if(pDoc->IMG2OPEN)
	{
		ShownImage2=m_frame2.GetImage();
		cvSetImageROI(ShownImage2,cvRect(0,0,pDoc->m_imgsize2.width,pDoc->m_imgsize2.height));
		cvCopy(pDoc->showImg2,ShownImage2);
		Invalidate(FALSE);
	}
}

void CMatchView1::OnMouseMove(UINT nFlags, CPoint point) 
{
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
	// TODO: Add your message handler code here and/or call default
	CStatusBar*pFrame=(CStatusBar*)AfxGetMainWnd();   
	CStatusBar*pStatusBar=(CStatusBar*)pFrame->GetDescendantWindow(AFX_IDW_STATUS_BAR);   
	CString strMousePoint;   
	strMousePoint.Format("%3d,%3d",point.x,point.y);   
	pStatusBar->SetPaneText(pStatusBar->CommandToIndex(ID_INDICATOR_POS),strMousePoint);

	CScrollView::OnMouseMove(nFlags, point);
}


void CMatchView1::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CvSize dstsize;
	IplImage* tempimg;
	CString outmsg;
	pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;//�õ�������ָ��
	CMatchDoc* pDoc=GetDocument();
	if(pDoc->isenlarge)
	{
		if(pDoc->scale1-2.8<1e-6)
		{
			pDoc->scale1+=0.2;
			//ʹScrollbar����ͼ���С
			if(pDoc->IMG1OPEN)
				SetScrollSizes(MM_TEXT,CSize(pDoc->m_imgsize2.width*pDoc->scale1,pDoc->m_imgsize2.height*pDoc->scale1));
			
			//��֤ÿ�δ�������ʾͼ���ڴ��С�����ͼ���Сһ��
			m_frame2.Create(pDoc->m_imgsize2.width*pDoc->scale1,pDoc->m_imgsize2.height*pDoc->scale1,24);
			
			//�����ʾͼ���ڴ�����
			if(pDoc->IMG1OPEN)
			{
				ShownImage2=m_frame2.GetImage();
				//	cvSetImageROI(ShownImage1,cvRect(0,0,pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale));
				dstsize.width=pDoc->m_imgsize2.width*pDoc->scale1;
				dstsize.height=pDoc->m_imgsize2.height*pDoc->scale1;
				tempimg=cvCreateImage(dstsize,pDoc->srcImg2->depth,pDoc->srcImg2->nChannels);
				cvResize(pDoc->showImg2,tempimg,0);
				cvCopy(tempimg,ShownImage2);
				outmsg.Format(">>ͼ��2��С������%d*%d",tempimg->width,tempimg->height);	
			}
			else
				outmsg=">>û�д�ͼ��2����������";
		}
		else
			outmsg=">>ͼ��2���ܼ�������";
		pFrame->m_listbox.SetTextColor(pDoc->crTextColor1);
		pFrame->m_listbox.InsertItem(0,outmsg);
	}
	else if(pDoc->isreduce)
	{
		if(pDoc->scale1-0.2>1e-6)
		{
			pDoc->scale1-=0.2;
			//ʹScrollbar����ͼ���С
			if(pDoc->IMG1OPEN)
				SetScrollSizes(MM_TEXT,CSize(pDoc->m_imgsize2.width*pDoc->scale1,pDoc->m_imgsize2.height*pDoc->scale1));
			
			//��֤ÿ�δ�������ʾͼ���ڴ��С�����ͼ���Сһ��
			m_frame2.Create(pDoc->m_imgsize2.width*pDoc->scale1,pDoc->m_imgsize2.height*pDoc->scale1,24);
			
			//�����ʾͼ���ڴ�����
			if(pDoc->IMG1OPEN)
			{
				ShownImage2=m_frame2.GetImage();
				//	cvSetImageROI(ShownImage1,cvRect(0,0,pDoc->m_imgsize1.width*pDoc->scale,pDoc->m_imgsize1.height*pDoc->scale));
				dstsize.width=pDoc->m_imgsize2.width*pDoc->scale1;
				dstsize.height=pDoc->m_imgsize2.height*pDoc->scale1;
				tempimg=cvCreateImage(dstsize,pDoc->srcImg2->depth,pDoc->srcImg2->nChannels);
				cvResize(pDoc->showImg2,tempimg,0);
				cvCopy(tempimg,ShownImage2);
				outmsg.Format(">>ͼ��2��С��С��%d*%d",tempimg->width,tempimg->height);	
			}
			else
				outmsg=">>û�д�ͼ��2�����ܼ�С";
		}
		else
			outmsg=">>ͼ��2���ܼ�����С";
		pFrame->m_listbox.SetTextColor(pDoc->crTextColor1);
		pFrame->m_listbox.InsertItem(0,outmsg);
	}
	if(pDoc->isdeletefeas1)
	{
		int nIn; //����һ�����ĵ��ֵ��
		nIn=GetDocument()->m_rectTracker1.HitTest(point); //�����㵽������
		if(nIn<0)  //�����ı��������ڣ�
		{
		}
		else 
			//���ı��������ڣ�
		{
			// Track()��CRectTracker��������ĺ�������ʱʱ�ĸı�����ߵ�m_rect;
			GetDocument()->m_rectTracker1.Track(this,point,TRUE);
			CClientDC dc(this);
			pDoc->m_rect2=pDoc->m_rectTracker1.m_rect;
			OnPrepareDC(&dc);
			dc.DPtoLP(&pDoc->m_rect2);
			//GetDocument()->m_rectTracker.Draw(&dc);
			bDraw=TRUE;
		}
	}
	Invalidate(true);
	CScrollView::OnLButtonDown(nFlags, point);
}

void CMatchView1::OnRButtonDown(UINT nFlags, CPoint point) 
{
	int nIn; //����һ�����ĵ��ֵ��
	nIn=GetDocument()->m_rectTracker1.HitTest(point); //�����㵽������
	if(nIn<0)  //�����ı��������ڣ�
	{
		GetDocument()->isdeletefeas1=false;	
		
	}
	else 
		//���ı��������ڣ�
	{
		CClientDC dc(this);
		GetDocument()->m_rect2=GetDocument()->m_rectTracker1.m_rect;
		OnPrepareDC(&dc);
		dc.DPtoLP(&GetDocument()->m_rect2);
		GetDocument()->DeletePts1(GetDocument()->m_rect2);
	}
	Invalidate();
	CScrollView::OnRButtonDown(nFlags, point);
}

BOOL CMatchView1::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (pWnd == this && GetDocument()->m_rectTracker1.SetCursor(this, nHitTest)) 
		return TRUE;
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}
