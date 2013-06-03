// MyOpenCV.cpp : my opencv functions
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "MyOpenCV.h"
#include <math.h>

// 画十字形标记函数
void quPlotCross(CvArr* img,CvPoint pt,CvScalar color,int thickness,int radius)
{
	CvPoint left,right,up,down;
	left.x=pt.x-radius;left.y=pt.y;
	right.x=pt.x+radius;right.y=pt.y;
	up.x=pt.x;up.y=pt.y+radius;
	down.x=pt.x;down.y=pt.y-radius;
	cvLine(img,left,right,color,thickness,0);
	cvLine(img,up,down,color,thickness,0);
}

// 特征点初始匹配函数
void quCornermatcher(IplImage* grayImage1,IplImage* grayImage2,int patch_radius,int max_disparity,
					 CvPoint2D32f* corners1,CvPoint2D32f* corners2,int cornerCount,
					 CvPoint2D32f* matches1,CvPoint2D32f* matches2,int* nmatches,int* mat12,int* mat21)
{
	int x1,y1,x2,y2;
	double norm,minnorm;
	IplImage* patchimg1=0;
	IplImage* patchimg2=0;
	*nmatches=0;
	
	patchimg1=cvCreateImage(cvSize(patch_radius*2+1,patch_radius*2+1),IPL_DEPTH_8U,1);
	patchimg2=cvCreateImage(cvSize(patch_radius*2+1,patch_radius*2+1),IPL_DEPTH_8U,1);

	iplSetBorderMode(grayImage1,IPL_BORDER_CONSTANT,IPL_SIDE_ALL,0);
	iplSetBorderMode(grayImage2,IPL_BORDER_CONSTANT,IPL_SIDE_ALL,0);

	//正向相关匹配(1->2)
	for(int i=0;i<cornerCount;i++)
	{
		minnorm=1.0e8;
		mat12[i]=-1;//if mat*[i]<0 canot found matches
		x1=cvRound(corners1[i].x);y1=cvRound(corners1[i].y);

		cvSetImageROI(grayImage1,cvRect(x1-patch_radius,y1-patch_radius,patch_radius*2+1,patch_radius*2+1));
		cvSetZero(patchimg1);
		iplCopy(grayImage1,patchimg1);
		cvSetImageROI(grayImage1,cvRect(0,0,grayImage1->width,grayImage1->height));

		for(int j=0;j<cornerCount;j++)
		{
			x2=cvRound(corners2[j].x);y2=cvRound(corners2[j].y);
			if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<max_disparity*max_disparity)
			{
				cvSetImageROI(grayImage2,cvRect(x2-patch_radius,y2-patch_radius,patch_radius*2+1,patch_radius*2+1));
				cvSetZero(patchimg2);
				iplCopy(grayImage2,patchimg2);
				cvSetImageROI(grayImage2,cvRect(0,0,grayImage2->width,grayImage2->height));

				norm=iplNorm(patchimg1,patchimg2,IPL_L2);//相关系数(图像2范数)

				if(norm<minnorm)
				{
					minnorm=norm;
					mat12[i]=j;
				}
			}
		}

		cvSetImageROI(grayImage1,cvRect(0,0,grayImage1->width,grayImage1->height));
		cvSetImageCOI(grayImage1,0);
	}

	//反向相关匹配(2->1)
	for(i=0;i<cornerCount;i++)
	{
		minnorm=1.0e8;
		mat21[i]=-1;//if mat*[i]<0 canot found matches
		x2=cvRound(corners2[i].x);y2=cvRound(corners2[i].y);

		cvSetImageROI(grayImage2,cvRect(x2-patch_radius,y2-patch_radius,patch_radius*2+1,patch_radius*2+1));
		cvSetZero(patchimg2);
		iplCopy(grayImage2,patchimg2);
		cvSetImageROI(grayImage2,cvRect(0,0,grayImage2->width,grayImage2->height));

		for(int j=0;j<cornerCount;j++)
		{
			x1=cvRound(corners1[j].x);y1=cvRound(corners1[j].y);
			if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<max_disparity*max_disparity)
			{
				cvSetImageROI(grayImage1,cvRect(x1-patch_radius,y1-patch_radius,patch_radius*2+1,patch_radius*2+1));
				cvSetZero(patchimg1);
				iplCopy(grayImage1,patchimg1);
				cvSetImageROI(grayImage1,cvRect(0,0,grayImage1->width,grayImage1->height));

				norm=iplNorm(patchimg1,patchimg2,IPL_L2);//相关系数(图像2范数)

				if(norm<minnorm)
				{
					minnorm=norm;
					mat21[i]=j;
				}
			}
		}

		cvSetImageROI(grayImage2,cvRect(0,0,grayImage2->width,grayImage2->height));
		cvSetImageCOI(grayImage2,0);
	}

	//重组匹配点矩阵
	for(i=0;i<cornerCount;i++)
	{
		//if(mat12[i]>=0)//(1->2)
		if(mat12[i]>=0&&mat21[mat12[i]]==i)//(1->2)&&(2->1)
		{
			matches1[*nmatches].x=corners1[i].x;matches1[*nmatches].y=corners1[i].y;
			matches2[*nmatches].x=corners2[mat12[i]].x;matches2[*nmatches].y=corners2[mat12[i]].y;
			(*nmatches)++;
		}
	}

	cvReleaseImage(&patchimg1);
	cvReleaseImage(&patchimg2);
}

