#if !defined(AFX_OPENIMAGEDLG_H__2C0F7E4F_B7FD_4C06_B175_63A77622A316__INCLUDED_)
#define AFX_OPENIMAGEDLG_H__2C0F7E4F_B7FD_4C06_B175_63A77622A316__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenImageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenImageDlg dialog

class COpenImageDlg : public CDialog
{
// Construction
public:
	COpenImageDlg(CWnd* pParent = NULL);   // standard constructor

	CString imgpath1;
	CString imgpath2;
// Dialog Data
	//{{AFX_DATA(COpenImageDlg)
	enum { IDD = IDD_OPEN_IMAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenImageDlg)
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENIMAGEDLG_H__2C0F7E4F_B7FD_4C06_B175_63A77622A316__INCLUDED_)
