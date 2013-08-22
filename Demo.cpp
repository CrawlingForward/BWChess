// Demo.cpp : implementation file
//

#include "stdafx.h"
#include "BWChess.h"
#include "Demo.h"
#include "GlobalVar.h"
#include "HelperAPI.h"
#include "HowToDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDemo dialog
CDemo::CDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemo)
	m_BSkill = g_nCbSkill-1;
	m_WSkill = g_nCwSkill-1;
	m_Speed = 3-g_nCSpeed;
	m_FilePath = AfxGetApp()->GetProfileString(_T("Settings"), _T("PathName"), _T(""));
	m_IsFile = g_bIsFromFile;
	//}}AFX_DATA_INIT
	m_DyShow=0;
	m_Success=0;

	CFileStatus status;
	if(!CFile::GetStatus(m_FilePath,status))
		m_FilePath=_T("");
	else
	{
		CFile file(m_FilePath, CFile::modeRead);
		int buffer[9000];
		unsigned int reallen=file.Read(buffer,9000*sizeof(int));
		if(((reallen!=(buffer[0]*sizeof(int))) || (reallen<140)) ||
			(buffer[1]!=EDITION) || !buffer[2])
		{
			m_FilePath=_T("");
		}
		else
			m_Success=1;
	}
}

void CDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemo)
	DDX_Control(pDX, IDC_HELP0, m_Help);
	DDX_Control(pDX, IDC_BROWNS, m_Browns);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Radio(pDX, IDC_B1, m_BSkill);
	DDX_Radio(pDX, IDC_W1, m_WSkill);
	DDX_Radio(pDX, IDC_SPEED1, m_Speed);
	DDX_Text(pDX, IDC_FILEPATH, m_FilePath);
	DDX_Check(pDX, IDC_ISFILE, m_IsFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDemo, CDialog)
	//{{AFX_MSG_MAP(CDemo)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ISFILE, OnIsfile)
	ON_BN_CLICKED(IDC_BROWNS, OnBrowns)
	ON_BN_CLICKED(IDC_HELP0, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo message handlers

BOOL CDemo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDI_SETTING);
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

	m_Browns.SetIcon ( IDI_OPENFILE );
	m_Browns.SetBtnCursor(IDC_HAND);
	m_Browns.AddToolTip ( _T("打开...") );
	m_Browns.SetActiveFgColor(RGB(0,0,255));

	m_Help.SetIcon ( IDI_HELP2 );
	m_Help.AddToolTip ( _T("帮助") );
	m_Help.SetBtnCursor(IDC_HAND);
	m_Help.SetActiveFgColor(RGB(0,0,255));

	UpdateData();
	EnableCtrl(m_IsFile);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDemo::OnCancel() 
{
	DynamicShow(this,0);		
	
	CDialog::OnCancel();
}

void CDemo::OnOK() 
{
	UpdateData();
	if(m_IsFile && (!m_Success))
	{
		MsgBox(IDS_ERROR_NOFILE,IDS_TITLE_CHINESE);
		return;
	}

	g_nCbSkill=m_BSkill+1;
	g_nCwSkill=m_WSkill+1;
	g_nCSpeed=3-m_Speed;
	g_bIsFromFile=m_IsFile;
	DynamicShow(this,0);		
	AfxGetApp()->WriteProfileString(_T("Settings"), _T("PathName"), m_FilePath);    
	CDialog::OnOK();
}

void CDemo::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(m_DyShow==0)
	{
		m_DyShow++;
		DynamicShow(this,1);
	}
}

void CDemo::OnIsfile() 
{
	UpdateData();
	EnableCtrl(m_IsFile);
}

void CDemo::OnBrowns() 
{
	TCHAR sFilter[50]=_T("BWChess File (*.BWS)|*.BWS||");
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,sFilter);

	if(dlg.DoModal()==IDOK)
	{
		CFile file(dlg.GetPathName(), CFile::modeRead);
		int buffer[9000];
		unsigned int reallen=file.Read(buffer,9000*sizeof(int));
		if((reallen!=(buffer[0]*sizeof(int))) || (reallen<140))
		{
			MsgBox(IDS_OPENERROR1,IDS_TITLE_CHINESE);
			m_Success=0;
			return;
		}
		if(buffer[1]!=EDITION)
		{
			MsgBox(IDS_OPENERROR2,IDS_TITLE_CHINESE);
			m_Success=0;
			return;
		}
		if(!buffer[2])
		{
			MsgBox(IDS_OPENERROR4,IDS_TITLE_CHINESE);
			m_Success=0;
			return;
		}
		m_Success=1;
		m_FilePath=dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDemo::OnHelp() 
{
	CHowToDlg dlg;
	dlg.SetHelpIndex (5);
	dlg.DoModal();	
}

void CDemo::EnableCtrl(BOOL flag)//equal to m_IsFile
{
	GetDlgItem(IDC_B1)->EnableWindow(!flag);
	GetDlgItem(IDC_B2)->EnableWindow(!flag);
	GetDlgItem(IDC_B3)->EnableWindow(!flag);
	GetDlgItem(IDC_W1)->EnableWindow(!flag);
	GetDlgItem(IDC_W2)->EnableWindow(!flag);
	GetDlgItem(IDC_W3)->EnableWindow(!flag);
	m_Browns.EnableWindow(flag);
}
