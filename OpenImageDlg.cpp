// OpenImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Match.h"
#include "OpenImageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenImageDlg dialog


COpenImageDlg::COpenImageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenImageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenImageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COpenImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenImageDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenImageDlg, CDialog)
	//{{AFX_MSG_MAP(COpenImageDlg)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenImageDlg message handlers

void COpenImageDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT1)->GetWindowText(imgpath1);
	GetDlgItem(IDC_EDIT2)->GetWindowText(imgpath2);
	CDialog::OnOK();
}

void COpenImageDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void COpenImageDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	LPCTSTR lpszFilters;
	lpszFilters="Image Files(*.jpg,*.bmp,*dib,*tif)|*.jpg;*.bmp;*dib;*tif|All Files(*.*)|*.*||";
	
	CFileDialog* filedialog=new CFileDialog(true,"jpg",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,lpszFilters,NULL);
	if(filedialog->DoModal()==IDOK)
	{
		CString imageName;
		imageName=filedialog->GetPathName();
		GetDlgItem(IDC_EDIT1)->SetWindowText(imageName);
	}
	delete(filedialog);
}

void COpenImageDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	LPCTSTR lpszFilters;
	lpszFilters="Image Files(*.jpg,*.bmp,*dib,*tif)|*.jpg;*.bmp;*dib;*tif|All Files(*.*)|*.*||";
	
	CFileDialog* filedialog=new CFileDialog(true,"jpg",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,lpszFilters,NULL);
	if(filedialog->DoModal()==IDOK)
	{
		CString imageName;
		imageName=filedialog->GetPathName();
		GetDlgItem(IDC_EDIT2)->SetWindowText(imageName);
	}
	delete(filedialog);
}
