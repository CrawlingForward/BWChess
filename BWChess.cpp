// BWChess.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BWChess.h"
#include "BWChessDlg.h"
#include "HelperAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBWChessApp

BEGIN_MESSAGE_MAP(CBWChessApp, CWinApp)
	//{{AFX_MSG_MAP(CBWChessApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBWChessApp construction

CBWChessApp::CBWChessApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBWChessApp object

CBWChessApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBWChessApp initialization

BOOL CBWChessApp::InitInstance()
{
	HANDLE hMutex=::CreateMutex(NULL,FALSE,_T("bwchessmadebyshuker1228"));

	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{
		MsgBox(IDS_ERROR_ALREADY_EXIST,IDS_TITLE_CHINESE);
		return FALSE;
	}

//	AfxEnableControlContainer();

//#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
//#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
//#endif

	SetRegistryKey(_T("Spray Soft"));
//	this->SetDialogBkColor (RGB(255,255,255));

	CBWChessDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	::CloseHandle (hMutex);
	return FALSE;
}
