// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__2B693D6D_E645_466E_801D_75852768388A__INCLUDED_)
#define AFX_MAINFRM_H__2B693D6D_E645_466E_801D_75852768388A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Mybar.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CToolBar    m_wndToolBar;
	CListCtrl m_listbox;
	CBitmap bitmap;
	CBitmap bitmap1;
	CBitmap bitmap2;
	CBitmap bitmap3;
	CBitmap bitmap4;
	CBitmap bitmap5;
	CBitmap bitmap6;
	CBitmap bitmap7;
	CBitmap bitmap8;
	CBitmap bitmap9;
	CBitmap bitmap10;
	CBitmap bitmap11;
	CBitmap bitmap12;
	CBitmap bitmap13;
	CBitmap bitmap14;
	CBitmap bitmap15;
// Operations
public:
	int viewnum;
	void setView(int viewcount);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
//	CToolBar    m_wndToolBar;
	CMybar m_wndMyBar;
	CSplitterWnd m_wndSplitter;
	bool issplitted;//是否已分割标志

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewInfoBar();
	afx_msg void OnUpdateViewInfoBar(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdateEnlarge(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__2B693D6D_E645_466E_801D_75852768388A__INCLUDED_)
