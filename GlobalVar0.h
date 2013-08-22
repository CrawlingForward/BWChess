#include <afxmt.h>

#ifndef _INC_GLOBALVAR0
#define _INC_GLOBALVAR0

/////////////////////////////////////////////////////////////////
// Global Vars
//              
CMutex m_Mutex;
CMutex Mutex1;
int g_nCbSkill=3;
int g_nCwSkill=3;
int g_nCSpeed=2;//should be 1,2,3
int 	g_nRunMode;	// 0 - With computer
					// 1 - Same computer

int  g_nSkill = 1;
int  g_nStoneNum = 0;
int g_nBestMark=0;
BOOL g_bSoundOn   = TRUE;
BOOL g_bUserBlack = TRUE;
BOOL g_bTopMost =TRUE;
BOOL g_bPeepOften= FALSE;
BOOL g_bShowDynamic=TRUE;
int g_nCanHintTimeB=3;
int g_nCanHintTimeW=3;
int g_nIsDemo=0;
int g_nMutex=0;
int g_nMoveSpeeds;//should be 1,2,3
//int g_nNetPlayMode;//should be 0,1: 0 for server,1 for client
BOOL g_bIsFromFile=TRUE;
//CString g_strName;
//int g_nPortNum=1228;
BOOL g_bMovePlace =TRUE;
BOOL g_bPrompt=TRUE;
int  g_nTime1 = 0;
int  g_nTime2 = 0;
int  g_nTime3 = 0;
int g_nMark1=0;
int g_nMark2=0;
int g_nMark3=0;
int g_nTimeLimit=0;//from 60 to 9000,µ•Œª√Î
int g_nIsNoTimeLimit=0;
CString g_strName1 = "Anonymous";
CString g_strName2 = "Anonymous";
CString g_strName3 = "Anonymous";

CString g_strSec1 = "";
CString g_strSec2 = "";
CString g_strSec3 = "";
//-----------
int g_nStrollSpeed=2;

#endif //!_INC_GLOBALVAR0
