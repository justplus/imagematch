# Microsoft Developer Studio Project File - Name="Match" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Match - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Match.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Match.mak" CFG="Match - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Match - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Match - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Match - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ml.lib cv.lib highgui.lib cxcore.lib cvcam.lib ipl.lib libgsl.a /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Match - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ml.lib cv.lib highgui.lib cxcore.lib cvcam.lib ipl.lib libgsl.a /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Match - Win32 Release"
# Name "Match - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\FeatherPts.cpp
# End Source File
# Begin Source File

SOURCE=.\folder_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\HarrisDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\imgfeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportFeapt.cpp
# End Source File
# Begin Source File

SOURCE=.\kdtree.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Match.cpp
# End Source File
# Begin Source File

SOURCE=.\Match.rc
# End Source File
# Begin Source File

SOURCE=.\MatchDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Matching.cpp
# End Source File
# Begin Source File

SOURCE=.\MatchView.cpp
# End Source File
# Begin Source File

SOURCE=.\MatchView1.cpp
# End Source File
# Begin Source File

SOURCE=.\minpq.cpp
# End Source File
# Begin Source File

SOURCE=.\Mybar.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenImageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Perference.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistrationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\sift.cpp
# End Source File
# Begin Source File

SOURCE=.\SiftDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\STMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\SubPixel.cpp
# End Source File
# Begin Source File

SOURCE=.\Utility.cpp
# End Source File
# Begin Source File

SOURCE=.\utils.cpp
# End Source File
# Begin Source File

SOURCE=.\xform.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\FeatherPts.h
# End Source File
# Begin Source File

SOURCE=.\folder_dialog.h
# End Source File
# Begin Source File

SOURCE=.\HarrisDlg.h
# End Source File
# Begin Source File

SOURCE=.\imgfeatures.h
# End Source File
# Begin Source File

SOURCE=.\ImportFeapt.h
# End Source File
# Begin Source File

SOURCE=.\kdtree.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Match.h
# End Source File
# Begin Source File

SOURCE=.\MatchDoc.h
# End Source File
# Begin Source File

SOURCE=.\Matching.h
# End Source File
# Begin Source File

SOURCE=.\MatchView.h
# End Source File
# Begin Source File

SOURCE=.\MatchView1.h
# End Source File
# Begin Source File

SOURCE=.\minpq.h
# End Source File
# Begin Source File

SOURCE=.\Mybar.h
# End Source File
# Begin Source File

SOURCE=.\OpenImageDlg.h
# End Source File
# Begin Source File

SOURCE=.\Perference.h
# End Source File
# Begin Source File

SOURCE=.\RegistrationDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\scbarg.h
# End Source File
# Begin Source File

SOURCE=.\Sift.h
# End Source File
# Begin Source File

SOURCE=.\SiftDlg.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\STMatch.h
# End Source File
# Begin Source File

SOURCE=.\SubPixel.h
# End Source File
# Begin Source File

SOURCE=.\Utility.h
# End Source File
# Begin Source File

SOURCE=.\utils.h
# End Source File
# Begin Source File

SOURCE=.\xform.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\app_abou.bmp
# End Source File
# Begin Source File

SOURCE=.\res\auto_reg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor2.cur
# End Source File
# Begin Source File

SOURCE=.\res\delete_f.bmp
# End Source File
# Begin Source File

SOURCE=.\res\enlarg_d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\enlarge.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fusion.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hariss.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\import_f.bmp
# End Source File
# Begin Source File

SOURCE=.\res\laplace.bmp
# End Source File
# Begin Source File

SOURCE=.\res\manual_r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Match.ico
# End Source File
# Begin Source File

SOURCE=.\res\Match.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MatchDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\perferen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reduce.bmp
# End Source File
# Begin Source File

SOURCE=.\res\software.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\view_ima.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
