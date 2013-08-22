// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BWChess.h"
#include "SettingDlg.h"
#include "GlobalVar.h"
#include "HelperAPI.h"
#include "HowToDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog


CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDlg)
	m_Dynamic = g_bMovePlace;
	m_PeepOften = g_bPeepOften;
	m_SoundOn = g_bSoundOn;
	m_TopMost = g_bTopMost;
	m_ShowDynamic =g_bShowDynamic;
	m_Speed = g_nMoveSpeeds-1;
	m_Prompt = g_bPrompt;
	//}}AFX_DATA_INIT
	m_DyShow=0;
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Control(pDX, IDC_HELP0, m_Help);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Check(pDX, IDC_DYNAMIC, m_Dynamic);
	DDX_Check(pDX, IDC_PEEPOFTEN, m_PeepOften);
	DDX_Check(pDX, IDC_SOUNDON, m_SoundOn);
	DDX_Check(pDX, IDC_TOPMOST, m_TopMost);
	DDX_Check(pDX, IDC_SHOWDYNAMIC, m_ShowDynamic);
	DDX_Radio(pDX, IDC_SPEED1, m_Speed);
	DDX_Check(pDX, IDC_PROMPT, m_Prompt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DYNAMIC, OnDynamic)
	ON_BN_CLICKED(IDC_HELP0, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers

BOOL CSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_SETTING);
	SetIcon(hIcon, TRUE);		// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon
	CenterWindow();
	
	m_OK.SetIcon ( IDI_OPEN );
	m_OK.AddToolTip ( _T("确定") );
	m_OK.SetBtnCursor(IDC_HAND);
	m_OK.SetActiveFgColor(RGB(0,0,255));

	m_Cancel.SetIcon ( IDI_CANCEL );
	m_Cancel.AddToolTip ( _T("取消") );
	m_Cancel.SetBtnCursor(IDC_HAND);
	m_Cancel.SetActiveFgColor(RGB(0,0,255));

	m_Help.SetIcon ( IDI_HELP2 );
	m_Help.AddToolTip ( _T("帮助") );
	m_Help.SetBtnCursor(IDC_HAND);
	m_Help.SetActiveFgColor(RGB(0,0,255));

	UpdateData(FALSE);

	OnDynamic() ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg::OnOK() 
{
	UpdateData();
	g_bMovePlace=m_Dynamic;
	g_bPeepOften=m_PeepOften;
	g_bSoundOn=m_SoundOn;
	g_bTopMost=m_TopMost;
	g_bShowDynamic=m_ShowDynamic;
	g_nMoveSpeeds=m_Speed+1;
	g_bPrompt=m_Prompt;

	DynamicShow(this,0);	
	
	CDialog::OnOK();
}

void CSettingDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if(!m_DyShow)
	{
		m_DyShow++;
		DynamicShow(this,1);
	}
}

void CSettingDlg::OnCancel() 
{
	DynamicShow(this,0);	
	
	CDialog::OnCancel();
}

void CSettingDlg::OnDynamic() 
{
	UpdateData();
	GetDlgItem(IDC_SPEED1)->EnableWindow(m_Dynamic);
	GetDlgItem(IDC_SPEED2)->EnableWindow(m_Dynamic);
	GetDlgItem(IDC_SPEED3)->EnableWindow(m_Dynamic);
}

void CSettingDlg::OnHelp() 
{
	CHowToDlg dlg;
	dlg.SetHelpIndex (1);
	dlg.DoModal();	
}
