#if !defined(AFX_MATCHVIEW1_H__8251F93C_E6FB_4F92_BAFE_DFEE706F54EA__INCLUDED_)
#define AFX_MATCHVIEW1_H__8251F93C_E6FB_4F92_BAFE_DFEE706F54EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatchView1.h : header file
//
#include "MatchDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CMatchView1 view

class CMatchView1 : public CScrollView
{
protected:
	CMatchView1();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMatchView1)

// Attributes
public:
	CMatchDoc* GetDocument();
	CMainFrame* pFrame;
	CImage m_frame2;
	IplImage* ShownImage2;
	BOOL bDraw;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatchView1)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMatchView1();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMatchView1)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATCHVIEW1_H__8251F93C_E6FB_4F92_BAFE_DFEE706F54EA__INCLUDED_)
