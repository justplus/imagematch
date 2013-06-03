#if !defined(AFX_STMATCH_H__9FE71DA7_2729_4740_818E_B0B6D390FBC4__INCLUDED_)
#define AFX_STMATCH_H__9FE71DA7_2729_4740_818E_B0B6D390FBC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// STMatch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSTMatch dialog

class CSTMatch : public CPropertyPage
{
	DECLARE_DYNCREATE(CSTMatch)

// Construction
public:
	CSTMatch();
	~CSTMatch();

// Dialog Data
	//{{AFX_DATA(CSTMatch)
	enum { IDD = IDD_STMATCH };
	int		patch_radius;
	int		max_disparity;
	double	max_distance;
	CString	rightper;
	int		fmethod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSTMatch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSTMatch)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STMATCH_H__9FE71DA7_2729_4740_818E_B0B6D390FBC4__INCLUDED_)
