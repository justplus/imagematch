// FeatherPts.h: interface for the CFeatherPts class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEATHERPTS_H__247A8C43_FCD9_4F6D_A5F0_49A9BDB179CC__INCLUDED_)
#define AFX_FEATHERPTS_H__247A8C43_FCD9_4F6D_A5F0_49A9BDB179CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXCORNERS 5000
#include "cv.h"
#include "highgui.h"

class CFeatherPts  
{
public:
	CFeatherPts();
	virtual ~CFeatherPts();
	CvPoint2D32f corners[MAXCORNERS];//´æ´¢½Çµã
	int cornersCount;//½ÇµãÊý
	
	void ClearCorners();
	void Harris_Method(IplImage* src,int cornercount,double quality_level,double min_distance,int blocksize);
	void SubPixel_Method(IplImage* src,int cornercount,int min_distance,double quality_level,int winlength,int max_iter,double epsilon,bool gaussblur,double sigma,int gauss_winwidth,int gauss_winheigth);
	void SIFT_Method(IplImage* src);
	bool Import_Method(CString path);
	bool Export_Method(CString path,CvPoint2D32f AllCorners[MAXCORNERS],int cornercount);
};

#endif // !defined(AFX_FEATHERPTS_H__247A8C43_FCD9_4F6D_A5F0_49A9BDB179CC__INCLUDED_)
