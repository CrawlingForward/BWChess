// ConfirmSec.cpp : implementation file
//

#include "stdafx.h"
#include "BWChess.h"
#include "ConfirmSec.h"
#include "GlobalVar.h"
#include "HelperAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfirmSec dialog


CConfirmSec::CConfirmSec(CWnd* pParent /*=NULL*/)
	: CDialog(CConfirmSec::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfirmSec)
	m_Sec = _T("");
	//}}AFX_DATA_INIT
	m_DyShow=0;
}


void CConfirmSec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfirmSec)
	DDX_Control(pDX, IDC_SEC, m_Sec0);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Text(pDX, IDC_SEC, m_Sec);
	DDV_MaxChars(pDX, m_Sec, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfirmSec, CDialog)
	//{{AFX_MSG_MAP(CConfirmSec)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfirmSec message handlers

void CConfirmSec::OnOK() 
{
	UpdateData(TRUE);

	CString temp;
	switch(m_S_Skill1)
	{
	case 1:
		temp=g_strSec1;
		break;
	case 2:
		temp=g_strSec2;
		break;
	case 3:
		temp=g_strSec3;
		break;
	}
	if(temp!=m_Sec)
	{
		MsgBox(IDS_SEC_ERR3,IDS_SEC_ERR0);
		m_Sec0.SetSel(0, -1);
		m_Sec0.SetFocus();
		return;
	}
	DynamicShow(this,0);		
	
	CDialog::OnOK();
}

BOOL CConfirmSec::OnInitDialog() 
{
	CDialog::OnInitDialog();
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDI_SEC0);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CenterWindow();
	
	m_OK.SetIcon ( IDI_OPEN );
	m_OK.SetBtnCursor(IDC_HAND);
	m_OK.AddToolTip ( _T("确定") );
	m_OK.SetActiveFgColor(RGB(0,0,255));

	m_Cancel.SetIcon ( IDI_CANCEL );
	m_Cancel.AddToolTip ( _T("取消") );
	m_Cancel.SetBtnCursor(IDC_HAND);
	m_Cancel.SetActiveFgColor(RGB(0,0,255));

	SetTitle();
	m_Sec0.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfirmSec::SetSkill(int k)
{
	m_S_Skill1=k;
}

void CConfirmSec::OnCancel() 
{
	DynamicShow(this,0);		
	
	CDialog::OnCancel();
}

void CConfirmSec::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(m_DyShow==0)
	{
		m_DyShow++;
		DynamicShow(this,1);
	}
}

void CConfirmSec::SetTitle()
{
	CString str2,str3,str4;
	str4.LoadString(IDS_CONSEC);
	switch(m_S_Skill1)
	{
	case 1:
		str2.LoadString(IDS_BEGINNER_CHINESE);
		break;
	case 2:
		str2.LoadString(IDS_INTERMEDIATE_CHINESE);
		break;
	case 3:
		str2.LoadString(IDS_EXPERT_CHINESE);
		break;
	}
	str3=str4+"："+str2;
	SetWindowText(str3);
}
