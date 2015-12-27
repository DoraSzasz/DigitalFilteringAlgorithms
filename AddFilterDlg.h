#pragma once
#include "afxwin.h"


// CAddFilterDlg dialog

class CAddFilterDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddFilterDlg)

public:
	CAddFilterDlg(CWnd* pParent = NULL);   // standard constructor
	CAddFilterDlg(CDialog* pCallerDialog, CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddFilterDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CComboBox m_ctlComboBox;
	CEdit m_ctlPassEdit;
	CEdit m_ctlEditCutoff;

	CDialog* m_dCallerDialog;
public:
	afx_msg void OnCbnDropdownComboFilterType();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
};
