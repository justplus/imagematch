// SiftDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Match.h"
#include "SiftDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSiftDlg property page

IMPLEMENT_DYNCREATE(CSiftDlg, CPropertyPage)

CSiftDlg::CSiftDlg() : CPropertyPage(CSiftDlg::IDD)
{
	//{{AFX_DATA_INIT(CSiftDlg)
	SIFT_INTVLS = 3;
	SIFT_SIGMA = 1.6;
	SIFT_CONTR_THR = 0.04;
	SIFT_CURV_THR = 10;
	SIFT_DESCR_WIDTH = 4;
	SIFT_DESCR_HIST_BINS = 8;
	SIFT_DESCR_MAG_THR = 0.2;
	//}}AFX_DATA_INIT
}

CSiftDlg::~CSiftDlg()
{
}

void CSiftDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSiftDlg)
	DDX_Text(pDX, IDC_EDIT1, SIFT_INTVLS);
	DDX_Text(pDX, IDC_EDIT2, SIFT_SIGMA);
	DDX_Text(pDX, IDC_EDIT3, SIFT_CONTR_THR);
	DDX_Text(pDX, IDC_EDIT4, SIFT_CURV_THR);
	DDX_Text(pDX, IDC_EDIT5, SIFT_DESCR_WIDTH);
	DDX_Text(pDX, IDC_EDIT6, SIFT_DESCR_HIST_BINS);
	DDX_Text(pDX, IDC_EDIT7, SIFT_DESCR_MAG_THR);
	DDV_MinMaxDouble(pDX, SIFT_DESCR_MAG_THR, 0., 1.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSiftDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CSiftDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSiftDlg message handlers
