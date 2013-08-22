#if !defined(AFX_BESTDLG_H__6867744F_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
#define AFX_BESTDLG_H__6867744F_7A80_11D4_9B45_8E32258B560A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBestDlg dialog
#include "BtnST.h"

class CBestDlg : public CDialog
{
// Construction
public:
	CBestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBestDlg)
	enum { IDD = IDD_BEST1 };
	CButtonST	m_Help;
	CButtonST	m_Rule;
	CButtonST	m_OK;
	CButtonST	m_Reset;
	CString	m_S1;
	CString	m_S2;
	CString	m_S3;
	//}}AFX_DATA
protected:
	CEdit&     	Name1Edit() 
				{ return *(CEdit*)GetDlgItem(IDC_EDIT1); }
	CEdit&     	Name2Edit() 
				{ return *(CEdit*)GetDlgItem(IDC_EDIT2); }
	CEdit&     	Name3Edit() 
				{ return *(CEdit*)GetDlgItem(IDC_EDIT3); }
	CEdit&     	Time1Edit() 
				{ return *(CEdit*)GetDlgItem(IDC_EDIT4); }
	CEdit&     	Time2Edit() 
				{ return *(CEdit*)GetDlgItem(IDC_EDIT5); }
	CEdit&     	Time3Edit() 
				{ return *(CEdit*)GetDlgItem(IDC_EDIT6); }
	CEdit&     	Mark1Edit() 
				{ return *(CEdit*)GetDlgItem(IDC_EDIT7); }
	CEdit&     	Mark2Edit() 
				{ return *(CEdit*)GetDlgItem(IDC_EDIT8); }
	CEdit&     	Mark3Edit() 
				{ return *(CEdit*)GetDlgItem(IDC_EDIT9); }


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	void DynamicShow();

	// Generated message map functions
	//{{AFX_MSG(CBestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRestartcount();
	afx_msg void OnRule();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnHelp1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_DyShow;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BESTDLG_H__6867744F_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
