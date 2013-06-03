// ImportFeapt.cpp : implementation file
//

#include "stdafx.h"
#include "Match.h"
#include "ImportFeapt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportFeapt dialog


CImportFeapt::CImportFeapt(CWnd* pParent /*=NULL*/)
	: CDialog(CImportFeapt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportFeapt)
	m_file1path = _T("");
	m_file2path = _T("");
	//}}AFX_DATA_INIT
}


void CImportFeapt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportFeapt)
	DDX_Text(pDX, IDC_EDIT1, m_file1path);
	DDX_Text(pDX, IDC_EDIT2, m_file2path);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportFeapt, CDialog)
	//{{AFX_MSG_MAP(CImportFeapt)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportFeapt message handlers

void CImportFeapt::OnButton1() 
{
	CFileDialog* filedialog=new CFileDialog(true,"txt",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"*.txt|*.TXT||",NULL);
	if(filedialog->DoModal()==IDOK)
	{
		CString imageName;
		imageName=filedialog->GetPathName();
		GetDlgItem(IDC_EDIT1)->SetWindowText(imageName);
	}
	delete(filedialog);
}

void CImportFeapt::OnButton2() 
{
	CFileDialog* filedialog=new CFileDialog(true,"txt",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"*.txt|*.TXT||",NULL);
	if(filedialog->DoModal()==IDOK)
	{
		CString imageName;
		imageName=filedialog->GetPathName();
		GetDlgItem(IDC_EDIT2)->SetWindowText(imageName);
	}
	delete(filedialog);
}

void CImportFeapt::OnButton3() 
{
	CDialog::OnOK();
}

void CImportFeapt::OnButton4() 
{
	CDialog::OnCancel();
}
