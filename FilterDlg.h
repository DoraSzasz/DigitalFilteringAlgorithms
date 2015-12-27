#pragma once
#include "AddWinFctDlg.h"
#include "AddFilterDlg.h"
#include "afxwin.h"



// CFilterDlg dialog

class CFilterDlg : public CDialog
{
	DECLARE_DYNAMIC(CFilterDlg)

public:
	CFilterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFilterDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	CListBox m_ctlListBox;
	afx_msg void OnBnClickedButton5();

	void AddWindowToList(int WindowId);
	void AddFilterToList( int* FilterProp );
	afx_msg void OnBnClickedButtonAddFilter();
protected:
	CEdit m_ctlEditFilterLen;
	CEdit m_ctlEditFFTLen;
public:
	afx_msg void OnEnChangeEditFilterLen();
	CButton m_btAddWindowFct;
protected:
	CButton m_btAddFilter;
public:
	CButton m_btRemoveItem;
protected:
	CButton m_btFilter;
	int m_nFilterLen;
	// //length of the Fast Fourier Transform
	int m_nFFTLen;
public:
	afx_msg void OnEnChangeEditFftLen();
protected:
	// //a string containing the name of the input file
	CString m_sInputFileName;
	// //control for the Set Input File Button
	CButton m_btSetInputFile;
	CStatic m_ctlSignalInfoTextBox;
public:
	afx_msg void OnBnClickedSetInputFile();
protected:
	// //pointer to a vector that holds the input signal
	double* m_vdInputSignal;
	CEdit m_ctlInputFileEditBox;
};
