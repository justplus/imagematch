// RegistrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Match.h"
#include "RegistrationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegistrationDlg dialog


CRegistrationDlg::CRegistrationDlg(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CRegistrationDlg::IDD)
{
	//{{AFX_DATA_INIT(CRegistrationDlg)
	m_transmode = 0;
	m_fillval = 1;
	//}}AFX_DATA_INIT
}


void CRegistrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegistrationDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_transmode);
	DDX_Radio(pDX, IDC_RADIO4, m_fillval);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegistrationDlg, CDialog)
	//{{AFX_MSG_MAP(CRegistrationDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegistrationDlg message handlers
