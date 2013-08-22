// Message1.cpp : implementation file
//

#include "stdafx.h"
#include "BWChess.h"
#include "Message1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessage1 dialog


CMessage1::CMessage1(CWnd* pParent /*=NULL*/)
	: CDialog(CMessage1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMessage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessage1)
	DDX_Control(pDX, IDOK, m_OK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessage1, CDialog)
	//{{AFX_MSG_MAP(CMessage1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessage1 message handlers

BOOL CMessage1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_QUERY);
	SetIcon(hIcon, TRUE);		// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon
	CenterWindow();
	
	// TODO: Add extra initialization here
	m_OK.SetIcon ( IDI_OPEN );
	m_OK.AddToolTip ( _T("È·¶¨") );
	m_OK.SetBtnCursor(IDC_HAND);
	m_OK.SetActiveFgColor(RGB(0,0,255));

	CMenu* sysmenu=GetSystemMenu(FALSE);
	sysmenu->DeleteMenu(1,MF_BYPOSITION);

	SetWindowText(m_title);
	SetDlgItemText(IDC_INFORMATION,m_con);

	MessageBeep(MB_ICONQUESTION);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMessage1::SetTitle(const CString &title)
{
	m_title=title;
}

void CMessage1::SetContent(const CString &con)
{
	m_con=con;
}


