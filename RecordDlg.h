#if !defined(AFX_RECORDDLG_H__68677453_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
#define AFX_RECORDDLG_H__68677453_7A80_11D4_9B45_8E32258B560A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecordDlg dialog
#include "BtnST.h"

class CRecordDlg : public CDialog
{
// Construction
public:
	CRecordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRecordDlg)
	enum { IDD = IDD_RECORD1 };
	CButtonST	m_Help;
	CButtonST	m_AddSec;
	CButtonST	m_OK;
	CButtonST	m_Cancel;
	//}}AFX_DATA
protected:
	CEdit&     	NameEdit() 
				{ return *(CEdit*)GetDlgItem(IDC_EDIT1); }
	CEdit&     	SkillEdit() 
				{ return *(CEdit*)GetDlgItem(IDC_EDIT2); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_IsAdd;
	CString m_tSec;

	// Generated message map functions
	//{{AFX_MSG(CRecordDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	virtual void OnCancel();
	afx_msg void OnAddsec();
	afx_msg void OnHelp1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_DyShow;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDDLG_H__68677453_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
