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
	//*********������**************
	CMainFrame* pFrame;
	bool oneView;//һ����ͼ����
	COLORREF crTextColor1,cornerColor;//������ɫ
//	int viewNum;//������ͼ����
	//*********��ͼ��************
	COpenImageDlg imgdlg;
	IplImage* srcImg1;
	IplImage* srcImg2;
	IplImage* grayImg1;
	IplImage* grayImg2;
	IplImage* showImg1;
	IplImage* showImg2;
	CvSize m_imgsize1,m_imgsize2;//Դͼ���С
	BOOL IMG1OPEN,IMG2OPEN;//�Ƿ��ͼ���־
	//*********����ƫ������**********
	CPerference perferenceDlg;
	CString DebugPath;
	int cb1;//��ȡini�еĲ���
	int cb2;
	int cb3;
	int cb4;
	CString	m_savepath;
	//COLORREF cornercolor;
	CvScalar cornercolor;
	COLORREF infolistcolor;
	//*********����ͼ�����**********
	bool isenlarge;//�Ƿ�Ŵ�ͼ���־
	bool isreduce;
	double scale;
	double scale1;//�ұ�ͼ�������ϵ��
	bool isview;
	//*********�������**************
	CHarrisDlg harrisDlg;
	CSubPixelDlg subpixelDlg;
	CSiftDlg siftdlg;
	CImportFeapt importfeaptDlg;
	CRegistrationDlg registrationDlg;
	CSTMatch stmatchdlg;
	//*********��������************
	CvPoint2D32f corners1[MAXFEATURES];
	CvPoint2D32f corners2[MAXFEATURES];
	int corner1count;
	int corner2count;
	
	//---------�����ؼ�-----------
	BOOL	m_guassblur;//�Ƿ�ʹ�ø�˹�˲���־
	int		m_cornercount;//�ǵ���Ŀ
	double	m_min_distance;//��������
	double	m_quality_level;//��С�ǵ�ǿ��ϵ��
	int		m_winlength;//����������
	int		m_max_iter;//����������
	double	m_epsilon;//�����ȷ��
	double	m_sigma;//Guassian����
	int		m_guass_winwidth;//�˲������
	int		m_guass_winheigth;//�˲����߶�
	//-----------Harris-----------
	int		m_corner_count;
	double	m_quality_level1;
	double	m_min_distance1;
	int		m_block_size;
	//-----------SIFT-------------
	int		SIFT_INTVLS;//��������
	double	SIFT_SIGMA;//ƽ����˹����
	double	SIFT_CONTR_THR;//�ȶ���������ֵ
	int		SIFT_CURV_THR;//��������ֵ
	int		SIFT_DESCR_WIDTH;//����������������
	int		SIFT_DESCR_HIST_BINS;//��������������ͶӰ��
	double	SIFT_DESCR_MAG_THR;//������ֵ
	//-----------����������--------
	CString file1path;
	CString file2path;
	//-----------�޳������������------
	CRectTracker m_rectTracker;
	bool isdeletefeas;//�Ƿ�Ҫɾ���ǵ�
	CRectTracker m_rectTracker1;
	bool isdeletefeas1;//�Ƿ�Ҫɾ���ǵ�

	CRect m_rect1;
	CRect m_rect2;
	//*********ͼ��ƥ��****************
	CMatching matching;
	CvMat* matchpt;//�洢��ƥ����������

	int		patch_radius;
	int		max_disparity;
	double	max_distance;
	int		fmethod;

	//*********ͼ����׼****************
	int		m_transmode;
	int		m_fillval;
	IplImage* regimg;
	bool isdeleteline;
	int LineCount;//�����޳���ƥ���ߵ�����
	int seqno;//�������޳������������е�λ��

	CRectTracker m_rectTracker2;
	CRect m_rect3;
	//*********Utility*****************
	CUtility utility;

	//*********�����Ƿ����************
	bool CornerDetection;//�Ƿ���ɽǵ���
	bool Match;//�Ƿ���ɽǵ�ƥ��
	bool Registration;//�Ƿ���ɽǵ���׼
	bool Fusion;//�Ƿ����ͼ���ں�
	bool Sift;//sift�ǵ����Ƿ����
	bool Subpixel;//�����ؼ��ǵ����Ƿ����
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
