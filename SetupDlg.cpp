// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BWChess.h"
#include "SetupDlg.h"
#include "HelperAPI.h"
#include "Globalvar.h"
#include "HowToDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
	m_PlayMode = g_nRunMode;
	m_WhoFirst = (int)(!g_bUserBlack);
	m_Skill = g_nSkill-1;
	m_TimeNum = g_nTimeLimit/60;
	//}}AFX_DATA_INIT
	m_DyShow=0;
}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
	DDX_Control(pDX, IDC_HELP1, m_Help);
	DDX_Control(pDX, IDC_TIMENUM, m_TimeNumC);
	DDX_Control(pDX, IDC_SPINNUM, m_Spin);
	DDX_Control(pDX, IDC_NONEEDTIME, m_NoNeedLimit);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Radio(pDX, IDC_RADIO_WITHCOMPUTER, m_PlayMode);
	DDX_Radio(pDX, IDC_RADIO_YOU_FIRST, m_WhoFirst);
	DDX_Radio(pDX, IDC_SKILL1, m_Skill);
	DDX_Text(pDX, IDC_TIMENUM, m_TimeNum);
	DDV_MinMaxInt(pDX, m_TimeNum, 1, 150);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_2PLAYER, OnRadio2player)
	ON_BN_CLICKED(IDC_RADIO_WITHCOMPUTER, OnRadioWithcomputer)
	ON_BN_CLICKED(IDC_NONEEDTIME, OnNoneedtime)
	ON_BN_CLICKED(IDC_HELP1, OnHelp1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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

	m_Spin.SetBuddy(&m_TimeNumC);
	m_Spin.SetRange(1,150);
	m_Spin.SetPos(m_TimeNum);

	UpdateData(FALSE);
	m_NoNeedLimit.SetCheck(g_nIsNoTimeLimit);

	if(m_NoNeedLimit.GetCheck())
	{
		GetDlgItem(IDC_TIMENUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPINNUM)->EnableWindow(FALSE);
	}
	EnableCtrl(!IsDlgButtonChecked(IDC_RADIO_2PLAYER));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(!m_DyShow)
	{
		m_DyShow++;
		DynamicShow(this,1);
	}
}

void CSetupDlg::OnRadio2player() 
{
	EnableCtrl(!IsDlgButtonChecked(IDC_RADIO_2PLAYER));
	OnNoneedtime();
}

void CSetupDlg::OnRadioWithcomputer() 
{
	EnableCtrl(IsDlgButtonChecked(IDC_RADIO_WITHCOMPUTER));
}

void CSetupDlg::OnCancel() 
{
	DynamicShow(this,0);		
	
	CDialog::OnCancel();
}

void CSetupDlg::OnOK() 
{
	UpdateData();

	g_bUserBlack=!m_WhoFirst;
	g_nRunMode=m_PlayMode;
	g_nSkill=m_Skill+1;
	g_nTimeLimit= m_TimeNum * 60;
	g_nIsNoTimeLimit=m_NoNeedLimit.GetCheck();

	DynamicShow(this,0);		
	
	CDialog::OnOK();
}

void CSetupDlg::OnNoneedtime() 
{
	BOOL flag=IsDlgButtonChecked(IDC_NONEEDTIME);
	GetDlgItem(IDC_TIMENUM)->EnableWindow(!flag);
	GetDlgItem(IDC_SPINNUM)->EnableWindow(!flag);
}

void CSetupDlg::OnHelp1() 
{
	CHowToDlg dlg;
	dlg.SetHelpIndex (4);
	dlg.DoModal();	
}

void CSetupDlg::EnableCtrl(BOOL flag)
{
	GetDlgItem(IDC_NONEEDTIME)->EnableWindow(!flag);
	GetDlgItem(IDC_TIMENUM)->EnableWindow(!flag);
	GetDlgItem(IDC_SPINNUM)->EnableWindow(!flag);
	GetDlgItem(IDC_RADIO_YOU_FIRST)->EnableWindow(flag);
	GetDlgItem(IDC_RADIO_COMPUTER_FIRST)->EnableWindow(flag);
	GetDlgItem(IDC_SKILL1)->EnableWindow(flag);
	GetDlgItem(IDC_SKILL2)->EnableWindow(flag);
	GetDlgItem(IDC_SKILL3)->EnableWindow(flag);
}
