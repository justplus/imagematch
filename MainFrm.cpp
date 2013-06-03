// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Match.h"
#include "MatchView.h"
#include "MatchView1.h"
#include "MatchDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_INFO_BAR, OnViewInfoBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INFO_BAR, OnUpdateViewInfoBar)
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(ID_ENLARGE, OnUpdateEnlarge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
	61446,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	issplitted=false;
	viewnum=2;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndMyBar.Create(_T("状态信息"),this,CSize(200,120),true,123,WS_VISIBLE)) 
	{ 
		TRACE0("Failed to create mybar\n"); return -1; 
	}
	m_wndMyBar.SetSCBStyle(m_wndMyBar.GetSCBStyle() |
		SCBS_SIZECHILD);
	if (!m_listbox.Create(WS_CHILD|WS_VISIBLE|TVS_LINESATROOT|LVS_REPORT,
		CRect(0, 0, 0, 0), &m_wndMyBar, 100))
	{
		TRACE0("Failed to create instant bar child\n");
		return -1;		// fail to create
	}

	m_listbox.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	m_listbox.InsertColumn(0,"状态信息",LVCFMT_CENTER,740);
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	m_wndMyBar.SetBarStyle(m_wndMyBar.GetBarStyle() | CBRS_TOOLTIPS | 
		CBRS_FLYBY | CBRS_SIZE_DYNAMIC); 
	m_wndMyBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMyBar, AFX_IDW_DOCKBAR_BOTTOM);

	//设置菜单前图标
	bitmap.LoadBitmap(IDB_IMAGE_OPEN);
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0,MF_BYPOSITION,&bitmap,&bitmap);
	bitmap1.LoadBitmap(IDB_IMAGE_SAVE);
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(1,MF_BYPOSITION,&bitmap1,&bitmap1);
	bitmap2.LoadBitmap(IDB_HARRIS);
	GetMenu()->GetSubMenu(1)->SetMenuItemBitmaps(0,MF_BYPOSITION,&bitmap2,&bitmap2);
	bitmap14.LoadBitmap(IDB_IMPORT_FEAPTS);
	GetMenu()->GetSubMenu(1)->SetMenuItemBitmaps(4,MF_BYPOSITION,&bitmap14,&bitmap14);
	bitmap3.LoadBitmap(IDB_DELETE_FEAPTS);
	GetMenu()->GetSubMenu(1)->SetMenuItemBitmaps(7,MF_BYPOSITION,&bitmap3,&bitmap3);
	bitmap4.LoadBitmap(IDB_LAPLACE);
	GetMenu()->GetSubMenu(2)->SetMenuItemBitmaps(0,MF_BYPOSITION,&bitmap4,&bitmap4);
	bitmap15.LoadBitmap(IDB_DELETE_LINES);
	GetMenu()->GetSubMenu(2)->SetMenuItemBitmaps(4,MF_BYPOSITION,&bitmap15,&bitmap15);
	bitmap5.LoadBitmap(IDB_AUTO_REGISTRATION);
	GetMenu()->GetSubMenu(3)->SetMenuItemBitmaps(0,MF_BYPOSITION,&bitmap5,&bitmap5);
	bitmap6.LoadBitmap(IDB_MANUAL_REGISTRATION);
	GetMenu()->GetSubMenu(3)->SetMenuItemBitmaps(1,MF_BYPOSITION,&bitmap6,&bitmap6);
	bitmap7.LoadBitmap(IDB_FUSION);
	GetMenu()->GetSubMenu(4)->SetMenuItemBitmaps(0,MF_BYPOSITION,&bitmap7,&bitmap7);
	bitmap8.LoadBitmap(IDB_SOFTWARE_SETTING);
	GetMenu()->GetSubMenu(5)->SetMenuItemBitmaps(0,MF_BYPOSITION,&bitmap8,&bitmap8);
	bitmap9.LoadBitmap(IDB_PERFERENCE);
	GetMenu()->GetSubMenu(5)->SetMenuItemBitmaps(1,MF_BYPOSITION,&bitmap9,&bitmap9);
	bitmap10.LoadBitmap(IDB_ENLARGE);
	GetMenu()->GetSubMenu(6)->SetMenuItemBitmaps(5,MF_BYPOSITION,&bitmap10,&bitmap10);
	bitmap11.LoadBitmap(IDB_REDUCE);
	GetMenu()->GetSubMenu(6)->SetMenuItemBitmaps(6,MF_BYPOSITION,&bitmap11,&bitmap11);
	bitmap12.LoadBitmap(IDB_VIEW_IMAGE);
	GetMenu()->GetSubMenu(6)->SetMenuItemBitmaps(7,MF_BYPOSITION,&bitmap12,&bitmap12);
	bitmap13.LoadBitmap(IDB_APP_ABOUT);
	GetMenu()->GetSubMenu(7)->SetMenuItemBitmaps(1,MF_BYPOSITION,&bitmap13,&bitmap13);
	//动态改变工具栏按钮响应函数
	CString DebugPath=AfxGetApp()->m_pszHelpFilePath;
	DebugPath=DebugPath.Left(DebugPath.ReverseFind('\\')); 
	DebugPath+= _T("\\");
	char initcorner[2];
	GetPrivateProfileString("Setting","角点检测",NULL,initcorner,2,DebugPath+"setting.ini");
	int cb1=atoi(initcorner);
	char initmatch[2];
	GetPrivateProfileString("Setting","角点匹配",NULL,initmatch,2,DebugPath+"setting.ini");
	int cb2=atoi(initmatch);
