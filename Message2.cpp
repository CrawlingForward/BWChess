// Message2.cpp : implementation file
//

#include "stdafx.h"
#include "BWChess.h"
#include "Message2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessage2 dialog


CMessage2::CMessage2(CWnd* pParent /*=NULL*/)
	: CDialog(CMessage2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMessage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessage2)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessage2, CDialog)
	//{{AFX_MSG_MAP(CMessage2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessage2 message handlers

BOOL CMessage2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_QUERY);
	SetIcon(hIcon, TRUE);		// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon
	CenterWindow();
	
	// TODO: Add extra initialization here
	m_OK.SetIcon ( IDI_OPEN );
	m_OK.AddToolTip ( _T("确定") );
	m_OK.SetBtnCursor(IDC_HAND);
	m_OK.SetActiveFgColor(RGB(0,0,255));

	m_Cancel.SetIcon ( IDI_CANCEL );
	m_Cancel.AddToolTip ( _T("取消") );
	m_Cancel.SetBtnCursor(IDC_HAND);
	m_Cancel.SetActiveFgColor(RGB(0,0,255));

	CMenu* sysmenu=GetSystemMenu(FALSE);
	sysmenu->DeleteMenu(1,MF_BYPOSITION);

	SetWindowText(m_title);
	SetDlgItemText(IDC_INFORMATION,m_con);
	MessageBeep(MB_ICONQUESTION);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMessage2::SetContent(const CString &con)
{
	m_con=con;
}

void CMessage2::SetTitle(const CString &title)
{
	m_title=title;
}

