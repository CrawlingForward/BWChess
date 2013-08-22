#if !defined(AFX_MESSAGE1_H__68677451_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
#define AFX_MESSAGE1_H__68677451_7A80_11D4_9B45_8E32258B560A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Message1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessage1 dialog
#include "BtnST.h"
#include "Resource.h"

class CMessage1 : public CDialog
{
// Construction
public:
	void SetContent(const CString &con);
	void SetTitle(const CString &title);
	CMessage1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessage1)
	enum { IDD = IDD_MESSAGE1 };
	CButtonST	m_OK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMessage1)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_con;
	CString m_title;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGE1_H__68677451_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
