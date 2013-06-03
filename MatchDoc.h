// MatchDoc.h : interface of the CMatchDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATCHDOC_H__26FD73B2_817F_417B_A92D_1023F55610AE__INCLUDED_)
#define AFX_MATCHDOC_H__26FD73B2_817F_417B_A92D_1023F55610AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MainFrm.h"
#include "OpenImageDlg.h"
#include "HarrisDlg.h"
#include "RegistrationDlg.h"
#include "SubPixel.h"
#include "SiftDlg.h"
#include "ImportFeapt.h"
#include "STMatch.h"
#include "Perference.h"
#include "Matching.h"
#include "Utility.h"
#include "cv.h"
#include "highgui.h"

#define MAXFEATURES 5000

class CMatchDoc : public CDocument
{
protected: // create from serialization only
	CMatchDoc();
	DECLARE_DYNCREATE(CMatchDoc)

// Attributes
public:
	//*********主窗口**************
	CMainFrame* pFrame;
	bool oneView;//一个视图窗口
	COLORREF crTextColor1,cornerColor;//字体颜色
//	int viewNum;//窗口视图个数
	//*********打开图像************
	COpenImageDlg imgdlg;
	IplImage* srcImg1;
	IplImage* srcImg2;
	IplImage* grayImg1;
	IplImage* grayImg2;
	IplImage* showImg1;
	IplImage* showImg2;
	CvSize m_imgsize1,m_imgsize2;//源图像大小
	BOOL IMG1OPEN,IMG2OPEN;//是否打开图像标志
	//*********个人偏好设置**********
	CPerference perferenceDlg;
	CString DebugPath;
	int cb1;//提取ini中的参数
	int cb2;
	int cb3;
	int cb4;
	CString	m_savepath;
	//COLORREF cornercolor;
	CvScalar cornercolor;
	COLORREF infolistcolor;
	//*********基本图像操作**********
	bool isenlarge;//是否放大图像标志
	bool isreduce;
	double scale;
	double scale1;//右边图像的缩放系数
	bool isview;
	//*********软件设置**************
	CHarrisDlg harrisDlg;
	CSubPixelDlg subpixelDlg;
	CSiftDlg siftdlg;
	CImportFeapt importfeaptDlg;
	CRegistrationDlg registrationDlg;
	CSTMatch stmatchdlg;
	//*********特征点检测************
	CvPoint2D32f corners1[MAXFEATURES];
	CvPoint2D32f corners2[MAXFEATURES];
	int corner1count;
	int corner2count;
	
	//---------亚像素级-----------
	BOOL	m_guassblur;//是否使用高斯滤波标志
	int		m_cornercount;//角点数目
	double	m_min_distance;//限制因子
	double	m_quality_level;//最小角点强度系数
	int		m_winlength;//搜索窗长度
	int		m_max_iter;//最大迭代次数
	double	m_epsilon;//结果精确度
	double	m_sigma;//Guassian方差
	int		m_guass_winwidth;//滤波器宽度
	int		m_guass_winheigth;//滤波器高度
	//-----------Harris-----------
	int		m_corner_count;
	double	m_quality_level1;
	double	m_min_distance1;
	int		m_block_size;
	//-----------SIFT-------------
	int		SIFT_INTVLS;//采样因子
	double	SIFT_SIGMA;//平滑高斯方差
	double	SIFT_CONTR_THR;//稳定特征点阈值
	int		SIFT_CURV_THR;//主曲率阈值
	int		SIFT_DESCR_WIDTH;//特征描述符邻域宽度
	int		SIFT_DESCR_HIST_BINS;//特征描述符邻域投影数
	double	SIFT_DESCR_MAG_THR;//比例阈值
	//-----------导入特征点--------
	CString file1path;
	CString file2path;
	//-----------剔除错误的特征点------
	CRectTracker m_rectTracker;
	bool isdeletefeas;//是否要删除角点
	CRectTracker m_rectTracker1;
	bool isdeletefeas1;//是否要删除角点

	CRect m_rect1;
	CRect m_rect2;
	//*********图像匹配****************
	CMatching matching;
	CvMat* matchpt;//存储已匹配的特征点对

	int		patch_radius;
	int		max_disparity;
	double	max_distance;
	int		fmethod;

	//*********图像配准****************
	int		m_transmode;
	int		m_fillval;
	IplImage* regimg;
	bool isdeleteline;
	int LineCount;//保存剔除的匹配线的数量
	int seqno;//保存欲剔除的线在数组中的位置

	CRectTracker m_rectTracker2;
	CRect m_rect3;
	//*********Utility*****************
	CUtility utility;

	//*********步骤是否完成************
	bool CornerDetection;//是否完成角点检测
	bool Match;//是否完成角点匹配
	bool Registration;//是否完成角点配准
	bool Fusion;//是否完成图像融合
	bool Sift;//sift角点检测是否完成
	bool Subpixel;//亚像素级角点检测是否完成
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatchDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DeleteLines(CvMat* mat,CRect rect);
	void DeletePts1(CRect rect);
	void DeletePts(CRect rect);
	virtual ~CMatchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMatchDoc)
	afx_msg void OnImageOpen();
	afx_msg void OnImageSave();
	afx_msg void OnImageSaveAs();
	afx_msg void OnPerference();
	afx_msg void OnEnlarge();
	afx_msg void OnReduce();
	afx_msg void OnViewImage();
	afx_msg void OnSoftwareSetting();
	afx_msg void OnHarris();
	afx_msg void OnSubpixel();
	afx_msg void OnSift();
	afx_msg void OnImportFeapts();
	afx_msg void OnExportFeapts();
	afx_msg void OnLaplace();
	afx_msg void OnAutoRegistration();
	afx_msg void OnDeleteFeapts();
	afx_msg void OnFusion();
	afx_msg void OnManualRegistration();
	afx_msg void OnScott();
	afx_msg void OnMenuitem32832();
	afx_msg void OnSiftmatch();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATCHDOC_H__26FD73B2_817F_417B_A92D_1023F55610AE__INCLUDED_)
