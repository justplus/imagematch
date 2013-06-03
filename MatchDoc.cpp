// MatchDoc.cpp : implementation of the CMatchDoc class
//

#include "stdafx.h"
#include "Match.h"
#include "MatchDoc.h"
#include "FeatherPts.h"
#include "Matching.h"
// #include "cv.h"
// #include "highgui.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatchDoc

IMPLEMENT_DYNCREATE(CMatchDoc, CDocument)

BEGIN_MESSAGE_MAP(CMatchDoc, CDocument)
	//{{AFX_MSG_MAP(CMatchDoc)
	ON_COMMAND(ID_IMAGE_OPEN, OnImageOpen)
	ON_COMMAND(ID_IMAGE_SAVE, OnImageSave)
	ON_COMMAND(ID_IMAGE_SAVE_AS, OnImageSaveAs)
	ON_COMMAND(ID_PERFERENCE, OnPerference)
	ON_COMMAND(ID_ENLARGE, OnEnlarge)
	ON_COMMAND(ID_REDUCE, OnReduce)
	ON_COMMAND(ID_VIEW_IMAGE, OnViewImage)
	ON_COMMAND(ID_SOFTWARE_SETTING, OnSoftwareSetting)
	ON_COMMAND(ID_HARRIS, OnHarris)
	ON_COMMAND(ID_SUBPIXEL, OnSubpixel)
	ON_COMMAND(ID_SIFT, OnSift)
	ON_COMMAND(ID_IMPORT_FEAPTS, OnImportFeapts)
	ON_COMMAND(ID_EXPORT_FEAPTS, OnExportFeapts)
	ON_COMMAND(ID_LAPLACE, OnLaplace)
	ON_COMMAND(ID_AUTO_REGISTRATION, OnAutoRegistration)
	ON_COMMAND(ID_DELETE_FEAPTS, OnDeleteFeapts)
	ON_COMMAND(ID_FUSION, OnFusion)
	ON_COMMAND(ID_MANUAL_REGISTRATION, OnManualRegistration)
	ON_COMMAND(ID_MENUITEM32832, OnMenuitem32832)
	ON_COMMAND(ID_SIFTMATCH, OnSiftmatch)
	ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatchDoc construction/destruction

CMatchDoc::CMatchDoc()
{
	//��ʼ����ͼ����
	oneView=false;
	//��ȡdebug·��
	DebugPath=AfxGetApp()->m_pszHelpFilePath;
	DebugPath=DebugPath.Left(DebugPath.ReverseFind('\\')); 
	DebugPath+= _T("\\");
	//��ʼ��ͼ��򿪱�־
	IMG1OPEN=FALSE;
	IMG2OPEN=FALSE;
	
	//��ʼ�����ű�־
	isenlarge=false;
	isreduce=false;
	scale=scale1=1.0;
	isview=false;
	//��ʼ����������
	m_guassblur = true;
	m_cornercount = 1000;
	m_min_distance = 3.0;
	m_quality_level = 1e-7;
	m_winlength = 3;
	m_max_iter = 10;
	m_epsilon = 0.1;
	m_sigma = 0.5;
	m_guass_winwidth = 3;
	m_guass_winheigth = 3;

	m_corner_count = 50;
	m_quality_level1 = 0.1;
	m_min_distance1 = 10;
	m_block_size = 3;

// 	m_transmode=0;
// 	m_fillval=1;
	patch_radius = 5;
	max_disparity = 50;
	max_distance = 1.5;
	fmethod = 2;

	SIFT_INTVLS = 3;
	SIFT_SIGMA = 1.6;
	SIFT_CONTR_THR = 0.04;
	SIFT_CURV_THR = 10;
	SIFT_DESCR_WIDTH = 4;
	SIFT_DESCR_HIST_BINS = 8;
	SIFT_DESCR_MAG_THR = 0.2;

	isdeletefeas=false;
	isdeleteline=false;
	LineCount=0;
	//�жϸ��������Ƿ����
	CornerDetection=false;
	Match=false;
	Registration=false;
	Fusion=false;
	Sift=false;
	Subpixel=false;
	//��ɫ��ʼ��
//	crTextColor1=0x007F00;//��Ϣ�б��������ɫ
//	cornerColor=0x007F00;//�ǵ���ɫ
	//����ƫ������
	char initpath[100];
	DWORD result=GetPrivateProfileString("Setting","ͼ�񱣴�λ��",NULL,initpath,100,DebugPath+"setting.ini");
	if(result>0)
		m_savepath.Format("%s",initpath);
	else
		m_savepath=DebugPath+"images";
	char initcolor1[11];
	GetPrivateProfileString("Setting","�ǵ���ɫ",NULL,initcolor1,11,DebugPath+"setting.ini");
	char initcolor2[11];
	GetPrivateProfileString("Setting","��Ϣ����ɫ",NULL,initcolor2,11,DebugPath+"setting.ini");
	CString cor1;
	cor1.Format("%s",initcolor1);
	int x0=cor1.Find(",",0);
	int x1=cor1.Find(",",x0+1);
	int cor1r=atoi(cor1.Mid(0,x0));
	int cor1g=atoi(cor1.Mid(x0+1,x1));
	int cor1b=atoi(cor1.Mid(x1+1));
	cornercolor=CV_RGB(cor1r,cor1g,cor1b);

	CString cor2;
	cor2.Format("%s",initcolor2);
	int x2=cor2.Find(",",0);
	int x3=cor2.Find(",",x2+1);
	int cor2r=atoi(cor2.Mid(0,x2));
	int cor2g=atoi(cor2.Mid(x2+1,x3));
	int cor2b=atoi(cor2.Mid(x3+1));
	infolistcolor=RGB(cor2r,cor2g,cor2b);
	crTextColor1=infolistcolor;


	//��ʼ����׼����
 	char inittran[2];
 	GetPrivateProfileString("Setting","�任ģ��",NULL,inittran,2,DebugPath+"setting.ini");
 	int cb3=atoi(inittran);
 	char initinsert[2];
 	GetPrivateProfileString("Setting","��ֵ����",NULL,initinsert,2,DebugPath+"setting.ini");
 	int cb4=atoi(initinsert);
	m_transmode=cb3;
	m_fillval=cb4;
}

