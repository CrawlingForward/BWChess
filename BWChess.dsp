# Microsoft Developer Studio Project File - Name="BWChess" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BWChess - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BWChess.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BWChess.mak" CFG="BWChess - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BWChess - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BWChess - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BWChess - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "BWChess - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BWChess - Win32 Release"
# Name "BWChess - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddSec.cpp
# End Source File
# Begin Source File

SOURCE=.\BestDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\BWChess.cpp
# End Source File
# Begin Source File

SOURCE=.\BWChess.rc
# End Source File
# Begin Source File

SOURCE=.\BWChessDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfirmSec.cpp
# End Source File
# Begin Source File

SOURCE=.\Creditstatic.cpp
# End Source File
# Begin Source File

SOURCE=.\Demo.cpp
# End Source File
# Begin Source File

SOURCE=.\Dib.cpp
# End Source File
# Begin Source File

SOURCE=.\DigitalPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\HelperAPI.cpp
# End Source File
# Begin Source File

SOURCE=.\HowToDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\Message1.cpp
# End Source File
# Begin Source File

SOURCE=.\Message2.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\stack.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Undo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddSec.h
# End Source File
# Begin Source File

SOURCE=.\BestDlg.h
# End Source File
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\BWChess.h
# End Source File
# Begin Source File

SOURCE=.\BWChessDlg.h
# End Source File
# Begin Source File

SOURCE=.\ConfirmSec.h
# End Source File
# Begin Source File

SOURCE=.\Creditstatic.h
# End Source File
# Begin Source File

SOURCE=.\Demo.h
# End Source File
# Begin Source File

SOURCE=.\Dib.h
# End Source File
# Begin Source File

SOURCE=.\DigitalPlayer.h
# End Source File
# Begin Source File

SOURCE=.\GlobalVar.h
# End Source File
# Begin Source File

SOURCE=.\GlobalVar0.h
# End Source File
# Begin Source File

SOURCE=.\HelperAPI.h
# End Source File
# Begin Source File

SOURCE=.\HowToDlg.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\Message1.h
# End Source File
# Begin Source File

SOURCE=.\Message2.h
# End Source File
# Begin Source File

SOURCE=.\RecordDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetUpDlg.h
# End Source File
# Begin Source File

SOURCE=.\stack.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Undo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\1.ico
# End Source File
# Begin Source File

SOURCE=.\res\32X32X16_QUESTION.ICO
# End Source File
# Begin Source File

SOURCE=.\res\32X32X256_LAMP.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Black.bmp
# End Source File
# Begin Source File

SOURCE=..\Res\Black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Book03.ico
# End Source File
# Begin Source File

SOURCE=..\Res\Book03.ico
# End Source File
# Begin Source File

SOURCE=.\res\bw.ico
# End Source File
# Begin Source File

SOURCE=.\res\BWChess.rc2
# End Source File
# Begin Source File

SOURCE=.\res\CanPlace1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CanPlace2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Crdfle13.ico
# End Source File
# Begin Source File

SOURCE=..\Res\Crdfle13.ico
# End Source File
# Begin Source File

SOURCE=.\res\CurBlack.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CurWhite.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Destop.ico
# End Source File
# Begin Source File

SOURCE=..\Res\Destop.ico
# End Source File
# Begin Source File

SOURCE=.\res\Empty.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Frame1-10.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame1-2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame1-3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame1-4.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame1-5.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame1-6.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame1-7.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame1-8.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame1-9.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame10-1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame10-10.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame10-2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame10-3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame10-4.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame10-5.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame10-6.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame10-7.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame10-8.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame10-9.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\Frame11.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Frame2-1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame2-10.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame3-1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame3-10.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame4-1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame4-10.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame5-1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame5-10.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame6-1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame6-10.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame7-1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame7-10.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame8-1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame8-10.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame9-1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Frame9-10.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# Begin Source File

SOURCE=..\Res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\Handblack.cur
# End Source File
# Begin Source File

SOURCE=..\Res\Handblack.cur
# End Source File
# Begin Source File

SOURCE=.\res\Handwhite.cur
# End Source File
# Begin Source File

SOURCE=..\Res\Handwhite.cur
# End Source File
# Begin Source File

SOURCE=".\res\Help File HLP.ico"
# End Source File
# Begin Source File

SOURCE="..\Res\Help File HLP.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Help GID.ico"
# End Source File
# Begin Source File

SOURCE="..\Res\Help GID.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Jester.ico
# End Source File
# Begin Source File

SOURCE=.\res\Key06.ico
# End Source File
# Begin Source File

SOURCE=.\res\ok.ico
# End Source File
# Begin Source File

SOURCE=..\Res\ok.ico
# End Source File
# Begin Source File

SOURCE=.\res\OPENFOLD.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Point6.ico
# End Source File
# Begin Source File

SOURCE=..\Res\Point6.ico
# End Source File
# Begin Source File

SOURCE=.\res\Secure3.ico
# End Source File
# Begin Source File

SOURCE=.\res\Secure4.ico
# End Source File
# Begin Source File

SOURCE=.\res\Support.ico
# End Source File
# Begin Source File

SOURCE=..\Res\Support.ico
# End Source File
# Begin Source File

SOURCE=.\res\User.ico
# End Source File
# Begin Source File

SOURCE=.\res\white.BMP
# End Source File
# Begin Source File

SOURCE=..\Res\white.BMP
# End Source File
# Begin Source File

SOURCE=.\res\WinPopup.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\error.wav
# End Source File
# Begin Source File

SOURCE=..\Res\error.wav
# End Source File
# Begin Source File

SOURCE=.\res\Lose1.wav
# End Source File
# Begin Source File

SOURCE=..\Res\Lose1.wav
# End Source File
# Begin Source File

SOURCE=.\res\putstone.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\undo.wav
# End Source File
# Begin Source File

SOURCE=..\Res\undo.wav
# End Source File
# Begin Source File

SOURCE=.\res\Win1.wav
# End Source File
# Begin Source File

SOURCE=..\Res\Win1.wav
# End Source File
# End Target
# End Project
