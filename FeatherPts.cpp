// FeatherPts.cpp: implementation of the CFeatherPts class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Match.h"
#include "FeatherPts.h"
#include "ImportFeapt.h"
#include "sift.h"
#include "imgfeatures.h"
#include "kdtree.h"
#include "utils.h"
#include "xform.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// #define B(image,x,y) ((uchar *)(image->imageData+image->widthStep*(y)))[(x)*3]
// #define G(image,x,y) ((uchar *)(image->imageData+image->widthStep*(y)))[(x)*3+1]
// #define R(image,x,y) ((uchar *)(image->imageData+image->widthStep*(y)))[(x)*3+2]
// #define S(image,x,y) ((uchar *)(image->imageData+image->widthStep*(y)))[(x)]
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFeatherPts::CFeatherPts()
{
	cornersCount=0;
}

CFeatherPts::~CFeatherPts()
{

}

void CFeatherPts::ClearCorners()
{
	cornersCount=0;
	for(int k=0;k<MAXCORNERS;k++)
		corners[k].x=corners[k].y=0;
}
//Harris角点检测
void CFeatherPts::Harris_Method(IplImage* src,int cornercount,double quality_level,double min_distance,int blocksize)
{
	ClearCorners();
	IplImage* grayimg=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	IplImage* eigimg=cvCreateImage(cvGetSize(src),IPL_DEPTH_32F,1);
	IplImage* tempimg=cvCloneImage(eigimg);
	//cvConvertImage(srcimg,grayimg,0);
	cvCvtColor(src,grayimg,CV_BGR2GRAY);
	cvGoodFeaturesToTrack(grayimg,eigimg,tempimg,corners,&cornercount,quality_level,min_distance,NULL,blocksize,0,0.04);
	cornersCount=cornercount;
}

//亚像素级角点检测
void CFeatherPts::SubPixel_Method(IplImage* src,int cornercount,int min_distance,double quality_level,int winlength,int max_iter,double epsilon,bool gaussblur,double sigma,int gauss_winwidth,int gauss_winheigth)
{
	ClearCorners();

	CvPoint temppt;
	IplImage* grayImg1=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	IplImage* smoothImg1=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	//转换得到灰度图像
	cvCvtColor(src,grayImg1,CV_BGR2GRAY);
	IplImage* eigImage1=cvCreateImage(cvGetSize(grayImg1),IPL_DEPTH_32F,1);
	IplImage* tempImage1=cvCreateImage(cvGetSize(grayImg1),IPL_DEPTH_32F,1);
	
	if(gaussblur)
	{//启用高斯滤波
		cvSmooth(grayImg1,smoothImg1,CV_GAUSSIAN,gauss_winheigth,gauss_winwidth);
		
		cvGoodFeaturesToTrack(smoothImg1,eigImage1,tempImage1,corners,&cornercount,quality_level,min_distance);
		cvFindCornerSubPix(smoothImg1,corners,cornercount,cvSize(winlength,winlength),cvSize(-1,-1),
			cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,max_iter,epsilon));
	}
	else
	{//不启用高斯滤波
		cvGoodFeaturesToTrack(grayImg1,eigImage1,tempImage1,corners,&cornercount,quality_level,min_distance);
		cvFindCornerSubPix(grayImg1,corners,cornercount,cvSize(winlength,winlength),cvSize(-1,-1),
			cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,max_iter,epsilon));
	}
	cornersCount=cornercount;
	
	cvReleaseImage(&eigImage1);
	cvReleaseImage(&tempImage1);
}

 void CFeatherPts::SIFT_Method(IplImage *src)
 {
 	ClearCorners();
 
 	struct feature* feature;
 	cornersCount=sift_features(src,&feature);
// 	cornersCount=(cornersCount>=MAXCORNERS)?MAXCORNERS:cornersCount;//设置角点最大值
 	for(int i=0;i<cornersCount;i++)
 	{
 		corners[i].x=(feature+i)->x;
 		corners[i].y=(feature+i)->y;
 	}
 }

bool CFeatherPts::Import_Method(CString path)
{
	ClearCorners();

	CStdioFile file;
	CString strLine;
	if(!file.Open(path,CFile::modeRead))
	{
		return false;
	}
	else
	{
		while(file.ReadString(strLine))
		{
			int blankpos1=strLine.Find(" ");
			int blankpos2=strLine.GetLength();
			if(strLine!="")
			{
				double x=atof(strLine.Mid(0,blankpos1));
				double y=atof(strLine.Mid(blankpos1+1,blankpos2-blankpos1));
				corners[cornersCount].x=x;
				corners[cornersCount].y=y;
				cornersCount++;
			}
		}
		return true;
	}
}

bool CFeatherPts::Export_Method(CString path,CvPoint2D32f AllCorners[MAXCORNERS],int cornercount)
{
	CStdioFile file;
	CString ptstr;
	if(!file.Open(path,CFile::modeWrite|CFile::modeCreate))
	{
		return false;
	}
	else
	{
		for(int i=0;i<cornercount;i++)
		{
			ptstr.Format("%f %f\n",AllCorners[i].x,AllCorners[i].y);
			file.SeekToEnd();
			file.WriteString(ptstr);
			file.Flush();
		}
	}
	file.Close();
	return true;
}