CMatchDoc::~CMatchDoc()
{
	if(IMG1OPEN)
	{
		cvReleaseImage(&srcImg1);
		cvReleaseImage(&showImg1);
	}
	if(IMG2OPEN)
	{
		cvReleaseImage(&srcImg2);
		cvReleaseImage(&showImg2);
	}
}

BOOL CMatchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	SetTitle("ͼ����׼ϵͳ");
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMatchDoc serialization

void CMatchDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMatchDoc diagnostics

#ifdef _DEBUG
void CMatchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMatchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMatchDoc commands

//��ͼ�񡾲˵���
void CMatchDoc::OnImageOpen() 
{
	//������ͼ����
	pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->viewnum=2;
	pFrame->setView(2);

	CString outputmsg1="";
	CString outputmsg2="";
	if(imgdlg.DoModal()==IDOK)
	{
		if(imgdlg.imgpath1!="")//ͼ��·��Ϊ��
		{
			srcImg1=cvvLoadImage(imgdlg.imgpath1);
			if(srcImg1==NULL)//ͼ���ʧ��
			{
				outputmsg1=">>δ�ܴ�ͼ��1,���ܸ�ʽ����; ";
			}
			else
			{
				m_imgsize1=cvGetSize(srcImg1);
				IMG1OPEN=TRUE;
				//��ʼ����ʾͼ��
				showImg1=cvCreateImage(cvGetSize(srcImg1),IPL_DEPTH_8U,3);
				cvCopy(srcImg1,showImg1);
				grayImg1=cvCreateImage(cvGetSize(srcImg1),IPL_DEPTH_8U,1);
				cvCvtColor(srcImg1,grayImg1,CV_BGR2GRAY);
				outputmsg1.Format(">>ͼ��1�Ĵ�С:%d*%d; ",m_imgsize1.width,m_imgsize1.height);
			}	
		}
		else
			outputmsg1=">>ͼ��1·��Ϊ��; ";
		if(imgdlg.imgpath2!="")
		{
			srcImg2=cvvLoadImage(imgdlg.imgpath2);//make copy
			if(srcImg2==NULL)
			{
				outputmsg2="δ�ܴ�ͼ��2,���ܸ�ʽ����";
			}
			else
			{
				m_imgsize2=cvGetSize(srcImg2);
				IMG2OPEN=TRUE;
				//��ʼ����ʾͼ��
				showImg2=cvCreateImage(cvGetSize(srcImg2),IPL_DEPTH_8U,3);
				cvCopy(srcImg2,showImg2);
				grayImg2=cvCreateImage(cvGetSize(srcImg2),IPL_DEPTH_8U,1);
				cvCvtColor(srcImg2,grayImg2,CV_BGR2GRAY);
				outputmsg2.Format("ͼ��2�Ĵ�С:%d*%d",m_imgsize2.width,m_imgsize2.height);
			}
		}
		else
			outputmsg2="ͼ��2·��Ϊ��";
		utility.PrintText(outputmsg1+outputmsg2,crTextColor1);
		CornerDetection=false;
		Match=false;
		Registration=false;
		Fusion=false;
		UpdateAllViews(NULL);	
	}
	CornerDetection=false;
	Match=false;
	Registration=false;
	Fusion=false;
}

//����ͼ�񡾲˵���
void CMatchDoc::OnImageSave() 
{
	 
	SYSTEMTIME st;//ϵͳʱ��
	GetLocalTime(&st);
	CString Filelast;
	Filelast.Format("%2d%2d",st.wMinute,st.wSecond);
	
	if(IMG1OPEN&&IMG2OPEN)
	{
		if(GetFileAttributes(m_savepath)!=-1)
		{
			if(!oneView)
			{
				cvSaveImage(m_savepath+"\\view1"+Filelast+".jpg",showImg1);
				cvSaveImage(m_savepath+"\\view2"+Filelast+".jpg",showImg2);
			}
			else if(!oneView)
				cvSaveImage(m_savepath+"\\view.jpg",showImg1);
			AfxMessageBox("ͼ���ѱ�����"+m_savepath+"�ļ�����");
		}
		else
			AfxMessageBox("�ļ��д���ʧ�ܣ�ͼ���޷����棡");
	}
	else
	{
		utility.PrintText(">>��ͼ��û��ͼ����Ҫ����",crTextColor1);
	}
}

//ͼ�����Ϊ���˵���
void CMatchDoc::OnImageSaveAs() 
{
	CString tipmsg;
	LPCTSTR lpszFilters; 
	lpszFilters="*.JPG|*.jpg|*.BMP|*.bmp|*.DIB|*.dib|*.TGA|*.tga|*.PCX|*.pcx|*.TIF|*.tif||";
	CFileDialog savedlg(false,"jpg",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,lpszFilters,NULL);
	if(savedlg.DoModal()==IDOK)
	{
		if(!(IMG1OPEN&&IMG2OPEN))
		{
			tipmsg="��ͼ��û��ͼ����Ҫ����";
		}
		else
		{
			cvSaveImage("View1"+savedlg.GetFileName(),showImg1);
			cvSaveImage("View2"+savedlg.GetFileName(),showImg2);
			tipmsg="ͼ�񱣴���ɣ�";
		}
		utility.PrintText(">>"+tipmsg,crTextColor1);
	}
}

//����ƫ�����á��˵���
void CMatchDoc::OnPerference() 
{
	if(perferenceDlg.DoModal()==IDOK)
	{
		CString Head="Setting";
		char CornerSeq[1],MatchSeq[1],TransSeq[1],InsertSeq[1];
		itoa(perferenceDlg.cb1,CornerSeq,10);
		itoa(perferenceDlg.cb2,MatchSeq,10);
		itoa(perferenceDlg.cb3,TransSeq,10);
		itoa(perferenceDlg.cb4,InsertSeq,10);
		CString SavePath=perferenceDlg.m_savepath;
		char color1r[3],color1g[3],color1b[3];
		char color2r[3],color2g[3],color2b[3];
		itoa(GetRValue(perferenceDlg.cornercolor),color1r,10);
		itoa(GetGValue(perferenceDlg.cornercolor),color1g,10);
		itoa(GetBValue(perferenceDlg.cornercolor),color1b,10);
		itoa(GetRValue(perferenceDlg.infolistcolor),color2r,10);
		itoa(GetGValue(perferenceDlg.infolistcolor),color2g,10);
		itoa(GetBValue(perferenceDlg.infolistcolor),color2b,10);
		CString color1;
		CString color2;
		color1.Format("%s,%s,%s",color1r,color1g,color1b);
		color2.Format("%s,%s,%s",color2r,color2g,color2b);
		WritePrivateProfileString(Head,"�ǵ���",CornerSeq,DebugPath+"\\setting.ini");
		WritePrivateProfileString(Head,"�ǵ�ƥ��",MatchSeq,DebugPath+"\\setting.ini");
		WritePrivateProfileString(Head,"�任ģ��",TransSeq,DebugPath+"\\setting.ini");
		WritePrivateProfileString(Head,"��ֵ����",InsertSeq,DebugPath+"\\setting.ini");
		WritePrivateProfileString(Head,"ͼ�񱣴�λ��",SavePath,DebugPath+"\\setting.ini");
		WritePrivateProfileString(Head,"�ǵ���ɫ",color1,DebugPath+"\\setting.ini");
		WritePrivateProfileString(Head,"��Ϣ����ɫ",color2,DebugPath+"\\setting.ini");
		AfxMessageBox("���ø����ѱ��棡�����������Ч��");
	}
}

