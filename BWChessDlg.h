// BWChessDlg.h : header file
//

#if !defined(AFX_BWChessDlg_H__9A01CC68_D589_11D1_92B0_000021003EA5__INCLUDED_)
#define AFX_BWChessDlg_H__9A01CC68_D589_11D1_92B0_000021003EA5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CBWChessDlg dialog

#include "Dib.h"
#include "Undo.h"	// Added by ClassView
#include "DigitalPlayer.h"	// Added by ClassView
#include "stack.h"	// Added by ClassView

#define NUM	8

class CBWChessDlg : public CDialog
{
// Construction
public:
	CBWChessDlg(CWnd* pParent = NULL);	// standard constructor
	~CBWChessDlg();
	friend UINT CCplayFunc(LPVOID p);
// Dialog Data
	//{{AFX_DATA(CBWChessDlg)
	enum { IDD = IDD_BWCHESS_DIALOG };
	CStatic	 m_Time0;
	CStatic	 m_Info;
	CListBox m_ListInfo;
	CStatic	 m_Wnum;
	CStatic	 m_Time;
	CStatic	 m_Bnum;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBWChessDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	ComputerPlay(int flag);
	void	DrawFrame(CDC *dc);
	void	SetChessTitle();
	void	RemoveStringFromList();
	void	AddStringToList(int x,int y, int color,int win=0);
	int		IsAllEatup(int x,int y,int flag);
	void	PutStone(BYTE, const CPoint &, CDC *);
	void	Ring(int m_nType);
	int		Distance(const CPoint &pt1, const CPoint &pt2);
	BOOL	IsStonePoint(CPoint& ptStone);
	BOOL	PointToStonePos(const CPoint &pt, CPoint& ptStone);
	void	InitParams();
	int		StyleSpecial(int x,int *flag);
	void	MultiGo(int *x,int *y,int color);
	int		OtherCanGo(int x1,int y1,int x2,int y2,int flag);
	int		IsEatDanger(int x,int y,int flag,int dir,int rorf);
	void	Walk2(int *x1, int *y1, int flag);
	int		IsDanger3(int x,int y);
//	void	PaintWelcome(CDC* dc);
	void	MoveCursor(int x, int y);
	void	RandGo(int *x,int *y,int color);
	void	Place(int *x,int *y,int color,int nSkill);
	void	duplicate();
	void	ShowNumber(int isTime=0);
	int		IsInPanel(CPoint &pt);
	void	Calcu_BW();
	int		ToEnd(int x,int y,int flag);
	int		Imitate(int x,int y,int flag);
	int		IsDanger(int x,int y);
	int		Condirect(int *x,int *y,int *flag,int direction,int *top);
	int		WhereAmI(int x,int y);
	int		Compare(int x1,int y1,int x2,int y2,int flag);
	int		Judge(int x,int y,const int flag);
	int		Walk1(int *x1,int *y1,int flag);
	int		Check(int x,int y);
	int		IsEnd(int whogo);
	int		BtoW(int x1,int y1,int flag);

protected:
	int				m_DemoOrReplay;//1 for demo, 0 for replay
	int				m_nIsContinueReplay;
	int				m_HintTime0;
	int				m_HintTime1;
	HACCEL			hAccelerator;
	HICON			m_hIcon;
	int				kernel[NUM][NUM];	//0 for none,1 for white,2 for black
	WORD			m_wXNull;
	WORD			m_wYNull;
	int				m_byColor;
	BOOL			m_bGameOver;       
	BOOL			m_bSoundOn;
	CRect			m_Client;
	CMenu *			m_pMenu;
	CDib  *			m_pDibEmpty;
	CDib  *			m_pDibHFrame[2][NUM+2];
	CDib  *			m_pDibVFrame[2][NUM];
	CDib  *			m_pDibBlack;
	CDib  *			m_pDibWhite;
	CDib  *			m_pDibBGo;
	CDib  *			m_pDibWGo;
	CDib  *			m_pDibCurB;
	CDib  *			m_pDibCurW;
	CPoint			m_CurPt;
	WORD			m_wStoneWidth;
	WORD			m_wStoneHeight;
	WORD			m_wFrameWidth;
	WORD			m_wFrameHeight;
	stack			ListInfo;
	stack			m_PointGo;
	int				m_PeekOnce;
	int				m_IsGameStart;
	int				x1, y1, x2, y2;//used for Hint
	int				m_HintOnce;
	int				m_TimerOn;
	CWinThread *	m_CcThread;
	int				m_PaintNum;
	CDigitalPlayer	WCount;
	CDigitalPlayer	BCount;
	CDigitalPlayer	TimeCount;
	CDigitalPlayer	TimeCount0;
	int				m_Interesting;
	CUndo			m_UndoPoint;
	long			m_PassedTime;
	long			m_PassedTime0;
	int				m_Skip;
	stack			wsp;
	stack			bsp;
	int				num_black;
	int				num_white;

	// Generated message map functions
	//{{AFX_MSG(CBWChessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT, CPoint);	
	afx_msg void OnNew();
	afx_msg void OnExit();
	afx_msg void OnAbout();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUndo();
	afx_msg void OnHowto();
	afx_msg void OnBest();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnHint();
	afx_msg void OnCanplace();
	afx_msg void OnSetting();
	afx_msg void OnOpen();
	afx_msg void OnSave();
	afx_msg void OnSaveinfo();
	afx_msg void OnDemo();
	afx_msg void OnReplay();
	//}}AFX_MSG
	afx_msg void OnListDoubleClicked();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BWChessDlg_H__9A01CC68_D589_11D1_92B0_000021003EA5__INCLUDED_)
