// RecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BWChess.h"
#include "RecordDlg.h"
#include "Globalvar.h"
#include "HelperAPI.h"
#include "AddSec.h"
#include "HowToDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordDlg dialog


CRecordDlg::CRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecordDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_DyShow=0;
	m_IsAdd=0;
}


void CRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecordDlg)
	DDX_Control(pDX, IDC_HELP1, m_Help);
	DDX_Control(pDX, IDC_ADDSEC, m_AddSec);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecordDlg, CDialog)
	//{{AFX_MSG_MAP(CRecordDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ADDSEC, OnAddsec)
	ON_BN_CLICKED(IDC_HELP1, OnHelp1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordDlg message handlers

BOOL CRecordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDI_RECORD);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CenterWindow();

	m_OK.SetIcon ( IDI_OPEN );
	m_OK.AddToolTip ( _T("确定") );
	m_OK.SetBtnCursor(IDC_HAND);
	m_OK.SetActiveFgColor(RGB(0,0,255));

	m_Cancel.SetIcon ( IDI_CANCEL );
	m_Cancel.AddToolTip ( _T("取消") );
	m_Cancel.SetBtnCursor(IDC_HAND);
	m_Cancel.SetActiveFgColor(RGB(0,0,255));

	m_AddSec.SetIcon ( IDI_SEC1 );
	m_AddSec.AddToolTip ( _T("加密") );
	m_AddSec.SetBtnCursor(IDC_HAND);
	m_AddSec.SetActiveFgColor(RGB(0,0,255));

	m_Help.SetIcon ( IDI_HELP2 );
	m_Help.AddToolTip ( _T("帮助") );
	m_Help.SetBtnCursor(IDC_HAND);
	m_Help.SetActiveFgColor(RGB(0,0,255));

	CString str;
	if (g_nSkill == 1)
	{
		str.LoadString(IDS_BEGINNER_CHINESE);
		SkillEdit().SetWindowText(str);
		NameEdit().SetWindowText(g_strName1);
	}
	else if (g_nSkill == 2)
	{
		str.LoadString(IDS_INTERMEDIATE_CHINESE);
		SkillEdit().SetWindowText(str);
		NameEdit().SetWindowText(g_strName2);
	}
	if (g_nSkill == 3)
	{
		str.LoadString(IDS_EXPERT_CHINESE);
		SkillEdit().SetWindowText(str);
		NameEdit().SetWindowText(g_strName3);
	}
	
	NameEdit().SetSel(0, -1);
	NameEdit().SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecordDlg::OnOK() 
{
	if (g_nSkill == 1)
	{
		NameEdit().GetWindowText(g_strName1);
		g_nTime1 = g_nStoneNum;
		g_nMark1=g_nBestMark;
		if(!m_IsAdd)
			g_strSec1=_T("");
	}
	else if (g_nSkill == 2)
	{
		NameEdit().GetWindowText(g_strName2);
		g_nTime2 = g_nStoneNum;
		g_nMark2=g_nBestMark;
		if(!m_IsAdd)
			g_strSec2=_T("");
	}
	if (g_nSkill == 3)
	{
		NameEdit().GetWindowText(g_strName3);
		g_nTime3 = g_nStoneNum;
		g_nMark3=g_nBestMark;
		if(!m_IsAdd)
			g_strSec3=_T("");
	}         
	
	DynamicShow(this,0);		
	CDialog::OnOK();
}

void CRecordDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if(!m_DyShow)
	{
		m_DyShow++;
		DynamicShow(this,1);
	}
}

void CRecordDlg::OnCancel() 
{
	DynamicShow(this,0);	
	switch(g_nSkill)
	{
	case 1:
		g_strSec1=m_tSec;
		break;
	case 2:
		g_strSec2=m_tSec;
		break;
	case 3:
		g_strSec3=m_tSec;
		break;
	}
	
	CDialog::OnCancel();
}


void CRecordDlg::OnAddsec() 
{
	switch(g_nSkill)
	{
	case 1:
		m_tSec=g_strSec1;
		break;
	case 2:
		m_tSec=g_strSec2;
		break;
	case 3:
		m_tSec=g_strSec3;
		break;
	}

	CAddSec dlg;
	dlg.DoModal();
	m_IsAdd=1;
}

void CRecordDlg::OnHelp1() 
{
	CHowToDlg dlg;
	dlg.SetHelpIndex (3);
	dlg.DoModal();	
}