//ͼ��Ŵ󡾲˵���
void CMatchDoc::OnEnlarge() 
{
	isreduce=isview=false;
	GetCapture();
	HCURSOR hlcursor;
	if(isenlarge)
	{
		isenlarge=false;
		hlcursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	}
	else
	{
		isenlarge=true;
		hlcursor=AfxGetApp()->LoadCursor(MAKEINTRESOURCE(IDB_ENLARGE));
	}
	SetCursor(hlcursor);
	UpdateAllViews(NULL);
}

//ͼ����С���˵���
void CMatchDoc::OnReduce() 
{
	isenlarge=isview=false;
	GetCapture();
	HCURSOR hlcursor;
	if(isreduce)
	{
		isreduce=false;
		hlcursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	}
	else
	{
		isreduce=true;
		hlcursor=AfxGetApp()->LoadCursor(MAKEINTRESOURCE(IDB_REDUCE));
	}
	SetCursor(hlcursor);
}

//�鿴ͼ�񡾲˵���
void CMatchDoc::OnViewImage() 
{
	isenlarge=isreduce=false;
	GetCapture();
	HCURSOR hlcursor;
	if(isview)
	{
		isview=false;
		hlcursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	}
	else
	{
		isview=true;
		hlcursor=AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649));
	}
	SetCursor(hlcursor);
	::ReleaseCapture();
}

//������á��˵���
void CMatchDoc::OnSoftwareSetting() 
{
	CPropertySheet dlgPropertySheet("�������",0);
	dlgPropertySheet.AddPage(&harrisDlg);
	dlgPropertySheet.AddPage(&subpixelDlg);
	dlgPropertySheet.AddPage(&siftdlg);
	dlgPropertySheet.AddPage(&stmatchdlg);
	dlgPropertySheet.AddPage(&registrationDlg);
	dlgPropertySheet.m_psh.dwFlags |= PSH_NOAPPLYNOW | PSH_PROPTITLE;
	if(dlgPropertySheet.DoModal()==IDOK)
	{
		//-----------�����ؼ�---------
		m_guassblur=subpixelDlg.m_guassblur;
		m_cornercount=subpixelDlg.m_cornercount;
		m_min_distance=subpixelDlg.m_min_distance;
		m_quality_level=subpixelDlg.m_quality_level;
		m_winlength=subpixelDlg.m_winlength;
		m_max_iter=subpixelDlg.m_max_iter;
		m_epsilon=subpixelDlg.m_epsilon;
		m_sigma=subpixelDlg.m_sigma;
		m_guass_winwidth=subpixelDlg.m_guass_winwidth;
		m_guass_winheigth=subpixelDlg.m_guass_winheigth;
		//-----------Harris-----------
		m_corner_count=harrisDlg.m_corner_count;
		m_quality_level1=harrisDlg.m_quality_level;
		m_min_distance1=harrisDlg.m_min_distance;
		m_block_size=harrisDlg.m_block_size;
		//----------SIFT--------------
		SIFT_INTVLS = siftdlg.SIFT_INTVLS;
		SIFT_SIGMA = siftdlg.SIFT_SIGMA;
		SIFT_CONTR_THR = siftdlg.SIFT_CONTR_THR;
		SIFT_CURV_THR = siftdlg.SIFT_CURV_THR;
		SIFT_DESCR_WIDTH = siftdlg.SIFT_DESCR_WIDTH;
		SIFT_DESCR_HIST_BINS = siftdlg.SIFT_DESCR_HIST_BINS;
		SIFT_DESCR_MAG_THR = siftdlg.SIFT_DESCR_MAG_THR;
	//*********ͼ��ƥ��****************
		patch_radius = stmatchdlg.patch_radius;
		max_disparity = stmatchdlg.max_disparity;
		max_distance = stmatchdlg.max_distance;
		fmethod = stmatchdlg.fmethod;
	//*********ͼ����׼****************
		m_transmode=registrationDlg.m_transmode;
		m_fillval=registrationDlg.m_fillval;
	}
}


//Harris�ǵ��⡾�˵���
void CMatchDoc::OnHarris() 
{
	CString text;
	if(IMG1OPEN&&IMG2OPEN)
	{
		//����������֤ÿ��Harris�ǵ���ƶ�����Դͼ���ϣ����������Ѵ����ͼ���ϵ���
		cvCopy(srcImg1,showImg1);
 		cvCopy(srcImg2,showImg2);
		CFeatherPts featherpt;
		CFeatherPts featherpt1;
		featherpt.Harris_Method(srcImg1,m_corner_count,m_quality_level1,m_min_distance1,m_block_size);
		for(int i=0;i<featherpt.cornersCount;i++)
		{
			utility.DrawCross(showImg1,featherpt.corners[i],cornercolor,1,4);
			corners1[i]=featherpt.corners[i];
		}
		corner1count=featherpt.cornersCount;

		featherpt1.Harris_Method(srcImg2,m_corner_count,m_quality_level1,m_min_distance1,m_block_size);
		for(int j=0;j<featherpt1.cornersCount;j++)
		{
			utility.DrawCross(showImg2,featherpt1.corners[j],cornercolor,1,4);
			corners2[j]=featherpt1.corners[j];
		}
		corner2count=featherpt1.cornersCount;

		text.Format(">>Harris�ǵ�����ɣ�ͼ��1,2�Ľǵ���Ŀ�ֱ�Ϊ%d,%d",featherpt.cornersCount,featherpt1.cornersCount);
	}
	else
	{
		text=">>���ȴ�����ͼ��";
	}
	utility.PrintText(text,crTextColor1);
	UpdateAllViews(NULL);
	CornerDetection=true;
	Match=false;
	Registration=false;
	Fusion=false;
}

