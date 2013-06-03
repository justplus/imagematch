// MyOpenCV.h : my opencv functions diclaration
//
/////////////////////////////////////////////////////////////////////////////

#include "ipl.h"
#include "cv.h"
#include "highgui.h"

// Operations
// ��ʮ���α�Ǻ���
void quPlotCross(CvArr* img,CvPoint pt,CvScalar color,int thickness,int radius);

// �������ʼƥ�亯��
void quCornermatcher(IplImage* grayImage1,IplImage* grayImage2,int patch_radius,int max_disparity,
					 CvPoint2D32f* corners1,CvPoint2D32f* corners2,int cornerCount,
					 CvPoint2D32f* matches1,CvPoint2D32f* matches2,int* nmatches,int* mat12,int* mat21);

// ����F������ƥ�亯��
void quGuidematcher(IplImage* grayImage1,IplImage* grayImage2,int patch_radius,int max_disparity,double epidis,
					 CvPoint2D32f* corners1,CvPoint2D32f* corners2,int cornerCount,CvMat* fundMatr,
					 CvPoint2D32f* matches1,CvPoint2D32f* matches2,int* nmatches,int* mat12,int* mat21);


// Attributes
