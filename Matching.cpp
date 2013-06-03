// Matching.cpp: implementation of the CMatching class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Match.h"
#include "Matching.h"
#include "sift.h"
#include "imgfeatures.h"
#include "kdtree.h"
#include "utils.h"
#include "xform.h"

/* the maximum number of keypoint NN candidates to check during BBF search */
#define KDTREE_BBF_MAX_NN_CHKS 200

/* threshold on squared ratio of distances between NN and 2nd NN */
#define NN_SQ_DIST_RATIO_THR 0.49

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatching::CMatching()
{

}

CMatching::~CMatching()
{

}

bool isMax(CvMat *mat, int row, int col)
{
	double rowmax=CV_MAT_ELEM(*mat,double,row,0);
	double colmax=CV_MAT_ELEM(*mat,double,0,col);
	double val=CV_MAT_ELEM(*mat,double,row,col);
	for(int j=0;j<mat->cols;j++)
	{
		double rowval=CV_MAT_ELEM(*mat,double,row,j);
		if(rowmax<rowval)
			rowmax=rowval;
	}
	for(int i=0;i<mat->rows;i++)
	{
		double colval=CV_MAT_ELEM(*mat,double,i,col);
		if(colmax<colval)
			colmax=colval;
	}
	if(rowmax==colmax&&rowmax==val)
		return true;
	else
		return false;
}

