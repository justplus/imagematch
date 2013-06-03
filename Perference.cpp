// Perference.cpp : implementation file
//

#include "stdafx.h"
#include "Match.h"
#include "Perference.h"
#include "folder_dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPerference dialog


CPerference::CPerference(CWnd* pParent /*=NULL*/)
	: CDialog(CPerference::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPerference)
	m_savepath = _T("");
	cornercolor=0x007F00;
	infolistcolor=0x007F00;
	//}}AFX_DATA_INIT
}


void CPerference::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPerference)
	DDX_Control(pDX, IDC_COMBO4, m_cb4);
	DDX_Control(pDX, IDC_COMBO3, m_cb3);
	DDX_Control(pDX, IDC_COMBO2, m_cb2);
	DDX_Control(pDX, IDC_COMBO1, m_cb1);
	DDX_Text(pDX, IDC_EDIT1, m_savepath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPerference, CDialog)
	//{{AFX_MSG_MAP(CPerference)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPerference message handlers


BOOL CPerference::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString DebugPath;
	DebugPath=AfxGetApp()->m_pszHelpFilePath;
	DebugPath=DebugPath.Left(DebugPath.ReverseFind('\\')); 
	DebugPath+= _T("\\");
	m_cb1.SetCurSel(0);
	m_cb2.SetCurSel(0);
	m_cb3.SetCurSel(0);
	m_cb4.SetCurSel(0);
	cb1=cb2=cb3=cb4=0;
	m_savepath=DebugPath+"images\\";
 	cornercolor=0x007F00;
 	infolistcolor=0x007F00;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPerference::OnButton1() 
{
	CFolderDialog folderdlg(&m_savepath);
	if(folderdlg.DoModal()==IDOK)
	{
		UpdateData(FALSE);
	}

}

void CPerference::OnButton2() 
{
	cb1=m_cb1.GetCurSel();
	cb2=m_cb2.GetCurSel();
	cb3=m_cb3.GetCurSel();
	cb4=m_cb4.GetCurSel();
	CDialog::OnOK();
}

void CPerference::OnButton3() 
{
	CDialog::OnCancel();
}

void CPerference::OnButton4() 
{
	CColorDialog cornerdlg;
	if(cornerdlg.DoModal()==IDOK)
	{
		cornercolor=cornerdlg.GetColor();
	}
}

void CPerference::OnButton5() 
{
	CColorDialog cornerdlg;
	if(cornerdlg.DoModal()==IDOK)
	{
		infolistcolor=cornerdlg.GetColor();
	}
}
