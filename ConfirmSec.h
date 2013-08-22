#if !defined(AFX_CONFIRMSEC_H__FAF01862_917F_11D4_B92C_5254AB200709__INCLUDED_)
#define AFX_CONFIRMSEC_H__FAF01862_917F_11D4_B92C_5254AB200709__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfirmSec.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfirmSec dialog
#include "BtnST.h"

class CConfirmSec : public CDialog
{
// Construction
public:
	void SetSkill(int k);
	CConfirmSec(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfirmSec)
	enum { IDD = IDD_CONFIRMSEC };
	CEdit	m_Sec0;
	CButtonST	m_OK;
	CButtonST	m_Cancel;
	CString	m_Sec;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfirmSec)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetTitle();
	int m_DyShow;
	int m_S_Skill1;

	// Generated message map functions
	//{{AFX_MSG(CConfirmSec)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIRMSEC_H__FAF01862_917F_11D4_B92C_5254AB200709__INCLUDED_)
