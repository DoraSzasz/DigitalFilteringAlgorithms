#pragma once


// CPowerDlg dialog

class CPowerDlg : public CDialog
{
	DECLARE_DYNAMIC(CPowerDlg)

public:
	CPowerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPowerDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
