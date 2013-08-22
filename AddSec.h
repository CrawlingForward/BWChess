#if !defined(AFX_ADDSEC_H__FAF01860_917F_11D4_B92C_5254AB200709__INCLUDED_)
#define AFX_ADDSEC_H__FAF01860_917F_11D4_B92C_5254AB200709__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddSec.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddSec dialog
#include "BtnST.h"

class CAddSec : public CDialog
{
// Construction
public:
	void SetSkill(int k);
	CAddSec(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddSec)
	enum { IDD = IDD_SEC };
	CEdit	m_Sec22;
	CEdit	m_Sec11;
	CButtonST	m_OK;
	CButtonST	m_Cancel;
	CString	m_Sec1;
	CString	m_Sec2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddSec)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_DyShow;
	int m_S_Skill1;

	// Generated message map functions
	//{{AFX_MSG(CAddSec)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDSEC_H__FAF01860_917F_11D4_B92C_5254AB200709__INCLUDED_)