CvMat* CMatching::Laplace_Method(IplImage* showimg1,CvPoint2D32f Corners1[MAXCORNERS],int cornercount1,IplImage* showimg2,CvPoint2D32f Corners2[MAXCORNERS],int cornercount2)
{
	int i,j;
	int L;//特征点数
	CvMat* r1,*c1,*r2,*c2;
	CvMat* M1,*M2,*M11,*M22;
	CvMat* U,*A,*V,*B;
	CvMat* X1,*Y1;
	CvMat* C;
	double x11,x22;
	CvPoint pt1,pt2;
	CvRect rect1,rect2;

	CvSize orisize1=cvGetSize(showimg1);
	//创建新的画布
	CvSize matchedsize;
	matchedsize.width=cvGetSize(showimg1).width*2+100;
	matchedsize.height=cvGetSize(showimg1).height*2+200;
	IplImage* matchedimg=cvCreateImage(matchedsize,IPL_DEPTH_8U,3);
	//更改m_imgsize1的大小，view中要用
	CvSize tempsize;
	tempsize=cvGetSize(showimg1);

	//将默认的黑色背景更改为白色
	cvSet(matchedimg,CV_RGB(255,255,255));
	//合并两幅图像
	
	rect1.x=0;//更改...
	rect1.y=0;
	rect1.width=showimg1->width;
	rect1.height=showimg1->height;
	cvSetImageROI(matchedimg,rect1);
	cvCopy(showimg1,matchedimg);
	
	cvResetImageROI(matchedimg);
	
	rect2.x=rect1.width+50;
	rect2.y=50;

	rect2.width=showimg2->width;
	rect2.height=showimg2->height;
	cvSetImageROI(matchedimg,rect2);
	cvCopy(showimg2,matchedimg);
	
	cvResetImageROI(matchedimg);
	cvReleaseImage(&showimg1);
	showimg1=cvCreateImage(matchedsize,IPL_DEPTH_8U,3);	
	cvCopy(matchedimg,showimg1);

	r1=cvCreateMat(cornercount1,1,CV_64FC1);
	c1=cvCloneMat(r1);
	r2=cvCreateMat(cornercount2,1,CV_64FC1);
	c2=cvCloneMat(r2);
	for(i=0;i<cornercount1;i++)
	{
		CV_MAT_ELEM(*r1,double,i,0)=Corners1[i].x;
		CV_MAT_ELEM(*c1,double,i,0)=Corners1[i].y;
	}
	for(j=0;j<cornercount2;j++)
	{
		CV_MAT_ELEM(*r2,double,j,0)=Corners2[j].x;
		CV_MAT_ELEM(*c2,double,j,0)=Corners2[j].y;
	}
	L=cornercount1;

	M1=cvCreateMat(L,L,CV_64FC1);
	cvSetZero(M1);
	M2=cvCloneMat(M1);
	M11=cvCreateMat(L,L,CV_64FC1);
	M22=cvCreateMat(L,L,CV_64FC1);
	for(i=0;i<L-1;i++)
		for(j=i+1;j<L;j++)
		{
			CV_MAT_ELEM(*M11,double,i,j)=sqrt(pow((CV_MAT_ELEM(*r1,double,i,0)-CV_MAT_ELEM(*r1,double,j,0)),2)+pow((CV_MAT_ELEM(*c1,double,i,0)-CV_MAT_ELEM(*c1,double,j,0)),2));
			CV_MAT_ELEM(*M1,double,i,j)=exp((-1)*CV_MAT_ELEM(*M11,double,i,j)/(2*20*20));
			CV_MAT_ELEM(*M22,double,i,j)=sqrt(pow((CV_MAT_ELEM(*r2,double,i,0)-CV_MAT_ELEM(*r2,double,j,0)),2)+pow((CV_MAT_ELEM(*c2,double,i,0)-CV_MAT_ELEM(*c2,double,j,0)),2));
			CV_MAT_ELEM(*M2,double,i,j)=exp((-1)*CV_MAT_ELEM(*M22,double,i,j)/(2*20*20));
		}
	for(i=1;i<L;i++)
		for(j=0;j<i-1;j++)
		{
			CV_MAT_ELEM(*M1,double,i,j)=CV_MAT_ELEM(*M1,double,j,i);
			CV_MAT_ELEM(*M2,double,i,j)=CV_MAT_ELEM(*M2,double,j,i);
		}
	U=cvCreateMat(L,L,CV_64FC1);
	V=cvCloneMat(U);
	A=cvCreateMat(L,1,CV_64FC1);
	B=cvCloneMat(A);
	
	cvSVD(M1,A,U);//奇异值分解
	cvSVD(M2,B,V);
	for(i=0;i<L;i++)
		for(j=0;j<L;j++)
	{
		double test=CV_MAT_ELEM(*U,double,i,j);
	}
	for(i=0;i<L;i++)
	{
		X1=cvCreateMat(L,1,CV_64FC1);
		Y1=cvCreateMat(L,1,CV_64FC1);
		for(int i0=0;i0<L;i0++)
		{
			CV_MAT_ELEM(*X1,double,i0,0)=CV_MAT_ELEM(*V,double,i0,i);
			CV_MAT_ELEM(*Y1,double,i0,0)=CV_MAT_ELEM(*U,double,i0,i);
		}
		x11=x22=0;
		for(j=0;j<L;j++)
		{
			x11=x11+pow((CV_MAT_ELEM(*X1,double,j,0)-CV_MAT_ELEM(*Y1,double,j,0)),2);
			x22=x22+pow(((-1)*CV_MAT_ELEM(*X1,double,j,0)-CV_MAT_ELEM(*Y1,double,j,0)),2);
		}
		if(x11>=x22)
		{
			for(j=0;j<L;j++)
				CV_MAT_ELEM(*V,double,j,i)=(-1)*CV_MAT_ELEM(*V,double,j,i);
		}
	}

	C=cvCreateMat(L,L,CV_64FC1);
	CvMat* W=cvCreateMat(L,L,CV_64FC1);
	cvTranspose(V,W);
	cvMatMul(U,W,C);
	CvMat* Mtpt=cvCreateMat(L,2,CV_32SC1);
	int k=0;
	for(i=0;i<L;i++)
		for(j=0;j<L;j++)
		{
			if(isMax(C,i,j))
			{
				CV_MAT_ELEM(*Mtpt,int,k,0)=i;
				CV_MAT_ELEM(*Mtpt,int,k,1)=j;
				k++;
			}
		}
	CvMat* matchpt=cvCreateMat(k,4,CV_64FC1);
	for(i=0;i<k;i++)
		{
			double pt1x=CV_MAT_ELEM(*r1,double,CV_MAT_ELEM(*Mtpt,int,i,0),0);
			double pt1y=CV_MAT_ELEM(*c1,double,CV_MAT_ELEM(*Mtpt,int,i,0),0);
			double pt2x=CV_MAT_ELEM(*r2,double,CV_MAT_ELEM(*Mtpt,int,i,1),0);
			double pt2y=CV_MAT_ELEM(*c2,double,CV_MAT_ELEM(*Mtpt,int,i,1),0);
			pt1.x=pt1x;
			pt1.y=pt1y;
			pt2.x=pt2x+orisize1.width+50;
			pt2.y=pt2y+50;

			CV_MAT_ELEM(*matchpt,double,i,0)=pt1x;
			CV_MAT_ELEM(*matchpt,double,i,1)=pt1y;
			CV_MAT_ELEM(*matchpt,double,i,2)=pt2x;
			CV_MAT_ELEM(*matchpt,double,i,3)=pt2y;
			cvLine(showimg1,pt1,pt2,CV_RGB(255,0,0),1,0);
		}

	cvReleaseMat(&r1);
	cvReleaseMat(&c1);
	cvReleaseMat(&r2);
	cvReleaseMat(&c2);
	cvReleaseMat(&M1);
	cvReleaseMat(&M11);
	cvReleaseMat(&M2);
	cvReleaseMat(&M22);
	cvReleaseMat(&U);
	cvReleaseMat(&A);
	cvReleaseMat(&V);
	cvReleaseMat(&B);
	cvReleaseMat(&X1);
	cvReleaseMat(&Y1);
	cvReleaseMat(&C);
	cvReleaseMat(&Mtpt);
	return matchpt;
}

