#if !defined(AFX_MESSAGE2_H__68677452_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
#define AFX_MESSAGE2_H__68677452_7A80_11D4_9B45_8E32258B560A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Message2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessage2 dialog
#include "BtnST.h"
#include "Resource.h"

class CMessage2 : public CDialog
{
// Construction
public:
	void SetTitle(const CString &title);
	void SetContent(const CString &con);
	CMessage2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessage2)
	enum { IDD = IDD_MESSAGE2 };
	CButtonST	m_OK;
	CButtonST	m_Cancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMessage2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_con;
	CString m_title;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGE2_H__68677452_7A80_11D4_9B45_8E32258B560A__INCLUDED_)
