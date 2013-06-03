// SubPixel.cpp : implementation file
//

#include "stdafx.h"
#include "Match.h"
#include "SubPixel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubPixel dialog


CSubPixelDlg::CSubPixelDlg(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CSubPixelDlg::IDD)
{
	//{{AFX_DATA_INIT(CSubPixel)
	m_guassblur = true;
	m_cornercount = 1000;
	m_min_distance = 3.0;
	m_quality_level = 1e-7;
	m_winlength = 3;
	m_max_iter = 10;
	m_epsilon = 0.1;
	m_sigma = 0.5;
	m_guass_winwidth = 3;
	m_guass_winheigth = 3;
	//}}AFX_DATA_INIT
}


void CSubPixelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubPixel)
	DDX_Check(pDX, IDC_CHECK1, m_guassblur);
	DDX_Text(pDX, IDC_EDIT1, m_cornercount);
	DDX_Text(pDX, IDC_EDIT2, m_min_distance);
	DDX_Text(pDX, IDC_EDIT3, m_quality_level);
	DDX_Text(pDX, IDC_EDIT4, m_winlength);
	DDX_Text(pDX, IDC_EDIT5, m_max_iter);
	DDX_Text(pDX, IDC_EDIT6, m_epsilon);
	DDX_Text(pDX, IDC_EDIT7, m_sigma);
	DDX_Text(pDX, IDC_EDIT8, m_guass_winwidth);
	DDX_Text(pDX, IDC_EDIT9, m_guass_winheigth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubPixelDlg, CDialog)
	//{{AFX_MSG_MAP(CSubPixel)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubPixel message handlers