//�����ؼ��ǵ��⡾�˵���
void CMatchDoc::OnSubpixel() 
{
	CString text;
	if(IMG1OPEN&&IMG2OPEN)
	{
		//����������֤ÿ��Harris�ǵ���ƶ�����Դͼ���ϣ����������Ѵ����ͼ���ϵ���
		cvCopy(srcImg1,showImg1);
		cvCopy(srcImg2,showImg2);
		CFeatherPts featherpt;
		CFeatherPts featherpt1;
		featherpt.SubPixel_Method(srcImg1,m_cornercount,m_min_distance,m_quality_level,m_winlength,m_max_iter,m_epsilon,m_guassblur,m_sigma,m_guass_winwidth,m_guass_winheigth);
		for(int i=0;i<featherpt.cornersCount;i++)
		{
			utility.DrawCross(showImg1,featherpt.corners[i],cornercolor,1,4);
			corners1[i]=featherpt.corners[i];
		}
		corner1count=featherpt.cornersCount;

		featherpt1.SubPixel_Method(srcImg2,m_cornercount,m_min_distance,m_quality_level,m_winlength,m_max_iter,m_epsilon,m_guassblur,m_sigma,m_guass_winwidth,m_guass_winheigth);
		for(int j=0;j<featherpt1.cornersCount;j++)
		{
			utility.DrawCross(showImg2,featherpt1.corners[j],cornercolor,1,4);
			corners2[j]=featherpt1.corners[j];
		}
		corner2count=featherpt1.cornersCount;

		text.Format(">>�����ؼ��ǵ�����ɣ�ͼ��1,2�Ľǵ���Ŀ�ֱ�Ϊ%d,%d",featherpt.cornersCount,featherpt1.cornersCount);
		Subpixel=true;
	}
	else
	{
		text=">>���ȴ�����ͼ��";
	}
	utility.PrintText(text,crTextColor1);
	UpdateAllViews(NULL);
	CornerDetection=true;
	Match=false;
	Registration=false;
	Fusion=false;
}

//SIFT�ǵ��⡾�˵���
void CMatchDoc::OnSift() 
{
	CString text;
	if(IMG1OPEN&&IMG2OPEN)
	{
		//����������֤ÿ��Harris�ǵ���ƶ�����Դͼ���ϣ����������Ѵ����ͼ���ϵ���
		cvCopy(srcImg1,showImg1);
		cvCopy(srcImg2,showImg2);
		CFeatherPts featherpt;
		CFeatherPts featherpt1;
		featherpt.SIFT_Method(srcImg1);
		for(int i=0;i<featherpt.cornersCount;i++)
		{
			utility.DrawCross(showImg1,featherpt.corners[i],cornercolor,1,4);
			corners1[i]=featherpt.corners[i];
		}
		corner1count=featherpt.cornersCount;

		featherpt1.SIFT_Method(srcImg2);
		for(int j=0;j<featherpt1.cornersCount;j++)
		{
			utility.DrawCross(showImg2,featherpt1.corners[j],cornercolor,1,4);
			corners2[j]=featherpt1.corners[j];
		}
		corner2count=featherpt1.cornersCount;

		text.Format(">>SIFT�ǵ�����ɣ�ͼ��1,2�Ľǵ���Ŀ�ֱ�Ϊ%d,%d",featherpt.cornersCount,featherpt1.cornersCount);
		Sift=true;
	}
	else
	{
		text=">>���ȴ�����ͼ��";
	}
	utility.PrintText(text,crTextColor1);
	UpdateAllViews(NULL);
	CornerDetection=true;
	Match=false;
	Registration=false;
	Fusion=false;
}

//����ǵ㡾�˵���
void CMatchDoc::OnImportFeapts() 
{
	if(importfeaptDlg.DoModal()==IDOK)
	{
		file1path=importfeaptDlg.m_file1path;
		file2path=importfeaptDlg.m_file2path;
		CString text;
		if(IMG1OPEN&&IMG2OPEN)
		{
			//����������֤ÿ��Harris�ǵ���ƶ�����Դͼ���ϣ����������Ѵ����ͼ���ϵ���
			cvCopy(srcImg1,showImg1);
			cvCopy(srcImg2,showImg2);
			CFeatherPts featherpt;
			CFeatherPts featherpt1;
			if(!featherpt.Import_Method(file1path))
			{
				text=">>�޷����ļ�1";
			}
			else if(!featherpt1.Import_Method(file2path))
			{
				text=">>�޷����ļ�2";
			}
			else
			{
				for(int i=0;i<featherpt.cornersCount;i++)
				{
					utility.DrawCross(showImg1,featherpt.corners[i],cornercolor,1,4);
					corners1[i]=featherpt.corners[i];
				}
				corner1count=featherpt.cornersCount;

				for(int j=0;j<featherpt1.cornersCount;j++)
				{
					utility.DrawCross(showImg2,featherpt1.corners[j],cornercolor,1,4);
					corners2[j]=featherpt1.corners[j];
				}
				corner2count=featherpt1.cornersCount;
				CornerDetection=true;
				text.Format(">>�ǵ㵼����ϣ�ͼ��1,2�Ľǵ���Ŀ�ֱ�Ϊ%d,%d",featherpt.cornersCount,featherpt1.cornersCount);
			}
		}
		else
		{
			text=">>���ȴ�����ͼ��";
			CornerDetection=false;
		}
		utility.PrintText(text,crTextColor1);
		UpdateAllViews(NULL);
		Match=false;
		Registration=false;
		Fusion=false;
	}
}

//�����ǵ㡾�˵���
void CMatchDoc::OnExportFeapts() 
{
	SYSTEMTIME st;//ϵͳʱ��
	GetLocalTime(&st);
	CString Filelast;
	Filelast.Format("%2d%2d",st.wMinute,st.wSecond);

	CFeatherPts featherpt;
//	CFeatherPts featherpt1;
	bool ex1=featherpt.Export_Method(DebugPath+"images\\"+Filelast+"������1.txt",corners1,corner1count);
	bool ex2=featherpt.Export_Method(DebugPath+"images\\"+Filelast+"������2.txt",corners2,corner2count);
	if(ex1&&ex2)
	{
		AfxMessageBox("�������ѱ�����"+DebugPath+"images�ļ�����");
	}
	else
	{
		utility.PrintText(">>�����㵼�����������ԣ�",crTextColor1);
	}
}

