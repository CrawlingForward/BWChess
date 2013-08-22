// BWChessDlg.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include <mmsystem.h>
#include "BWChess.h"
#include "SetupDlg.h"
#include "AboutDlg.h"
#include "HowToDlg.h"
#include "Globalvar0.h"
#include "HelperAPI.h"
#include "BWChessDlg.h"
#include "RecorDdlg.h"
#include "BestDlg.h"
#include <time.h>
#include "SettingDlg.h"
#include "Demo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define EDITION 17
#define PASSEDTIME 1

BOOL PlaySounds(UINT IDSoundRes, WORD wFlag = SND_ASYNC);

static TCHAR pSettings[]=_T("Settings");

/////////////////////////////////////////////////////////////////////////////
// CBWChessDlg dialog
BOOL PlaySounds(UINT IDSoundRes, WORD wFlag)
{               
	if (g_bSoundOn)
		if (PlaySound(MAKEINTRESOURCE(IDSoundRes),
			AfxGetInstanceHandle(),
			wFlag|SND_RESOURCE|SND_NODEFAULT))
			return TRUE;
	return FALSE;
}

CBWChessDlg::CBWChessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_BWCHESS_DIALOG, pParent)
{
	//{{AFX_DATA_INIT(CBWChessDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pMenu = new CMenu();

	m_pDibEmpty = new CDib;
	m_pDibBlack = new CDib;
	m_pDibWhite = new CDib;
	m_pDibBGo=new CDib;
	m_pDibWGo=new CDib;
	m_pDibCurB=new CDib;
	m_pDibCurW=new CDib;

	int i,j;
	for(i=0;i<2;i++)
	{
		for(j=0;j<NUM+2;j++)
			m_pDibHFrame[i][j]=new CDib;
		for(j=0;j<NUM;j++)
			m_pDibVFrame[i][j]=new CDib;
	}

	m_PaintNum=0;
	hAccelerator=::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_ACC));

	g_nCanHintTimeB=AfxGetApp()->GetProfileInt(_T("Supior Option"), _T("CanHintTimesB"), 3);
	g_nCanHintTimeW=AfxGetApp()->GetProfileInt(_T("Supior Option"), _T("CanHintTimesW"), 3);
	g_nStrollSpeed=AfxGetApp()->GetProfileInt(_T("Supior Option"), _T("StrollSpeed"), 2);
	//
	g_nStrollSpeed=abs(g_nStrollSpeed);
	g_nStrollSpeed%=3;
	g_nCanHintTimeB=abs(g_nCanHintTimeB);
	g_nCanHintTimeB%=31;
	if(g_nCanHintTimeB<3)
		g_nCanHintTimeB=3;

	g_nCanHintTimeW=abs(g_nCanHintTimeW);
	g_nCanHintTimeW%=31;
	if(g_nCanHintTimeW<3)
		g_nCanHintTimeW=3;
	//
	g_bPrompt		=AfxGetApp()->GetProfileInt(pSettings,_T("Prompt"),1);
//	g_nPortNum		=AfxGetApp()->GetProfileInt(pSettings, _T("PortNum"), 1228);
	g_bIsFromFile	=AfxGetApp()->GetProfileInt(pSettings, _T("FromFiles"), 0);
//	g_strName		=AfxGetApp()->GetProfileString(pSettings, _T("CurrentName"), _T("Lovely Babby"));
//	g_nNetPlayMode	=AfxGetApp()->GetProfileInt(pSettings, _T("NetPlayMode"), 0);
	g_nMoveSpeeds	=AfxGetApp()->GetProfileInt(pSettings, _T("ComputerWalkSpeed"), 2);
	g_nCbSkill		=AfxGetApp()->GetProfileInt(pSettings, _T("ComputerBlackSkill"), 3);
	g_nCwSkill		=AfxGetApp()->GetProfileInt(pSettings, _T("ComputerWhiteSkill"), 3);
	g_nCSpeed		=AfxGetApp()->GetProfileInt(pSettings, _T("ComputerDemoSpeed"), 2);
	g_nIsNoTimeLimit=AfxGetApp()->GetProfileInt(pSettings, _T("IsNoTimeLimit"), 0);
	g_nTimeLimit	=AfxGetApp()->GetProfileInt(pSettings, _T("TimeLimit"), 60);
	g_bShowDynamic	=AfxGetApp()->GetProfileInt(pSettings, _T("ShowDynamic"), 0);
	g_bPeepOften	=AfxGetApp()->GetProfileInt(pSettings, _T("PeepOften"), 1);
	g_bTopMost		=AfxGetApp()->GetProfileInt(pSettings, _T("TopMost"), 0);
	g_bSoundOn		=AfxGetApp()->GetProfileInt(pSettings, _T("SoundOn"), 1);
	g_bUserBlack	=AfxGetApp()->GetProfileInt(pSettings, _T("UserUseBlackStone"), 1);
	g_nRunMode		=AfxGetApp()->GetProfileInt(pSettings, _T("Player"), MODE_WITH_COMPUTER);    
	g_nSkill		=AfxGetApp()->GetProfileInt(pSettings, _T("Skill"), 1);
	g_nTime1		=AfxGetApp()->GetProfileInt(pSettings, _T("Time1"), 0);    
	g_nTime2		=AfxGetApp()->GetProfileInt(pSettings, _T("Time2"), 0);    
	g_nTime3		=AfxGetApp()->GetProfileInt(pSettings, _T("Time3"), 0);
	g_nMark1		=AfxGetApp()->GetProfileInt(pSettings, _T("Mark1"), 0);    
	g_nMark2		=AfxGetApp()->GetProfileInt(pSettings, _T("Mark2"), 0);    
	g_nMark3		=AfxGetApp()->GetProfileInt(pSettings, _T("Mark3"), 0);    
	g_strName1		=AfxGetApp()->GetProfileString(pSettings, _T("Name1"), _T("Anonymous"));    
	g_strName2		=AfxGetApp()->GetProfileString(pSettings, _T("Name2"), _T("Anonymous"));    
	g_strName3		=AfxGetApp()->GetProfileString(pSettings, _T("Name3"), _T("Anonymous"));    
	g_strSec1		=AfxGetApp()->GetProfileString(pSettings, _T("Sec1"), _T(""));    
	g_strSec2		=AfxGetApp()->GetProfileString(pSettings, _T("Sec2"), _T(""));    
	g_strSec3		=AfxGetApp()->GetProfileString(pSettings, _T("Sec3"), _T(""));    
	g_bMovePlace	=AfxGetApp()->GetProfileInt(pSettings, _T("ComputerPlaceDynamic"), 1);

	CString str;
	str.LoadString (IDS_AUTHOR);
	AfxGetApp()->WriteProfileString(_T("Author"), _T("Shuker"), str);  
}

CBWChessDlg::~CBWChessDlg()
{
	delete m_pMenu;
	delete m_pDibEmpty;
	delete m_pDibBlack;
	delete m_pDibWhite;
	delete m_pDibBGo;
	delete m_pDibWGo;
	delete m_pDibCurB;
	delete m_pDibCurW;

	int i,j;
	for(i=0;i<2;i++)
	{
		for(j=0;j<NUM+2;j++)
			delete m_pDibHFrame[i][j];
		for(j=0;j<NUM;j++)
			delete m_pDibVFrame[i][j];
	}

	AfxGetApp()->WriteProfileInt(pSettings, _T("Prompt"),g_bPrompt);
	AfxGetApp()->WriteProfileInt(pSettings, _T("ComputerBlackSkill"), g_nCbSkill);
	AfxGetApp()->WriteProfileInt(pSettings, _T("ComputerWhiteSkill"), g_nCwSkill);
	AfxGetApp()->WriteProfileInt(pSettings, _T("ComputerDemoSpeed"), g_nCSpeed);
	AfxGetApp()->WriteProfileInt(pSettings, _T("ComputerWalkSpeed"), g_nMoveSpeeds);
	AfxGetApp()->WriteProfileInt(pSettings, _T("ShowDynamic"), g_bShowDynamic);
	AfxGetApp()->WriteProfileInt(pSettings, _T("PeepOften"), g_bPeepOften);
	AfxGetApp()->WriteProfileInt(pSettings, _T("TopMost"), g_bTopMost);
	AfxGetApp()->WriteProfileInt(pSettings, _T("SoundOn"), g_bSoundOn);
	AfxGetApp()->WriteProfileInt(pSettings, _T("UserUseBlackStone"), g_bUserBlack);
	AfxGetApp()->WriteProfileInt(pSettings, _T("Player"), g_nRunMode);    
	AfxGetApp()->WriteProfileInt(pSettings, _T("Skill"), g_nSkill);
	AfxGetApp()->WriteProfileInt(pSettings, _T("Time1"), g_nTime1);    
	AfxGetApp()->WriteProfileInt(pSettings, _T("Time2"), g_nTime2);    
	AfxGetApp()->WriteProfileInt(pSettings, _T("Time3"), g_nTime3);  
	AfxGetApp()->WriteProfileInt(pSettings, _T("Mark1"), g_nMark1);    
	AfxGetApp()->WriteProfileInt(pSettings, _T("Mark2"), g_nMark2);    
	AfxGetApp()->WriteProfileInt(pSettings, _T("Mark3"), g_nMark3);    
	AfxGetApp()->WriteProfileString(pSettings, _T("Name1"), g_strName1);    
	AfxGetApp()->WriteProfileString(pSettings, _T("Name2"), g_strName2);    
	AfxGetApp()->WriteProfileString(pSettings, _T("Name3"), g_strName3);    
	AfxGetApp()->WriteProfileString(pSettings, _T("Sec1"), g_strSec1);    
	AfxGetApp()->WriteProfileString(pSettings, _T("Sec2"), g_strSec2);    
	AfxGetApp()->WriteProfileString(pSettings, _T("Sec3"), g_strSec3);    
	AfxGetApp()->WriteProfileInt(pSettings, _T("ComputerPlaceDynamic"), g_bMovePlace); 
	AfxGetApp()->WriteProfileInt(pSettings, _T("TimeLimit"), g_nTimeLimit);
	AfxGetApp()->WriteProfileInt(pSettings, _T("IsNoTimeLimit"), g_nIsNoTimeLimit);
	AfxGetApp()->WriteProfileInt(_T("Supior Option"), _T("StrollSpeed"), g_nStrollSpeed);
	AfxGetApp()->WriteProfileInt(_T("Supior Option"), _T("CanHintTimesB"), g_nCanHintTimeB);
	AfxGetApp()->WriteProfileInt(_T("Supior Option"), _T("CanHintTimesW"), g_nCanHintTimeW);
//	AfxGetApp()->WriteProfileInt(pSettings, _T("NetPlayMode"), g_nNetPlayMode);
//	AfxGetApp()->WriteProfileString(pSettings, _T("CurrentName"), g_strName); 
	AfxGetApp()->WriteProfileInt(pSettings, _T("FromFiles"), g_bIsFromFile);
//	AfxGetApp()->WriteProfileInt(pSettings, _T("PortNum"), g_nPortNum);
}

void CBWChessDlg::InitParams()
{
	for (int i=0; i<NUM;i++)
		for (int j=0; j<NUM; j++)
			kernel[i][j] = 0;	

	kernel[3][3]=kernel[4][4]=2;
	kernel[3][4]=kernel[4][3]=1;

	m_CurPt.x = m_CurPt.y =-1;

	num_black=2;
	num_white=2;

	m_PassedTime=0;
	m_PassedTime0=0;
	m_bGameOver = FALSE;	              
	m_byColor = 0; 
	m_Skip=0;
	m_Interesting=1;
	g_nStoneNum=0;
	m_TimerOn=0;
	m_HintOnce=0;//0 for have not hinted yet,1 for have hinted
	m_PeekOnce=0;
	m_IsGameStart=0;
	m_ListInfo.ResetContent();
	m_HintTime0=0;
	m_HintTime1=0;
	ListInfo.destroy();

	m_UndoPoint.Destroy();
}

void CBWChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBWChessDlg)
	DDX_Control(pDX, IDC_TIME_CHINESE0, m_Time0);
	DDX_Control(pDX, IDC_INFO, m_Info);
	DDX_Control(pDX, IDC_LISTINFO, m_ListInfo);
	DDX_Control(pDX, IDC_WNUM, m_Wnum);
	DDX_Control(pDX, IDC_TIME_CHINESE, m_Time);
	DDX_Control(pDX, IDC_BNUM, m_Bnum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBWChessDlg, CDialog)
	//{{AFX_MSG_MAP(CBWChessDlg)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()                           	
	ON_COMMAND(IDM_NEW, OnNew)			
	ON_COMMAND(IDM_EXIT, OnExit)			
	ON_COMMAND(IDM_ABOUT, OnAbout)			
	ON_WM_SETCURSOR()
	ON_WM_QUERYDRAGICON()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_SYSCOMMAND()
	ON_WM_CONTEXTMENU()
	ON_WM_TIMER()
	ON_COMMAND(IDM_UNDO, OnUndo)
	ON_COMMAND(IDM_HOWTO, OnHowto)
	ON_COMMAND(IDM_BEST, OnBest)
	ON_COMMAND(IDM_HINT, OnHint)
	ON_COMMAND(IDM_CANPLACE, OnCanplace)
	ON_COMMAND(IDM_SETTING, OnSetting)
	ON_COMMAND(IDM_OPEN, OnOpen)
	ON_COMMAND(IDM_SAVE, OnSave)
	ON_COMMAND(IDM_SAVEINFO, OnSaveinfo)
	ON_COMMAND(IDM_DEMO, OnDemo)
	ON_COMMAND(IDM_REPLAY, OnReplay)
	//}}AFX_MSG_MAP
	ON_LBN_DBLCLK(IDC_LISTINFO , OnListDoubleClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBWChessDlg message handlers

BOOL CBWChessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Check system display ability
	CDC *pDC = GetDC();
	int nSystemColors = pDC->GetDeviceCaps(BITSPIXEL);
	if (nSystemColors<8)	// 2**8 == 256
	{
		if (MsgBox(IDS_COLOR_LESS_CHINESE, IDS_TITLE_CHINESE,2) != IDOK)
		{
			CDialog::EndDialog(0);
			return TRUE;  					// return from InitDialog
		}
	}

	// Load Dibs
	m_pDibEmpty->LoadDib(IDDIB_EMPTY);
	m_pDibEmpty->MakeBitmap(pDC);
	m_pDibEmpty->GetPalette();

	m_pDibBlack->LoadDib(IDDIB_BLACK);
	m_pDibBlack->MakeBitmap(pDC);
	m_pDibBlack->GetPalette();

	m_pDibWhite->LoadDib(IDDIB_WHITE);
	m_pDibWhite->MakeBitmap(pDC);
	m_pDibWhite->GetPalette();

	m_pDibBGo->LoadDib(IDDIB_CANPLACE1);
	m_pDibBGo->MakeBitmap(pDC);
	m_pDibBGo->GetPalette();

	m_pDibWGo->LoadDib(IDDIB_CANPLACE2);
	m_pDibWGo->MakeBitmap(pDC);
	m_pDibWGo->GetPalette();

	m_pDibCurB->LoadDib(IDDIB_CURBLACK);
	m_pDibCurB->MakeBitmap(pDC);
	m_pDibCurB->GetPalette();

	m_pDibCurW->LoadDib(IDDIB_CURWHITE);
	m_pDibCurW->MakeBitmap(pDC);
	m_pDibCurW->GetPalette();

	m_pDibHFrame[0][0]->LoadDib(IDDIB_F1_1);
	m_pDibHFrame[0][1]->LoadDib(IDDIB_F1_2);
	m_pDibHFrame[0][2]->LoadDib(IDDIB_F1_3);
	m_pDibHFrame[0][3]->LoadDib(IDDIB_F1_4);
	m_pDibHFrame[0][4]->LoadDib(IDDIB_F1_5);
	m_pDibHFrame[0][5]->LoadDib(IDDIB_F1_6);
	m_pDibHFrame[0][6]->LoadDib(IDDIB_F1_7);
	m_pDibHFrame[0][7]->LoadDib(IDDIB_F1_8);
	m_pDibHFrame[0][8]->LoadDib(IDDIB_F1_9);
	m_pDibHFrame[0][9]->LoadDib(IDDIB_F1_10);
	m_pDibHFrame[1][0]->LoadDib(IDDIB_F10_1);
	m_pDibHFrame[1][1]->LoadDib(IDDIB_F10_2);
	m_pDibHFrame[1][2]->LoadDib(IDDIB_F10_3);
	m_pDibHFrame[1][3]->LoadDib(IDDIB_F10_4);
	m_pDibHFrame[1][4]->LoadDib(IDDIB_F10_5);
	m_pDibHFrame[1][5]->LoadDib(IDDIB_F10_6);
	m_pDibHFrame[1][6]->LoadDib(IDDIB_F10_7);
	m_pDibHFrame[1][7]->LoadDib(IDDIB_F10_8);
	m_pDibHFrame[1][8]->LoadDib(IDDIB_F10_9);
	m_pDibHFrame[1][9]->LoadDib(IDDIB_F10_10);

	m_pDibVFrame[0][0]->LoadDib(IDDIB_F2_1);
	m_pDibVFrame[0][1]->LoadDib(IDDIB_F3_1);
	m_pDibVFrame[0][2]->LoadDib(IDDIB_F4_1);
	m_pDibVFrame[0][3]->LoadDib(IDDIB_F5_1);
	m_pDibVFrame[0][4]->LoadDib(IDDIB_F6_1);
	m_pDibVFrame[0][5]->LoadDib(IDDIB_F7_1);
	m_pDibVFrame[0][6]->LoadDib(IDDIB_F8_1);
	m_pDibVFrame[0][7]->LoadDib(IDDIB_F9_1);
	m_pDibVFrame[1][0]->LoadDib(IDDIB_F2_10);
	m_pDibVFrame[1][1]->LoadDib(IDDIB_F3_10);
	m_pDibVFrame[1][2]->LoadDib(IDDIB_F4_10);
	m_pDibVFrame[1][3]->LoadDib(IDDIB_F5_10);
	m_pDibVFrame[1][4]->LoadDib(IDDIB_F6_10);
	m_pDibVFrame[1][5]->LoadDib(IDDIB_F7_10);
	m_pDibVFrame[1][6]->LoadDib(IDDIB_F8_10);
	m_pDibVFrame[1][7]->LoadDib(IDDIB_F9_10);

	int i,j;
	for(i=0;i<2;i++)
	{
		for(j=0;j<NUM;j++)
		{
			m_pDibVFrame[i][j]->MakeBitmap(pDC);
			m_pDibVFrame[i][j]->GetPalette();
		}
		for(j=0;j<NUM+2;j++)
		{
			m_pDibHFrame[i][j]->MakeBitmap(pDC);
			m_pDibHFrame[i][j]->GetPalette();
		}
	}
	ReleaseDC(pDC);
	////////////////////////////////////////
	// Stone size
	m_wStoneWidth  = m_pDibEmpty->GetWidth();
	m_wStoneHeight = m_pDibEmpty->GetHeight();
	m_wFrameWidth  = m_pDibHFrame[0][1]->GetWidth();
	m_wFrameHeight = m_pDibHFrame[0][1]->GetHeight();

	int cxScreen = ::GetSystemMetrics(SM_CXSCREEN);
	int cyScreen = ::GetSystemMetrics(SM_CYSCREEN);
	int cxDlgFrame = ::GetSystemMetrics(SM_CXDLGFRAME);
	int cyDlgFrame = ::GetSystemMetrics(SM_CYDLGFRAME);
	int cxCaption = ::GetSystemMetrics(SM_CYCAPTION); 
	int cyMenu = ::GetSystemMetrics(SM_CYMENU);
	int nWidth  = m_wFrameHeight*2+ m_wFrameWidth*8 + 2*cxDlgFrame;
	int nHeight = m_wFrameHeight*2+ m_wFrameWidth*8 + cxCaption + 2*cyDlgFrame + cyMenu;

	MoveWindow((cxScreen-nWidth-230)/2, (cyScreen-nHeight)/2,
			   nWidth+230, nHeight+2);

	TimeCount.Create(this,nWidth+ 20, 40  ,0,4);
	TimeCount0.Create(this,nWidth+20, 120 ,0,4);
	BCount.Create	(this,nWidth+ 34, 230 ,0,2);
	WCount.Create	(this,nWidth+ 34 ,310 ,0,2);

//	ShowNumber(1);
	m_Time.MoveWindow(nWidth+18  ,20  ,60,20);
	m_Time0.MoveWindow(nWidth+18 ,100 ,60,20);
	m_Bnum.MoveWindow(nWidth+18  ,210 ,60,20);
	m_Wnum.MoveWindow(nWidth+18  ,290 ,60,20);

	m_ListInfo.MoveWindow(nWidth+95,22,110,410);
	m_Info.MoveWindow(nWidth+95,2,110,20);

	m_IsGameStart=1;
	//delete system menu item called size
	CMenu* sysmenu=GetSystemMenu(FALSE);
	sysmenu->DeleteMenu(2,MF_BYPOSITION);

	CString str;
	str.LoadString(IDS_TITLE_CHINESE);
	SetWindowText(str);

	m_pMenu->DestroyMenu();
	m_pMenu->LoadMenu(IDR_MENU_CHINESE);
	SetMenu(m_pMenu);
	m_pMenu->EnableMenuItem(IDM_HINT,MF_GRAYED);
	m_pMenu->EnableMenuItem(IDM_UNDO,MF_GRAYED);
	m_pMenu->EnableMenuItem(IDM_CANPLACE,MF_GRAYED);
	m_pMenu->EnableMenuItem(IDM_SAVE,MF_GRAYED);
	m_pMenu->EnableMenuItem(IDM_SAVEINFO,MF_GRAYED);
	m_pMenu->EnableMenuItem(IDM_REPLAY,MF_GRAYED);

	if(g_bTopMost)
		SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
	else
		SetWindowPos(&wndNoTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
	// Adjust the 4 values to suit board
	m_wXNull = m_wFrameHeight+1;//9
	m_wYNull = m_wFrameHeight+1;//10
	m_Client.top = m_wYNull;
	m_Client.left = m_wXNull;
	m_Client.bottom =m_wYNull + NUM * m_wStoneHeight;
	m_Client.right =m_wXNull + NUM * m_wStoneWidth;

	for (i=0; i<NUM;++i)
		for (j=0; j<NUM; j++)
			kernel[i][j] = 0;	

	num_black=0;
	num_white=0;

	m_PassedTime=0;
	m_PassedTime0=0;
	m_TimerOn=0;
	m_HintOnce=0;//0 for have not hinted yet,1 for have hinted
	m_PeekOnce=0;
	m_HintTime0=0;
	m_HintTime1=0;

	m_bGameOver=TRUE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBWChessDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		ShowNumber(1);
		DrawFrame(&dc);

		if(!m_IsGameStart)
//			PaintWelcome(&dc);
//		else
		{
			for (int i=0; i<NUM; ++i)
				for (int j=0; j<NUM; ++j)
				{
					if (kernel[i][j])             
						PutStone(kernel[i][j]-1, CPoint(j,i), &dc);
				}
			if(m_CurPt.x >=0)
			{
				int nX = m_CurPt.x*m_wStoneWidth + m_wXNull;
				int nY = m_CurPt.y*m_wStoneHeight + m_wYNull;
				int byColor= kernel[m_CurPt.y][m_CurPt.x]-1;
				CPoint ptLUCorner(nX, nY);
				if (byColor == 0)
					m_pDibCurW->Display(&dc, ptLUCorner, SRCCOPY);
				else if (byColor == 1)
					m_pDibCurB->Display(&dc, ptLUCorner, SRCCOPY);
			}
		}

		if(m_HintOnce)
		{
			COLORREF crColor = m_byColor ? RGB(255,255,255) : RGB(0,0,0);
			CPen pen(PS_SOLID, 2, crColor);
			CPen *pOldPen = dc.SelectObject(&pen);	
			dc.MoveTo(x1, y1);
			dc.LineTo(x2, y1);
			dc.LineTo(x2, y2);
			dc.LineTo(x1, y2);
			dc.LineTo(x1, y1);
			dc.LineTo(x2, y2);
			dc.MoveTo(x2, y1);
			dc.LineTo(x1, y2);
			dc.SelectObject(pOldPen);
		}
		if(m_PeekOnce)
		{
			int px,py;
			int xx1,yy1;
			int length,hy;

			if(m_byColor)
				length=wsp.isempty();
			else
				length=bsp.isempty();
			if(length)
				return;

			do
			{
				if(m_byColor)
					length=wsp.GetNextPos(&py,&px,&hy);
				else
					length=bsp.GetNextPos(&py,&px,&hy);
				xx1 = px*m_wStoneWidth + m_wXNull;//-4 + m_cxGrid / 2;
				yy1 = py*m_wStoneHeight + m_wYNull;//-4 + m_cyGrid / 2;
				CPoint ptt(xx1,yy1);
				if(m_byColor)
					m_pDibWGo->Display (&dc,ptt);
				else
					m_pDibBGo->Display (&dc,ptt);
			}
			while(length);

			if(m_byColor)
				wsp.CopyBackIndex ();
			else
				bsp.CopyBackIndex ();
		}
		Mutex1.Lock();
		if(g_nIsDemo && g_nMutex)
		{
			g_nMutex=0;

			m_Mutex.Unlock();
		}
		Mutex1.Unlock();
	}	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBWChessDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBWChessDlg::OnLButtonDown(UINT nFlag, CPoint point)
{       
	CPoint pt;
	if(!IsInPanel(point) || m_bGameOver || g_nIsDemo)
		return;
	if (PointToStonePos(point, pt))
	{
		int nX = pt.x;
		int nY = pt.y;
		if (kernel[nY][nX]==0)      
		{
			if (g_nRunMode == MODE_WITH_COMPUTER)
			{
				if ((g_bUserBlack && !m_byColor) || 
					(!g_bUserBlack && m_byColor)) 
				{                                    
					// User
					m_byColor = !m_byColor;			// 1-Black  0-White
					//undo
					duplicate();
					//end undo
					if(BtoW(nY,nX,m_byColor+1))
					{
						m_HintOnce=0;
						m_PeekOnce=0;
						m_CurPt=pt;
						AddStringToList(nY,nX,m_byColor);
						InvalidateRect(m_Client, FALSE);
						UpdateWindow();
						PlaySounds(IDSOUND_PUTSTONE);   
						Ring(IsEnd(!m_byColor+1));
						// Computer                       
						if (!m_bGameOver && !m_Skip)
						{
							do
							{
								m_byColor = !m_byColor;			// 1-Black  0-White
								int ptBest_x,ptBest_y;
								//undo
								duplicate();
								//end undo
								Place(&ptBest_x,&ptBest_y,m_byColor+1,g_nSkill);
								BtoW(ptBest_x,ptBest_y,m_byColor+1);
								CPoint pt;
								pt.x = ptBest_y*m_wStoneWidth + m_wXNull+m_wStoneWidth/2;
								pt.y = ptBest_x*m_wStoneHeight + m_wYNull+m_wStoneWidth/2;
								m_CurPt.x=ptBest_y;
								m_CurPt.y=ptBest_x;
								ClientToScreen(&pt);
								MoveCursor(pt.x, pt.y);
								InvalidateRect(m_Client, FALSE);
								UpdateWindow();
								AddStringToList(ptBest_x,ptBest_y,m_byColor);
								PlaySounds(IDSOUND_PUTSTONE);
								Ring(IsEnd(!m_byColor+1));
							}
							while(m_Skip);
						}
						if(!m_bGameOver && g_bPeepOften)
							OnCanplace();
					}
					else
					{
						int temp[NUM*NUM];
						m_UndoPoint.pop(temp);
						m_byColor=!m_byColor;
						PlaySounds(IDSOUND_ERROR);
					}					
				}
			}
			else if (g_nRunMode == MODE_2PLAYER)			// Users
			{
				m_byColor = !m_byColor;			// 1-Black  0-White
				duplicate();
				if(BtoW(nY,nX,m_byColor+1))
				{
					m_HintOnce=0;
					m_PeekOnce=0;
					m_CurPt=pt;
					AddStringToList(nY,nX,m_byColor);
					InvalidateRect(m_Client,FALSE);
					UpdateWindow();
					PlaySounds(IDSOUND_PUTSTONE);        
					Ring(IsEnd(!m_byColor+1));
					if(!m_bGameOver && g_bPeepOften)
						OnCanplace();
				}
				else
				{
					int temp[NUM*NUM];
					m_UndoPoint.pop(temp);
					m_byColor=!m_byColor;
					PlaySounds(IDSOUND_ERROR);
				}
			}
		}	            
		else
			PlaySounds(IDSOUND_ERROR);
	}
	else
		PlaySounds(IDSOUND_ERROR);

	CDialog::OnLButtonDown(nFlag, point);
}             
		  
int CBWChessDlg::Distance(const CPoint &pt1, const CPoint &pt2)
{
	return (int)sqrt((double)(pt1.x-pt2.x)*(pt1.x-pt2.x) + (double)(pt1.y-pt2.y)*(pt1.y-pt2.y));
}

BOOL CBWChessDlg::IsStonePoint(CPoint& ptStone)
{
	if (ptStone.x<0 || ptStone.x>=NUM || ptStone.y<0 || ptStone.y>=NUM)
	{
		if (ptStone.x<0)
			ptStone.x = 0;
		else if (ptStone.x>=NUM)
			ptStone.x = NUM-1;
		if (ptStone.y<0)
			ptStone.y = 0;
		else if (ptStone.y>=NUM)
			ptStone.y = NUM-1;
		
		return FALSE;
	}
	return TRUE;
}

BOOL CBWChessDlg::PointToStonePos(const CPoint &pt, CPoint& ptStone)
{
	int nPosX = (pt.x - m_wXNull-m_wStoneWidth/2)/m_wStoneWidth;
	int nPosY = (pt.y - m_wYNull-m_wStoneWidth/2)/m_wStoneHeight;
	CPoint pt0(nPosX * m_wStoneWidth + m_wXNull+m_wStoneWidth/2, nPosY*m_wStoneHeight+m_wYNull+m_wStoneWidth/2);
	CPoint pt1((nPosX+1)*m_wStoneWidth+m_wXNull+m_wStoneWidth/2, nPosY*m_wStoneHeight+m_wYNull+m_wStoneWidth/2);
	CPoint pt2((nPosX+1)*m_wStoneWidth+m_wXNull+m_wStoneWidth/2, (nPosY+1)*m_wStoneHeight+m_wYNull+m_wStoneWidth/2);
	CPoint pt3(nPosX*m_wStoneWidth+m_wXNull+m_wStoneWidth/2, (nPosY+1)*m_wStoneHeight+m_wYNull+m_wStoneWidth/2);
	
	int nDis0 = Distance(pt, pt0);
	int nDis1 = Distance(pt, pt1);
	int nDis2 = Distance(pt, pt2);
	int nDis3 = Distance(pt, pt3);
	int nLimit = m_wStoneWidth/2-4;
	if (nDis0 <= nLimit)
		ptStone = CPoint(nPosX, nPosY);
	else if (nDis1 <= nLimit)
		ptStone = CPoint(nPosX+1, nPosY);
	else if (nDis2 <= nLimit)
		ptStone = CPoint(nPosX+1, nPosY+1);
	else if (nDis3 <= nLimit)
		ptStone = CPoint(nPosX, nPosY+1);
	else
	{
		int nMin1 = min(nDis0, nDis1);
		int nMin2 = min(nDis2, nDis3);
		int nMin = min(nMin1, nMin2);

		if (nMin == nDis0)
			ptStone = CPoint(nPosX, nPosY);
		else if (nMin == nDis1)
			ptStone = CPoint(nPosX+1, nPosY);
		else if (nMin == nDis2)
			ptStone = CPoint(nPosX+1, nPosY+1);
		else if (nMin == nDis3)
			ptStone = CPoint(nPosX, nPosY+1);

		IsStonePoint(ptStone);
		return FALSE;
	}
	return IsStonePoint(ptStone);
}

void CBWChessDlg::Ring(int m_nType)
{
	Calcu_BW();
	ShowNumber();
	m_Skip=0;//only when m_nType==0,then m_Skip==1;
				//other m_Skip==0;
	switch(m_nType)
	{
	case -1:
		{
			int win=0;
			int addp=0;
			m_bGameOver = TRUE;
			if(m_TimerOn)
			{
				KillTimer(PASSEDTIME);
				m_TimerOn=0;
			}
			m_pMenu->EnableMenuItem(IDM_HINT,MF_GRAYED);
			m_pMenu->EnableMenuItem(IDM_UNDO,MF_GRAYED);
			m_pMenu->EnableMenuItem(IDM_CANPLACE,MF_GRAYED);
//			m_pMenu->EnableMenuItem(IDM_SAVE,MF_GRAYED);
			m_pMenu->EnableMenuItem(IDM_SAVEINFO,MF_ENABLED);
			m_pMenu->EnableMenuItem(IDM_REPLAY,MF_ENABLED);

			CString str1,str2, str3,strPrompt;
			TCHAR str[64];

			str2.LoadString(IDS_TITLE_CHINESE);

			if(g_nRunMode == MODE_2PLAYER)
			{
				if(num_white<num_black)
				{
					addp=2;
					str1.LoadString(IDS_BLACKWIN_CHINESE);
				}
				else if(num_white>num_black)
				{
					addp=1;
					str1.LoadString(IDS_WHITEWIN_CHINESE);
				}
				else
				{
					addp=3;
					str1.LoadString(IDS_TIE_CHINESE);
				}
				str3.LoadString(IDS_END_CHINESE);
				
				wsprintf(str, str3.GetBuffer(256), num_black,num_white);
				strPrompt = str;
				strPrompt += str1; 
			}
			else
			{
				g_nStoneNum=abs(num_black-num_white);
				g_nBestMark=abs((num_white+num_black)*(num_white-num_black));
				if(!(num_black && num_white))
					g_nBestMark+=800;
				if(num_white>num_black)
					addp=1;
				if(num_white<num_black)
					addp=2;
				if(num_white==num_black)
				{
					str1.LoadString(IDS_TIE_CHINESE);
					win=1;
					addp=3;
				}
				else if((g_bUserBlack && (num_white>num_black)) || ((!g_bUserBlack) && (num_white<num_black)))
				{
					if(!num_white || !num_black)
						str1.LoadString(IDS_COMPUTERWIN0_CHINESE);
					else if(g_nStoneNum>=40)
						str1.LoadString(IDS_COMPUTERWIN1_CHINESE);
					else
						str1.LoadString(IDS_COMPUTERWIN2_CHINESE);
				}
				else if((g_bUserBlack && (num_white<num_black)) || ((!g_bUserBlack) && (num_white>num_black)))
				{
					win=1;
					if(!num_white || !num_black)
						str1.LoadString(IDS_USERWIN0_CHINESE);
					else if(g_nStoneNum<=6)
						str1.LoadString(IDS_USERWIN2_CHINESE);
					else
						str1.LoadString(IDS_USERWIN1_CHINESE);
				}

				if(num_white!=num_black)
				{
					if(num_white && num_black)
					{
						wsprintf(str, str1.GetBuffer(256), g_nStoneNum);
						strPrompt=str;
					}
					else
						strPrompt=str1;
				}
				else
					strPrompt=str1;
			}

			AddStringToList(0,0,0,addp);

			if(g_nRunMode == MODE_2PLAYER)
				PlaySounds(IDSOUND_USERWIN);
			else
				PlaySounds((win==0) ? IDSOUND_COMPUTERWIN : IDSOUND_USERWIN );

			MsgBox(strPrompt,str2);

			BOOL bWinner = FALSE;
			if ((g_nSkill==1 && g_nBestMark>g_nMark1) ||
				(g_nSkill==2 && g_nBestMark>g_nMark2) ||
				(g_nSkill==3 && g_nBestMark>g_nMark3))
				bWinner = TRUE;
			
			if (g_nRunMode == MODE_WITH_COMPUTER && bWinner &&
				(win==1))
			{
				CRecordDlg recordDlg;
//    			int result=
				recordDlg.DoModal();
//				if(result==IDOK)
//					OnBest();
			}
		}
		break;
	case 0:
		{
			CString str3,str2;
			if(g_nRunMode == MODE_WITH_COMPUTER)
			{
				if((g_bUserBlack && !m_byColor) || (!g_bUserBlack && m_byColor))
					str3.LoadString(IDS_USER_NOPLACE_CHINESE);
				else if((g_bUserBlack && m_byColor) || (!g_bUserBlack && !m_byColor))
					str3.LoadString(IDS_COMPUTER_NOPLACE_CHINESE);
			}
			if(g_nRunMode == MODE_2PLAYER)
			{
				if(!m_byColor)
					str3.LoadString(IDS_BLACK_NOPLACE_CHINESE);
				else
					str3.LoadString(IDS_WHITE_NOPLACE_CHINESE);
			}
			str2.LoadString(IDS_TITLE_CHINESE);
			MsgBox(str3,str2);
			//important type
			m_Skip=1;
			//
			m_byColor=!m_byColor;
		}
		break;
	}
}

void CBWChessDlg::OnNew()
{
	int HaveKilled=0;
	if(m_TimerOn)
	{
		HaveKilled=1;
		KillTimer(PASSEDTIME);
		m_TimerOn=0;
	}

	if(!m_bGameOver)
	{
		if(g_bPrompt && (MsgBox(IDS_ABORT,IDS_TITLE_CHINESE,2)==IDCANCEL))
		{
			if(HaveKilled)
			{				
				SetTimer(PASSEDTIME,1000,NULL);
				m_TimerOn=1;
			}
			return;
		}
	}

	CSetupDlg setupDlg;
	if (setupDlg.DoModal()==IDCANCEL)
	{
		if(HaveKilled)
		{			
			SetTimer(PASSEDTIME,1000,NULL);
			m_TimerOn=1;
		}
		return;
	}

	InitParams();
	Invalidate();   
	UpdateWindow();   
	ShowNumber(1);

	SetChessTitle();

	m_pMenu->EnableMenuItem(IDM_HINT,MF_ENABLED);
	m_pMenu->EnableMenuItem(IDM_UNDO,MF_ENABLED);
	m_pMenu->EnableMenuItem(IDM_CANPLACE,MF_ENABLED);
	m_pMenu->EnableMenuItem(IDM_SAVE,MF_ENABLED);
	m_pMenu->EnableMenuItem(IDM_SAVEINFO,MF_GRAYED);
	m_pMenu->EnableMenuItem(IDM_REPLAY,MF_GRAYED);

	PlaySounds(IDSOUND_NEWGAME);
	UpdateWindow();

	if (g_nRunMode==MODE_WITH_COMPUTER && !g_bUserBlack)
	{
		CPoint pt;            			// Computer first
		m_byColor = !m_byColor;			// 1-Black  0-White
		int ptBest_x,ptBest_y;
		IsEnd(m_byColor+1);
		Place(&ptBest_x,&ptBest_y,m_byColor+1,g_nSkill);
		BtoW(ptBest_x,ptBest_y,m_byColor+1);
		AddStringToList(ptBest_x,ptBest_y,m_byColor);
		pt.x = ptBest_y*m_wStoneWidth + m_wXNull+m_wStoneWidth/2;
		pt.y = ptBest_x*m_wStoneHeight + m_wYNull+m_wStoneWidth/2;
		m_CurPt.x=ptBest_y;
		m_CurPt.y=ptBest_x;
		ClientToScreen(&pt);
		SetCursorPos(pt.x, pt.y);
		InvalidateRect(m_Client, FALSE);
		UpdateWindow();
		PlaySounds(IDSOUND_PUTSTONE);
	}  
//	m_nType=IsEnd(!m_byColor+1);
	Ring(IsEnd(!m_byColor+1));
	if(!m_bGameOver && g_bPeepOften)
		OnCanplace();

	SetTimer(PASSEDTIME,1000,NULL);
	m_TimerOn=1;
	//
	m_nIsContinueReplay=1;
}

void CBWChessDlg::OnAbout()
{
	CAboutDlg aboutDlg(this);
	aboutDlg.DoModal();
}

void CBWChessDlg::OnExit()
{
	if(g_bPrompt && (MsgBox(m_bGameOver? IDS_LEAVE_END : IDS_LEAVE_NOEND ,IDS_TITLE_CHINESE,2)==IDCANCEL))
		return ;

	if(m_TimerOn)
		KillTimer(PASSEDTIME);
	if(g_nIsDemo)
		::TerminateThread(m_CcThread->m_hThread,0);

	CDialog::EndDialog(0);
}

void CBWChessDlg::PutStone(BYTE byColor, const CPoint &point, CDC *pDC)
{                                      
	int nX = point.x*m_wStoneWidth + m_wXNull;                             
	int nY = point.y*m_wStoneHeight + m_wYNull;
	CPoint ptLUCorner(nX, nY);
	if (byColor == 0)
		m_pDibWhite->Display(pDC, ptLUCorner, SRCCOPY);
	else if (byColor == 1)
		m_pDibBlack->Display(pDC, ptLUCorner, SRCCOPY);
}

BOOL CBWChessDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CPoint point, pt;
	::GetCursorPos(&point);
	ScreenToClient(&point);
	if (PointToStonePos(point, pt) && !m_bGameOver && !g_nIsDemo)
	{	
		::SetCursor(AfxGetApp()->LoadCursor(m_byColor ? IDC_WHITE_HAND:IDC_BLACK_HAND));
		return TRUE;
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CBWChessDlg::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CDialog::OnPaletteChanged(pFocusWnd);
	
	if (pFocusWnd != this)
		OnQueryNewPalette();
}

BOOL CBWChessDlg::OnQueryNewPalette()
{
	CClientDC dc(this);
	CPalette *pOldPal = dc.SelectPalette (m_pDibEmpty->GetPalette(), FALSE);

	int nChangedColors = dc.RealizePalette();

	dc.SelectPalette (pOldPal, FALSE);

	// If any palette entries changed, repaint the window.
	if (nChangedColors > 0)
		Invalidate();
	
	return CDialog::OnQueryNewPalette();
}

void CBWChessDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if(nID == SC_CLOSE)
		OnExit();
	
	CDialog::OnSysCommand(nID, lParam);
}

void CBWChessDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CRect rect;
	GetClientRect(&rect);
	CPoint pt=point;
	ScreenToClient(&pt);
	if(!rect.PtInRect (pt))
	{
		CDialog::OnContextMenu (pWnd,point);
		return;
	}
	if(g_nIsDemo)
		return;
	CMenu menu;
	menu.LoadMenu(IDR_MENU_CONTEXT_CHINESE);

	if(/*m_IsGameStart || */m_bGameOver)
	{
		menu.EnableMenuItem(IDM_UNDO, MF_GRAYED);   
		menu.EnableMenuItem(IDM_HINT, MF_GRAYED);   
		menu.EnableMenuItem(IDM_CANPLACE, MF_GRAYED);
		menu.EnableMenuItem(IDM_SAVEINFO,MF_ENABLED);
		menu.EnableMenuItem(IDM_REPLAY,MF_ENABLED);
//		menu.EnableMenuItem(IDM_SAVE, MF_GRAYED);
	}
//	if(m_bGameOver && !m_IsGameStart)
//	{
		
//	}
	if(!m_bGameOver/* || m_IsGameStart*/)
	{
		menu.EnableMenuItem(IDM_SAVEINFO,MF_GRAYED);
		menu.EnableMenuItem(IDM_REPLAY,MF_GRAYED);
	}
	if(m_IsGameStart)
		menu.EnableMenuItem(IDM_SAVE, MF_GRAYED);

	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, 
										   point.x, point.y, this);
}
////////////////////////// End of BWCHESS.CPP ////////////////////////////////

int CBWChessDlg::BtoW(int x1, int y1, int flag)
{
	int yes;//if yes ==0 then there is no position to change
			//if yes==1 then there is any position to change
	int temp=flag;
	int x=0,y=0,i=0,j=0;
	int result=0;//result==0 indicate that x1,y1 is the wrong position
				 //result==1 indicate that they are legal position

	if(x1<0 || x1>=NUM || y1<0 || y1>=NUM)
		return 0;

	//横向--当前左
	x=x1;
	//y=0;
	yes=0;

	for(i=y1-1;i>=0;i--)
	{
		if(kernel[x][i]==0)
		{
			yes=0;
			break;
		}
		else if(kernel[x][i]==temp)
			break;
		else
			yes=1;
	}

	if((i!=0-1) && (yes==1))
	{
		for(i++;i<y1;i++)
		{
			kernel[x][i]=temp;
			result=1;
		}
	}

	//横向--当前向右
	//x=x1;
	//y=NUM;
	yes=0;

	for(i=y1+1;i<NUM;i++)
	{
		if(kernel[x][i]==0)
		{
			yes=0;
			break;
		}
		else if(kernel[x][i]==temp)
			break;
		else
			yes=1;
	}

	if((i!=NUM) && (yes==1))
	{
		for(i--;i>y1;i--)
		{
			kernel[x][i]=temp;
			result=1;
		}
	}

	//竖向--向上
	//x=0;
	y=y1;
	yes=0;

	for(i=x1-1;i>=0;i--)
	{
		if(kernel[i][y]==0)
		{
			yes=0;
			break;
		}
		else if(kernel[i][y]==temp)
			break;
		else
			yes=1;
	}

	if((i!=0-1) && (yes==1))
	{
		for(i++;i<x1;i++)
		{
			kernel[i][y]=temp;
			result=1;
		}
	}

	//竖向--向下
	//x=NUM;
	//y=y1;
	yes=0;

	for(i=x1+1;i<NUM;i++)
	{
		if(kernel[i][y]==0)
		{
			yes=0;
			break;
		}
		else if(kernel[i][y]==temp)
			break;
		else
			yes=1;
	}

	if((i!=NUM) && (yes==1))
	{
		for(i--;i>x1;i--)
		{
			kernel[i][y]=temp;
			result=1;
		}
	}

	//斜向左上
	//x=0;
	//y=y1;
	yes=0;

	for(i=x1-1,j=y1-1;(i>=0)&&(j>=0);i--,j--)
	{
		if(kernel[i][j]==0)
		{
			yes=0;
			break;
		}
		else if(kernel[i][j]==temp)
			break;
		else
			yes=1;
	}

	if((i!=0-1) && (j!=-1) && (yes==1))
	{
		for(i++,j++;i<x1;i++,j++)
		{
			kernel[i][j]=temp;
			result=1;
		}
	}

	//斜向上向右
	yes=0;

	for(i=x1-1,j=y1+1;(i>=0)&&(j<NUM);i--,j++)
	{
		if(kernel[i][j]==0)
		{
			yes=0;
			break;
		}
		else if(kernel[i][j]==temp)
			break;
		else
			yes=1;
	}

	if((i!=0-1) && (j!=NUM) && (yes==1))
	{
		for(i++,j--;i<x1;i++,j--)
		{
			kernel[i][j]=temp;
			result=1;
		}
	}

	//斜向左下
	yes=0;

	for(i=x1+1,j=y1-1;(i<NUM)&&(j>=0);i++,j--)
	{
		if(kernel[i][j]==0)
		{
			yes=0;
			break;
		}
		else if(kernel[i][j]==temp)
			break;
		else
			yes=1;
	}

	if((i!=NUM) && (j!=-1) && (yes==1))
	{
		for(i--,j++;i>x1;i--,j++)
		{
			kernel[i][j]=temp;
			result=1;
		}
	}

	//斜向右下
	yes=0;

	for(i=x1+1,j=y1+1;(i<NUM)&&(j<NUM);i++,j++)
	{
		if(kernel[i][j]==0)
		{
			yes=0;
			break;
		}
		else if(kernel[i][j]==temp)
			break;
		else
			yes=1;
	}

	if((i!=NUM) && (j!=NUM) && (yes==1))
	{
		for(i--,j--;i>x1;i--,j--)
		{
			kernel[i][j]=temp;
			result=1;
		}
	}

	if(result==1)
		kernel[x1][y1]=temp;

	return result;
}

int CBWChessDlg::IsEnd(/*int *x1, int *y1, */int whogo)
{
	int i,j;
	int x,y;
	int wn=0,bn=0; //indicate how many position can 2 and 1 stand
	int btp_x=-7,btp_y=-7,wtp_x=-7,wtp_y=-7;
	int temp,temp2;

	if(!wsp.isempty())
		wsp.destroy();

	if(!bsp.isempty())
		bsp.destroy();

	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
		{
			if(kernel[i][j]==0)
			{
				//水平向左
				if(Check(i,j-1) && Check(i,j-2))
				{
					x=i,y=j;
					temp=kernel[x][y-1];
					for(y-=2;y>=0;y--)
					{
						temp2=kernel[x][y];
						if(temp2==0)
							break;
						if(temp2!=temp)
						{
							if(temp2==1)
							{
								if(wtp_x!=i || wtp_y!=j)
								{
									wtp_x=i,wtp_y=j;
									wn++;
									wsp.push (i,j);
								}
							}
							else
							{
								if(btp_x!=i || btp_y!=j)
								{
									btp_x=i,btp_y=j;
									bn++;
									bsp.push (i,j);
								}
							}
							break;
						}
					}
				}
				//水平向右
				if(Check(i,j+1) && Check(i,j+2))
				{
					x=i,y=j;
					temp=kernel[x][y+1];
					for(y+=2;y<NUM;y++)
					{
						temp2=kernel[x][y];
						if(temp2==0)
							break;
						if(temp2!=temp)
						{
							if(temp2==1)
							{
								if(wtp_x!=i || wtp_y!=j)
								{
									wtp_x=i,wtp_y=j;
									wn++;
									wsp.push (i,j);
								}
							}
							else
							{
								if(btp_x!=i || btp_y!=j)
								{
									btp_x=i,btp_y=j;
									bn++;
									bsp.push (i,j);
								}
							}
							break;
						}
					}
				}
				//垂直向上
				if(Check(i-1,j) && Check(i-2,j))
				{
					x=i,y=j;
					temp=kernel[x-1][y];
					for(x-=2;x>=0;x--)
					{
						temp2=kernel[x][y];
						if(temp2==0)
							break;
						if(temp2!=temp)
						{
							if(temp2==1)
							{
								if(wtp_x!=i || wtp_y!=j)
								{
									wtp_x=i,wtp_y=j;
									wn++;
									wsp.push (i,j);
								}
							}
							else
							{
								if(btp_x!=i || btp_y!=j)
								{
									btp_x=i,btp_y=j;
									bn++;
									bsp.push (i,j);
								}
							}
							break;
						}
					}
				}

				//垂直向下
				if(Check(i+1,j) && Check(i+2,j))
				{
					x=i,y=j;
					temp=kernel[x+1][y];
					for(x+=2;x<NUM;x++)
					{
						temp2=kernel[x][y];
						if(temp2==0)
							break;
						if(temp2!=temp)
						{
							if(temp2==1)
							{
								if(wtp_x!=i || wtp_y!=j)
								{
									wtp_x=i,wtp_y=j;
									wn++;
									wsp.push (i,j);
								}
							}
							else
							{
								if(btp_x!=i || btp_y!=j)
								{
									btp_x=i,btp_y=j;
									bn++;
									bsp.push (i,j);
								}
							}
							break;
						}
					}
				}

				//斜向左上
				if(Check(i-1,j-1) && Check(i-2,j-2))
				{
					x=i,y=j;
					temp=kernel[x-1][y-1];
					for(x-=2,y-=2;(x>=0) && (y>=0);x--,y--)
					{
						temp2=kernel[x][y];
						if(temp2==0)
							break;
						if(temp2!=temp)
						{
							if(temp2==1)
							{
								if(wtp_x!=i || wtp_y!=j)
								{
									wtp_x=i,wtp_y=j;
									wn++;
									wsp.push (i,j);
								}
							}
							else
							{
								if(btp_x!=i || btp_y!=j)
								{
									btp_x=i,btp_y=j;
									bn++;
									bsp.push (i,j);
								}
							}
							break;
						}
					}
				}

				//斜向右上
				if(Check(i-1,j+1) && Check(i-2,j+2))
				{
					x=i,y=j;
					temp=kernel[x-1][y+1];
					for(x-=2,y+=2;(x>=0) && (y<NUM);x--,y++)
					{
						temp2=kernel[x][y];
						if(temp2==0)
							break;
						if(temp2!=temp)
						{
							if(temp2==1)
							{
								if(wtp_x!=i || wtp_y!=j)
								{
									wtp_x=i,wtp_y=j;
									wn++;
									wsp.push (i,j);
								}
							}
							else
							{
								if(btp_x!=i || btp_y!=j)
								{
									btp_x=i,btp_y=j;
									bn++;
									bsp.push (i,j);
								}
							}
							break;
						}
					}
				}

				//斜向左下
				if(Check(i+1,j-1) && Check(i+2,j-2))
				{
					x=i,y=j;
					temp=kernel[x+1][y-1];
					for(x+=2,y-=2;(x<NUM) && (y>=0);x++,y--)
					{
						temp2=kernel[x][y];
						if(temp2==0)
							break;
						if(temp2!=temp)
						{
							if(temp2==1)
							{
								if(wtp_x!=i || wtp_y!=j)
								{
									wtp_x=i,wtp_y=j;
									wn++;
									wsp.push (i,j);
								}
							}
							else
							{
								if(btp_x!=i || btp_y!=j)
								{
									btp_x=i,btp_y=j;
									bn++;
									bsp.push (i,j);
								}
							}
							break;
						}
					}
				}

				//斜向右下
				if(Check(i+1,j+1) && Check(i+2,j+2))
				{
					x=i,y=j;
					temp=kernel[x+1][y+1];
					for(x+=2,y+=2;(x<NUM) && (y<NUM);x++,y++)
					{
						temp2=kernel[x][y];
						if(temp2==0)
							break;
						if(temp2!=temp)
						{
							if(temp2==1)
							{
								if(wtp_x!=i || wtp_y!=j)
								{
									wtp_x=i,wtp_y=j;
									wn++;
									wsp.push (i,j);
								}
							}
							else
							{
								if(btp_x!=i || btp_y!=j)
								{
									btp_x=i,btp_y=j;
									bn++;
									bsp.push (i,j);
								}
							}
							break;
						}
					}
				}
				////////////////////

			}//end if
		}//end second for

//return -1 for both
//return 0 for the int have no position
//////return 1 for the int have one position ,no use now
//return 2 for have more than one
	if((bn==0) && (wn==0))
		return -1;

	if((bn>=2) && (wn>=2))
		return 2;

	switch(whogo)
	{
	case 1:
		if(wn==0)
			return 0;
//		if(wn==1)
//		{
//			*x1=wtp_x;
//			*y1=wtp_y;
//			return 1;
//		}
		break;
	case 2:
		if(bn==0)
			return 0;
//		if(bn==1)
//		{
//			*x1=btp_x;
//			*y1=btp_y;
//			return 1;
//		}
		break;
	}
	return 2;
}

int CBWChessDlg::Check(int x, int y)
{
	if(x<0 || x>=NUM || y<0 || y>=NUM)
		return 0;
	if(kernel[x][y]==0)
		return 0;
	return 1;

}

int CBWChessDlg::Walk1(int *x1, int *y1, int flag)
{
	int i,j;
	int result;
	int best_x=0,best_y=0;
	int bestmark=-2,tempmark=-2;
	int fv=flag;

	//算法开始!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//本算法采用计分制
	do
	{
		if(fv==1)
			wsp.pop(&i,&j);
		else
			bsp.pop(&i,&j);
		////i,j即可以放的坐标
		if(IsAllEatup(i,j,fv))
		{
			best_x=i;
			best_y=j;
			break;
		}
		tempmark=Judge(i,j,fv);
		if(tempmark>bestmark)
		{
			bestmark=tempmark;
			best_x=i;
			best_y=j;
		}
		else if(tempmark==bestmark)
		{
			result=Compare(i,j,best_x,best_y,fv);
			if(result==0)
				best_x=i,best_y=j;
		}//end if

		if(fv==1)
			result=wsp.isempty();
		else
			result=bsp.isempty();
	}
	while(!result);
	
	*x1=best_x ;
	*y1=best_y ;

	return 0;
}


