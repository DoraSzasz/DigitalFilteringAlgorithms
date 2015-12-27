#pragma once


// CCorrelDlg dialog

class CCorrelDlg : public CDialog
{
	DECLARE_DYNAMIC(CCorrelDlg)

public:
	CCorrelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCorrelDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