//�޳�����������㡾�˵���
void CMatchDoc::OnDeleteFeapts() 
{
	if(CornerDetection&&!Match)
	{
		isdeletefeas=true;
		m_rect1.SetRect(0,0,50,50); 
		m_rectTracker.m_nStyle=CRectTracker::resizeInside|CRectTracker::dottedLine;

		isdeletefeas1=true;
		m_rect2.SetRect(0,0,50,50); 
		m_rectTracker1.m_nStyle=CRectTracker::resizeInside|CRectTracker::dottedLine;
		UpdateAllViews(NULL);
	}
	else
	{
		utility.PrintText(">>��������������ȡ��",crTextColor1);
	}
	CornerDetection=true;
	Match=false;
	Registration=false;
	Fusion=false;
}

//Laplace�ǵ�ƥ�䡾�˵���
void CMatchDoc::OnLaplace() 
{
	if(CornerDetection&&!Match)
	{
		//������ͼ����
		pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pFrame->viewnum=1;
		pFrame->setView(1);
		
		m_imgsize1.width=cvGetSize(srcImg1).width*2+100;
		m_imgsize1.height=cvGetSize(srcImg1).height*2+200;
		
		matchpt=matching.Laplace_Method(showImg1,corners1,corner1count,showImg2,corners2,corner2count);
		CString text;
		text.Format(">>Laplace�ǵ�ƥ����ɣ��ǵ�ƥ����Ŀ:%d��",matchpt->rows);
		LineCount=matchpt->rows;
		utility.PrintText(text,crTextColor1);
		CornerDetection=true;
		Match=true;
		UpdateAllViews(NULL);
	}
	else if(!CornerDetection)
	{
		utility.PrintText(">>��������������ȡ��",crTextColor1);
		CornerDetection=false;
		Match=false;
	}
	else if(Match)
	{
		utility.PrintText(">>��ǰƥ�䷽������ɣ�",crTextColor1);
		Match=true;
	}
	Registration=false;
	Fusion=false;
}

//ɾ��view1����Ƥ������ڵĽǵ�
void CMatchDoc::DeletePts(CRect rect)
{
	CString text;
	//CRect rect;
	//m_rectTracker.GetTrueRect(&rect);
	for(int i=0;i<corner1count;i++)
	{
		if(corners1[i].x>rect.left&&corners1[i].x<rect.right&&corners1[i].y>rect.top&&corners1[i].y<rect.bottom)
		{
			//corners1[i].x=corners1[i].y=-1;
			corners1[i]=corners1[corner1count-1];
			corner1count--;
		}
	}
	text.Format(">>��ǰͼ��1�ǵ���ĿΪ:%d",corner1count);
	cvCopy(srcImg1,showImg1);
	for(i=0;i<corner1count;i++)
	{
		utility.DrawCross(showImg1,corners1[i],CV_RGB(0,255,0),1,4);
	}
	utility.PrintText(text,crTextColor1);
	UpdateAllViews(NULL);
}

//ɾ��view2����Ƥ������ڵĽǵ�
void CMatchDoc::DeletePts1(CRect rect)
{
	CString text;
	//CRect rect;
	//m_rectTracker.GetTrueRect(&rect);
	for(int i=0;i<corner2count;i++)
	{
		if(corners2[i].x>rect.left&&corners2[i].x<rect.right&&corners2[i].y>rect.top&&corners2[i].y<rect.bottom)
		{
			//corners1[i].x=corners1[i].y=-1;
			corners2[i]=corners2[corner2count-1];
			corner2count--;
		}
	}
	text.Format(">>��ǰͼ��2�ǵ���ĿΪ:%d",corner2count);
	cvCopy(srcImg2,showImg2);
	for(i=0;i<corner2count;i++)
	{
		utility.DrawCross(showImg2,corners2[i],CV_RGB(0,255,0),1,4);
	}
	utility.PrintText(text,crTextColor1);
	UpdateAllViews(NULL);
}

