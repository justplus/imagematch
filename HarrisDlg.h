#if !defined(AFX_HARRISDLG_H__27A88F89_AF06_419B_A588_F66D79D6D75C__INCLUDED_)
#define AFX_HARRISDLG_H__27A88F89_AF06_419B_A588_F66D79D6D75C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HarrisDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHarrisDlg dialog

class CHarrisDlg : public CPropertyPage
{
// Construction
public:
	CHarrisDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHarrisDlg)
	enum { IDD = IDD_Harris };
	int		m_corner_count;
	double	m_quality_level;
	double	m_min_distance;
	int		m_block_size;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHarrisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHarrisDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HARRISDLG_H__27A88F89_AF06_419B_A588_F66D79D6D75C__INCLUDED_)
