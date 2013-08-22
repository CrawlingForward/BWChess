#if !defined(AFX_NETPLAY_H__9F315A84_3112_4C0F_ACCC_7E27DEBEDB06__INCLUDED_)
#define AFX_NETPLAY_H__9F315A84_3112_4C0F_ACCC_7E27DEBEDB06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetPlay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetPlay dialog
#include "BtnST.h"

class CNetPlay : public CDialog
{
// Construction
public:
	CNetPlay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetPlay)
	enum { IDD = IDD_NETPLAY };
	CButtonST	m_Help;
	CButtonST	m_MoRen;
	CButtonST	m_Cancel;
	CIPAddressCtrl	m_IP;
	CButtonST	m_Connect;
	CString	m_Name;
	int		m_S1;
	int		m_Port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetPlay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_DyShow;

	// Generated message map functions
	//{{AFX_MSG(CNetPlay)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnCancel();
	afx_msg void OnConnect();
	afx_msg void OnClient();
	afx_msg void OnServer();
	afx_msg void OnMoren();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETPLAY_H__9F315A84_3112_4C0F_ACCC_7E27DEBEDB06__INCLUDED_)