int CBWChessDlg::Compare(int x1, int y1, int x2, int y2, int flag)
{
//分数一样,进行比较
//return 0,indicate that x1,y1 is superior to x2,y2
//return 1,indicate that x1,y1 is no superior to x2,y2
	int i,j;
	int num1=0,num2=0;
	int numt;
	int temp[NUM][NUM];
	int tempw,tempb;//copy num_black and num_white for copy back

	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			temp[i][j]=kernel[i][j];
	
	Calcu_BW();
	tempw=num_white;
	tempb=num_black;

	if(flag==1)
		num2=num1=num_white;
	else
		num2=num1=num_black;
	BtoW(x1,y1,flag);
	Calcu_BW();
	if(flag==1)
		numt=num_white;
	else
		numt=num_black;
	
	num1=numt-num1;
	///end 1
	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			kernel[i][j]=temp[i][j];

	BtoW(x2,y2,flag);
	Calcu_BW();
	if(flag==1)
		numt=num_white;
	else
		numt=num_black;
	
	num2=numt-num2;
	///end 2
	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			kernel[i][j]=temp[i][j];

	num_black=tempb;
	num_white=tempw;
	
	if(num1>num2)
		return 0;
	else
		return 1;

}

int CBWChessDlg::WhereAmI(int x, int y)
{
//详细确定点的位置
//return 0 顶点
//return 1 上边
//return 2 左边
//return 3 右边
//return 4 下边
//return 5 上面第二排4格
//return 6 左……
//return 7 右……
//return 8 下……
//return 9 中间16格
//return 10 危险的4格

	if((x>1) && (x<NUM-2) && (y>1) && (y<NUM-2))
	{
		return 9;//中间16格
	}
	else if((x==0 || x==NUM-1) && (y==0 || y==NUM-1))
	{
		return 0;//顶点
	}
	else if((x==0) || (x==NUM-1) || (y==0) || (y==NUM-1))
	{
		if(x==0)
			return 1;//上边
		if(x==NUM-1)
			return 4;//下边
		if(y==0)
			return 2;//左边
		if(y==NUM-1)
			return 3;//右边
	}
	else if((x==1 || x==NUM-2) && (y==1 || y==NUM-2))
	{
		return 10;//危险的4格
	}
	else
	{
		if(x==1)
			return 5;//上面第二排4格
		if(x==NUM-2)
			return 8;//下面第二排4格
		if(y==1)
			return 6;//左面第二排4格
		if(y==NUM-2)
			return 7;//右面第二排4格
	}
	return -1;//error??????

}

int CBWChessDlg::Condirect(int *x, int *y, int *flag, int direction, int *top)
{
	//察看点(x,y)在方向direction上有多少的flag子,
	//若有,(x,y)返回末子的坐标
	//返回非0,说明有多少粒flag子(flag指示是否是自己人,0-yes),此时,*top=0 说明没有顶点,1说明有顶点
	//返回0,说明没子
	//direction:	0	向左
	//				1	向右		
	//				2	向上
	//				3	向下
	//				4	左上
	//				5	右上
	//				6	左下
	//				7	右下
	
	//----------------------begin------------------------//
	int i=*x,j=*y,f=0;
	int v=0,tempv=0;
	int num=0;

	switch(direction)
	{
	case 0://向左
		{
			if(j<=0)
				return 0;
			for(j--,tempv=v=kernel[i][j];j>=0;j--,tempv=v,num++)
			{
				v=kernel[i][j];
				if(v!=tempv)
				{
					f=1;
					break;
				}
			}
			if(f==1)
				*top=0;
			else
				*top=1;
			*x=i;
			*y=j+1;
		}
		break;
	case 1://向右
		{
			if(j>=NUM-1)
				return 0;
			for(j++,tempv=v=kernel[i][j];j<NUM;j++,tempv=v,num++)
			{
				v=kernel[i][j];
				if(v!=tempv)
				{
					f=1;
					break;
				}
			}
			if(f==1)
				*top=0;
			else
				*top=1;
			*x=i;
			*y=j-1;
		}
		break;
	case 2://向上
		{
			if(i<=0)
				return 0;
			for(i--,tempv=v=kernel[i][j];i>=0;i--,tempv=v,num++)
			{
				v=kernel[i][j];
				if(v!=tempv)
				{
					f=1;
					break;
				}
			}
			if(f==1)
				*top=0;
			else
				*top=1;
			*x=i+1;
			*y=j;
		}
		break;
	case 3://向下
		{
			if(i>=NUM-1)
				return 0;
			for(i++,tempv=v=kernel[i][j];i<NUM;i++,tempv=v,num++)
			{
				v=kernel[i][j];
				if(v!=tempv)
				{
					f=1;
					break;
				}
			}
			if(f==1)
				*top=0;
			else
				*top=1;
			*x=i-1;
			*y=j;
		}
		break;
	case 4://左上
		{
			if(i<=0 || j<=0)
				return 0;
			for(i--,j--,tempv=v=kernel[i][j];(i>=0) && (j>=0);i--,j--,tempv=v,num++)
			{
				v=kernel[i][j];
				if(v!=tempv)
				{
					f=1;
					break;
				}
			}
			if(f==1)
				*top=0;
			else
				*top=1;
			*x=i+1;
			*y=j+1;
		}
		break;
	case 5://右上
		{
			if(i<=0 || j>=NUM-1)
				return 0;
			for(i--,j++,tempv=v=kernel[i][j];(i>=0) && (j<NUM);i--,j++,tempv=v,num++)
			{
				v=kernel[i][j];
				if(v!=tempv)
				{
					f=1;
					break;
				}
			}
			if(f==1)
				*top=0;
			else
				*top=1;
			*x=i+1;
			*y=j-1;
		}
		break;
	case 6://左下
		{
			if(i>=NUM-1 || j<=0)
				return 0;
			for(i++,j--,tempv=v=kernel[i][j];(i<NUM) && (j>=0);i++,j--,tempv=v,num++)
			{
				v=kernel[i][j];
				if(v!=tempv)
				{
					f=1;
					break;
				}
			}
			if(f==1)
				*top=0;
			else
				*top=1;
			*x=i-1;
			*y=j+1;
		}
		break;
	case 7://右下
		{
			if(i>=NUM-1 || j>=NUM-1)
				return 0;
			for(i++,j++,tempv=v=kernel[i][j];(i<NUM) && (j<NUM);i++,j++,tempv=v,num++)
			{
				v=kernel[i][j];
				if(v!=tempv)
				{
					f=1;
					break;
				}
			}
			if(f==1)
				*top=0;
			else
				*top=1;
			*x=i-1;
			*y=j-1;
		}
		break;
	}//end switch
	if(tempv==0)
		*flag=0;
	else if(abs(tempv-*flag)==0)
		*flag=1;
	else 
		*flag=2;

	return num;//

}

int CBWChessDlg::IsDanger(int x, int y)//indicate whether the point is the second point or not
{
	if((x==0 || x==NUM-1) && (y==1 || y==NUM-2))
		return 1;
	if((y==0 || y==NUM-1) && (x==1 || x==NUM-2))
		return 1;
	return 0;
}

int CBWChessDlg::Imitate(int x, int y, int flag)
{
	int onum=0,inum=0;
	int tempb,tempw;
	int temp[NUM][NUM];
	int i,j;

	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			temp[i][j]=kernel[i][j];
	
	Calcu_BW();
	tempb=num_black;
	tempw=num_white;

	if(flag==1)
		onum=num_white;
	else
		onum=num_black;

	BtoW(x,y,flag);
	Calcu_BW();

	if(flag==1)
		inum=num_white;
	else
		inum=num_black;

	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			kernel[i][j]=temp[i][j];

	num_black=tempb;
	num_white=tempw;

	return (inum-onum);
}

int CBWChessDlg::ToEnd(int x, int y, int flag)
{
//return 0 for no toend,1 for toend but not reach top,2 for toend and reach top
	int i,j;
	int result=0;
	int temp[NUM][NUM];

	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			temp[i][j]=kernel[i][j];
	
	i=x,j=y;
	BtoW(i,j,flag);

	if(i==1 && j==1)
	{
		i=0,j=0;
		int val=flag,top;
		Condirect(&i,&j,&val,7,&top);
		if(top)
		{
			result=2;
		}
		else
		{
			val=flag;
			Condirect(&i,&j,&val,7,&top);
			if(val==0)
				result=1;
			else
				result=0;
		}
//		return result;
	}
	else if(i==1 && (j==NUM-2))
	{
		i=0,j=NUM-1;
		int val=flag,top;
		Condirect(&i,&j,&val,6,&top);
		if(top)
		{
			result=2;
		}
		else
		{
			val=flag;
			Condirect(&i,&j,&val,6,&top);
			if(val==0)
				result=1;
			else
				result=0;
		}
//		return result;
	}
	else if((i==NUM-2) && j==1)
	{
		i=NUM-1,j=0;
		int val=flag,top;
		Condirect(&i,&j,&val,5,&top);
		if(top)
		{
			result=2;
		}
		else
		{
			val=flag;
			Condirect(&i,&j,&val,5,&top);
			if(val==0)
				result=1;
			else
				result=0;
		}
	}
	else if((i==NUM-2) && (j==NUM-2))
	{
		i=j=NUM-1;
		int val=flag,top;
		Condirect(&i,&j,&val,4,&top);
		if(top)
		{
			result=2;
		}
		else
		{
			val=flag;
			Condirect(&i,&j,&val,4,&top);
			if(val==0)
				result=1;
			else
				result=0;
		}
	}
	
	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			kernel[i][j]=temp[i][j];

	return result;
}

void CBWChessDlg::Calcu_BW()
{
	int nw=0,nb=0;
	int i,j;
	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			if(kernel[i][j]==1)
				nw++;
			else if(kernel[i][j]==2)
				nb++;

	num_black=nb;
	num_white=nw;
}

int CBWChessDlg::IsInPanel(CPoint &pt)
{
	if(pt.x<=m_wXNull || pt.x>=(m_wXNull + NUM*m_wStoneWidth))
		return 0;
	if(pt.y<=m_wYNull || pt.y>=(m_wYNull + NUM*m_wStoneHeight))
		return 0;
	return 1;
}

void CBWChessDlg::ShowNumber(int isTime)
{
	BCount.SetNumber(num_black);
	WCount.SetNumber(num_white);
	if(isTime)
	{
		TimeCount.SetNumber(m_PassedTime);
		TimeCount0.SetNumber(m_PassedTime0);
	}
}

void CBWChessDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==PASSEDTIME)
	{
		if(!m_byColor)
			m_PassedTime++;
		else
			m_PassedTime0++;
		ShowNumber(1);
		if(g_nRunMode == MODE_2PLAYER && !g_nIsNoTimeLimit)
		{
			if((m_PassedTime>=g_nTimeLimit) || (m_PassedTime0>=g_nTimeLimit))
			{
				m_bGameOver=TRUE;
				if(m_TimerOn)
				{
					KillTimer(PASSEDTIME);
					m_TimerOn=0;
				}
				m_pMenu->EnableMenuItem(IDM_HINT,MF_GRAYED);
				m_pMenu->EnableMenuItem(IDM_UNDO,MF_GRAYED);
				m_pMenu->EnableMenuItem(IDM_CANPLACE,MF_GRAYED);

				AddStringToList(0,0,0,(m_PassedTime>=g_nTimeLimit)? 1 : 2);

				PlaySounds(IDSOUND_USERWIN);

				MsgBox((m_PassedTime>=g_nTimeLimit)? IDS_BLACK_LIMIT : IDS_WHITE_LIMIT ,IDS_TITLE_CHINESE);
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CBWChessDlg::OnUndo() 
{
	m_PeekOnce=0;
	if(m_UndoPoint.IsEmpty())
	{
		PlaySounds(IDSOUND_ERROR);
		MsgBox(IDS_CANNOT_UNDO1_CHINESE, IDS_TITLE_CHINESE);
		return;
	}
	if (m_bGameOver)   
		return;

	int c1,c2,i,j,k=0;
	c1=m_UndoPoint.GetTopColor();
	int temp[NUM*NUM];
	m_UndoPoint.pop(temp);
	RemoveStringFromList();
	if(g_nRunMode == MODE_WITH_COMPUTER)
	{
		if(c1==m_byColor)
		{
			while(!m_UndoPoint.IsEmpty())
			{
				c2=m_UndoPoint.GetTopColor();
				RemoveStringFromList();
				if(c1!=c2)
				{
					m_UndoPoint.pop(temp);
					break;
				}
				else
				{
					int again_pop[NUM*NUM];
					m_UndoPoint.pop(again_pop);
				}
			}// end while
		}//end if
	}
	else
	{
		if(m_UndoPoint.IsEmpty())
		{
			if(g_bUserBlack)
				m_byColor=0;
			else
				m_byColor=1;
		}
		else
		{
			m_byColor=m_UndoPoint.GetTopColor ();
		}
	}
	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
		{
			kernel[i][j]=temp[k];
			k++;
		}

	IsEnd(!m_byColor+1);
	if(!m_bGameOver && g_bPeepOften)
		OnCanplace();

	m_HintOnce=0;
	Calcu_BW();
	ShowNumber();
	PlaySounds(IDSOUND_UNDO);
	InvalidateRect(m_Client, TRUE);
	UpdateWindow();
}

void CBWChessDlg::OnHowto() 
{
	CHowToDlg howto(this);
	howto.DoModal();	
}

void CBWChessDlg::duplicate()
{
	int temp[NUM*NUM];
	int i,j,k=0;
	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			temp[k++]=kernel[i][j];
	m_UndoPoint.push(temp,m_byColor);
}

void CBWChessDlg::Place(int *x, int *y,int color,int nSkill)
{
	int mx=0,my=0;
	switch(nSkill)
	{
	case 1:
		{
			switch(rand()%3)
			{
			case 0:
				Walk1(&mx,&my,color);
				break;
			case 1:
				RandGo(&mx,&my,color);
				break;
			case 2:
				MultiGo(&mx,&my,color);
				break;
			}			
		}
		break;
	case 2:
		if(m_Interesting)
		{
			m_Interesting=0;
			RandGo(&mx,&my,color);
		}
		else
			Walk1(&mx,&my,color);
		break;
	case 3:
		if(m_Interesting)
		{
			m_Interesting=0;
			RandGo(&mx,&my,color);
		}
		else
			Walk2(&mx,&my,color);
		break;
	}//end switch
	*x=mx;
	*y=my;
}

void CBWChessDlg::RandGo(int *x, int *y, int color)
{
	time_t  time1,k;
	int temp,num;
	int tx,ty;
	
	k=time(&time1);
	srand((int)k);
	if(color==1)
		temp=wsp.Len();
	else
		temp=bsp.Len();
	num=rand() % temp;
	do
	{
		if(color==1)
			wsp.pop(&tx,&ty);
		else
			bsp.pop(&tx,&ty);
		num--;
	}
	while(num>=0);
	*x=tx;
	*y=ty;
}

void CBWChessDlg::OnBest() 
{
	CBestDlg bestDlg;
	bestDlg.DoModal();	
}

void CBWChessDlg::OnCancel() 
{
}

void CBWChessDlg::OnOK() 
{
}

void CBWChessDlg::OnHint() 
{
	const int HINTSIZE=7;
	if (m_bGameOver)  
		return;
	if(m_HintOnce)
		return;
	if(g_nRunMode == MODE_2PLAYER)
	{
		if(((m_HintTime0>=g_nCanHintTimeW) && m_byColor) ||
			((m_HintTime1>=g_nCanHintTimeB) && !m_byColor))
		{
			CString str1,str2;
			TCHAR s[200];
			str1.LoadString(IDS_MORETHANTHREE_CHINESE);
			str2.LoadString(IDS_TITLE_CHINESE);
			if(m_HintTime0>=g_nCanHintTimeW)
				wsprintf(s,str1.GetBuffer(256),g_nCanHintTimeW);
			else
				wsprintf(s,str1.GetBuffer(256),g_nCanHintTimeB);
			CString str(s);
			MsgBox(str,str2);
			return;
		}
		if(m_byColor)
			m_HintTime0++;
		else
			m_HintTime1++;
	}
	else //g_nRunMode == MODE_WITHCOMPUTER
	{
		if(m_HintTime0>=g_nCanHintTimeW || m_HintTime1>=g_nCanHintTimeB)
		{
			CString str1,str2;
			TCHAR s[200];
			str1.LoadString(IDS_MORETHANTHREE_CHINESE);
			str2.LoadString(IDS_TITLE_CHINESE);
			if(m_HintTime0>=g_nCanHintTimeW)
				wsprintf(s,str1.GetBuffer(256),g_nCanHintTimeW);
			else
				wsprintf(s,str1.GetBuffer(256),g_nCanHintTimeB);
			CString str(s);
			MsgBox(str,str2);
			return;
		}
		else
		{
			if(m_byColor)
				m_HintTime0++;
			else
				m_HintTime1++;
		}
	}

	int px,py;
	Walk2(&py,&px,!m_byColor+1);
	x1 = px*m_wStoneWidth + m_wXNull-HINTSIZE + m_wStoneWidth / 2;
	y1 = py*m_wStoneHeight + m_wYNull-HINTSIZE + m_wStoneHeight / 2;
	x2 = px*m_wStoneWidth + m_wXNull+HINTSIZE + m_wStoneWidth / 2;
	y2 = py*m_wStoneHeight + m_wYNull+HINTSIZE + m_wStoneHeight / 2;
	CClientDC dc(this);
	COLORREF crColor = m_byColor ? RGB(255,255,255) : RGB(0,0,0);
	CPen pen(PS_SOLID, 2, crColor);
	CPen *pOldPen = dc.SelectObject(&pen);	

	dc.MoveTo(x1, y1);
	dc.LineTo(x2, y1);
	dc.LineTo(x2, y2);
	dc.LineTo(x1, y2);
	dc.LineTo(x1, y1);
	dc.LineTo(x2, y2);
	dc.MoveTo(x2, y1);
	dc.LineTo(x1, y2);
	dc.SelectObject(pOldPen);

	m_HintOnce=1;
}

void CBWChessDlg::MoveCursor(int x, int y)
{
	if(!g_bMovePlace)
	{
//		SetCursorPos(x,y);
		return;
	}
	CPoint pt;

	GetCursorPos(&pt);

	int m,n;
	int sleep_interval=2;

	m=pt.x ;
	n=pt.y ;

	if(m >x)
	{
		while(m>x)
		{
			m-=g_nMoveSpeeds;
			Sleep(sleep_interval);
			SetCursorPos(m,n);
		}
	}
	else if(m<x)
	{
		while(m<x)
		{
			m+=g_nMoveSpeeds;
			Sleep(sleep_interval);
			SetCursorPos(m,n);
		}
	}

	if(n >y)
	{
		while(n>y)
		{
			n-=g_nMoveSpeeds;
			Sleep(sleep_interval);
			SetCursorPos(m,n);
		}
	}
	else if(n < y)
	{
		while(n < y)
		{
			n+=g_nMoveSpeeds;
			Sleep(sleep_interval);
			SetCursorPos(m,n);
		}
	}
}
/*
void CBWChessDlg::PaintWelcome(CDC *dc)
{
	return;
	CFont *OldFont;
	dc->SetBkMode(TRANSPARENT);
	{
		CFont NewFont;
		LOGFONT lf;
		GetFont()->GetLogFont(&lf);
		lf.lfWeight = FW_BOLD;
		lf.lfItalic	   = TRUE;
		lf.lfHeight *=5;
		lf.lfHeight /=2;
		NewFont.CreateFontIndirect(&lf);

		OldFont=dc->SelectObject(&NewFont);
		CString str;
		str.LoadString(IDS_EDITION);
		CRect rect(m_wXNull,m_wYNull+2*m_wStoneHeight,m_wXNull+NUM*m_wStoneWidth,m_wYNull+4*m_wStoneHeight);

		dc->SetTextColor(RGB(0,0,255));
		dc->DrawText(str,str.GetLength(),&rect, DT_CENTER | DT_SINGLELINE);
	}
	{
		CFont NewFont;
		LOGFONT lf;
		GetFont()->GetLogFont(&lf);
		lf.lfWeight = 600;
		lf.lfItalic	   = FALSE;
		lf.lfHeight *=3;
		lf.lfHeight /=2;
		strcpy(lf.lfFaceName,"楷体_GB2312");
		NewFont.CreateFontIndirect(&lf);

		dc->SelectObject(&NewFont);
		CString str;
		str.LoadString(IDS_AUTHOR);
		CRect rect(m_wXNull,m_wYNull+4*m_wStoneHeight,m_wXNull+NUM*m_wStoneWidth,m_wYNull+5*m_wStoneHeight);

		dc->SetTextColor(RGB(255,255,200));//(RGB(67,235,119));
		dc->DrawText(str,str.GetLength(),&rect, DT_CENTER | DT_SINGLELINE);

	}
	dc->SelectObject(OldFont);
}
*/
int CBWChessDlg::Judge(int x, int y, const int flag)
{
	int fv=flag;
	int op=flag%2+1;
	int dir=0;

	switch(WhereAmI(x,y))
	{
	case 0://顶点
		{
			if(x==0 && y==0)
			{
				int ppp;
				if(fv==1)
					ppp=bsp.IsThere (0,0);
				else
					ppp=wsp.IsThere (0,0);
				if(ppp)
					return 1000;
				int color,rt;
				color=fv;
				rt=StyleSpecial(1,&color);
				if(rt==1)
				{
					if(color==1)
						return 530;//----newly add
					else
						return 1000;
				}

				if(!kernel[0][NUM-1])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,1,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,1,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				////////////////
				if(!kernel[NUM-1][0])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,3,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,3,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				///////////////////
				if(!kernel[NUM-1][NUM-1])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,7,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,7,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				////////////////////
			}
			else if(x==0 && y==NUM-1)
			{
				int ppp;
				if(fv==1)
					ppp=bsp.IsThere (0,NUM-1);
				else
					ppp=wsp.IsThere (0,NUM-1);
				if(ppp)
					return 1000;
				int color,rt;
				color=fv;
				rt=StyleSpecial(2,&color);
				if(rt==1)
				{
					if(color==1)
						return 530;//----newly add
					else
						return 1000;
				}

				if(!kernel[0][0])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,0,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,0,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				////////////////
				if(!kernel[NUM-1][0])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,6,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,6,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				///////////////////
				if(!kernel[NUM-1][NUM-1])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,3,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,3,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				////////////////////

			}
			else if(x==NUM-1 && y==0)
			{
				int ppp;
				if(fv==1)
					ppp=bsp.IsThere (NUM-1,0);
				else
					ppp=wsp.IsThere (NUM-1,0);
				if(ppp)
					return 1000;
				int color,rt;
				color=fv;
				rt=StyleSpecial(3,&color);
				if(rt==1)
				{
					if(color==1)
						return 530;//----newly add
					else
						return 1000;
				}

				if(!kernel[0][NUM-1])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,5,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,5,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				////////////////
				if(!kernel[0][0])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,2,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,2,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				///////////////////
				if(!kernel[NUM-1][NUM-1])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,1,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,1,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				////////////////////

			}
			else //x==NUM-1 && y==NUM-1
			{
				int ppp;
				if(fv==1)
					ppp=bsp.IsThere (NUM-1,NUM-1);
				else
					ppp=wsp.IsThere (NUM-1,NUM-1);
				if(ppp)
					return 1000;
				int color,rt;
				color=fv;
				rt=StyleSpecial(4,&color);
				if(rt==1)
				{
					if(color==1)
						return 530;//----newly add
					else
						return 1000;
				}

				if(!kernel[0][NUM-1])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,2,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,2,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				////////////////
				if(!kernel[NUM-1][0])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,0,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,0,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				///////////////////
				if(!kernel[0][0])//is none
				{
					int fr,x1,y1,top,num;
					fr=fv;
					x1=x,y1=y;
					num=Condirect(&x1,&y1,&fr,4,&top);//toward right
					if(fr==2 && (num<NUM-2))
					{
						int numr;
						fr=fv;
						numr=Condirect(&x1,&y1,&fr,4,&top);
						if(fr==1 && (numr+num==NUM-2))
							return 995;
					}
					return 1000;
				}
				else
					return 1000;
				////////////////////

			}
			return 1000;//---1
		}// case 0
		break;
	case 2://左边
	case 3://右边 the same
		dir=2;
	case 1://上边
	case 4://下边 the same
		{
			int il=x,jl=y,ir=x,jr=y;
			int vall=flag,valr=flag;
			int istopl=0,istopr=0;
			int numl=0,numr=0;
			
			if(IsDanger(x,y))
			{
				//int fff=0;
				if(x==1 || x==NUM-2)
				{
					if(x==1)
					{
						if(y==0)
						{
							if(kernel[1][1]==op && !kernel[0][0])
							{
								int xd=x,yd=y;
								int ff=fv;
								int topf=0;
								int num=Condirect(&xd,&yd,&ff,1,&topf);
								if(!topf)
								{
									ff=fv;
									num=Condirect(&xd,&yd,&ff,1,&topf);
									if(ff)
										return 460;//----11
								}
							}
						}
						else//x==1,y==NUM-1
						{
							if(kernel[1][NUM-2]==op && !kernel[0][NUM-1])
							{
								int xd=x,yd=y;
								int ff=fv;
								int topf=0;
								int num=Condirect(&xd,&yd,&ff,0,&topf);
								if(!topf)
								{
									ff=fv;
									num=Condirect(&xd,&yd,&ff,0,&topf);
									if(ff)
										return 460;//----11
								}
							}
						}
					}
					else//x==NUM-2
					{
						if(y==0)
						{
							if(kernel[NUM-2][1]==op && !kernel[NUM-1][0])
							{
								int xd=x,yd=y;
								int ff=fv;
								int topf=0;
								int num=Condirect(&xd,&yd,&ff,1,&topf);
								if(!topf)
								{
									ff=fv;
									num=Condirect(&xd,&yd,&ff,1,&topf);
									if(ff)
										return 460;//----11
								}
							}
						}
						else//x==NUM-2,y==NUM-1
						{
							if(kernel[NUM-2][NUM-2]==op && !kernel[NUM-1][NUM-1])
							{
								int xd=x,yd=y;
								int ff=fv;
								int topf=0;
								int num=Condirect(&xd,&yd,&ff,0,&topf);
								if(!topf)
								{
									ff=fv;
									num=Condirect(&xd,&yd,&ff,0,&topf);
									if(ff)
										return 460;//----11
								}
							}
						}
					}//end x!=1 and NUM-2
				}
				if(y==1 || y==NUM-2)
				{
					if(y==1)
					{
						if(x==0)
						{
							if(kernel[1][1]==op && !kernel[0][0])
							{
								int xd=x,yd=y;
								int ff=fv;
								int topf=0;
								int num=Condirect(&xd,&yd,&ff,3,&topf);
								if(!topf)
								{
									ff=fv;
									num=Condirect(&xd,&yd,&ff,3,&topf);
									if(ff)
										return 460;//----11
								}
							}
						}
						else//x==NUM-1,y==1
						{
							if(kernel[NUM-2][1]==op && !kernel[NUM-1][0])
							{
								int xd=x,yd=y;
								int ff=fv;
								int topf=0;
								int num=Condirect(&xd,&yd,&ff,2,&topf);
								if(!topf)
								{
									ff=fv;
									num=Condirect(&xd,&yd,&ff,2,&topf);
									if(ff)
										return 460;//----11
								}
							}
						}
					}
					else//y==NUM-2
					{
						if(x==0)
						{
							if(kernel[1][NUM-2]==op && !kernel[0][NUM-1])
							{
								int xd=x,yd=y;
								int ff=fv;
								int topf=0;
								int num=Condirect(&xd,&yd,&ff,3,&topf);
								if(!topf)
								{
									ff=fv;
									num=Condirect(&xd,&yd,&ff,3,&topf);
									if(ff)
										return 460;//----11
								}
							}
						}
						else//x==NUM-1,y==NUM-2
						{
							if(kernel[NUM-2][NUM-2]==op && !kernel[NUM-1][NUM-1])
							{
								int xd=x,yd=y;
								int ff=fv;
								int topf=0;
								int num=Condirect(&xd,&yd,&ff,2,&topf);
								if(!topf)
								{
									ff=fv;
									num=Condirect(&xd,&yd,&ff,2,&topf);
									if(ff)
										return 460;//----11
								}
							}
						}
					}
				}
			}
			//not the danger place
			//now find whether is the third place
			if(IsDanger3(x,y))
			{
				if((x==0) && (y==2) && kernel[1][1] && kernel[2][0])
					if((kernel[1][1]==op) && (kernel[2][0]==fv))
						return 460;//-----12
				if((x==0) && (y==NUM-3) && kernel[1][NUM-2] && kernel[2][NUM-1])
					if((kernel[1][NUM-2]==op) && (kernel[2][NUM-1]==fv))
						return 460;//-----12
				if((x==NUM-1) && (y==2) && kernel[NUM-2][1] && kernel[NUM-3][0])
					if((kernel[NUM-2][1]==op) && (kernel[NUM-3][0]==fv))
						return 460;//-----12
				if((x==NUM-1) && (y==NUM-3) && kernel[NUM-2][NUM-2] && kernel[NUM-3][NUM-1])
					if((kernel[NUM-2][NUM-2]==op) && (kernel[NUM-3][NUM-1]==fv))
						return 460;//-----12
				if((x==2) && (y==0) && kernel[1][1] && kernel[0][2])
					if((kernel[1][1]==op) && (kernel[0][2]==fv))
						return 460;//-----12
				if((x==NUM-3) && (y==0) && kernel[NUM-2][1] && kernel[NUM-1][2])
					if((kernel[NUM-2][1]==op) && (kernel[NUM-1][2]==fv))
						return 460;//-----12
				if((x==2) && (y==NUM-1) && kernel[1][NUM-2] && kernel[0][NUM-3])
					if((kernel[1][NUM-2]==op) && (kernel[0][NUM-3]==fv))
						return 460;//-----12
				if((x==NUM-3) && (y==NUM-1) && kernel[NUM-2][NUM-2] && kernel[NUM-1][NUM-3])
					if((kernel[NUM-2][NUM-2]==op) && (kernel[NUM-1][NUM-3]==fv))
						return 460;//-----12
			}
			//not the third place
			//then begin
			numl=Condirect(&il,&jl,&vall,dir,&istopl);//向左
			numr=Condirect(&ir,&jr,&valr,1+dir,&istopr);//向右
			if(vall==0 && valr==0)//both the side are none
			{
				if(istopl==1 && istopr==1)//both to the top
				{
					if(IsDanger(x,y))
						return 595;//---newly add
					return 700;//----13
				}
				else if(istopl==1 && istopr==0)//left to top,right not
				{
					valr=flag;
					Condirect(&ir,&jr,&valr,1+dir,&istopr);
					if(valr==1)//right side is mine
					{
						if(numr==1)
						{
							if(istopr)
							{
								if(IsDanger(x,y))
									return 590;//----65
								else
									return 760;//-----14
							}
							else
								return 560;//----15
						}
						else if(numr==2)
							return 690;//---16
						else 
							return 560;//-----17---newly modified
					}
					else//valr==2,right side is others
					{
						if(numr==1)
						{
							if(istopr)
								return 580;//----18
							else
								return 730;//----19
						}
						else if(numr==2)
						{
							if(numl==1)
								return 460;//----newly add
						}
						return 720;//----20
					}///end search in the right side
				}
				else if(istopl==0 && istopr==1)
				{
					vall=flag;
					Condirect(&il,&jl,&vall,dir,&istopl);
					if(vall==1)//left side is mine
					{
						if(numl==1)
						{
							if(istopl)
							{
								if(IsDanger(x,y))
									return 590;//----65
								else
									return 760;//-----14
							}
							else
								return 560;//----15
						}
						else if(numl==2)
							return 690;//---16
						else
							return 560;//-----17---newly modified
					}
					else//vall==2,left side is others
					{
						if(numl==1)
						{
							if(istopl)
								return 580;//----18
							else
								return 730;//----19
						}
						else if(numl==2)
						{
							if(numr==1)
								return 460;//newly add
						}
						return 720;//----20
					}///end search in the left side
				}
				else if(istopl==0 && istopr==0)//both side are not to top
				{
					vall=valr=flag;
					Condirect(&ir,&jr,&valr,1+dir,&istopr);
					Condirect(&il,&jl,&vall,dir,&istopl);
					if(vall==1 && valr==1)//again both side are mine
					{
						if((numl==1) || (numr==1))
							return 550;//---24
						else
							return 660;//----25
					}
					else if(vall==1 && valr==2)//left are mine,other side are others
					{
						if(numl==1)
							return 570;//----22
						else
							return 670;//----23
					}
					else if(vall==2 && valr==1)
					{
						if(numr==1)
							return 570;//----22
						else
							return 670;//----23
					}
					else if(vall==2 && valr==2)
					{
						return 710;//----21
					}
				}
			}//end both sides are none
			else if(vall==1 && valr==1)//both the side are mine
			{
				int xll=il,yll=jl;
				int xrr=ir,yrr=jr;
				if(istopl==1 && istopr==1)
					return 840;//----26
				if(istopl==0 && istopr==0)
				{
					vall=valr=flag;
					Condirect(&il,&jl,&vall,dir,&istopl);//向左
					Condirect(&ir,&jr,&valr,1+dir,&istopr);//向右

					if(vall==0 && valr==0)//both side are none
					{
						return 970;//----31
					}
					else if(vall==2 && valr==2)//both side are others
					{
						return 920;//----28
					}
					else if(vall==0 && valr==2)
					{
						if(istopr)
							return 510;//----29
						else
						{
							if(IsDanger(xll,yll))
								return 460;//----30
							else
								return 540;//----10
						}
					}
					else if(vall==2 && valr==0)
					{
						if(istopl)
							return 510;//----29
						else
						{
							if(IsDanger(xrr,yrr))
								return 460;//----30
							else
								return 540;//----10
						}
					}
				}
				if(istopl==0 && istopr==1)
				{
					return 940;//------27
				}
				else if(istopl==1 && istopr==0)
				{
					return 940;//------27
				}
			}//end both sides are mine
			else if(vall==2 && valr==2)//both the side are others
			{
				if(istopl==0 && istopr==0)//both others don't reach the top
				{
					vall=valr=flag;
					Condirect(&il,&jl,&vall,dir,&istopl);//向左
					Condirect(&ir,&jr,&valr,1+dir,&istopr);//向右
					
					if(vall==1 && valr==1)
						return 910;//----36
					if(vall==1 && valr==0)
					{
						if(istopl)
							return 870;//---37
						else
						{
							if(!IsDanger(il,jl))
								return 540;//----38
							else
								return 460;//----81
						}
					}
					if(vall==0 && valr==1)
					{
						if(istopr)
							return 870;//---37
						else
						{
							if(!IsDanger(ir,jr))
								return 540;//----38
							else
								return 460;//----81
						}
					}
					return 820;//-----39
				}
				else if(istopl==1 && istopr==1)
				{
					return 830;//----32
				}
				else if(istopl==0 && istopr==1)
				{
					vall=flag;
					int ll=Condirect(&il,&jl,&vall,dir,&istopl);

					if(vall==1)
					{
						if(istopl==1)
							return 880;//----33
						else
						{
							vall=flag;
							Condirect(&il,&jl,&vall,dir,&istopl);
							if(vall==2)
								return 950;//----34
							else
								return 510;//----35
						}
					}
					else//vall==0
					{
						if(istopl==1 && ll==1)
							return 995;//----newly add
						else
							return 815;//----94
					}
				}
				else if(istopl==1 && istopr==0)
				{
					valr=flag;
					int rr=Condirect(&ir,&jr,&valr,1+dir,&istopr);

					if(valr==1)
					{
						if(istopr==1)
							return 880;//----33
						else
						{
							valr=flag;
							Condirect(&ir,&jr,&valr,1+dir,&istopr);
							if(valr==2)
								return 950;//----34
							else
								return 510;//----35
						}
					}
					else
					{
						if(rr==1 && istopr==1)
							return 995;//----newly add
						else
							return 815;//-----94
					}
				}
			}//end both sides are others
			else if(vall==1 && valr==2)//left side is mine,right side is others
			{
				if(istopl==0 && istopr==0)
				{
					vall=valr=flag;
					int ll=Condirect(&il,&jl,&vall,dir,&istopl);//向左
					Condirect(&ir,&jr,&valr,1+dir,&istopr);//向右
					if(vall==0 && valr==1)
					{
						if(istopr)
							return 940;//-----57
						else
						{
							valr=flag;
							Condirect(&ir,&jr,&valr,1+dir,&istopr);
							if(valr==2)
							{
								if(ll==1)
									return 460;//----58
								else
									return 540;//----92
							}
							else
								return 980;//-----59
						}
					}
					else if(vall==2 && valr==0)
					{
						if(istopl)
							return 990;//-----60
						else
						{
							vall=flag;
							Condirect(&il,&jl,&vall,dir,&istopl);
							if(vall==1)
								return 610;//-----61
							else
								return 980;//-----62
						}
					}
					else if(vall==0 && valr==0)
					{
						if(istopl && ll==1)
							return 460;
						else
							return 520;//-----56
					}
					else if(vall==2 && valr==1)
					{
						if(istopr)
							return 930;//----63
						else
							return 540;//-----64
					}
				}
				else if(istopl==1 && istopr==1)
				{
					return 860;//-------52
				}
				else if(istopl==0 && istopr==1)
				{
					vall=flag;
					Condirect(&il,&jl,&vall,dir,&istopl);

					if(vall==2)
						return 990;//-----55
					else
						return 500;//----54
				}
				else if(istopl==1 && istopr==0)
				{
					return 870;//-----53
				}
			}//end left side is mine,right side is others
			else if(vall==1 && valr==0)//left side is mine, right side are none
			{
				if(istopl==0 && istopr==0)
				{
					vall=valr=flag;
					Condirect(&il,&jl,&vall,dir,&istopl);//向左
					Condirect(&ir,&jr,&valr,1+dir,&istopr);//向右
					if(vall==0 && valr==1)
					{
						if(numr==1)
							return 560;//----66
						else
							return 810;//----67
					}
					else if(vall==2 && valr==2)
					{
						if(istopl)
							return 580;//----72
						else
						{
							vall=flag;
							Condirect(&il,&jl,&vall,dir,&istopl);
							if(vall==1)
								return 780;//----73
							else
							{
								if(numr==1)
									return 540;//-----74
								else
									return 750;//-----88
							}
						}
					}
					else if(vall==2 && valr==1)
					{
						if(istopl)
							return 510;//----68
						else
						{
							vall=flag;
							Condirect(&il,&jl,&vall,dir,&istopl);
							if(vall==1)
								return 790;//-----69
							else
							{
								if(numr==1)
									return 770;//----70
								else
									return 540;//-----93
							}
						}
					}
					else if(vall==0 && valr==2)
					{
						return 810;//----71
					}
				}
				else if(istopl==1 && istopr==1)
				{
					return 850;//----40
				}
				else if(istopl==1 && istopr==0)
				{
					return 850;//----45
				}
				else if(istopl==0 && istopr==1)
				{
					vall=flag;
					Condirect(&il,&jl,&vall,dir,&istopl);
					if(vall==0)
						return 810;//----41
					else//others
					{
						if(istopl)
							return 510;//----42
						else
						{
							if(numr==1)
								return 460;//-----44
							vall=flag;
							Condirect(&il,&jl,&vall,dir,&istopl);
							if(vall==1)
								return 800;//----43
							else//none
								return 540;//-----87
						}
					}
				}
			}
			else if(vall==2 && valr==1)//left side is others ,right side are mine
			{
				if(istopl==0 && istopr==0)
				{
					vall=valr=flag;
					Condirect(&il,&jl,&vall,dir,&istopl);//向左
					int rr=Condirect(&ir,&jr,&valr,1+dir,&istopr);//向右
					if(vall==1 && valr==0)
					{
						if(istopl)
							return 940;//-----57
						else
						{
							vall=flag;
							Condirect(&il,&jl,&vall,dir,&istopl);
							if(vall==2)
							{
								if(rr==1)
									return 460;//----58
								else
									return 540;//----92
							}
							else
								return 980;//-----59
						}
					}
					else if(vall==0 && valr==2)
					{
						if(istopr)
							return 990;//-----60
						else
						{
							valr=flag;
							Condirect(&ir,&jr,&valr,1+dir,&istopr);
							if(valr==1)
								return 610;//-----61
							else
								return 980;//-----62
						}
					}
					else if(vall==0 && valr==0)
					{
						if(istopr && rr==1)
							return 460;
						else	
							return 520;//-----56
					}
					else if(vall==1 && valr==2)
					{
						if(istopl)
							return 930;//----63
						else
							return 540;//-----64
					}
				}
				else if(istopl==1 && istopr==1)
				{
					return 860;//-------52
				}
				else if(istopl==1 && istopr==0)
				{
					valr=flag;
					Condirect(&ir,&jr,&valr,1+dir,&istopr);

					if(valr==2)
						return 990;//-----55
					else
						return 500;//----54
				}
				else if(istopl==0 && istopr==1)
				{
					return 870;//-----53
				}
			}
			else if(vall==2 && valr==0)//left side is others, right side are none
			{
				if(istopl==0 && istopr==0)
				{
					vall=valr=flag;
					Condirect(&il,&jl,&vall,dir,&istopl);//向左
					Condirect(&ir,&jr,&valr,1+dir,&istopr);//向右
					if(vall==1 && valr==1)
					{
						if(istopr)
							return 760;//-----78
						else
						{
							valr=flag;
							Condirect(&ir,&jr,&valr,1+dir,&istopr);
							if(valr==2)
							{
								if(numr==1)
									return 770;//-----79
								else
									return 540;//----77
							}
							if(valr==0)
							{
								if(numr==1)
									return 560;//---80
								else
									return 490;//----89
							}
						}
						if(istopl)
							return 760;//-----78
						else
						{
							vall=flag;
							Condirect(&il,&jl,&vall,dir,&istopl);
							if(vall==2)
							{
								if(numl==1)
									return 770;//-----79
								else
									return 540;//----77
							}
							if(vall==0)
							{
								if(numl==1)
									return 560;//---80
								else
									return 490;//----89
							}
						}
					}
					else if(vall==0 && valr==2)
					{
						if(numr==1)
							return 540;//----82
						else
							return 740;//----90
					}
					else if(vall==0 && valr==1)
					{
						if(numr==1)
							return 770;//----75
						else
							return 540;//----76
					}
					else if(vall==1 && valr==2)
					{
						if(istopl)
							return 760;//---83
						else
						{
							vall=flag;
							Condirect(&il,&jl,&vall,dir,&istopl);
							if(vall==2)
								return 540;//----84
							else
								return 960;//----85
						}
					}
				}
				else if(istopl==1 && istopr==1)
				{
					return 500;//---46
				}
				else if(istopl==1 && istopr==0)
				{
					return 500;//----51
				}
				else if(istopl==0 && istopr==1)
				{
					vall=flag;
					Condirect(&il,&jl,&vall,dir,&istopl);
					if(vall==1)
					{
						if(istopl==1)
							return 870;//----48
						else
						{
							vall=flag;
							int lll=Condirect(&il,&jl,&vall,dir,&istopl);
							if(vall==2)
							{
								if(IsDanger(x,y))
									return 460;//----91
								else
									return 540;//----49
							}
							else//vall==0
							{
								if(lll==1 && !istopl)
								{
									vall=flag;
									Condirect(&il,&jl,&vall,dir,&istopl);
									if(vall==1)
										return 550;//---86
								}
								else 
									return 960;//----50
							}
						}
					}
					else
					{
						if(numr==1)
							return 460;//-----undefinited
						else
							return 530;//---47
					}
				}
			}
			else if(vall==0 && valr==1)//left side is 0, right side are mine
			{
				if(istopl==0 && istopr==0)
				{
					vall=valr=flag;
					Condirect(&il,&jl,&vall,dir,&istopl);//向左
					Condirect(&ir,&jr,&valr,1+dir,&istopr);//向右
					if(vall==1 && valr==0)
					{
						if(numl==1)
							return 560;//----66
						else
							return 810;//----67
					}
					else if(vall==2 && valr==2)
					{
						if(istopr)
							return 580;//----72
						else
						{
							valr=flag;
							Condirect(&ir,&jr,&valr,1+dir,&istopr);
							if(valr==1)
								return 780;//----73
							else
							{
								if(numl==1)
									return 540;//-----74
								else
									return 750;//-----88
							}
						}
					}
					else if(vall==1 && valr==2)
					{
						if(istopr)
							return 510;//----68
						else
						{
							valr=flag;
							Condirect(&ir,&jr,&valr,1+dir,&istopr);
							if(valr==1)
								return 790;//-----69
							else
							{
								if(numl==1)
									return 770;//----70
								else
									return 540;//-----93
							}
						}
					}
					else if(vall==2 && valr==0)
					{
						return 810;//----71
					}
				}
				else if(istopl==1 && istopr==1)
				{
					return 850;//----40
				}
				else if(istopl==0 && istopr==1)
				{
					return 850;//----45
				}
				else if(istopl==1 && istopr==0)
				{
					valr=flag;
					Condirect(&ir,&jr,&valr,1+dir,&istopr);
					if(valr==0)
						return 810;//----41
					else
					{
						if(istopr)
							return 510;//----42
						else
						{
							if(numl==1)
								return 460;//-----44

							valr=flag;
							Condirect(&ir,&jr,&valr,1+dir,&istopr);
							if(valr==1)
								return 800;//----43
							else
								return 540;//-----87
						}
					}
				}
			}
			else if(vall==0 && valr==2)//left side is none, right side are others
			{
				if(istopl==0 && istopr==0)
				{
					vall=valr=flag;
					Condirect(&il,&jl,&vall,dir,&istopl);//向左
					Condirect(&ir,&jr,&valr,1+dir,&istopr);//向右
					if(vall==1 && valr==1)
					{
						if(istopl)
							return 760;//-----78
						else
						{
							vall=flag;
							Condirect(&il,&jl,&vall,dir,&istopl);
							if(vall==2)
							{
								if(numl==1)
									return 770;//-----79
								else
									return 540;//----77
							}
							if(vall==0)
							{
								if(numl==1)
									return 560;//---80
								else
									return 490;//----89
							}
						}
						if(istopr)
							return 760;//-----78
						else
						{
							valr=flag;
							Condirect(&ir,&jr,&valr,1+dir,&istopr);
							if(valr==2)
							{
								if(numr==1)
									return 770;//-----79
								else
									return 540;//----77
							}
							if(valr==0)
							{
								if(numr==1)
									return 560;//---80
								else
									return 490;//----89
							}
						}
					}
					else if(vall==2 && valr==0)
					{
						if(numl==1)
							return 540;//----82
						else
							return 740;//----90
					}
					else if(vall==1 && valr==0)
					{
						if(numl==1)
							return 770;//----75
						else
							return 540;//----76
					}
					else if(vall==2 && valr==1)
					{
						if(istopr)
							return 760;//---83
						else
						{
							valr=flag;
							Condirect(&ir,&jr,&valr,1+dir,&istopr);
							if(valr==2)
								return 540;//----84
							else
								return 960;//----85
						}
					}
				}
				else if(istopl==1 && istopr==1)
				{
					return 500;//---46
				}
				else if(istopl==0 && istopr==1)
				{
					return 500;//----51
				}
				else if(istopl==1 && istopr==0)
				{
					valr=flag;
					Condirect(&ir,&jr,&valr,1+dir,&istopr);
					if(valr==1)
					{
						if(istopr==1)
							return 870;//----48
						else
						{
							valr=flag;
							int rrr=Condirect(&ir,&jr,&valr,1+dir,&istopr);
							if(valr==2)
							{
								if(IsDanger(x,y))
									return 460;//----91
								else
									return 540;//----49
							}
							else//valr==0
							{
								if(rrr==1 && !istopr)
								{
									valr=flag;
									Condirect(&ir,&jr,&valr,1+dir,&istopr);
									if(valr==1)
										return 550;//---86
								}
								else
									return 960;//----50
							}
						}
					}
					else
					{
						if(numl==1)
							return 460;//-----undefinited
						else
							return 530;//---47
					}
				}
			}
		}//end case right,left,top,bottom
		break;
	case 5://上面第二排4格
		{
			int i,j;
			int fff=0;
			int m=0,n=0,h=0;//两票或两票以上为5,or equal 4
			//prepare ,duplicate kernel
			int temp[NUM][NUM];
			int p,q;
			//first let me look for the danger place
			if(kernel[0][0]==0)
			{
				if(kernel[1][1]==op)
				{
					if(IsEatDanger(x,y,fv,0,0))
						return 460;//-------newly add
				}
			}
			if(kernel[0][NUM-1]==0)
			{
				if(kernel[1][NUM-2]==op)
				{
					if(IsEatDanger(x,y,fv,0,1))
						return 460;//-------newly add
				}
			}

			for(p=0;p<NUM;p++)
				for(q=0;q<NUM;q++)
					temp[p][q]=kernel[p][q];
			BtoW(x,y,fv);
			//end prepare

			i=x,j=y;
			//斜向左下
			if(kernel[i-1][j+1]==0)
			{
				for(fff=0,i=x+1,j=y-1;j>=0;i++,j--)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					m=0;//---7
				else
					m=1;//---6
			}//end if
			else
				m=1;

			i=x,j=y;
			//斜向右下
			if(kernel[i-1][j-1]==0)
			{
				for(fff=0,i=x+1,j=y+1;j<NUM;i++,j++)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					n=0;//---7
				else
					n=1;//---6
			}//end if
			else
				n=1;

			i=x,j=y;
			//垂直向下
			if(kernel[i-1][j]==0)
			{
				for(fff=0,i=x+1,j=y;i<NUM;i++)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					h=0;//---7
				else
					h=1;//---6
			}//end if
			else
				h=1;
			//copy back,temp->kernel
			for(p=0;p<NUM;p++)
				for(q=0;q<NUM;q++)
					kernel[p][q]=temp[p][q];
			//end copy

			if(m && n && h)
				return 620;//---4
			else
				return 600;//---3
		}
		// case 5
		break;
	case 6://左面第二排4格
		{
			int i,j;
			int fff=0;
			int m=0,n=0,h=0;//两票或两票以上为5,or equal 4
			//prepare ,duplicate kernel
			int temp[NUM][NUM];
			int p,q;

			if(kernel[0][0]==0)
			{
				if(kernel[1][1]==op)
				{
					if(IsEatDanger(x,y,fv,1,0))
						return 460;//-------newly add
				}
			}
			if(kernel[NUM-1][0]==0)
			{
				if(kernel[NUM-2][1]==op)
				{
					if(IsEatDanger(x,y,fv,1,1))
						return 460;//-------newly add
				}
			}

			for(p=0;p<NUM;p++)
				for(q=0;q<NUM;q++)
					temp[p][q]=kernel[p][q];
			BtoW(x,y,fv);
			//end prepare

			i=x,j=y;
			//斜向右下
			if(kernel[i-1][j-1]==0)
			{
				for(fff=0,i=x+1,j=y+1;i<NUM;i++,j++)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					m=0;//---7
				else
					m=1;//---6
			}//end if
			else
				m=1;

			i=x,j=y;
			//斜向右上
			if(kernel[i+1][j-1]==0)
			{
				for(fff=0,i=x-1,j=y+1;i>=0;i--,j++)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					n=0;//---7
				else
					n=1;//---6
			}//end if
			else
				n=1;

			i=x,j=y;
			//水平向右
			if(kernel[i][j-1]==0)
			{
				for(fff=0,i=x,j=y+1;j<NUM;j++)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					h=0;//---7
				else
					h=1;//---6
			}//end if
			else
				h=1;
			//copy back,temp->kernel
			for(p=0;p<NUM;p++)
				for(q=0;q<NUM;q++)
					kernel[p][q]=temp[p][q];
			//end copy

			if(m && n && h)
				return 620;//---4
			else
				return 600;//---3
		}// case 6
		break;
	case 7://右面第二排4格
		{
			int i,j;
			int fff=0;
			int m=0,n=0,h=0;//两票或两票以上为5,or equal 4
			//prepare ,duplicate kernel
			int temp[NUM][NUM];
			int p,q;

			if(kernel[0][NUM-1]==0)
			{
				if(kernel[1][NUM-2]==op)
				{
					if(IsEatDanger(x,y,fv,1,0))
						return 460;//-------newly add
				}
			}
			if(kernel[NUM-1][NUM-1]==0)
			{
				if(kernel[NUM-2][NUM-2]==op)
				{
					if(IsEatDanger(x,y,fv,1,1))
						return 460;//-------newly add
				}
			}

			for(p=0;p<NUM;p++)
				for(q=0;q<NUM;q++)
					temp[p][q]=kernel[p][q];
			BtoW(x,y,fv);
			//end prepare

			i=x,j=y;
			//斜向左下
			if(kernel[i-1][j+1]==0)
			{
				for(fff=0,i=x+1,j=y-1;i<NUM;i++,j--)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					m=0;//---7
				else
					m=1;//---6
			}//end if
			else
				m=1;

			i=x,j=y;
			//斜向左上
			if(kernel[i+1][j+1]==0)
			{
				for(fff=0,i=x-1,j=y-1;i>=0;i--,j--)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					n=0;//---7
				else
					n=1;//---6
			}//end if
			else
				n=1;

			i=x,j=y;
			//水平向左
			if(kernel[i][j+1]==0)
			{
				for(fff=0,i=x,j=y-1;j>=0;j--)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					h=0;//---7
				else
					h=1;//---6
			}//end if
			else
				h=1;
			//copy back,temp->kernel
			for(p=0;p<NUM;p++)
				for(q=0;q<NUM;q++)
					kernel[p][q]=temp[p][q];
			//end copy

			if(m && n && h)
				return 620;//---4
			else
				return 600;//---3
		}// case 7
		break;
	case 8://下面第二排4格
		{
			int i,j;
			int fff=0;
			int m=0,n=0,h=0;//两票或两票以上为5,or equal 4
			//prepare ,duplicate kernel
			int temp[NUM][NUM];
			int p,q;

			if(kernel[NUM-1][0]==0)
			{
				if(kernel[NUM-2][1]==op)
				{
					if(IsEatDanger(x,y,fv,0,0))
						return 460;//-------newly add
				}
			}
			if(kernel[NUM-1][NUM-1]==0)
			{
				if(kernel[NUM-2][NUM-2]==op)
				{
					if(IsEatDanger(x,y,fv,0,1))
						return 460;//-------newly add
				}
			}

			for(p=0;p<NUM;p++)
				for(q=0;q<NUM;q++)
					temp[p][q]=kernel[p][q];
			BtoW(x,y,fv);
			//end prepare

			i=x,j=y;
			//斜向左上
			if(kernel[i+1][j+1]==0)
			{
				for(fff=0,i=x-1,j=y-1;j>=0;i--,j--)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					m=0;//---7
				else
					m=1;//---6
			}//end if
			else
				m=1;

			i=x,j=y;
			//斜向右上
			if(kernel[i+1][j-1]==0)
			{
				for(fff=0,i=x-1,j=y+1;j<NUM;i--,j++)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					n=0;//---7
				else
					n=1;//---6
			}//end if
			else
				n=1;

			i=x,j=y;
			//垂直向上
			if(kernel[i+1][j]==0)
			{
				for(fff=0,i=x-1,j=y;i>=0;i--)
				{
					if(kernel[i][j]==0)
						break;
					if(kernel[i][j]==op)
					{
						fff=1;
						break;
					}
				}//end for
				if(fff==1)
					h=0;//---7
				else
					h=1;//---6
			}//end if
			else
				h=1;
			//copy back,temp->kernel
			for(p=0;p<NUM;p++)
				for(q=0;q<NUM;q++)
					kernel[p][q]=temp[p][q];
			//end copy

			if(m && n && h)
				return 620;//---4
			else
				return 600;//---3
		}
		// case 8
		break;
	case 9://中间16格
		{
			//还可以增加算法
			int num=0;
			num=Imitate(x,y,fv);

			return (630+num);//----2
		}// case 9
		break;
	case 10://危险的4格
		{
			//还可以增加算法
			int i=x,j=y;
			int value;
			int dir2=0;

			if(i==1 && j==1)
			{
				dir2=1;
				value=kernel[0][0];
			}
			else if(i==1 && (j==NUM-2))
			{
				dir2=2;
				value=kernel[0][NUM-1];
			}
			else if((i==NUM-2) && j==1)
			{
				dir2=3;
				value=kernel[NUM-1][0];
			}
			else
			{
				dir2=4;
				value=kernel[NUM-1][NUM-1];
			}

			if(value==1)
				return 900;//----5
			else if(value==2)
			{
				int results=ToEnd(i,j,fv);
				if(results==1)
					return 470;//----6
				else
					return 890;//----7
			}
			else//no chess in the top
			{
				int results=ToEnd(i,j,fv);
				if(results==0)
				{
					int r0,co;
					co=fv;
					r0=StyleSpecial(dir2,&co);
					if(r0==0)
						return 460;//----9
					else if(r0==2)
						return 480;//---newly add
					else
					{
						if(co==1)
							return 460;//---newly add
						else
							return 490;
					}
				}
				else
					return 480;//----8
			}
			
		}// case 10
		break;
	default:
		break;
	}//end switch

	return 0;//return marks
	
}

int CBWChessDlg::IsDanger3(int x, int y)//whether the point is the third or not
{
	if((x==0 || x==NUM-1) && (y==2 || y==NUM-3))
		return 1;
	if((y==0 || y==NUM-1) && (x==2 || x==NUM-3))
		return 1;
	return 0;

}

void CBWChessDlg::OnCanplace() 
{
	if (m_bGameOver)     
		return;
	if(m_PeekOnce)
		return;

	int px,py;
	int xx1,yy1;
	int length,hy;
	CClientDC dc(this);
//	COLORREF crColor = m_byColor ? RGB(255,255,255) : RGB(0,0,0);
//	CPen pen(PS_SOLID, 1, crColor);
//	CPen *pOldPen = dc.SelectObject(&pen);
	if(m_byColor)
		length=wsp.isempty();
	else
		length=bsp.isempty();
	if(length)
		return;

	do
	{
		if(m_byColor)
			length=wsp.GetNextPos(&py,&px,&hy);
		else
			length=bsp.GetNextPos(&py,&px,&hy);
		xx1 = px*m_wStoneWidth + m_wXNull;//-4 + m_cxGrid / 2;
		yy1 = py*m_wStoneHeight + m_wYNull;//-4 + m_cyGrid / 2;
		CPoint ptt(xx1,yy1);
		if(m_byColor)
			m_pDibWGo->Display (&dc,ptt);
		else
			m_pDibBGo->Display (&dc,ptt);
	}
	while(length);
	if(m_byColor)
		wsp.CopyBackIndex();
	else
		bsp.CopyBackIndex();

	m_PeekOnce=1;
}

int CBWChessDlg::IsAllEatup(int x, int y, int flag)
{
	int temp[NUM][NUM];
	int i,j;
	int nb,nw;
	int result;

	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			temp[i][j]=kernel[i][j];
	Calcu_BW();
	nb=num_black;
	nw=num_white;

	BtoW(x,y,flag);
	Calcu_BW();
	if(num_black && num_white)
		result=0;
	else
		result=1;

	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			kernel[i][j]=temp[i][j];
	num_black=nb;
	num_white=nw;
	return result;
}

void CBWChessDlg::Walk2(int *x1, int *y1, int flag)
{
	int i,j;
	int result;
	int tempmark=-2;
	int fv=flag;
	int temp,temp2;
	int tm;

	do
	{
		if(fv==1)
			result=wsp.GetNextPos(&i,&j,&temp);
		else
			result=bsp.GetNextPos(&i,&j,&temp);
		////i,j即可以放的坐标
		if(IsAllEatup(i,j,fv))//先不考虑
		{
			*x1=i;
			*y1=j;
			return;
		}
		tempmark=Judge(i,j,fv);
		temp2=Imitate(i,j,fv)+10*tempmark;
		if(fv==1)
			wsp.SetMarks (temp2);
		else
			bsp.SetMarks (temp2);
	}
	while(result);

	if(fv==1)
		wsp.Sort();
	else
		bsp.Sort();

	int num=0;
	int iflow=0;
	int is960=0;//?
	do
	{
		num++;
		if(fv==1)
			result=wsp.GetNextPos(&i,&j,&tm);
		else
			result=bsp.GetNextPos(&i,&j,&tm);
		if((tm>9500) && (tm<10000))
		{
			is960=1;
			break;
		}
		if(tm>6100)//the middle mark
		{
			int re;
			if(fv==1)//whether the other can go
				re=bsp.IsThere (i,j);
			else
				re=wsp.IsThere (i,j);

			if(re)//other can place there
				break;
		}
		else
		{
			iflow=1;
			break;//also can go on
		}
	}
	while(result);

	if(is960)
	{
		*x1=i;
		*y1=j;
		return;
	}

	if(num==1 || !result)
	{
		if(fv==1)
			wsp.pop (x1,y1);
		else
			bsp.pop (x1,y1);
		return;
	}
	if(num==2 && iflow)
	{
		if(fv==1)
			wsp.pop (x1,y1);
		else
			bsp.pop (x1,y1);
		return;
	}
	if((num>2) && iflow)
	{
		int xx1,yy1;
		int xx2,yy2;
		if(fv==1)
		{
			wsp.pop(&xx1,&yy1);
			wsp.pop(&xx2,&yy2);
		}
		else
		{
			bsp.pop(&xx1,&yy1);
			bsp.pop(&xx2,&yy2);
		}
		int r1,r2;
		r1=OtherCanGo(xx1,yy1,xx2,yy2,fv);
		r2=OtherCanGo(xx2,yy2,xx1,yy1,fv);
		if((r1==r2) || r2)
		{
			*x1=xx1;
			*y1=yy1;
			return;
		}
		else
		{
			*x1=xx2;
			*y1=yy2;
			return;
		}
	}
	
	////other possible
	// I only use the first compare with the last one
	//can add code in here
	{
		int xxx1,yyy1;
		if(fv==1)
			wsp.pop (&xxx1,&yyy1);
		else
			bsp.pop (&xxx1,&yyy1);

		int ss=OtherCanGo(i,j,xxx1,yyy1,flag);
		if(ss)
		{
			*x1=xxx1;
			*y1=yyy1;
			return;
		}
		else
		{
			*x1=i;
			*y1=j;
			return;
		}
	}

//	return 0;
}

int CBWChessDlg::IsEatDanger(int x, int y, int flag, int dir, int rorf)
{
//x,y -->the position of the point
//flag-->the color of the point
//dir: equals 0 or 1.  0 for horizontal,1 for vertical
//rorf: equals 0 or 1.   0 for left or upward,1 for right or downward
//return 1 for can eat the danger point,0 for cannot
	//direction:	0	向左
	//				1	向右		
	//				2	向上
	//				3	向下
	//				4	左上
	//				5	右上
	//				6	左下
	//				7	右下//the Condirection function

	int i,j;
	int top;
	int direction=0;
	int temp[NUM][NUM];

	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			temp[i][j]=kernel[i][j];
	
	BtoW(x,y,flag);
	if(dir==0 && rorf==0)
		direction=0;
	else if(dir==1 && rorf==0)
		direction=2;
	else if(dir==0 && rorf==1)
		direction=1;
	else if(dir==1 && rorf==1)
		direction=3;

	Condirect(&x,&y,&flag,direction,&top);

	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			kernel[i][j]=temp[i][j];

	if(top && (flag==1))
		return 1;
	else
		return 0;
}

//i place at x1,y1.if other can place at x2,y2, then return 1.else return 0
//add: and after i place at x1,y1. i still can place at x2,y2
int CBWChessDlg::OtherCanGo(int x1, int y1, int x2, int y2, int flag)
{
	int temp[NUM][NUM];
	int i,j;
	int op=flag%2+1;

	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			temp[i][j]=kernel[i][j];

	BtoW(x1,y1,flag);
	IsEnd(op);
	
	int r1=0;
	int r2=0;
	if(flag==1)
	{
		r2=wsp.IsThere (x2,y2);
		r1=bsp.IsThere (x2,y2);
	}
	else
	{
		r1=bsp.IsThere (x2,y2);
		r2=wsp.IsThere (x2,y2);
	}

	for(i=0;i<NUM;i++)
		for(j=0;j<NUM;j++)
			kernel[i][j]=temp[i][j];
	IsEnd(op);

	if(flag==1)
	{
		if(r2 && !r1)
			return 1;
	}
	else
	{
		if(r1 && !r2)
			return 1;
	}

	return 0;
}

void CBWChessDlg::MultiGo(int *x, int *y, int color)
{
	int result;
	int m,n;
	int b_x=0,b_y=0;
	int bestmark=-1;
	int tempmark=-1;

	do
	{
		if(color==1)
			wsp.pop (&m,&n);
		else
			bsp.pop (&m,&n);
		tempmark=Imitate(m,n,color);
		if(tempmark>bestmark)
		{
			bestmark=tempmark;
			b_x=m;
			b_y=n;
		}
		if(color==1)
			result=wsp.isempty ();
		else
			result=bsp.isempty ();
	}
	while(!result);
	*x=b_x;
	*y=b_y;
}

//censor whether the chess is like:--*****-
//if so ,return 1, or return 0, return 2 for one is mine and other is others
//flag return the style is mine or others,1 for mine,2 for others
//x indicate which point
int CBWChessDlg::StyleSpecial(int x, int *flag)
{
	int r1=0,r2=0;
	int c1=0,c2=0;
	switch(x)
	{
	case 1:
		{
			int num,m,n,top,fv;
			m=0,n=0;
			fv=*flag;
			num=Condirect(&m,&n,&fv,1,&top);
			if(num==1 && fv==0)
			{
				fv=*flag;
				num=Condirect(&m,&n,&fv,1,&top);
				if(!top)
				{
					c1=fv;
					fv=*flag;
					num=Condirect(&m,&n,&fv,1,&top);
					if(top && (num==1) && (fv==0))
						r1=1;
				}
			}
			/////////////////
			m=0,n=0;
			fv=*flag;
			num=Condirect(&m,&n,&fv,3,&top);
			if(num==1 && fv==0)
			{
				fv=*flag;
				num=Condirect(&m,&n,&fv,3,&top);
				if(!top)
				{
					c2=fv;
					fv=*flag;
					num=Condirect(&m,&n,&fv,3,&top);
					if(top && (num==1) && (fv==0))
						r2=1;
				}
			}
		}
		break;
	case 2:
		{
			int num,m,n,top,fv;
			m=0,n=NUM-1;
			fv=*flag;
			num=Condirect(&m,&n,&fv,0,&top);
			if(num==1 && fv==0)
			{
				fv=*flag;
				num=Condirect(&m,&n,&fv,0,&top);
				if(!top)
				{
					c1=fv;
					fv=*flag;
					num=Condirect(&m,&n,&fv,0,&top);
					if(top && (num==1) && (fv==0))
						r1=1;
				}
			}
			/////////////////
			m=0,n=NUM-1;
			fv=*flag;
			num=Condirect(&m,&n,&fv,3,&top);
			if(num==1 && fv==0)
			{
				fv=*flag;
				num=Condirect(&m,&n,&fv,3,&top);
				if(!top)
				{
					c2=fv;
					fv=*flag;
					num=Condirect(&m,&n,&fv,3,&top);
					if(top && (num==1) && (fv==0))
						r2=1;
				}
			}
		}
		break;
	case 3:
		{
			int num,m,n,top,fv;
			m=NUM-1,n=0;
			fv=*flag;
			num=Condirect(&m,&n,&fv,1,&top);
			if(num==1 && fv==0)
			{
				fv=*flag;
				num=Condirect(&m,&n,&fv,1,&top);
				if(!top)
				{
					c1=fv;
					fv=*flag;
					num=Condirect(&m,&n,&fv,1,&top);
					if(top && (num==1) && (fv==0))
						r1=1;
				}
			}
			/////////////////
			m=NUM-1,n=0;
			fv=*flag;
			num=Condirect(&m,&n,&fv,2,&top);
			if(num==1 && fv==0)
			{
				fv=*flag;
				num=Condirect(&m,&n,&fv,2,&top);
				if(!top)
				{
					c2=fv;
					fv=*flag;
					num=Condirect(&m,&n,&fv,2,&top);
					if(top && (num==1) && (fv==0))
						r2=1;
				}
			}
		}
		break;
	case 4:
		{
			int num,m,n,top,fv;
			m=NUM-1,n=NUM-1;
			fv=*flag;
			num=Condirect(&m,&n,&fv,0,&top);
			if(num==1 && fv==0)
			{
				fv=*flag;
				num=Condirect(&m,&n,&fv,0,&top);
				if(!top)
				{
					c1=fv;
					fv=*flag;
					num=Condirect(&m,&n,&fv,0,&top);
					if(top && (num==1) && (fv==0))
						r1=1;
				}
			}
			/////////////////
			m=NUM-1,n=NUM-1;
			fv=*flag;
			num=Condirect(&m,&n,&fv,2,&top);
			if(num==1 && fv==0)
			{
				fv=*flag;
				num=Condirect(&m,&n,&fv,2,&top);
				if(!top)
				{
					c2=fv;
					fv=*flag;
					num=Condirect(&m,&n,&fv,2,&top);
					if(top && (num==1) && (fv==0))
						r2=1;
				}
			}
		}
		break;
	default:
		MessageBox("error in stylespecial","error");
		break;
	}

	if(r1 && r2)
	{
		if(c1==c2)
		{
			*flag=c1;
			return 1;
		}
		else 
			return 2;
	}
	if(r1)
	{
		*flag=c1;
		return 1;
	}
	if(r2)
	{
		*flag=c2;
		return 1;
	}
	return 0;
}

void CBWChessDlg::OnSetting() 
{
	CSettingDlg dlg;
	dlg.DoModal ();
	if(g_bTopMost)
		SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
	else
		SetWindowPos(&wndNoTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
}

void CBWChessDlg::OnOpen() 
{
	if(!m_bGameOver && g_bPrompt)
		if(MsgBox(IDS_ABORT,IDS_TITLE_CHINESE,2)==IDCANCEL)
			return ;

	TCHAR sFilter[50]="BWChess File (*.BWS)|*.BWS||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					sFilter);
	int result=dlg.DoModal();
	if(result==IDOK)
	{
		CFile file(dlg.GetPathName(), CFile::modeRead);
		int buffer[9000],len,t;
		unsigned int reallen=file.Read(buffer,9000*sizeof(int));
		if((reallen!=(buffer[0]*sizeof(int))) || (reallen<140))
		{
			MsgBox(IDS_OPENERROR1,IDS_TITLE_CHINESE);
			return;
		}
		if(buffer[1]!=EDITION)
		{
			MsgBox(IDS_OPENERROR2,IDS_TITLE_CHINESE);
			return;
		}
		if(buffer[2])
		{
			MsgBox(IDS_OPENERROR3,IDS_TITLE_CHINESE);
			return;
		}

		len=buffer[0]/2-1;

		BOOL changeI=FALSE;
		for(t=0;t<len;t++)
		{
			if(buffer[t+3]!=buffer[3+len+t])
			{
				changeI=TRUE;
				break;
			}
		}
		if(changeI)
		{
			MsgBox(IDS_OPENERROR1,IDS_TITLE_CHINESE);
			return;
		}

		if(m_TimerOn)
		{
			KillTimer(PASSEDTIME);
			m_TimerOn=0;
		}
		m_bGameOver = FALSE;	              
		m_Skip=0;
		m_Interesting=0;
		g_nStoneNum=0;
		m_HintOnce=0;//0 for have not hinted yet,1 for have hinted
		m_PeekOnce=g_bPeepOften;
		m_IsGameStart=0;
		ListInfo.destroy();
		m_ListInfo.ResetContent();

		if(!m_UndoPoint.IsEmpty())
			m_UndoPoint.Destroy();

		len=3;///important

		m_byColor=buffer[len++];
		g_nRunMode=buffer[len++];
		m_PassedTime=buffer[len++];
		m_PassedTime0=buffer[len++];
		g_nSkill=buffer[len++];
		g_bUserBlack=buffer[len++];
		m_HintTime0=buffer[len++];
		m_HintTime1=buffer[len++];
		g_nTimeLimit=buffer[len++];
		g_nIsNoTimeLimit=buffer[len++];
		len+=5;
		int i,j;
		for(i=0;i<NUM;i++)
			for(j=0;j<NUM;j++)
				kernel[i][j]=buffer[len++];
		int x,y,num,tc;
		num=buffer[len++];
		while(num>0)
		{
			x=buffer[len++];
			y=buffer[len++];
			tc=buffer[len++];
			AddStringToList(x,y,tc);
			num--;
		}
		//read m_UndoPoint
		num=buffer[len++];
		while(num>0)
		{
			int temp[NUM*NUM];
			for(x=0;x<NUM*NUM;x++)
				temp[x]=buffer[len++];
			tc=buffer[len++];
			m_UndoPoint.push(temp,tc);
			num--;
		}
		IsEnd(1);
		Calcu_BW();

		SetChessTitle();

		m_pMenu->EnableMenuItem(IDM_SAVEINFO,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_SAVE,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_HINT,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_UNDO,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_CANPLACE,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_REPLAY,MF_GRAYED);

		InvalidateRect(NULL,TRUE);
		SetTimer(PASSEDTIME,1000,NULL);
		m_TimerOn=1;
	}	
}

void CBWChessDlg::OnSave() 
{
	TCHAR sFilter[50]=_T("BWChess File (*.BWS)|*.BWS||");
	TCHAR sExt[10]=_T("BWS");
	CFileDialog dlg(FALSE,sExt,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					sFilter);
//	int result=dlg.DoModal();
	if(dlg.DoModal()==IDOK)
	{
		CFile file(dlg.GetPathName(),CFile::modeCreate | CFile::modeWrite);
		int buffer[9000],len=3;// the buffer need about 4000 size
		for(int ii=0;ii<2;ii++)//copy twice
		{
			buffer[len++]=m_byColor;
			buffer[len++]=g_nRunMode;
			buffer[len++]=m_PassedTime;
			buffer[len++]=m_PassedTime0;
			buffer[len++]=g_nSkill;
			buffer[len++]=g_bUserBlack;
			buffer[len++]=m_HintTime0;
			buffer[len++]=m_HintTime1;
			buffer[len++]=g_nTimeLimit;
			buffer[len++]=g_nIsNoTimeLimit;
			//restore 5 position for future use
			buffer[len++]=0;
			buffer[len++]=0;
			buffer[len++]=0;
			buffer[len++]=0;
			buffer[len++]=0;
			//end
			int i,j;
			for(i=0;i<NUM;i++)
				for(j=0;j<NUM;j++)
					buffer[len++]=kernel[i][j];
			int num=ListInfo.Len();
			buffer[len++]=num;
			int x,y,tc;
			int re;
			stack ts;
			do
			{
				re=ListInfo.GetNextPos(&x,&y,&tc);
				ts.push(x,y);
				ts.SetMarks (tc);
			}
			while(re);
			do
			{
				re=ts.GetNextPos(&x,&y,&tc);
				buffer[len++]=x;
				buffer[len++]=y;
				buffer[len++]=tc;
			}
			while(re);
			ListInfo.CopyBackIndex();
			// store m_UndoPoint
			int tlen=m_UndoPoint.Len();
			buffer[len++]=tlen;
			int tempUndo[NUM*NUM];
			do
			{
				re=m_UndoPoint.GetNextPos(tempUndo,&tc);
				for(x=0;x<NUM*NUM;x++)
					buffer[len++]=tempUndo[x];
				buffer[len++]=tc;
			}
			while(re);
			m_UndoPoint.CopyBackIndex();
		}
		buffer[0]=len;
		buffer[1]=EDITION;//this the edition of the banben
		buffer[2]=(int)m_bGameOver;
		file.Write(buffer,len*sizeof(int));
	}	
}

void CBWChessDlg::AddStringToList(int x, int y, int color,int win)
{
	CString str;
	int result=m_ListInfo.GetCount();

	if(!win)
	{
		if(color)
			str.LoadString(IDS_SBLACK);
		else
			str.LoadString(IDS_SWHITE);
		TCHAR s[100];
		wsprintf(s, str.GetBuffer(256),result+1, y+65,x+1);
		m_ListInfo.AddString(s);
		ListInfo.push(x,y);
		ListInfo.SetMarks(color);
	}
	else
	{
		if(win==1)
			str.LoadString(IDS_WHITEWIN_CHINESE);
		else if(win==2)
			str.LoadString(IDS_BLACKWIN_CHINESE);
		else
			str.LoadString(IDS_TIE);
		m_ListInfo.AddString(str);
	}
	m_ListInfo.SetCurSel(result);
	m_ListInfo.SetFocus();
}

void CBWChessDlg::RemoveStringFromList()
{
	int index=m_ListInfo.GetCount();
	m_ListInfo.DeleteString(index-1);
	int x,y;
	ListInfo.pop(&x,&y);
	ListInfo.GetTop(x,y);
	m_CurPt.x =x,m_CurPt.y=y;
	index=m_ListInfo.GetCount();
	if(index)
	{
		m_ListInfo.SetCurSel(index-1);
		m_ListInfo.SetFocus();
	}
}


void CBWChessDlg::OnSaveinfo() 
{
	TCHAR sFilter[50]=_T("文本文件(*.TXT)|*.TXT||");
	TCHAR sExt[10]=_T("txt");
	CFileDialog dlg(FALSE,sExt,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					sFilter);
	if(dlg.DoModal()==IDOK)
	{
		CFile file(dlg.GetPathName(),CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		TCHAR buffer[300];
		int len=0,index=0;
		len=GetWindowText(buffer,300);
		buffer[len++]=13;
		buffer[len++]=10;
		file.Write(buffer,len);
		len=m_ListInfo.GetCount();
		while(index<len)
		{
			int slen=m_ListInfo.GetText(index++,buffer);
			buffer[slen]=13;
			buffer[slen+1]=10;
			file.Write(buffer,slen+2);
		}
	}	
}

BOOL CBWChessDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(!::TranslateAccelerator(m_hWnd,hAccelerator,	pMsg))
		return CDialog::PreTranslateMessage(pMsg);
	return TRUE;
}


void CBWChessDlg::SetChessTitle()
{
	CString str;
	if (g_nRunMode==MODE_WITH_COMPUTER && g_bUserBlack)
		str.LoadString(IDS_SINGLE_USER_CHINESE);
	else if (g_nRunMode==MODE_WITH_COMPUTER && !g_bUserBlack)
		str.LoadString(IDS_SINGLE_COMPUTER_CHINESE);
	else if	(g_nRunMode==MODE_2PLAYER)
	{
		if(g_nIsNoTimeLimit)
			str.LoadString(IDS_DOUBLE_NOLIMIT_CHINESE);
		else
		{
			str.LoadString(IDS_DOUBLE_LIMIT_CHINESE);
			TCHAR str1[200];
			wsprintf(str1, str.GetBuffer(256), g_nTimeLimit);
			str=str1;
		}
	}
	SetWindowText(str);
}

void CBWChessDlg::OnListDoubleClicked()
{
	if(m_bGameOver || g_nIsDemo)
		return;
	int nSel=m_ListInfo.GetCurSel();
	int length=m_ListInfo.GetCount()-1;
	int mark=ListInfo.GetMarks(length-nSel);
	if(((BOOL)g_bUserBlack)==((BOOL)mark) || (g_nRunMode == MODE_2PLAYER))
	{
		int temp[NUM*NUM];
		while(length>=nSel)
		{
//			OnUndo();
			m_UndoPoint.pop(temp);
			RemoveStringFromList();
			length=m_ListInfo.GetCount()-1;
		}
		int i,j,k=0;
		for(i=0;i<NUM;i++)
			for(j=0;j<NUM;j++)
			{
				kernel[i][j]=temp[k];
				k++;
			}

		if(ListInfo.Len())
		{
			m_byColor=ListInfo.GetMarks(0);
		}
		else
		{
			if(g_bUserBlack)
				m_byColor=0;
			else
				m_byColor=1;
		}

		IsEnd(!m_byColor+1);
		if(!m_bGameOver && g_bPeepOften)
			OnCanplace();

		m_HintOnce=0;
		Calcu_BW();
		ShowNumber();
		PlaySounds(IDSOUND_UNDO);
		InvalidateRect(m_Client, TRUE);
		UpdateWindow();
	}
}

void CBWChessDlg::DrawFrame(CDC *dc)
{
	const int Sx=1;
	const int Sy=1;
	int i,j;
	int wx0,wy0,wx1,wy1;

	wx0=Sx,wy0=Sy;
	CPoint ptt0(wx0,wy0);
	m_pDibHFrame[0][0]->Display(dc,ptt0,SRCCOPY);//SRCPAINT);
	wx0=Sx+m_wFrameHeight+NUM*m_wFrameWidth,wy0=Sy;
	CPoint ptt1(wx0,wy0);
	m_pDibHFrame[0][9]->Display(dc,ptt1,SRCCOPY);
	wx0=Sx,wy0=Sy+m_wFrameHeight+NUM*m_wStoneHeight;
	CPoint ptt2(wx0,wy0);
	m_pDibHFrame[1][0]->Display(dc,ptt2,SRCCOPY);
	wx0=Sx+m_wFrameHeight+NUM*m_wStoneWidth,wy0=Sy+m_wFrameHeight+NUM*m_wStoneHeight;
	CPoint ptt3(wx0,wy0);
	m_pDibHFrame[1][9]->Display(dc,ptt3,SRCCOPY);

	for(i=1,wx0=Sx+m_wFrameHeight,wy0=Sy,wx1=Sx+m_wFrameHeight,wy1=Sy+m_wFrameHeight+m_wStoneWidth*NUM;i<NUM+1;i++)
	{
		CPoint pt0(wx0,wy0);
		CPoint pt1(wx1,wy1);
		m_pDibHFrame[0][i]->Display(dc,pt0,SRCCOPY);
		m_pDibHFrame[1][i]->Display(dc,pt1,SRCCOPY);
		wx0+=m_wFrameWidth;
		wx1+=m_wFrameWidth;
	}
	for(i=0,wx0=Sx,wy0=Sy+m_wFrameHeight,wx1=Sx+m_wFrameHeight+NUM*m_wStoneWidth,wy1=Sy+m_wFrameHeight;i<NUM;i++)
	{
		CPoint pt0(wx0,wy0);
		CPoint pt1(wx1,wy1);
		m_pDibVFrame[0][i]->Display(dc,pt0,SRCCOPY);
		m_pDibVFrame[1][i]->Display(dc,pt1,SRCCOPY);
		wy0+=m_wStoneHeight;
		wy1+=m_wStoneHeight;
	}
	for(i=0,wx0=Sx+m_wFrameHeight,wy0=Sy+m_wFrameHeight;i<NUM;i++,wx0=Sx+m_wFrameHeight,wy0=i*m_wStoneHeight+Sy+m_wFrameHeight)
		for(j=0;j<NUM;j++,wx0+=m_wStoneWidth)
		{
			if(!kernel[i][j])
			{
				CPoint pt(wx0,wy0);
				m_pDibEmpty->Display(dc,pt,SRCCOPY);
			}
		}		
}

void CBWChessDlg::OnDemo() 
{
	CString str;
	if(g_nIsDemo)
	{
		::TerminateThread(m_CcThread->m_hThread,0);
		m_pMenu->EnableMenuItem(IDM_NEW,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_OPEN,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_SAVE,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_NETPLAY,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_REPLAY,MF_ENABLED);

		str.LoadString(IDS_DEMOTITLE0);
		m_pMenu->ModifyMenu(IDM_DEMO,MF_BYCOMMAND | MF_STRING,IDM_DEMO,str);

		g_nIsDemo=0;
		m_bGameOver=TRUE;
	}
	else
	{
		int HaveKilled=0;
		if(m_TimerOn)
		{
			HaveKilled=1;
			KillTimer(PASSEDTIME);
			m_TimerOn=0;
		}

		if(!m_bGameOver && g_bPrompt)
		{
			if(MsgBox(IDS_ABORT,IDS_TITLE_CHINESE,2)==IDCANCEL)
			{
				if(HaveKilled)
				{					
					SetTimer(PASSEDTIME,1000,NULL);
					m_TimerOn=1;
				}
				return;
			}
		}

		CDemo dlg;
		if(dlg.DoModal()==IDCANCEL)
		{
			if(HaveKilled)
			{				
				SetTimer(PASSEDTIME,1000,NULL);
				m_TimerOn=1;
			}
			return;
		}
		
		m_pMenu->EnableMenuItem(IDM_HINT,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_UNDO,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_CANPLACE,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_SAVE,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_SAVEINFO,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_NEW,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_OPEN,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_NETPLAY,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_REPLAY,MF_GRAYED);

		str.LoadString(IDS_DEMOTITLE1);
		m_pMenu->ModifyMenu(IDM_DEMO,MF_BYCOMMAND | MF_STRING,IDM_DEMO,str);

		int flag=0;
		if(dlg.m_IsFile)
		{
			CFile file(dlg.m_FilePath, CFile::modeRead);
			int buffer[9000],len;
			file.Read(buffer,9000*sizeof(int));

			len=18+NUM*NUM;///important
			m_PointGo.destroy();

			int x,y,num,tc;
			stack tt;
			num=buffer[len++];
			while(num>0)
			{
				x=buffer[len++];
				y=buffer[len++];
				tc=buffer[len++];
				tt.push(x,y);
				tt.SetMarks(tc);
				num--;
			}
			while(!tt.isempty ())
			{
				tc=tt.GetMarks (0);
				tt.pop (&x,&y);
				m_PointGo.push(x,y);
				m_PointGo.SetMarks(tc);
			}
			flag=0;
		}
		else
		{
			CString str1;
			switch(g_nCbSkill)
			{
			case 1:
				switch(g_nCwSkill)
				{
				case 1:
					str1.LoadString(IDS_DEMO_TITLE_11);
					break;
				case 2:
					str1.LoadString(IDS_DEMO_TITLE_12);
					break;
				case 3:
					str1.LoadString(IDS_DEMO_TITLE_13);
					break;
				}
				break;
			case 2:
				switch(g_nCwSkill)
				{
				case 1:
					str1.LoadString(IDS_DEMO_TITLE_21);
					break;
				case 2:
					str1.LoadString(IDS_DEMO_TITLE_22);
					break;
				case 3:
					str1.LoadString(IDS_DEMO_TITLE_23);
					break;
				}
				break;
			case 3:
				switch(g_nCwSkill)
				{
				case 1:
					str1.LoadString(IDS_DEMO_TITLE_31);
					break;
				case 2:
					str1.LoadString(IDS_DEMO_TITLE_32);
					break;
				case 3:
					str1.LoadString(IDS_DEMO_TITLE_33);
					break;
				}
				break;
			}

			SetWindowText(str1);
			flag=1;
		}
		g_nIsDemo=1;
		m_DemoOrReplay=1;
		m_CcThread=AfxBeginThread(CCplayFunc,(LPVOID )flag,THREAD_PRIORITY_NORMAL,
									0,CREATE_SUSPENDED);
		m_Mutex.Lock();
		m_CcThread->ResumeThread();	
	}
	m_nIsContinueReplay=1;
}

UINT CCplayFunc(LPVOID p)
{
	CBWChessDlg *dlg=(CBWChessDlg *)(AfxGetApp()->m_pMainWnd); 
	dlg->ComputerPlay ((int)p);
	return 0;
}

void CBWChessDlg::ComputerPlay(int flag)
{
	InitParams();
	IsEnd(m_byColor+1);
	m_PeekOnce=(int)g_bPeepOften;
	Mutex1.Lock();
	g_nMutex=1;
	Mutex1.Unlock();
	InvalidateRect(&m_Client, FALSE);
	m_Mutex.Lock();

	while(1)
	{
		m_byColor = !m_byColor;			// 1-Black  0-White
		int ptBest_x=0,ptBest_y=0,result=0,ret=0;
		if(flag)
		{
			if(m_byColor)
				Place(&ptBest_x,&ptBest_y,m_byColor+1,g_nCbSkill);
			else
				Place(&ptBest_x,&ptBest_y,m_byColor+1,g_nCwSkill);
		}
		else
		{///add here
			ret=m_PointGo.GetNextPos(&ptBest_x,&ptBest_y,&m_byColor);
		}
		BtoW(ptBest_x,ptBest_y,m_byColor+1);
		Calcu_BW();
		result=IsEnd(!m_byColor+1);

		Mutex1.Lock();
		g_nMutex=1;
		Mutex1.Unlock();
		InvalidateRect(&m_Client, FALSE);
		UpdateWindow();
		m_Mutex.Lock();

		AddStringToList(ptBest_x,ptBest_y,m_byColor);
		PlaySounds(IDSOUND_PUTSTONE);

		if(!ret && !flag)
		{
			m_bGameOver=TRUE;
			break;
		}

		if(result==-1)
		{
			CString str1,str2,str3,strPrompt;
			TCHAR str[300];
			int addp=0;
			m_bGameOver=TRUE;
			Calcu_BW();
			str2.LoadString (IDS_TITLE_CHINESE);
			if(num_white<num_black)
			{
				addp=2;
				str1.LoadString(IDS_BLACKWIN_CHINESE);
			}
			else if(num_white>num_black)
			{
				addp=1;
				str1.LoadString(IDS_WHITEWIN_CHINESE);
			}
			else
			{
				addp=3;
				str1.LoadString(IDS_TIE_CHINESE);
			}
			str3.LoadString(IDS_END_CHINESE);
			
			wsprintf(str, str3.GetBuffer(256), num_black,num_white);
			strPrompt = str;
			strPrompt += str1; 
			AddStringToList(0,0,0,addp);
			Mutex1.Lock();
			g_nMutex=1;
			Mutex1.Unlock();
			InvalidateRect(&m_Client,FALSE);
			m_Mutex.Lock();

			PlaySounds(IDSOUND_USERWIN);

			MsgBox(strPrompt,str2);

			break;
		}
		else if(result==0)
			m_byColor=!m_byColor;
		Sleep(500*g_nCSpeed);
	}//end while
	CString strT;
	m_pMenu->EnableMenuItem(IDM_NEW,MF_ENABLED);
	m_pMenu->EnableMenuItem(IDM_OPEN,MF_ENABLED);
	m_pMenu->EnableMenuItem(IDM_SAVE,MF_ENABLED);
	m_pMenu->EnableMenuItem(IDM_NETPLAY,MF_ENABLED);

	if(m_DemoOrReplay)
	{
		strT.LoadString(IDS_DEMOTITLE0);
		m_pMenu->ModifyMenu(IDM_DEMO,MF_BYCOMMAND | MF_STRING,IDM_DEMO,strT);
		m_pMenu->EnableMenuItem(IDM_REPLAY,MF_ENABLED);
	}
	else
	{//add here
		strT.LoadString(IDS_REPLAY0);
		m_pMenu->ModifyMenu(IDM_REPLAY,MF_BYCOMMAND | MF_STRING,IDM_REPLAY,strT);
		m_pMenu->EnableMenuItem(IDM_DEMO,MF_ENABLED);
	}
	g_nIsDemo=0;
	m_PointGo.CopyBackIndex();
}



void CBWChessDlg::OnReplay() 
{
	CString str;
	if(g_nIsDemo)
	{
		::TerminateThread(m_CcThread->m_hThread,0);
		m_pMenu->EnableMenuItem(IDM_NEW,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_OPEN,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_SAVE,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_NETPLAY,MF_ENABLED);
		m_pMenu->EnableMenuItem(IDM_DEMO,MF_ENABLED);

		str.LoadString(IDS_REPLAY0);
		m_pMenu->ModifyMenu(IDM_REPLAY,MF_BYCOMMAND | MF_STRING,IDM_REPLAY,str);

		g_nIsDemo=0;
		m_bGameOver=TRUE;
		m_PointGo.CopyBackIndex();
	}
	else
	{
		int HaveKilled=0;
		if(m_TimerOn)
		{
			HaveKilled=1;
			KillTimer(PASSEDTIME);
			m_TimerOn=0;
		}

		if(!m_bGameOver && g_bPrompt)
		{
			if(MsgBox(IDS_ABORT,IDS_TITLE_CHINESE,2)==IDCANCEL)
			{
				if(HaveKilled)
				{					
					SetTimer(PASSEDTIME,1000,NULL);
					m_TimerOn=1;
				}
				return;
			}
		}

		m_pMenu->EnableMenuItem(IDM_HINT,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_UNDO,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_CANPLACE,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_SAVE,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_SAVEINFO,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_NEW,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_OPEN,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_NETPLAY,MF_GRAYED);
		m_pMenu->EnableMenuItem(IDM_DEMO,MF_GRAYED);

		str.LoadString(IDS_REPLAY1);
		m_pMenu->ModifyMenu(IDM_REPLAY,MF_BYCOMMAND | MF_STRING,IDM_REPLAY,str);

		//duplicate stack
		if(m_nIsContinueReplay)
		{
			m_PointGo.destroy();

			while(!ListInfo.isempty())
			{
				int x,y,mark;
				mark=ListInfo.GetMarks(0);
				ListInfo.pop(&x,&y);
				m_PointGo.push(x,y);
				m_PointGo.SetMarks(mark);
			}
			m_nIsContinueReplay=0;//防止第二次赋值
		}
		g_nIsDemo=1;
		m_DemoOrReplay=0;
		m_CcThread=AfxBeginThread(CCplayFunc,(LPVOID)0,THREAD_PRIORITY_NORMAL,
									0,CREATE_SUSPENDED);
		m_Mutex.Lock();
		m_CcThread->ResumeThread();	
	}
}
