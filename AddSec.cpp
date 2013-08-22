// AddSec.cpp : implementation file
//

#include "stdafx.h"
#include "BWChess.h"
#include "AddSec.h"
#include "GlobalVar.h"
#include "HelperAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddSec dialog


CAddSec::CAddSec(CWnd* pParent /*=NULL*/)
	: CDialog(CAddSec::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddSec)
	m_Sec1 = _T("");
	m_Sec2 = _T("");
	//}}AFX_DATA_INIT
	m_DyShow=0;
}


void CAddSec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddSec)
	DDX_Control(pDX, IDC_SEC2, m_Sec22);
	DDX_Control(pDX, IDC_SEC1, m_Sec11);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Text(pDX, IDC_SEC1, m_Sec1);
	DDV_MaxChars(pDX, m_Sec1, 15);
	DDX_Text(pDX, IDC_SEC2, m_Sec2);
	DDV_MaxChars(pDX, m_Sec2, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddSec, CDialog)
	//{{AFX_MSG_MAP(CAddSec)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddSec message handlers

void CAddSec::OnOK() 
{
	UpdateData(TRUE);
	if(m_Sec1.GetLength()==0)
	{
		MsgBox(IDS_SEC_ERR1,IDS_SEC_ERR0);
		m_Sec11.SetFocus();
		return ;
	}
	if(m_Sec1!=m_Sec2)
	{
		MsgBox(IDS_SEC_ERR2,IDS_SEC_ERR0);
		m_Sec22.SetSel(0, -1);
		m_Sec22.SetFocus();
		return;
	}

	switch(g_nSkill)
	{
	case 1:
		g_strSec1=m_Sec1;
		break;
	case 2:
		g_strSec2=m_Sec1;
		break;
	case 3:
		g_strSec3=m_Sec1;
		break;
	}	
	DynamicShow(this,0);		
	
	CDialog::OnOK();
}

void CAddSec::OnCancel() 
{
	DynamicShow(this,0);		
	
	CDialog::OnCancel();
}

BOOL CAddSec::OnInitDialog() 
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

	m_Sec11.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddSec::SetSkill(int k)
{
	m_S_Skill1=k;
}

void CAddSec::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(m_DyShow==0)
	{
		m_DyShow++;
		DynamicShow(this,1);
	}
}
