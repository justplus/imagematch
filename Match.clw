; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Match.h"
LastPage=0

ClassCount=14
Class1=CMatchApp
Class2=CMatchDoc
Class3=CMatchView
Class4=CMainFrame

ResourceCount=10
Resource1=IDD_Harris
Class5=CAboutDlg
Class6=CMatchView1
Resource2=IDD_OPEN_IMAGE
Class7=COpenImageDlg
Resource3=IDD_SUBPIXEL
Class8=CPerference
Resource4=IDD_IMPORT_FEAPTS
Resource5=IDD_SIFT
Resource6=IDD_PERFERENCE
Class9=CHarrisDlg
Class10=CSubPixel
Class11=CRegistrationDlg
Resource7=IDR_MAINFRAME
Class12=CSiftDlg
Resource8=IDD_REGISTRATION
Class13=CImportFeapt
Resource9=IDD_ABOUTBOX
Class14=CSTMatch
Resource10=IDD_STMATCH

[CLS:CMatchApp]
Type=0
HeaderFile=Match.h
ImplementationFile=Match.cpp
Filter=N

[CLS:CMatchDoc]
Type=0
HeaderFile=MatchDoc.h
ImplementationFile=MatchDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CMatchView]
Type=0
HeaderFile=MatchView.h
ImplementationFile=MatchView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_ENLARGE




[CLS:CAboutDlg]
Type=0
HeaderFile=Match.cpp
ImplementationFile=Match.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_IMAGE_OPEN
Command2=ID_IMAGE_SAVE
Command3=ID_IMAGE_SAVE_AS
Command4=ID_APP_EXIT
Command5=ID_HARRIS
Command6=ID_SIFT
Command7=ID_SUBPIXEL
Command8=ID_IMPORT_FEAPTS
Command9=ID_EXPORT_FEAPTS
Command10=ID_DELETE_FEAPTS
Command11=ID_LAPLACE
Command12=ID_MENUITEM32832
Command13=ID_SIFTMATCH
Command14=ID_MANUAL_REGISTRATION
Command15=ID_AUTO_REGISTRATION
Command16=ID_FUSION
Command17=ID_SOFTWARE_SETTING
Command18=ID_PERFERENCE
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_VIEW_INFO_BAR
Command22=ID_ENLARGE
Command23=ID_REDUCE
Command24=ID_VIEW_IMAGE
Command25=ID_HELP
Command26=ID_APP_ABOUT
CommandCount=26

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_IMAGE_OPEN
Command2=ID_IMAGE_SAVE
Command3=ID_HARRIS
Command4=ID_IMPORT_FEAPTS
Command5=ID_DELETE_FEAPTS
Command6=ID_LAPLACE
Command7=ID_MANUAL_REGISTRATION
Command8=ID_AUTO_REGISTRATION
Command9=ID_FUSION
Command10=ID_SOFTWARE_SETTING
Command11=ID_PERFERENCE
Command12=ID_ENLARGE
Command13=ID_REDUCE
Command14=ID_VIEW_IMAGE
Command15=ID_APP_ABOUT
CommandCount=15

[CLS:CMatchView1]
Type=0
HeaderFile=MatchView1.h
ImplementationFile=MatchView1.cpp
BaseClass=CScrollView
Filter=C
LastObject=CMatchView1
VirtualFilter=VWC

[DLG:IDD_OPEN_IMAGE]
Type=1
Class=COpenImageDlg
ControlCount=8
Control1=IDC_IMAGE1,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_BUTTON2,button,1342242816
Control7=IDC_BUTTON3,button,1342242816
Control8=IDC_BUTTON4,button,1342242816

[CLS:COpenImageDlg]
Type=0
HeaderFile=OpenImageDlg.h
ImplementationFile=OpenImageDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON2
VirtualFilter=dWC

