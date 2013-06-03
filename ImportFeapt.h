#if !defined(AFX_IMPORTFEAPT_H__D8411363_8D69_4B1C_8AC0_2A2CA8E7E151__INCLUDED_)
#define AFX_IMPORTFEAPT_H__D8411363_8D69_4B1C_8AC0_2A2CA8E7E151__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportFeapt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportFeapt dialog

class CImportFeapt : public CDialog
{
// Construction
public:
	CImportFeapt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImportFeapt)
	enum { IDD = IDD_IMPORT_FEAPTS };
	CString	m_file1path;
	CString	m_file2path;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportFeapt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportFeapt)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTFEAPT_H__D8411363_8D69_4B1C_8AC0_2A2CA8E7E151__INCLUDED_)
