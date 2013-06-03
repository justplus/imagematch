// Utility.cpp: implementation of the CUtility class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Match.h"
#include "Utility.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUtility::CUtility()
{

}

CUtility::~CUtility()
{

}

//标注角点
void CUtility::DrawCross(CvArr *img, CvPoint2D32f pt, CvScalar color, int thickness, int radius)
{
	CvPoint left,right,up,down;
	left.x=pt.x-radius;left.y=pt.y;
	right.x=pt.x+radius;right.y=pt.y;
	up.x=pt.x;up.y=pt.y+radius;
	down.x=pt.x;down.y=pt.y-radius;
	cvLine(img,left,right,color,thickness,0);
	cvLine(img,up,down,color,thickness,0);	
}

//输出字符

void CUtility::PrintText(CString text,COLORREF color)
{
	CMainFrame* pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;//得到主窗口指针
	pFrame->m_listbox.SetTextColor(color);
	pFrame->m_listbox.InsertItem(0,text);
}

//判断一点是否在某一条直线上
// bool CUtility::PtInLine(CvPoint2D32f pt, CvPoint2D32f lineStart, CvPoint2D32f lineEnd)
// {
// 	double dis1=sqrt(pow(pt.x-lineStart.x,2)+pow(pt.y-lineStart.y,2));
// 	double dis2=sqrt(pow(pt.x-lineEnd.x,2)+pow(pt.y-lineEnd.y,2));
// 	double dis3=sqrt(pow(lineEnd.x-lineStart.x,2)+pow(lineEnd.y-lineStart.y,2));
// 	if(abs(dis1+dis2-dis3)<=10.0)
// 		return true;
// 	else
// 		return false;
// }
