// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AboutDlg.h"
#include "Globalvar.h"
#include "HelperAPI.h"

#define LENGTHES 170

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog


CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_DyShow=0;
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_DYSTATIC, m_DyStatic);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_ADDRESS, m_Address);
	DDX_Control(pDX, IDC_MORE, m_More);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_MORE, OnMore)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);		// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon
	CenterWindow();
	
	m_Address.SetURL ( _T("mailto:shuker@263.net") );
	m_Address.SetLinkCursor ( AfxGetApp()->LoadCursor ( IDC_HAND ) );
	m_Address.SetToolTip( _T("发邮件至：shuker@263.net") );
	m_Address.SetUnderline();
	m_Address.SetItalic();

	m_OK.SetIcon ( IDI_OPEN );
	m_OK.AddToolTip ( _T("确定") );
	m_OK.SetBtnCursor(IDC_HAND);
	m_OK.SetActiveFgColor(RGB(0,0,255));

	m_More.SetIcon ( IDI_MORE );
	m_More.AddToolTip ( _T("更多的...") );
	m_More.SetBtnCursor(IDC_HAND);
	m_More.SetActiveFgColor(RGB(0,0,255));

	CString str;

	// fill memory info
	MEMORYSTATUS MemStat;
	MemStat.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&MemStat);
	// Total Physical mem
	str.Format( _T("%lu KB"), MemStat.dwTotalPhys / 1024L);
	SetDlgItemText(IDC_PHYSICAL_MEM, str);
	// Free Physical mem
	str.Format( _T("%lu KB"), MemStat.dwAvailPhys / 1024L);
	SetDlgItemText(IDC_AVAIL_MEM, str);
	// Free Virtual mem
	str.Format( _T("%lu KB"), MemStat.dwAvailVirtual / 1024L);
	SetDlgItemText(IDC_AVAIL_VIRTUAL_MEM, str);

	// fill CPU info
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	switch (SysInfo.dwProcessorType)
	{
	case PROCESSOR_INTEL_486:
			str = _T("Intel 80486");
			break;
	case PROCESSOR_INTEL_PENTIUM:
			str = _T("Intel Pentium");
			break;
	default:
			str = _T("");
			break;
	}
	SetDlgItemText(IDC_CPU, str);

	// fill OS info
	OSVERSIONINFO OsInfo;
	OsInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&OsInfo))
	{
		// platform
		switch (OsInfo.dwPlatformId)
		{
		case VER_PLATFORM_WIN32_WINDOWS:
			str = _T("Windows 95/98");
			break;
		case VER_PLATFORM_WIN32_NT:
			str = _T("Windows NT");
			break;
		default:
			str = _T("");
			break;
		}
		SetDlgItemText(IDC_OS, str);

		// version and language
		TCHAR   szVer[512]= _T("不明");
		GetWindowsVersion((LPSTR)szVer);

		str.Format(_T("%ld.%ld, %s"), OsInfo.dwMajorVersion, 
							OsInfo.dwMinorVersion, szVer);
		SetDlgItemText(IDC_VERSION, str);
	}

	// fill disk information
	TCHAR szWindowsPath[_MAX_PATH];
	GetWindowsDirectory(szWindowsPath, _MAX_PATH);
	ULARGE_INTEGER TotalNumberOfBytes, TotalNumberOfFreeBytes;
	GetDiskFreeSpaceEx((LPSTR)szWindowsPath,
						NULL,
						&TotalNumberOfBytes,
						&TotalNumberOfFreeBytes);
	// total space
	str.Format(_T("%lu KB"), TotalNumberOfBytes.QuadPart / 1024L);
	SetDlgItemText(IDC_TOTAL_SPACE, str);
	// free space
	str.Format(_T("%lu KB"), TotalNumberOfFreeBytes.QuadPart / 1024L);
	SetDlgItemText(IDC_FREE_SPACE, str);

	m_Max=0;
	CRect rc;
	GetWindowRect(&rc);
	rc.top+=LENGTHES/2;
	rc.bottom -= LENGTHES/2;
	MoveWindow(&rc);

	TCHAR *pArrCredit = { 
		_T("黑白棋\t|"
        "1.6版||"
        "作者\r|上海财经大学98信息系|"
        "蔡莹||"    // this is a quoted bitmap resource 
		"声明\r"
		"|本软件属于自由免费软件"
		"|您可以任意拷贝"
		"|如有任何意见或建议"
		"|请给我发邮件"
		"|E-mail:  shuker@263.net"
		"|您的意见对我很重要！"
		"|||||")};
	
	// TODO: Add extra initialization here
	m_DyStatic.SubclassDlgItem(IDD_ABOUTDLG1,this);
	m_DyStatic.SetCredits(pArrCredit,'|');
	m_DyStatic.SetSpeed(g_nStrollSpeed);//you can change it in the regedit
	m_DyStatic.SetColor(BACKGROUND_COLOR, RGB(0,255,200));
	m_DyStatic.SetTransparent();
	m_DyStatic.SetGradient(GRADIENT_RIGHT_DARK);
	m_DyStatic.StartScrolling();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnMore() 
{
	m_More.EnableWindow( false );
	CRect rc;
	GetWindowRect(&rc);
	if (m_Max)
	{
		SizeWindow(LENGTHES,1);
		SetDlgItemText(IDC_MORE,_T("更多的"));
		m_More.AddToolTip ( _T("更多的...") );
	}
	else
	{
		SizeWindow(LENGTHES,0);
		SetDlgItemText(IDC_MORE,_T("隐藏"));
		m_More.AddToolTip ( _T("隐藏") );
	}
	m_Max = !m_Max;
	m_More.EnableWindow( true );
	UpdateWindow();		
}

void CAboutDlg::SizeWindow(int length, int de)//de ==1 for making small,else for large
{
	CRect rc;
	GetWindowRect(&rc);
	if(de)
	{
		for (int i= 0; i < length; i+=2)
		{
			rc.bottom--;
			rc.top++;
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

void CAboutDlg::OnPaint() 
{
	CPaintDC dc(this);
	if(m_DyShow==0)
	{
		m_DyShow++;
		DynamicShow(this,1);
	}
}

void CAboutDlg::OnOK() 
{
	DynamicShow(this,0);		
	CDialog::OnOK();
}

void CAboutDlg::OnClose() 
{
	DynamicShow(this,0);	
	CDialog::OnClose();
}

int CAboutDlg::GetWindowsVersion(LPSTR strVersion)
{
	TCHAR lpszSysPath[512];	/* address of buffer for Windows directory	*/

	GetWindowsDirectory(lpszSysPath, 512);
	lstrcat(lpszSysPath,_T("\\system\\user.exe"));

	BYTE   abData[512];
	DWORD  handle;
	DWORD  dwSize;
	typedef struct tagLANGANDCP
	{
    	WORD wLanguage;
    	WORD wCodePage;
  	} LANGANDCP;
    LANGANDCP FAR  *lpBuffer;           // holds lang and codepage

	dwSize = GetFileVersionInfoSize(lpszSysPath, &handle);
#ifdef _DEBUG
	if(!dwSize)
		return 0;
#endif 

	GetFileVersionInfo(lpszSysPath, handle, dwSize, abData);

	VerQueryValue(abData, _T("\\VarFileInfo\\Translation"), (VOID FAR* FAR*)&lpBuffer, (UINT FAR *)&dwSize);
  	VerLanguageName (lpBuffer->wLanguage, strVersion, 512);

    return LOBYTE(LOWORD(GetVersion())); // windows version greater than 3.x?
}
