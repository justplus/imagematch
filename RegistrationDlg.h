#if !defined(AFX_REGISTRATIONDLG_H__D773088B_F4AF_41B7_9912_133ACE4D5FFC__INCLUDED_)
#define AFX_REGISTRATIONDLG_H__D773088B_F4AF_41B7_9912_133ACE4D5FFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegistrationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegistrationDlg dialog

class CRegistrationDlg : public CPropertyPage
{
// Construction
public:
	CRegistrationDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegistrationDlg)
	enum { IDD = IDD_REGISTRATION };
	int		m_transmode;
	int		m_fillval;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegistrationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegistrationDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTRATIONDLG_H__D773088B_F4AF_41B7_9912_133ACE4D5FFC__INCLUDED_)
