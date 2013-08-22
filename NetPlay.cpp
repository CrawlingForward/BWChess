// NetPlay.cpp : implementation file
//

#include "stdafx.h"
#include "BWChess.h"
#include "NetPlay.h"
#include "HelperAPI.h"
#include "Globalvar.h"
#include "HowToDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetPlay dialog


CNetPlay::CNetPlay(CWnd* pParent /*=NULL*/)
	: CDialog(CNetPlay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetPlay)
	m_Name = g_strName;// _T("");
	m_S1 = g_nNetPlayMode;
	m_Port = g_nPortNum;
	//}}AFX_DATA_INIT
	m_DyShow=0;
}


void CNetPlay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetPlay)
	DDX_Control(pDX, IDC_HELP0, m_Help);
	DDX_Control(pDX, IDC_MOREN, m_MoRen);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDC_IPADDRESS, m_IP);
	DDX_Control(pDX, IDC_CONNECT, m_Connect);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 20);
	DDX_Radio(pDX, IDC_SERVER, m_S1);
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDV_MinMaxInt(pDX, m_Port, 256, 65500);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetPlay, CDialog)
	//{{AFX_MSG_MAP(CNetPlay)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_CLIENT, OnClient)
	ON_BN_CLICKED(IDC_SERVER, OnServer)
	ON_BN_CLICKED(IDC_MOREN, OnMoren)
	ON_BN_CLICKED(IDC_HELP0, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetPlay message handlers

BOOL CNetPlay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_NETPLAY);
	SetIcon(hIcon, TRUE);		// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon
	CenterWindow();
	
	// TODO: Add extra initialization here
	m_Connect.SetIcon ( IDI_OPEN );
	m_Connect.AddToolTip ( _T("连接") );
	m_Connect.SetBtnCursor(IDC_HAND);
	m_Connect.SetActiveFgColor(RGB(0,0,255));

	m_Cancel.SetIcon ( IDI_CANCEL );
	m_Cancel.AddToolTip ( _T("取消") );
	m_Cancel.SetBtnCursor(IDC_HAND);
	m_Cancel.SetActiveFgColor(RGB(0,0,255));

	m_MoRen.SetIcon ( IDI_MORE );
	m_MoRen.AddToolTip ( _T("默认") );
	m_MoRen.SetBtnCursor(IDC_HAND);
	m_MoRen.SetActiveFgColor(RGB(0,0,255));

	m_Help.SetIcon ( IDI_HELP2 );
	m_Help.AddToolTip ( _T("帮助") );
	m_Help.SetBtnCursor(IDC_HAND);
	m_Help.SetActiveFgColor(RGB(0,0,255));

	UpdateData();

	m_IP.EnableWindow(m_S1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetPlay::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(!m_DyShow)
	{
		m_DyShow++;
		DynamicShow(this,1);
	}
}

void CNetPlay::OnCancel() 
{
	DynamicShow(this,0);	
	
	CDialog::OnCancel();
}

void CNetPlay::OnConnect() 
{
	if(!UpdateData())
		return;
	g_strName=m_Name;
	g_nNetPlayMode=m_S1;
	g_nPortNum=m_Port;

	EndDialog(-1);
}

void CNetPlay::OnClient() 
{
	m_IP.EnableWindow(IsDlgButtonChecked(IDC_CLIENT));
}

void CNetPlay::OnServer() 
{
	m_IP.EnableWindow(!IsDlgButtonChecked(IDC_SERVER));
}

void CNetPlay::OnMoren() 
{
	if(!UpdateData())
		return;
	m_Port=1228;
	UpdateData(FALSE);
}

void CNetPlay::OnHelp() 
{
	CHowToDlg dlg;
	dlg.SetHelpIndex (2);
	dlg.DoModal();	
}
