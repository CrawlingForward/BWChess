#include <afxmt.h>

#ifndef _INC_GLOBALVAR
#define _INC_GLOBALVAR

/////////////////////////////////////////////////////////////////
// Global Vars
//        
extern CMutex m_Mutex;  
extern CMutex Mutex1;    
extern int g_nCbSkill;
extern int g_nCwSkill;
extern int g_nCSpeed;//should be 1,2,3
		   
extern int 	g_nRunMode;	// 0 - With computer
						// 1 - Same computer
extern int  g_nSkill;
extern int  g_nStoneNum;
extern int g_nBestMark;
extern BOOL g_bSoundOn;
extern BOOL g_bUserBlack;
extern BOOL g_bTopMost;
extern BOOL g_bShowDynamic;
extern BOOL g_bPrompt;
extern int g_nIsDemo;
extern int g_nMutex;
//extern int g_nNetPlayMode;
//extern CString g_strName;
//extern int g_nPortNum;
extern int g_nMoveSpeeds;
extern int g_nTimeLimit;
extern int g_nIsNoTimeLimit;
extern BOOL g_bPeepOften;
extern BOOL g_bMovePlace;
extern int g_nCanHintTimeB;
extern int g_nCanHintTimeW;
extern int g_nStrollSpeed;
extern BOOL g_bIsFromFile;
extern int  g_nTime1;
extern int  g_nTime2;
extern int  g_nTime3;
extern int g_nMark1;
extern int g_nMark2;
extern int g_nMark3;
extern CString g_strName1;
extern CString g_strName2;
extern CString g_strName3;
extern CString g_strSec1;
extern CString g_strSec2;
extern CString g_strSec3;

#endif //!_INC_GLOBALVAR
