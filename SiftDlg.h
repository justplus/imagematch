#if !defined(AFX_SIFTDLG_H__610A6949_DE96_42FA_8E7A_AF8679DFF22F__INCLUDED_)
#define AFX_SIFTDLG_H__610A6949_DE96_42FA_8E7A_AF8679DFF22F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SiftDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSiftDlg dialog

class CSiftDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CSiftDlg)

// Construction
public:
	CSiftDlg();
	~CSiftDlg();

// Dialog Data
	//{{AFX_DATA(CSiftDlg)
	enum { IDD = IDD_SIFT };
	int		SIFT_INTVLS;
	double	SIFT_SIGMA;
	double	SIFT_CONTR_THR;
	int		SIFT_CURV_THR;
	int		SIFT_DESCR_WIDTH;
	int		SIFT_DESCR_HIST_BINS;
	double	SIFT_DESCR_MAG_THR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSiftDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSiftDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIFTDLG_H__610A6949_DE96_42FA_8E7A_AF8679DFF22F__INCLUDED_)