// 基于F的引导匹配函数
void quGuidematcher(IplImage* grayImage1,IplImage* grayImage2,int patch_radius,int max_disparity,double epidis,
					 CvPoint2D32f* corners1,CvPoint2D32f* corners2,int cornerCount,CvMat* fundMatr,
					 CvPoint2D32f* matches1,CvPoint2D32f* matches2,int* nmatches,int* mat12,int* mat21)
{
	int x1,y1,x2,y2;
	double norm,minnorm;
	CvMat* points1=0;
    CvMat* points2=0;
    CvMat* wpoints1=0;
    CvMat* wpoints2=0;
    CvMat* corrLines1=0;
    CvMat* corrLines2=0;
	IplImage* patchimg1=0;
	IplImage* patchimg2=0;
	*nmatches=0;
	
    points1=cvCreateMat(2,cornerCount,CV_32F);
    points2=cvCreateMat(2,cornerCount,CV_32F);
    wpoints1=cvCreateMat(3,cornerCount,CV_64F);
    wpoints2=cvCreateMat(3,cornerCount,CV_64F);
    corrLines1=cvCreateMat(3,cornerCount,CV_64F);
    corrLines2=cvCreateMat(3,cornerCount,CV_64F);

	for(int i=0;i<cornerCount;i++)
	{
		cvmSet(points1,0,i,corners1[i].x); cvmSet(points1,1,i,corners1[i].y);
		cvmSet(points2,0,i,corners2[i].x); cvmSet(points2,1,i,corners2[i].y);
	}
	cvMake3DPoints(points1,wpoints1);
    cvMake3DPoints(points2,wpoints2);

	patchimg1=cvCreateImage(cvSize(patch_radius*2+1,patch_radius*2+1),IPL_DEPTH_8U,1);
	patchimg2=cvCreateImage(cvSize(patch_radius*2+1,patch_radius*2+1),IPL_DEPTH_8U,1);

	iplSetBorderMode(grayImage1,IPL_BORDER_CONSTANT,IPL_SIDE_ALL,0);
	iplSetBorderMode(grayImage2,IPL_BORDER_CONSTANT,IPL_SIDE_ALL,0);

	cvComputeCorrespondEpilines(wpoints1,1,fundMatr,corrLines2);
	cvComputeCorrespondEpilines(wpoints2,2,fundMatr,corrLines1);

	//正向引导匹配(1->2)
	for(i=0;i<cornerCount;i++)
	{
		minnorm=1.0e8;
		mat12[i]=-1;//if mat*[i]<0 canot found matches
		x1=cvRound(corners1[i].x);y1=cvRound(corners1[i].y);

		cvSetImageROI(grayImage1,cvRect(x1-patch_radius,y1-patch_radius,patch_radius*2+1,patch_radius*2+1));
		cvSetZero(patchimg1);
		iplCopy(grayImage1,patchimg1);
		cvSetImageROI(grayImage1,cvRect(0,0,grayImage1->width,grayImage1->height));

		CvMat pnt1,pnt2;
		CvMat lin1,lin2;
		cvGetCol(wpoints1,&pnt1,i);
		cvGetCol(corrLines2,&lin2,i);
		
		for(int j=0;j<cornerCount;j++)
		{
			x2=cvRound(corners2[j].x);y2=cvRound(corners2[j].y);
			
			if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<max_disparity*max_disparity)
			{
                cvGetCol(wpoints2,&pnt2,j);
                cvGetCol(corrLines1,&lin1,j);
                double dist1,dist2;
                dist1=fabs(cvDotProduct(&pnt1,&lin1));
                dist2=fabs(cvDotProduct(&pnt2,&lin2));
				
				if(dist1<epidis && dist2<epidis)
				{
					cvSetImageROI(grayImage2,cvRect(x2-patch_radius,y2-patch_radius,patch_radius*2+1,patch_radius*2+1));
					cvSetZero(patchimg2);
					iplCopy(grayImage2,patchimg2);
					cvSetImageROI(grayImage2,cvRect(0,0,grayImage2->width,grayImage2->height));

					norm=iplNorm(patchimg1,patchimg2,IPL_L2);//相关系数(图像2范数)

					if(norm<minnorm)
					{
						minnorm=norm;
						mat12[i]=j;
					}
				}
			}
		}

		cvSetImageROI(grayImage1,cvRect(0,0,grayImage1->width,grayImage1->height));
		cvSetImageCOI(grayImage1,0);
	}

	//反向引导匹配(2->1)
	for(i=0;i<cornerCount;i++)
	{
		minnorm=1.0e8;
		mat21[i]=-1;//if mat*[i]<0 canot found matches
		x2=cvRound(corners2[i].x);y2=cvRound(corners2[i].y);

		cvSetImageROI(grayImage2,cvRect(x2-patch_radius,y2-patch_radius,patch_radius*2+1,patch_radius*2+1));
		cvSetZero(patchimg2);
		iplCopy(grayImage2,patchimg2);
		cvSetImageROI(grayImage2,cvRect(0,0,grayImage2->width,grayImage2->height));

		CvMat pnt1,pnt2;
		CvMat lin1,lin2;
		cvGetCol(wpoints2,&pnt2,i);
		cvGetCol(corrLines1,&lin1,i);

		for(int j=0;j<cornerCount;j++)
		{
			x1=cvRound(corners1[j].x);y1=cvRound(corners1[j].y);
			if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<max_disparity*max_disparity)
			{
                cvGetCol(wpoints1,&pnt1,j);
                cvGetCol(corrLines2,&lin2,j);
                double dist1,dist2;
                dist1=fabs(cvDotProduct(&pnt1,&lin1));
                dist2=fabs(cvDotProduct(&pnt2,&lin2));

				if(dist1<epidis && dist2<epidis)
				{				
					cvSetImageROI(grayImage1,cvRect(x1-patch_radius,y1-patch_radius,patch_radius*2+1,patch_radius*2+1));
					cvSetZero(patchimg1);
					iplCopy(grayImage1,patchimg1);
					cvSetImageROI(grayImage1,cvRect(0,0,grayImage1->width,grayImage1->height));

					norm=iplNorm(patchimg1,patchimg2,IPL_L2);//相关系数(图像2范数)

					if(norm<minnorm)
					{
						minnorm=norm;
						mat21[i]=j;
					}
				}
			}
		}

		cvSetImageROI(grayImage2,cvRect(0,0,grayImage2->width,grayImage2->height));
		cvSetImageCOI(grayImage2,0);
	}

	
	//重组匹配点矩阵
	for(i=0;i<cornerCount;i++)
	{
		if(mat12[i]>=0)//(1->2)
		if(mat12[i]>=0&&mat21[mat12[i]]==i)//(1->2)&&(2->1)
		{
			matches1[*nmatches].x=corners1[i].x;matches1[*nmatches].y=corners1[i].y;
			matches2[*nmatches].x=corners2[mat12[i]].x;matches2[*nmatches].y=corners2[mat12[i]].y;
			(*nmatches)++;
		}
	}
	
    cvReleaseMat(&points1);
    cvReleaseMat(&points2);
    cvReleaseMat(&wpoints1);
    cvReleaseMat(&wpoints2);
    cvReleaseMat(&corrLines1);
    cvReleaseMat(&corrLines2);
	cvReleaseImage(&patchimg1);
	cvReleaseImage(&patchimg2);
}