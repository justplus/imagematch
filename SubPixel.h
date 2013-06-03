#if !defined(AFX_SUBPIXEL_H__6B2E4827_5FE8_4216_9FCB_203F60212EDB__INCLUDED_)
#define AFX_SUBPIXEL_H__6B2E4827_5FE8_4216_9FCB_203F60212EDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubPixel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubPixel dialog

class CSubPixelDlg : public CPropertyPage
{
// Construction
public:
	CSubPixelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubPixel)
	enum { IDD = IDD_SUBPIXEL };
	BOOL	m_guassblur;
	int		m_cornercount;
	double	m_min_distance;
	double	m_quality_level;
	int		m_winlength;
	int		m_max_iter;
	double	m_epsilon;
	double	m_sigma;
	int		m_guass_winwidth;
	int		m_guass_winheigth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubPixel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubPixel)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBPIXEL_H__6B2E4827_5FE8_4216_9FCB_203F60212EDB__INCLUDED_)
