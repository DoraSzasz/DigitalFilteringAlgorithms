
// LFP_Demo_DialogDlg.h : header file
//

#pragma once
#include "mytabctrl.h"
#include "FilterDlg.h"
#include "CorrelDlg.h"
#include "PowerDlg.h"


// CLFP_Demo_DialogDlg dialog
class CLFP_Demo_DialogDlg : public CDialog
{
// Construction
public:
	CLFP_Demo_DialogDlg(CWnd* pParent = NULL);	// standard constructor


	CFilterDlg	m_dFilterDlg;
	CCorrelDlg	m_dCorrelDlg;
	CPowerDlg	m_dPowerDlg;

// Dialog Data
	enum { IDD = IDD_LFP_DEMO_DIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CBrush m_brush;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CRect m_rSettingsRect;
public:
	void ShowWindowNumber(int number);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CMyTabCtrl m_ctlMyTabControl;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};