[DLG:IDD_PERFERENCE]
Type=1
Class=CPerference
ControlCount=19
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_EDIT1,edit,1350631552
Control9=IDC_BUTTON1,button,1342242816
Control10=IDC_BUTTON2,button,1342242816
Control11=IDC_BUTTON3,button,1342242816
Control12=IDC_COMBO1,combobox,1344339970
Control13=IDC_COMBO2,combobox,1344339970
Control14=IDC_COMBO3,combobox,1344339970
Control15=IDC_COMBO4,combobox,1344339970
Control16=IDC_CC1,static,1342308352
Control17=IDC_BUTTON4,button,1342242816
Control18=IDC_CC2,static,1342308352
Control19=IDC_BUTTON5,button,1342242816

[CLS:CPerference]
Type=0
HeaderFile=Perference.h
ImplementationFile=Perference.cpp
BaseClass=CDialog
Filter=D
LastObject=CPerference
VirtualFilter=dWC

[DLG:IDD_Harris]
Type=1
Class=CHarrisDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT4,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_SUBPIXEL]
Type=1
Class=CSubPixel
ControlCount=22
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,button,1342177287
Control10=IDC_CHECK1,button,1342242819
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT1,edit,1350631552
Control15=IDC_EDIT2,edit,1350631552
Control16=IDC_EDIT3,edit,1350631552
Control17=IDC_EDIT4,edit,1350631552
Control18=IDC_EDIT5,edit,1350631552
Control19=IDC_EDIT6,edit,1350631552
Control20=IDC_EDIT7,edit,1350631552
Control21=IDC_EDIT8,edit,1350631552
Control22=IDC_EDIT9,edit,1350631552

[DLG:IDD_REGISTRATION]
Type=1
Class=CRegistrationDlg
ControlCount=8
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO1,button,1342308361
Control3=IDC_RADIO3,button,1342177289
Control4=IDC_STATIC,button,1342177287
Control5=IDC_RADIO4,button,1342308361
Control6=IDC_RADIO5,button,1342177289
Control7=IDC_RADIO6,button,1342177289
Control8=IDC_RADIO7,button,1342177289

[CLS:CHarrisDlg]
Type=0
HeaderFile=HarrisDlg.h
ImplementationFile=HarrisDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CHarrisDlg

[CLS:CSubPixel]
Type=0
HeaderFile=SubPixel.h
ImplementationFile=SubPixel.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECK1

[CLS:CRegistrationDlg]
Type=0
HeaderFile=RegistrationDlg.h
ImplementationFile=RegistrationDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_RADIO1

[DLG:IDD_SIFT]
Type=1
Class=CSiftDlg
ControlCount=16
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT1,edit,1350633600
Control9=IDC_EDIT2,edit,1350633600
Control10=IDC_EDIT3,edit,1350633600
Control11=IDC_EDIT4,edit,1350633600
Control12=IDC_EDIT5,edit,1350633600
Control13=IDC_EDIT6,edit,1350633600
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT7,edit,1350633600
Control16=IDC_STATIC,static,1342308352

[CLS:CSiftDlg]
Type=0
HeaderFile=SiftDlg.h
ImplementationFile=SiftDlg.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=idWC

[DLG:IDD_IMPORT_FEAPTS]
Type=1
Class=CImportFeapt
ControlCount=8
Control1=IDC_IMAGE1,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_BUTTON2,button,1342242816
Control7=IDC_BUTTON3,button,1342242816
Control8=IDC_BUTTON4,button,1342242816

[CLS:CImportFeapt]
Type=0
HeaderFile=ImportFeapt.h
ImplementationFile=ImportFeapt.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_STMATCH]
Type=1
Class=CSTMatch
ControlCount=15
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_EDIT3,edit,1350631552
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_RADIO1,button,1342308361
Control9=IDC_RADIO2,button,1342177289
Control10=IDC_RADIO3,button,1342177289
Control11=IDC_RADIO4,button,1342177289
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT2,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT4,edit,1350633600

[CLS:CSTMatch]
Type=0
HeaderFile=STMatch.h
ImplementationFile=STMatch.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=idWC

