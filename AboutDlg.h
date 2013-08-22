#if !defined(AFX_ABOUTDLG_H__6867744E_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
#define AFX_ABOUTDLG_H__6867744E_7A80_11D4_9B45_8E32258B560A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog
#include "BtnST.h"
#include "HyperLink.h"
#include "Resource.h"
#include "CreditStatic.h"

class CAboutDlg : public CDialog
{
// Construction
public:
	int GetWindowsVersion(LPSTR strVersion);
	CAboutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTDLG1 };
	CCreditStatic	m_DyStatic;
	CButtonST	m_OK;
	CHyperLink	m_Address;
	CButtonST	m_More;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SizeWindow(int length,int de);
//	void DynamicShow();

	// Generated message map functions
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnMore();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_Max;
	int m_DyShow;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTDLG_H__6867744E_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
