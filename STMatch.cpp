// STMatch.cpp : implementation file
//

#include "stdafx.h"
#include "Match.h"
#include "STMatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSTMatch property page

IMPLEMENT_DYNCREATE(CSTMatch, CPropertyPage)

CSTMatch::CSTMatch() : CPropertyPage(CSTMatch::IDD)
{
	//{{AFX_DATA_INIT(CSTMatch)
	patch_radius = 5;
	max_disparity = 50;
	max_distance = 1.5;
	rightper = _T("99%");
	fmethod = 2;
	//}}AFX_DATA_INIT
}

CSTMatch::~CSTMatch()
{
}

void CSTMatch::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSTMatch)
	DDX_Text(pDX, IDC_EDIT1, patch_radius);
	DDX_Text(pDX, IDC_EDIT2, max_disparity);
	DDX_Text(pDX, IDC_EDIT3, max_distance);
	DDX_Text(pDX, IDC_EDIT4, rightper);
	DDX_Radio(pDX, IDC_RADIO1, fmethod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSTMatch, CPropertyPage)
	//{{AFX_MSG_MAP(CSTMatch)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTMatch message handlers
