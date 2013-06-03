// Matching.h: interface for the CMatching class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATCHING_H__4D933B9B_A1A3_470B_9B45_B65CE4F1A614__INCLUDED_)
#define AFX_MATCHING_H__4D933B9B_A1A3_470B_9B45_B65CE4F1A614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ipl.h"
#include "cv.h"
#include "highgui.h"

#define MAXCORNERS 5000
class CMatching  
{
public:
	CMatching();
//	CvMat* matchpt;
	virtual ~CMatching();
	
	CvMat* Laplace_Method(IplImage* showimg1,CvPoint2D32f Corners1[MAXCORNERS],int cornercount1,IplImage* showimg2,CvPoint2D32f Corners2[MAXCORNERS],int cornercount2);
	CvMat* Init_Method(IplImage* showimg1,IplImage* showimg2,IplImage* grayImage1,IplImage* grayImage2,int patch_radius,int max_disparity,
		CvPoint2D32f* corners1,CvPoint2D32f* corners2,int cornerCount,
					 CvPoint2D32f* matches1,CvPoint2D32f* matches2,int* nmatches,int* mat12,int* mat21);
	CvMat* quCornermatcher(IplImage* showimg1,IplImage* showimg2,IplImage* grayImage1,IplImage* grayImage2,int patch_radius,int max_disparity,double max_diatance,int fmethod,
		CvPoint2D32f* corners1,CvPoint2D32f* corners2,int cornerCount,
		CvPoint2D32f* matches1,CvPoint2D32f* matches2,int* nmatches,int* mat12,int* mat21);
	CvMat* SIFT_Method(IplImage* showimg1,IplImage* showimg2,IplImage* srcImg1,IplImage* srcImg2,int *nmatches);
};

#endif // !defined(AFX_MATCHING_H__4D933B9B_A1A3_470B_9B45_B65CE4F1A614__INCLUDED_)
