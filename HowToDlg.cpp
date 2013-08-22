// HowToDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BWChess.h"
#include "HowToDlg.h"
#include "HelperAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LEN 119

/////////////////////////////////////////////////////////////////////////////
// CHowToDlg dialog


CHowToDlg::CHowToDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHowToDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHowToDlg)
	m_Content = _T("");
	//}}AFX_DATA_INIT
	m_DyShow=0;
	m_Index=-1;
}


void CHowToDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHowToDlg)
	DDX_Control(pDX, IDC_TITLE, m_Title);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Text(pDX, IDC_CONTENT, m_Content);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHowToDlg, CDialog)
	//{{AFX_MSG_MAP(CHowToDlg)
	ON_BN_CLICKED(IDC_ADVANCE, OnAdvance)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RULES, OnRules)
	ON_BN_CLICKED(IDC_HHINT, OnHhint)
	ON_BN_CLICKED(IDC_HOPEN, OnHopen)
	ON_BN_CLICKED(IDC_HSAVE, OnHsave)
	ON_BN_CLICKED(IDC_HSAVEINFO, OnHsaveinfo)
	ON_BN_CLICKED(IDC_HSETTING, OnHsetting)
	ON_BN_CLICKED(IDC_HUNDO, OnHundo)
	ON_BN_CLICKED(IDC_HHERO, OnHhero)
	ON_BN_CLICKED(IDC_HLIMIT, OnHlimit)
	ON_BN_CLICKED(IDC_HSEC, OnHsec)
	ON_BN_CLICKED(IDC_HDEMO, OnHdemo)
	ON_BN_CLICKED(IDC_HNETPLAY, OnHnetplay)
	ON_BN_CLICKED(IDC_HPEEP, OnHpeep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHowToDlg message handlers

void CHowToDlg::OnAdvance() 
{
	LoadHelp(IDS_HMIJUE0,IDS_HMIJUE1);
}

BOOL CHowToDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_HOWTO);
	SetIcon(hIcon, TRUE);		// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon
	CenterWindow();
	
	InitButton();

	if(m_Index<0)
	{
		m_Start=TRUE;
		CRect rc;
		GetWindowRect(&rc);
		rc.bottom -= LEN/2;
		rc.top+=LEN/2;
		MoveWindow(&rc);
	}
	else
	{
		m_Start=FALSE;
		switch(m_Index)
		{
		case 0:
			LoadHelp(IDS_HHERO0,IDS_HHERO1);
			break;
		case 1:
			LoadHelp(IDS_HSETTING0,IDS_HSETTING1);
			break;
		case 2:
			LoadHelp(IDS_HNETPLAY0,IDS_HNETPLAY1);
			break;
		case 3:
			LoadHelp(IDS_HSEC0,IDS_HSEC1);
			break;
		case 4:
			LoadHelp(IDS_HLIMIT0,IDS_HLIMIT1);
			break;
		case 5:
			LoadHelp(IDS_HDEMO0,IDS_HDEMO1);
			break;
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHowToDlg::SizeWindow(int length, int de)
{
	CRect rc;
	GetWindowRect(&rc);
	if(de)
	{
		for (int i= 0; i < length; i+=2)
		{
			rc.bottom--;
			rc.top++;
			//::Sleep(2);
			MoveWindow(&rc);
		}
	}
	else
	{
		for (int i= 0; i < length; i+=2)
		{
			rc.bottom++;
			rc.top--;
			//::Sleep(2);
			MoveWindow(&rc);
		}
	}
}

void CHowToDlg::OnPaint() 
{
	CPaintDC dc(this);// very important here

	if(!m_DyShow)
	{
		m_DyShow++;
		DynamicShow(this,1);
	}
}


void CHowToDlg::OnClose() 
{
	DynamicShow(this,0);		
	
	CDialog::OnClose();
}

void CHowToDlg::OnOK() 
{
	DynamicShow(this,0);		
	
	CDialog::OnOK();
}

void CHowToDlg::OnRules() 
{
	LoadHelp(IDS_HRULES0,IDS_HRULES1);
}

void CHowToDlg::LoadHelp(UINT iTitle, UINT iContent)
{
	CRect rc;
	GetWindowRect(&rc);
	if (!m_Start)
		SizeWindow(LEN,1);	
	else
		m_Start=FALSE;

	CString str;
	str.LoadString(iTitle);
	m_Title.SetWindowText(str);
	m_Content.LoadString(iContent);
	Sleep(200);

	UpdateData(FALSE);
	SizeWindow(LEN,0);
}

void CHowToDlg::OnHhint() 
{
	LoadHelp(IDS_HHINT0,IDS_HHINT1);
}

void CHowToDlg::OnHopen() 
{
	LoadHelp(IDS_HOPEN0,IDS_HOPEN1);
}

void CHowToDlg::OnHsave() 
{
	LoadHelp(IDS_HSAVE0,IDS_HSAVE1);
}

void CHowToDlg::OnHsaveinfo() 
{
	LoadHelp(IDS_HSAVEINFO0,IDS_HSAVEINFO1);
}

void CHowToDlg::OnHsetting() 
{
	LoadHelp(IDS_HSETTING0,IDS_HSETTING1);
}

void CHowToDlg::OnHundo() 
{
	LoadHelp(IDS_HUNDO0,IDS_HUNDO1);
}

void CHowToDlg::OnHhero() 
{
	LoadHelp(IDS_HHERO0,IDS_HHERO1);
}

void CHowToDlg::OnHlimit() 
{
	LoadHelp(IDS_HLIMIT0,IDS_HLIMIT1);
}

void CHowToDlg::OnHsec() 
{
	LoadHelp(IDS_HSEC0,IDS_HSEC1);
}

void CHowToDlg::OnHdemo() 
{
	LoadHelp(IDS_HDEMO0,IDS_HDEMO1);
}

void CHowToDlg::OnHnetplay() 
{
	LoadHelp(IDS_HNETPLAY0,IDS_HNETPLAY1);
}

void CHowToDlg::OnHpeep() 
{
	LoadHelp(IDS_HPEEP0,IDS_HPEEP1);
}

void CHowToDlg::SetHelpIndex(int Index)
{
	m_Index=Index;
}

void CHowToDlg::InitButton()
{
	m_OK.SetIcon ( IDI_SHANKHAND);
	m_OK.AddToolTip ( _T("ÎÒ¶®ÁË") );
	m_OK.SetBtnCursor(IDC_HAND);
	m_OK.SetActiveFgColor(RGB(0,0,255));
}
