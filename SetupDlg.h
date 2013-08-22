#if !defined(AFX_SETUPDLG_H__0594D946_C085_4AC8_8B75_99BAE318EB17__INCLUDED_)
#define AFX_SETUPDLG_H__0594D946_C085_4AC8_8B75_99BAE318EB17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog
#include "BtnST.h"

class CSetupDlg : public CDialog
{
// Construction
public:
	CSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupDlg)
	enum { IDD = IDD_SETUPDLG1 };
	CButtonST	m_Help;
	CEdit	m_TimeNumC;
	CSpinButtonCtrl	m_Spin;
	CButton	m_NoNeedLimit;
	CButtonST	m_Cancel;
	CButtonST	m_OK;
	int		m_PlayMode;
	int		m_WhoFirst;
	int		m_Skill;
	int		m_TimeNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableCtrl(BOOL flag);
	int m_DyShow;

	// Generated message map functions
	//{{AFX_MSG(CSetupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnRadio2player();
	afx_msg void OnRadioWithcomputer();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnNoneedtime();
	afx_msg void OnHelp1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDLG_H__0594D946_C085_4AC8_8B75_99BAE318EB17__INCLUDED_)
