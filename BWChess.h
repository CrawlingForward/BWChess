// BWChess.h : main header file for the BWCHESS application
//

#if !defined(AFX_BWCHESS_H__68677444_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
#define AFX_BWCHESS_H__68677444_7A80_11D4_9B45_8E32258B560A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#define MODE_WITH_COMPUTER	0
#define MODE_2PLAYER		1
//#define MODE_2PLAYER_NET	2
//#define MODE_2PLAYER_MODEM	3
#define EDITION 17

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBWChessApp:
// See BWChess.cpp for the implementation of this class
//

class CBWChessApp : public CWinApp
{
public:
	CBWChessApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBWChessApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBWChessApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BWCHESS_H__68677444_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
