#if !defined(AFX_DEMO_H__5020BA92_3ECE_4F90_9CDC_B75583D1643D__INCLUDED_)
#define AFX_DEMO_H__5020BA92_3ECE_4F90_9CDC_B75583D1643D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Demo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDemo dialog
#include "BtnST.h"

class CDemo : public CDialog
{
// Construction
public:
	CDemo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDemo)
	enum { IDD = IDD_DEMO };
	CButtonST	m_Help;
	CButtonST	m_Browns;
	CButtonST	m_OK;
	CButtonST	m_Cancel;
	int		m_BSkill;
	int		m_WSkill;
	int		m_Speed;
	CString	m_FilePath;
	BOOL	m_IsFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableCtrl(BOOL flag);
	int m_Success;
	int m_DyShow;

	// Generated message map functions
	//{{AFX_MSG(CDemo)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnIsfile();
	afx_msg void OnBrowns();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO_H__5020BA92_3ECE_4F90_9CDC_B75583D1643D__INCLUDED_)
