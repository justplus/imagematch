// MatchView.h : interface of the CMatchView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATCHVIEW_H__3137072C_D3F9_4780_B3FA_A1D94526EC51__INCLUDED_)
#define AFX_MATCHVIEW_H__3137072C_D3F9_4780_B3FA_A1D94526EC51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MatchDoc.h"

class CMatchView : public CScrollView
{
protected: // create from serialization only
	CMatchView();
	DECLARE_DYNCREATE(CMatchView)

// Attributes
public:
	CMatchDoc* GetDocument();
	CMainFrame* pFrame;
	CImage m_frame1;
	IplImage* ShownImage1;
	BOOL bDraw;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatchView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMatchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMatchView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MatchView.cpp
inline CMatchDoc* CMatchView::GetDocument()
   { return (CMatchDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATCHVIEW_H__3137072C_D3F9_4780_B3FA_A1D94526EC51__INCLUDED_)
