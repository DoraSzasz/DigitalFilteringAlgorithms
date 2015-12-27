#pragma once

#include "FilterDlg.h"
#include "afxwin.h"

// CAddWinFctDlg dialog

class CAddWinFctDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddWinFctDlg)

public:
	//CAddWinFctDlg(CWnd* pParent = NULL);   // standard constructor
	CAddWinFctDlg(CDialog* filterDialog, CWnd* pParent = NULL);   // standard constructor

	virtual ~CAddWinFctDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG4 };

private:
	CDialog*	m_FilterDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	// control variable for the control box that selects the window type
	CComboBox m_cbWindowType;

public:
	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnBnClickedOk();
	void AddWindowToList( int FilterId );
	
};
