#if !defined(AFX_PERFERENCE_H__550824BE_7FFC_49DD_A4F0_FA4256D4ABF5__INCLUDED_)
#define AFX_PERFERENCE_H__550824BE_7FFC_49DD_A4F0_FA4256D4ABF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Perference.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPerference dialog

class CPerference : public CDialog
{
// Construction
public:
	CPerference(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPerference)
	enum { IDD = IDD_PERFERENCE };
	CComboBox	m_cb4;
	CComboBox	m_cb3;
	CComboBox	m_cb2;
	CComboBox	m_cb1;
	int cb1;
	int cb2;
	int cb3;
	int cb4;
	CString	m_savepath;
	COLORREF cornercolor;
	COLORREF infolistcolor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPerference)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPerference)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERFERENCE_H__550824BE_7FFC_49DD_A4F0_FA4256D4ABF5__INCLUDED_)
