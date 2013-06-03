// Utility.h: interface for the CUtility class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTILITY_H__F5A1B921_2A1D_41FC_9F98_0799E7280005__INCLUDED_)
#define AFX_UTILITY_H__F5A1B921_2A1D_41FC_9F98_0799E7280005__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cv.h"
#include "highgui.h"

class CUtility  
{
public:
	bool PtInLine(CvPoint2D32f pt,CvPoint2D32f lineStart,CvPoint2D32f lineEnd);
	void PrintText(CString text,COLORREF color);
	void DrawCross(CvArr *img, CvPoint2D32f pt, CvScalar color, int thickness, int radius);
	CUtility();
	virtual ~CUtility();

};

#endif // !defined(AFX_UTILITY_H__F5A1B921_2A1D_41FC_9F98_0799E7280005__INCLUDED_)
