#if !defined(AFX_SETTINGDLG_H__BC3B88A0_7E62_11D4_9B45_DC4C9AE68892__INCLUDED_)
#define AFX_SETTINGDLG_H__BC3B88A0_7E62_11D4_9B45_DC4C9AE68892__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog
#include "BtnST.h"

class CSettingDlg : public CDialog
{
// Construction
public:
	CSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg)
	enum { IDD = IDD_SETTING1 };
	CButtonST	m_Help;
	CButtonST	m_OK;
	CButtonST	m_Cancel;
	BOOL	m_Dynamic;
	BOOL	m_PeepOften;
	BOOL	m_SoundOn;
	BOOL	m_TopMost;
	BOOL	m_ShowDynamic;
	int		m_Speed;
	BOOL	m_Prompt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSettingDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	virtual void OnCancel();
	afx_msg void OnDynamic();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_DyShow;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__BC3B88A0_7E62_11D4_9B45_DC4C9AE68892__INCLUDED_)