CvMat* CMatching::Init_Method(IplImage* showimg1,IplImage* showimg2,IplImage* grayImage1,IplImage* grayImage2,int patch_radius,int max_disparity,
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
//			if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<max_disparity*max_disparity)
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
//			if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<max_disparity*max_disparity)
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

	CvRect rect1,rect2;
//	CvMat* r1,*c1,*r2,*c2;
	CvPoint pt1,pt2;
	CvSize orisize1=cvGetSize(showimg1);
	//创建新的画布
	CvSize matchedsize;
	matchedsize.width=cvGetSize(showimg1).width*2+100;
	matchedsize.height=cvGetSize(showimg1).height*2+200;
	IplImage* matchedimg=cvCreateImage(matchedsize,IPL_DEPTH_8U,3);
	//更改m_imgsize1的大小，view中要用
	CvSize tempsize;
	tempsize=cvGetSize(showimg1);
	
	//将默认的黑色背景更改为白色
	cvSet(matchedimg,CV_RGB(255,255,255));
	//合并两幅图像
	
	rect1.x=0;//更改...
	rect1.y=0;
	rect1.width=showimg1->width;
	rect1.height=showimg1->height;
	cvSetImageROI(matchedimg,rect1);
	cvCopy(showimg1,matchedimg);
	
	cvResetImageROI(matchedimg);
	
	rect2.x=rect1.width+50;
	rect2.y=50;
	
	rect2.width=showimg2->width;
	rect2.height=showimg2->height;
	cvSetImageROI(matchedimg,rect2);
	cvCopy(showimg2,matchedimg);
	
	cvResetImageROI(matchedimg);
	cvReleaseImage(&showimg1);
	showimg1=cvCreateImage(matchedsize,IPL_DEPTH_8U,3);	
	cvCopy(matchedimg,showimg1);
	
	CvMat* matchpt=cvCreateMat(*nmatches,4,CV_64FC1);
	for(i=0;i<*nmatches;i++)
	{
		double pt1x=matches1[i].x;
		double pt1y=matches1[i].y;
		double pt2x=matches2[i].x;
		double pt2y=matches2[i].y;
		pt1.x=pt1x;
		pt1.y=pt1y;
		pt2.x=pt2x+orisize1.width+50;
		pt2.y=pt2y+50;
		
		CV_MAT_ELEM(*matchpt,double,i,0)=pt1x;
		CV_MAT_ELEM(*matchpt,double,i,1)=pt1y;
		CV_MAT_ELEM(*matchpt,double,i,2)=pt2x;
		CV_MAT_ELEM(*matchpt,double,i,3)=pt2y;
		cvLine(showimg1,pt1,pt2,CV_RGB(255,0,0),1,0);
	}
	
	cvReleaseImage(&patchimg1);
	cvReleaseImage(&patchimg2);
	return matchpt;
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

CvMat* CMatching::quCornermatcher(IplImage* showimg1,IplImage* showimg2,IplImage* grayImage1,IplImage* grayImage2,int patch_radius,int max_disparity,double max_diatance,int fmethod,
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
	
	CvMat* points1=cvCreateMat(2,*nmatches,CV_32F);
	CvMat* points2 =cvCreateMat(2,*nmatches,CV_32F);
	CvMat* fundMatr=cvCreateMat(3,3,CV_32F);
	CvMat* status  =cvCreateMat(1,*nmatches,CV_32F);
	CvMat* corrLines1=cvCreateMat(3,*nmatches,CV_32F);
	CvMat* corrLines2=cvCreateMat(3,*nmatches,CV_32F);
	for(i=0;i<*nmatches;i++)
	{
		cvmSet(points1,0,i,matches1[i].x); cvmSet(points1,1,i,matches1[i].y);
		cvmSet(points2,0,i,matches2[i].x); cvmSet(points2,1,i,matches2[i].y);
	}
	int num;
	if(fmethod==0)
	{
		if(*nmatches>=7)			
			num=cvFindFundamentalMat(points1,points2,fundMatr,CV_FM_7POINT);
	}
	else if(fmethod==1)
	{
		if(*nmatches>=8)
			num=cvFindFundamentalMat(points1,points2,fundMatr,CV_FM_8POINT);
	}
	else if(fmethod==2)
	{
		if(*nmatches>=8)
			num=cvFindFundamentalMat(points1,points2,fundMatr,CV_FM_RANSAC,max_diatance,0.99,status);
	}
	else if(fmethod==3)
	{
		if(*nmatches>=8)
			num=cvFindFundamentalMat(points1,points2,fundMatr,CV_FM_LMEDS,max_diatance,0.99,status);
	}
	if(num>0)
	{
		cvComputeCorrespondEpilines(points1,1,fundMatr,corrLines2);
		cvComputeCorrespondEpilines(points2,2,fundMatr,corrLines1);
		
		quGuidematcher(grayImage1,grayImage2,patch_radius,max_disparity,max_diatance,
			corners1,corners2,cornerCount,fundMatr,
			matches1,matches2,nmatches,mat12,mat21);
		
		CvRect rect1,rect2;
//		CvMat* r1,*c1,*r2,*c2;
		CvPoint pt1,pt2;
		CvSize orisize1=cvGetSize(showimg1);
		//创建新的画布
		CvSize matchedsize;
		matchedsize.width=cvGetSize(showimg1).width*2+100;
		matchedsize.height=cvGetSize(showimg1).height*2+200;
		IplImage* matchedimg=cvCreateImage(matchedsize,IPL_DEPTH_8U,3);
		//更改m_imgsize1的大小，view中要用
		CvSize tempsize;
		tempsize=cvGetSize(showimg1);
		
		//将默认的黑色背景更改为白色
		cvSet(matchedimg,CV_RGB(255,255,255));
		//合并两幅图像
		
		rect1.x=0;//更改...
		rect1.y=0;
		rect1.width=showimg1->width;
		rect1.height=showimg1->height;
		cvSetImageROI(matchedimg,rect1);
		cvCopy(showimg1,matchedimg);
		
		cvResetImageROI(matchedimg);
		
		rect2.x=rect1.width+50;
		rect2.y=50;
		
		rect2.width=showimg2->width;
		rect2.height=showimg2->height;
		cvSetImageROI(matchedimg,rect2);
		cvCopy(showimg2,matchedimg);
		
		cvResetImageROI(matchedimg);
		cvReleaseImage(&showimg1);
		showimg1=cvCreateImage(matchedsize,IPL_DEPTH_8U,3);	
		cvCopy(matchedimg,showimg1);	
		
		CvMat* matchpt=cvCreateMat(*nmatches,4,CV_64FC1);
		for(i=0;i<*nmatches;i++)
		{
			double pt1x=matches1[i].x;
			double pt1y=matches1[i].y;
			double pt2x=matches2[i].x;
			double pt2y=matches2[i].y;
			pt1.x=pt1x;
			pt1.y=pt1y;
			pt2.x=pt2x+orisize1.width+50;
			pt2.y=pt2y+50;
			
			CV_MAT_ELEM(*matchpt,double,i,0)=pt1x;
			CV_MAT_ELEM(*matchpt,double,i,1)=pt1y;
			CV_MAT_ELEM(*matchpt,double,i,2)=pt2x;
			CV_MAT_ELEM(*matchpt,double,i,3)=pt2y;
			cvLine(showimg1,pt1,pt2,CV_RGB(255,0,0),1,0);
		}
		
		cvReleaseImage(&patchimg1);
		cvReleaseImage(&patchimg2);
		return matchpt;
	}
	else
		return NULL;
}

CvMat* CMatching::SIFT_Method(IplImage* showimg1,IplImage* showimg2,IplImage* srcImg1,IplImage* srcImg2,int *nmatches)
{
	struct feature* feat1, * feat2, * feat;
	struct feature** nbrs;
	struct kd_node* kd_root;
	IplImage* stacked;
	//	CvPoint pt1, pt2;
	double d0, d1;
	int n1, n2, k, i, m = 0;

	CvRect rect1,rect2;
	CvMat* r1,*c1,*r2,*c2;
	CvPoint pt1,pt2;
	CvSize orisize1=cvGetSize(showimg1);
	//创建新的画布
	CvSize matchedsize;
	matchedsize.width=cvGetSize(showimg1).width*2+100;
	matchedsize.height=cvGetSize(showimg1).height*2+200;
	IplImage* matchedimg=cvCreateImage(matchedsize,IPL_DEPTH_8U,3);
	//更改m_imgsize1的大小，view中要用
	CvSize tempsize;
	tempsize=cvGetSize(showimg1);
	
	//合并两幅图像
	
	rect1.x=0;//更改...
	rect1.y=0;
	rect1.width=showimg1->width;
	rect1.height=showimg1->height;
	cvSetImageROI(matchedimg,rect1);
	cvCopy(showimg1,matchedimg);
	
	cvResetImageROI(matchedimg);
	
	rect2.x=rect1.width+50;
	rect2.y=50;
	
	rect2.width=showimg2->width;
	rect2.height=showimg2->height;
	cvSetImageROI(matchedimg,rect2);
	cvCopy(showimg2,matchedimg);
	
	cvResetImageROI(matchedimg);
	cvReleaseImage(&showimg1);
	showimg1=cvCreateImage(matchedsize,IPL_DEPTH_8U,3);
	cvCopy(matchedimg,showimg1);

	n1 = sift_features( srcImg1, &feat1 );
	n2 = sift_features( srcImg2, &feat2 );

	kd_root = kdtree_build( feat2, n2 );
	
	CvMat* matchpt=cvCreateMat(n1,4,CV_64FC1);
	for( i = 0; i < n1; i++ )
	{
		feat = feat1 + i;
		k = kdtree_bbf_knn( kd_root, feat, 2, &nbrs, KDTREE_BBF_MAX_NN_CHKS );
		if( k == 2 )
		{
			d0 = descr_dist_sq( feat, nbrs[0] );
			d1 = descr_dist_sq( feat, nbrs[1] );
			if( d0 < d1 * NN_SQ_DIST_RATIO_THR )
			{
				pt1 = cvPoint( cvRound( feat->x ), cvRound( feat->y ) );
				pt2 = cvPoint( cvRound( nbrs[0]->x ), cvRound( nbrs[0]->y ) );
				
				double pt1x=pt1.x;
				double pt1y=pt1.y;
				double pt2x=pt2.x;
				double pt2y=pt2.y;
				pt1.x=pt1x;
				pt1.y=pt1y;
				pt2.x=pt2x+orisize1.width+50;
				pt2.y=pt2y+50;
				
				CV_MAT_ELEM(*matchpt,double,i,0)=pt1x;
				CV_MAT_ELEM(*matchpt,double,i,1)=pt1y;
				CV_MAT_ELEM(*matchpt,double,i,2)=pt2x;
				CV_MAT_ELEM(*matchpt,double,i,3)=pt2y;
				cvLine(showimg1,pt1,pt2,CV_RGB(255,0,0),1,0);
				m++;
				feat1[i].fwd_match = nbrs[0];	
			}
		}
		free( nbrs );
	}
	*nmatches=m;
	kdtree_release( kd_root );
	free( feat1 );
	free( feat2 );	
	return matchpt;
}