//�Զ���׼���˵���
void CMatchDoc::OnAutoRegistration() 
{
	if(Match&&!Registration)
	{
	//����ģ��
		if(m_transmode==0)
		{
			int i,j;
			int m=LineCount;
			//*********************����H����****************************	
			CvMat* A=cvCreateMat(m*2,1,CV_64FC1);
			CvMat* B=cvCreateMat(m*2,6,CV_64FC1);
			CvMat* tempH=cvCreateMat(6,1,CV_64FC1);
			CvMat* H=cvCreateMat(2,3,CV_64FC1);
			CvMat* temp=cvCreateMat(6,2*m,CV_64FC1);
			cvSetZero(B);
			for(i=0;i<m;i++)
				for(j=0;j<2;j++)
				{
					CV_MAT_ELEM(*B,double,i,j)=CV_MAT_ELEM(*matchpt,double,i,j+2);
					CV_MAT_ELEM(*B,double,i+m,j+2)=CV_MAT_ELEM(*matchpt,double,i,j+2);
				}
			for(i=0;i<m;i++)
			{
				CV_MAT_ELEM(*B,double,i,4)=1;
				CV_MAT_ELEM(*B,double,i,5)=0;
				CV_MAT_ELEM(*B,double,i+m,4)=0;
				CV_MAT_ELEM(*B,double,i+m,5)=1;
			}
			for(i=0;i<m;i++)
			{
				CV_MAT_ELEM(*A,double,i,0)=CV_MAT_ELEM(*matchpt,double,i,0);
				CV_MAT_ELEM(*A,double,i+m,0)=CV_MAT_ELEM(*matchpt,double,i,1);
			}

			cvInvert(B,temp,CV_SVD);
			cvMatMul(temp,A,tempH);

			CV_MAT_ELEM(*H,double,0,0)=CV_MAT_ELEM(*tempH,double,0,0);
			CV_MAT_ELEM(*H,double,0,1)=CV_MAT_ELEM(*tempH,double,1,0);
			CV_MAT_ELEM(*H,double,0,2)=CV_MAT_ELEM(*tempH,double,4,0)+100;
			CV_MAT_ELEM(*H,double,1,0)=CV_MAT_ELEM(*tempH,double,2,0);
			CV_MAT_ELEM(*H,double,1,1)=CV_MAT_ELEM(*tempH,double,3,0);
			CV_MAT_ELEM(*H,double,1,2)=CV_MAT_ELEM(*tempH,double,5,0)+100;

// 			posx+=100;//�ı����λ��
// 			posy+=100;
		//*************************************************************	
			cvSet(showImg1,CV_RGB(255,255,255));//����ͼ�񱳾�
  			cvSetImageROI(showImg1,cvRect(0,0,srcImg1->width,srcImg1->height));
 			cvCopy(srcImg1,showImg1,NULL);
			cvSetImageROI(showImg1,cvRect(srcImg1->width+50,0,srcImg2->width,srcImg2->height));
			cvCopy(srcImg2,showImg1,NULL);

			cvSetImageROI(showImg1,cvRect(0,srcImg1->height+50,srcImg1->width+srcImg2->width+50,srcImg1->height+200));
			if(m_fillval==0)
				cvWarpAffine(srcImg2,showImg1,H,CV_WARP_FILL_OUTLIERS|CV_INTER_NN);
			else if(m_fillval==1)
				cvWarpAffine(srcImg2,showImg1,H,CV_WARP_FILL_OUTLIERS|CV_INTER_LINEAR);
			else if(m_fillval==2)
				cvWarpAffine(srcImg2,showImg1,H,CV_WARP_FILL_OUTLIERS|CV_INTER_CUBIC);
			else if(m_fillval==3)
				cvWarpAffine(srcImg2,showImg1,H,CV_WARP_FILL_OUTLIERS|CV_INTER_AREA);
			regimg=cvCreateImage(cvGetSize(showImg1),IPL_DEPTH_8U,3);
			cvCopy(showImg1,regimg,NULL);
			cvResetImageROI(showImg1);

//			posy+=srcImg1->height+50;//�ı����λ��
			CString text;
			text.Format(">>ͼ����׼��ɣ�H����[%f %f %f;%f %f %f;0.0 0.0 1.0]",CV_MAT_ELEM(*tempH,double,0,0),CV_MAT_ELEM(*tempH,double,1,0),CV_MAT_ELEM(*tempH,double,4,0),CV_MAT_ELEM(*tempH,double,2,0),CV_MAT_ELEM(*tempH,double,3,0),CV_MAT_ELEM(*tempH,double,5,0));
			utility.PrintText(text,crTextColor1);
 			cvReleaseMat(&A);
 			cvReleaseMat(&B);
 			cvReleaseMat(&H);
 			cvReleaseMat(&temp);
			cvReleaseMat(&tempH);
			Registration=true;
			UpdateAllViews(NULL);
		}
		else if(m_transmode==1)//��Ӱģ��
		{
			int i,j;
			int m=LineCount;
			//*********************����H����****************************	
			CvMat* A=cvCreateMat(m*3,1,CV_64FC1);
			CvMat* B=cvCreateMat(m*3,9,CV_64FC1);
			CvMat* tempH=cvCreateMat(9,1,CV_64FC1);
			CvMat* H=cvCreateMat(3,3,CV_64FC1);
			CvMat* temp=cvCreateMat(9,3*m,CV_64FC1);
			cvSetZero(B);
			for(i=0;i<m;i++)
				for(j=0;j<2;j++)
				{
					CV_MAT_ELEM(*B,double,i,j)=CV_MAT_ELEM(*matchpt,double,i,j+2);
					CV_MAT_ELEM(*B,double,i+m,j+2)=CV_MAT_ELEM(*matchpt,double,i,j+2);
					CV_MAT_ELEM(*B,double,i+m*2,j+4)=CV_MAT_ELEM(*matchpt,double,i,j+2);
				}
			for(i=0;i<m;i++)
			{
				CV_MAT_ELEM(*B,double,i,6)=1;
				CV_MAT_ELEM(*B,double,i+m,7)=1;
				CV_MAT_ELEM(*B,double,i+m*2,8)=1;
			}
			for(i=0;i<m;i++)
			{
				CV_MAT_ELEM(*A,double,i,0)=CV_MAT_ELEM(*matchpt,double,i,0);
				CV_MAT_ELEM(*A,double,i+m,0)=CV_MAT_ELEM(*matchpt,double,i,1);
				CV_MAT_ELEM(*A,double,i+m*2,0)=1;
			}

			cvInvert(B,temp,CV_SVD);
			cvMatMul(temp,A,tempH);

			CV_MAT_ELEM(*H,double,0,0)=CV_MAT_ELEM(*tempH,double,0,0);
			CV_MAT_ELEM(*H,double,0,1)=CV_MAT_ELEM(*tempH,double,1,0);
			CV_MAT_ELEM(*H,double,0,2)=CV_MAT_ELEM(*tempH,double,6,0)+100;
			CV_MAT_ELEM(*H,double,1,0)=CV_MAT_ELEM(*tempH,double,2,0);
			CV_MAT_ELEM(*H,double,1,1)=CV_MAT_ELEM(*tempH,double,3,0);
			CV_MAT_ELEM(*H,double,1,2)=CV_MAT_ELEM(*tempH,double,7,0)+100;
			CV_MAT_ELEM(*H,double,2,0)=CV_MAT_ELEM(*tempH,double,4,0);
			CV_MAT_ELEM(*H,double,2,1)=CV_MAT_ELEM(*tempH,double,5,0);
			CV_MAT_ELEM(*H,double,2,2)=1;

// 			posx+=100;//�ı����λ��
// 			posy+=100;
		//*************************************************************	
			cvSet(showImg1,CV_RGB(255,255,255));//����ͼ�񱳾�
  			cvSetImageROI(showImg1,cvRect(0,0,srcImg1->width,srcImg1->height));
 			cvCopy(srcImg1,showImg1,NULL);
			cvSetImageROI(showImg1,cvRect(srcImg1->width+50,0,srcImg2->width,srcImg2->height));
			cvCopy(srcImg2,showImg1,NULL);

			cvSetImageROI(showImg1,cvRect(0,srcImg1->height+50,srcImg1->width+srcImg2->width+50,srcImg1->height+200));
			if(m_fillval==0)
				cvWarpPerspective(srcImg2,showImg1,H,CV_WARP_FILL_OUTLIERS|CV_INTER_NN);
			else if(m_fillval==1)
				cvWarpPerspective(srcImg2,showImg1,H,CV_WARP_FILL_OUTLIERS|CV_INTER_LINEAR);
			else if(m_fillval==2)
				cvWarpPerspective(srcImg2,showImg1,H,CV_WARP_FILL_OUTLIERS|CV_INTER_CUBIC);
			else if(m_fillval==3)
				cvWarpPerspective(srcImg2,showImg1,H,CV_WARP_FILL_OUTLIERS|CV_INTER_AREA);
			regimg=cvCreateImage(cvGetSize(showImg1),IPL_DEPTH_8U,3);
			cvCopy(showImg1,regimg,NULL);
			cvResetImageROI(showImg1);

			CString text;
			text.Format(">>ͼ����׼��ɣ�H����[%f %f %f;%f %f %f;%f %f 1.0]",CV_MAT_ELEM(*tempH,double,0,0),CV_MAT_ELEM(*tempH,double,1,0),CV_MAT_ELEM(*tempH,double,4,0),CV_MAT_ELEM(*tempH,double,2,0),CV_MAT_ELEM(*tempH,double,3,0),CV_MAT_ELEM(*tempH,double,5,0),CV_MAT_ELEM(*tempH,double,6,0),CV_MAT_ELEM(*tempH,double,7,0));
			utility.PrintText(text,crTextColor1);
 			cvReleaseMat(&A);
 			cvReleaseMat(&B);
 			cvReleaseMat(&H);
 			cvReleaseMat(&temp);
			cvReleaseMat(&tempH);
			UpdateAllViews(NULL);
			Registration=true;
		}
	}
	else if(!Match)
	{
		utility.PrintText(">>������������ƥ�䣡",crTextColor1);
		Registration=false;
	}
	else if(Registration)
	{
		utility.PrintText(">>��ǰͼ����׼����ɣ�",crTextColor1);
		Registration=false;
	}
}

