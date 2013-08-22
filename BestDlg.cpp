// BestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BWChess.h"
#include "Globalvar.h"
#include "BestDlg.h"
#include "HelperAPI.h"
#include "ConfirmSec.h"
#include "HowToDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBestDlg dialog


CBestDlg::CBestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBestDlg)
	m_S1 = _T("");
	m_S2 = _T("");
	m_S3 = _T("");
	//}}AFX_DATA_INIT
	m_DyShow=0;
}


void CBestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBestDlg)
	DDX_Control(pDX, IDC_HELP1, m_Help);
	DDX_Control(pDX, IDC_RULE, m_Rule);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_RESTARTCOUNT, m_Reset);
	DDX_Text(pDX, IDC_SEC1, m_S1);
	DDX_Text(pDX, IDC_SEC2, m_S2);
	DDX_Text(pDX, IDC_SEC3, m_S3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBestDlg, CDialog)
	//{{AFX_MSG_MAP(CBestDlg)
	ON_BN_CLICKED(IDC_RESTARTCOUNT, OnRestartcount)
	ON_BN_CLICKED(IDC_RULE, OnRule)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_HELP1, OnHelp1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBestDlg message handlers

BOOL CBestDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	HICON m_hIcon;	
	m_hIcon = AfxGetApp()->LoadIcon(IDI_HERO);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CenterWindow();

	m_OK.SetIcon ( IDI_OPEN );
	m_OK.SetBtnCursor(IDC_HAND);
	m_OK.AddToolTip ( _T("确定") );
	m_OK.SetActiveFgColor(RGB(0,0,255));

	m_Reset.SetIcon ( IDI_RESET );
	m_Reset.AddToolTip ( _T("重置") );
	m_Reset.SetBtnCursor(IDC_HAND);
	m_Reset.SetActiveFgColor(RGB(0,0,255));

	m_Rule.SetIcon ( IDI_RULE );
	m_Rule.AddToolTip ( _T("计分规则") );
	m_Rule.SetBtnCursor(IDC_HAND);
	m_Rule.SetActiveFgColor(RGB(0,0,255));

	m_Help.SetIcon ( IDI_HELP2 );
	m_Help.AddToolTip ( _T("帮助") );
	m_Help.SetBtnCursor(IDC_HAND);
	m_Help.SetActiveFgColor(RGB(0,0,255));

	Name1Edit().SetWindowText(g_strName1);
	Name2Edit().SetWindowText(g_strName2);
	Name3Edit().SetWindowText(g_strName3);
		
	TCHAR str[6]; 
	wsprintf(str,_T("%d"),g_nTime1);
	Time1Edit().SetWindowText(str);
	wsprintf(str,_T("%d"),g_nTime2);
	Time2Edit().SetWindowText(str);
	wsprintf(str,_T("%d"),g_nTime3);
	Time3Edit().SetWindowText(str);

	wsprintf(str,_T("%d"),g_nMark1);
	Mark1Edit().SetWindowText(str);
	wsprintf(str,_T("%d"),g_nMark2);
	Mark2Edit().SetWindowText(str);
	wsprintf(str,_T("%d"),g_nMark3);
	Mark3Edit().SetWindowText(str);

	m_S1.LoadString(g_strSec1.GetLength()? IDS_HAVESEC : IDS_NOSEC);

	m_S2.LoadString(g_strSec2.GetLength()? IDS_HAVESEC : IDS_NOSEC);

	m_S3.LoadString(g_strSec3.GetLength()? IDS_HAVESEC : IDS_NOSEC);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBestDlg::OnRestartcount() 
{
	int flag=0;

	if(g_strSec1.GetLength()!=0)
	{
		CConfirmSec dlg;
		dlg.SetSkill (1);
		if(dlg.DoModal()==IDOK)
			flag=1;
	}
	else
		flag=1;
	if(flag)
	{
		g_strSec1=_T("");
		g_strName1 = _T("Anonymous");
		g_nTime1 = 0;
		g_nMark1 = 0;
		Name1Edit().SetWindowText(g_strName1);
		Time1Edit().SetWindowText(_T("0"));
		Mark1Edit().SetWindowText(_T("0"));
		m_S1.LoadString(IDS_NOSEC);
		UpdateData(FALSE);
	}

	flag=0;

	if(g_strSec2.GetLength()!=0)
	{
		CConfirmSec dlg;
		dlg.SetSkill (2);
		if(dlg.DoModal()==IDOK)
			flag=1;
	}
	else
		flag=1;
	if(flag)
	{
		g_strSec2=_T("");
		g_strName2 = _T("Anonymous");
		g_nTime2 = 0;
		g_nMark2 = 0;
		Name2Edit().SetWindowText(g_strName2);
		Time2Edit().SetWindowText(_T("0"));
		Mark2Edit().SetWindowText(_T("0"));
		m_S2.LoadString(IDS_NOSEC);
		UpdateData(FALSE);
	}

	flag=0;

	if(g_strSec3.GetLength()!=0)
	{
		CConfirmSec dlg;
		dlg.SetSkill (3);
		if(dlg.DoModal()==IDOK)
			flag=1;
	}
	else
		flag=1;
	if(flag)
	{
		g_strSec3=_T("");
		g_strName3 = _T("Anonymous");
		g_nTime3 = 0;
		g_nMark3 = 0;
		Name3Edit().SetWindowText(g_strName3);
		Time3Edit().SetWindowText(_T("0"));
		Mark3Edit().SetWindowText(_T("0"));
		m_S3.LoadString(IDS_NOSEC);
		UpdateData(FALSE);
	}
}

void CBestDlg::OnRule() 
{
	MsgBox(IDS_RULE_CONTENT,IDS_RULE_TITLE); 
}

void CBestDlg::OnPaint() 
{
	CPaintDC dc(this);
	if(m_DyShow==0)
	{
		m_DyShow++;
		DynamicShow(this,1);
	}
}


void CBestDlg::OnOK() 
{
	DynamicShow(this,0);		
	
	CDialog::OnOK();
}

void CBestDlg::OnClose() 
{
	DynamicShow(this,0);		
	CDialog::OnClose();
}

void CBestDlg::OnHelp1() 
{
	CHowToDlg dlg;
	dlg.SetHelpIndex (0);
	dlg.DoModal();	
}
