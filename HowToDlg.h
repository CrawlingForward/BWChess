#if !defined(AFX_HOWTODLG_H__68677450_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
#define AFX_HOWTODLG_H__68677450_7A80_11D4_9B45_8E32258B560A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HowToDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHowToDlg dialog
#include "BtnST.h"

class CHowToDlg : public CDialog
{
// Construction
public:
	void SetHelpIndex(int Index);
	CHowToDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHowToDlg)
	enum { IDD = IDD_HOWTO1 };
	CButton		m_Title;
	CButtonST	m_OK;
	CString	    m_Content;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHowToDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InitButton();
	void LoadHelp(UINT iTitle,UINT iContent);
//	void DynamicShow();
	void SizeWindow(int length, int de);

	// Generated message map functions
	//{{AFX_MSG(CHowToDlg)
	afx_msg void OnAdvance();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	virtual void OnOK();
	afx_msg void OnRules();
	afx_msg void OnHhint();
	afx_msg void OnHopen();
	afx_msg void OnHsave();
	afx_msg void OnHsaveinfo();
	afx_msg void OnHsetting();
	afx_msg void OnHundo();
	afx_msg void OnHhero();
	afx_msg void OnHlimit();
	afx_msg void OnHsec();
	afx_msg void OnHdemo();
	afx_msg void OnHnetplay();
	afx_msg void OnHpeep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_Index;
	int m_DyShow;
	BOOL m_Start;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOWTODLG_H__68677450_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