// 	char inittran[2];
// 	GetPrivateProfileString("Setting","变换模型",NULL,inittran,1,DebugPath+"setting.ini");
// 	int cb3=atoi(inittran);
// 	char initinsert[2];
// 	GetPrivateProfileString("Setting","插值方法",NULL,initinsert,1,DebugPath+"setting.ini");
// 	int cb4=atoi(initinsert);
	m_wndToolBar.SetButtonInfo(3,UINT(ID_HARRIS+cb1),UINT(TBSTYLE_BUTTON),2);
	switch(cb2)
	{
	case 0:
		m_wndToolBar.SetButtonInfo(6,UINT(ID_MENUITEM32832),UINT(TBSTYLE_BUTTON),5);
		break;
	case 1:
		m_wndToolBar.SetButtonInfo(6,UINT(ID_LAPLACE),UINT(TBSTYLE_BUTTON),5);
		break;
	case 2:
		m_wndToolBar.SetButtonInfo(6,UINT(ID_SCOTT),UINT(TBSTYLE_BUTTON),5);
		break;
	}
	//设置工具栏按钮状态为凹下凸起状态
//	m_wndToolBar.SetButtonInfo(5,UINT(ID_DELETE_FEAPTS),UINT(TBBS_CHECKBOX),4);
//	m_wndToolBar.SetButtonInfo(7,UINT(ID_MANUAL_REGISTRATION),UINT(TBBS_CHECKBOX),6);
	m_wndToolBar.SetButtonInfo(14,UINT(ID_ENLARGE),UINT(TBSTYLE_GROUP | TBSTYLE_CHECK),11);
	m_wndToolBar.SetButtonInfo(15,UINT(ID_REDUCE),UINT(TBSTYLE_GROUP | TBSTYLE_CHECK),12);
	m_wndToolBar.SetButtonInfo(16,UINT(ID_VIEW_IMAGE),UINT(TBSTYLE_GROUP | TBSTYLE_CHECK),13);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx=800;
	cs.cy=600;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnViewInfoBar() 
{
	// TODO: Add your command handler code here
	BOOL bShow = m_wndMyBar.IsVisible();
	ShowControlBar(&m_wndMyBar, !bShow, FALSE);
}

void CMainFrame::OnUpdateViewInfoBar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndMyBar.IsVisible());
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rect;
	GetClientRect(&rect);
	if(m_wndSplitter.CreateStatic(this,1,2)==NULL)
		return false;
	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CMatchView),CSize(rect.Width()/2,0),pContext);
	m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CMatchView1),CSize(rect.Width()/2,0),pContext);
	issplitted=true;
	return true;
}


void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	setView(viewnum);
// 	if(issplitted)
// 	{
// 		CRect rect;
// 		GetClientRect(&rect);
// 		m_wndSplitter.SetRowInfo(0, rect.Height(), 10); 
// 		m_wndSplitter.SetColumnInfo(0,rect.Width()/2,10);
// 		m_wndSplitter.SetColumnInfo(1,rect.Width()/2,10);
// 		m_wndSplitter.RecalcLayout(); 
// 	}
}

void CMainFrame::OnUpdateEnlarge(CCmdUI* pCmdUI) 
{
// 	pCmdUI->Enable();
// 	pCmdUI->SetCheck(doc.isenlarge);
}

//设置视图窗口
void CMainFrame::setView(int viewcount)
{
	if(issplitted)
	{
		if(viewcount==1)
		{
			CRect rect;
			GetClientRect(&rect);
			m_wndSplitter.SetRowInfo(0, rect.Height(), 10); 
			m_wndSplitter.SetColumnInfo(0,rect.Width(),10);
			m_wndSplitter.SetColumnInfo(1,0,0);
			m_wndSplitter.RecalcLayout();
		}
		else
		{
			CRect rect;
			GetClientRect(&rect);
			m_wndSplitter.SetRowInfo(0, rect.Height(), 10); 
			m_wndSplitter.SetColumnInfo(0,rect.Width()/2,10);
			m_wndSplitter.SetColumnInfo(1,rect.Width()/2,10);
			m_wndSplitter.RecalcLayout(); 
		}
	}
}