//ͼ���ںϡ��˵���
void CMatchDoc::OnFusion() 
{
	isdeleteline=false;
	if(Registration&&!Fusion)
	{
		CvSize fusionsize;
		fusionsize.width=cvGetSize(srcImg1).width*2;
		fusionsize.height=cvGetSize(srcImg1).height*2;
		IplImage* fusionimg=cvCreateImage(fusionsize,IPL_DEPTH_8U,3);
		IplImage* tempimg=cvCreateImage(fusionsize,IPL_DEPTH_8U,3);
		showImg1=cvCreateImage(fusionsize,IPL_DEPTH_8U,3);
		//����m_imgsize1�Ĵ�С��view��Ҫ��
		m_imgsize1.width=fusionsize.width;
		m_imgsize1.height=fusionsize.height;
		
		cvSetImageROI(fusionimg,cvRect(100,100,srcImg1->width,srcImg1->height));
		cvCopy(srcImg1,fusionimg);
		cvResetImageROI(fusionimg);
		CvMat* tempH=cvCreateMat(2,3,CV_64FC1);
		CV_MAT_ELEM(*tempH,double,0,0)=1;
		CV_MAT_ELEM(*tempH,double,0,1)=0;
		//CV_MAT_ELEM(*tempH,double,0,2)=-posx;
		CV_MAT_ELEM(*tempH,double,0,2)=0;
		CV_MAT_ELEM(*tempH,double,1,0)=0;
		CV_MAT_ELEM(*tempH,double,1,1)=1;
		//CV_MAT_ELEM(*tempH,double,1,2)=0;
		CV_MAT_ELEM(*tempH,double,1,2)=0;
		cvWarpAffine(regimg,tempimg,tempH,CV_WARP_FILL_OUTLIERS);
		cvResetImageROI(fusionimg);
		//	cvAdd(fusionimg,tempimg,showImg1,NULL);
		cvAddWeighted(fusionimg,0.5,tempimg,0.5,0,showImg1);
		utility.PrintText(">>ͼ���ں���ɣ�",crTextColor1);
		UpdateAllViews(NULL);
		cvReleaseImage(&fusionimg);
		Fusion=true;
	}
	else if(!Registration)
	{
		utility.PrintText(">>������ͼ����׼��",crTextColor1);
		Fusion=false;
	}
	else if(Fusion)
	{
		utility.PrintText(">>��ǰͼ���ں�����ɣ�",crTextColor1);
		Fusion=true;
	}
	Registration=true;
}

//�ֶ��޳�ƥ���ߡ��˵���
void CMatchDoc::OnManualRegistration() 
{
	if(Match&&!Registration)
	{
		isdeleteline=true;
		m_rect3.SetRect(5,5,20,20); 
		m_rectTracker2.m_nStyle=CRectTracker::resizeInside|CRectTracker::dottedLine;
	}
	else
	{
		utility.PrintText(">>��ǰ���ܽ����޳�ƥ���ߵĲ�����",crTextColor1);
		UpdateAllViews(NULL);
	}
}

