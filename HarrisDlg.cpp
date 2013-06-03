// HarrisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Match.h"
#include "HarrisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHarrisDlg dialog


CHarrisDlg::CHarrisDlg(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CHarrisDlg::IDD)
{
	//{{AFX_DATA_INIT(CHarrisDlg)
	m_corner_count = 50;
	m_quality_level = 0.1;
	m_min_distance = 10;
	m_block_size = 3;
	//}}AFX_DATA_INIT
}


void CHarrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHarrisDlg)
	DDX_Text(pDX, IDC_EDIT1, m_corner_count);
	DDX_Text(pDX, IDC_EDIT2, m_quality_level);
	DDV_MinMaxDouble(pDX, m_quality_level, 0., 1.);
	DDX_Text(pDX, IDC_EDIT3, m_min_distance);
	DDX_Text(pDX, IDC_EDIT4, m_block_size);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHarrisDlg, CDialog)
	//{{AFX_MSG_MAP(CHarrisDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHarrisDlg message handlers