//ɾ��ƥ���ߡ��˵���
void CMatchDoc::DeleteLines(CvMat* mat,CRect rect)
{
	CvSize orisize=cvGetSize(srcImg1);
	for(int i=0;i<LineCount;i++)
	{
		double pt1x=CV_MAT_ELEM(*mat,double,i,0);
		double pt1y=CV_MAT_ELEM(*mat,double,i,1);
		double pt2x=CV_MAT_ELEM(*mat,double,i,2)+orisize.width+50;
		double pt2y=CV_MAT_ELEM(*mat,double,i,3)+50;
		if(pt1x>rect.left&&pt1x<rect.right&&pt1y>rect.top&&pt1y<rect.bottom)
		{
			double ptsx=CV_MAT_ELEM(*mat,double,i,0);
			CV_MAT_ELEM(*mat,double,i,0)=CV_MAT_ELEM(*mat,double,LineCount-1,0);
			double ptsy=CV_MAT_ELEM(*mat,double,i,1);
			CV_MAT_ELEM(*mat,double,i,1)=CV_MAT_ELEM(*mat,double,LineCount-1,1);
			double ptex=CV_MAT_ELEM(*mat,double,i,2)+orisize.width+50;
			CV_MAT_ELEM(*mat,double,i,2)=CV_MAT_ELEM(*mat,double,LineCount-1,2);
			double ptey=CV_MAT_ELEM(*mat,double,i,3)+50;
			CV_MAT_ELEM(*mat,double,i,3)=CV_MAT_ELEM(*mat,double,LineCount-1,3);
			LineCount--;
			cvLine(showImg1,cvPoint(cvRound(ptsx),cvRound(ptsy)),cvPoint(cvRound(ptex),cvRound(ptey)),CV_RGB(0,255,0),1,0);
		}
		else if(pt2x>rect.left&&pt2x<rect.right&&pt2y>rect.top&&pt2y<rect.bottom)
		{
			double ptsx=CV_MAT_ELEM(*mat,double,i,0);
			CV_MAT_ELEM(*mat,double,i,0)=CV_MAT_ELEM(*mat,double,LineCount-1,0);
			double ptsy=CV_MAT_ELEM(*mat,double,i,1);
			CV_MAT_ELEM(*mat,double,i,1)=CV_MAT_ELEM(*mat,double,LineCount-1,1);
			double ptex=CV_MAT_ELEM(*mat,double,i,2)+orisize.width+50;
			CV_MAT_ELEM(*mat,double,i,2)=CV_MAT_ELEM(*mat,double,LineCount-1,2);
			double ptey=CV_MAT_ELEM(*mat,double,i,3)+50;
			CV_MAT_ELEM(*mat,double,i,3)=CV_MAT_ELEM(*mat,double,LineCount-1,3);
			LineCount--;
			cvLine(showImg1,cvPoint(cvRound(ptsx),cvRound(ptsy)),cvPoint(cvRound(ptex),cvRound(ptey)),CV_RGB(0,255,0),1,0);
		}
	}
 	CString text;
 	text.Format(">>��ǰƥ������ĿΪ:%d",LineCount);
	utility.PrintText(text,crTextColor1);
 	UpdateAllViews(NULL);
	Match=true;
	Registration=false;
	Fusion=false;	
}
/*
//��ʼƥ�䡾�˵���
void CMatchDoc::OnScott() 
{
	// TODO: Add your command handler code here
	if(CornerDetection&&!Match)
	{
		//������ͼ����
		pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pFrame->viewnum=1;
		pFrame->setView(1);
		
		m_imgsize1.width=cvGetSize(srcImg1).width*2+100;
		m_imgsize1.height=cvGetSize(srcImg1).height*2+200;

		int mat12[MAXFEATURES],mat21[MAXFEATURES];
		CvPoint2D32f matches1[MAXFEATURES];
		CvPoint2D32f matches2[MAXFEATURES];
		int nmatches=0;		
		matchpt=matching.Init_Method(showImg1,showImg2,grayImg1,grayImg2,patch_radius,max_disparity,corners1,corners2,corner1count,matches1,matches2,&nmatches,mat12,mat21);
		CString text;
		text.Format(">>��ʼ�ǵ�ƥ����ɣ��ǵ�ƥ����Ŀ:%d��",matchpt->rows);
		LineCount=matchpt->rows;
		utility.PrintText(text,crTextColor1);
		Match=true;
		UpdateAllViews(NULL);
	}
	else if(!CornerDetection)
	{
		utility.PrintText(">>��������������ȡ��",crTextColor1);
		Match=false;
	}
	else if(Match)
	{
		utility.PrintText(">>��ǰƥ�䷽������ɣ�",crTextColor1);
		Match=true;
	}
	Registration=false;
	Fusion=false;
}
*/
//Լ��ƥ�䡾�˵���
void CMatchDoc::OnMenuitem32832() 
{
	if(CornerDetection&&Subpixel&&!Match)
	{
		pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pFrame->viewnum=1;
		pFrame->setView(1);
		
		m_imgsize1.width=cvGetSize(srcImg1).width*2+100;
		m_imgsize1.height=cvGetSize(srcImg1).height*2+200;
		
		int mat12[MAXFEATURES],mat21[MAXFEATURES];
		CvPoint2D32f matches1[MAXFEATURES];
		CvPoint2D32f matches2[MAXFEATURES];
		int nmatches=0;
		
		matchpt=matching.quCornermatcher(showImg1,showImg2,grayImg1,grayImg2,patch_radius,max_disparity,max_distance,fmethod,corners1,corners2,corner1count,matches1,matches2,&nmatches,mat12,mat21);
		
		CString text;
		text.Format(">>�ǵ�ƥ����ɣ��ǵ�ƥ����Ŀ:%d��",nmatches);
		LineCount=nmatches;
		utility.PrintText(text,crTextColor1);
		Match=true;
		UpdateAllViews(NULL);
	}
	else if(!CornerDetection)
	{
		utility.PrintText(">>��������������ȡ��",crTextColor1);
		Match=false;
	}
	else if(Match)
	{
		utility.PrintText(">>��ǰƥ�䷽������ɣ�",crTextColor1);
		Match=true;
	}
	else if(!Subpixel)
	{
		utility.PrintText(">>���Ƚ��������ؼ���������ȡ��",crTextColor1);
		Match=false;
	}
	Registration=false;
	Fusion=false;
}

//SIFTƥ�䡾�˵���
void CMatchDoc::OnSiftmatch() 
{
	if(CornerDetection&&Sift&&!Match)
	{
		pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pFrame->viewnum=1;
		pFrame->setView(1);
		
		m_imgsize1.width=cvGetSize(srcImg1).width*2+100;
		m_imgsize1.height=cvGetSize(srcImg1).height*2+200;
		
		int nmatches=0;
		matchpt=matching.SIFT_Method(showImg1,showImg2,srcImg1,srcImg2,&nmatches);
		CString text;
		text.Format(">>SIFT�ǵ�ƥ����ɣ��ǵ�ƥ����Ŀ:%d��",nmatches);
		LineCount=nmatches;
		utility.PrintText(text,crTextColor1);
		Match=true;
		UpdateAllViews(NULL);
	}
	else if(!CornerDetection)
	{
		utility.PrintText(">>��������������ȡ��",crTextColor1);
		Match=false;
	}
	else if(Match)
	{
		utility.PrintText(">>��ǰƥ�䷽������ɣ�",crTextColor1);
		Match=true;
	}
	else if(!Sift)
	{
		utility.PrintText(">>���Ƚ���SIFT��������ȡ��",crTextColor1);
		Match=false;
	}
	Registration=false;
	Fusion=false;
	
}

void CMatchDoc::OnHelp() 
{
	ShellExecute(NULL,"open",DebugPath+"\\ͼ����׼ϵͳ����.CHM","","", SW_SHOW );
}
