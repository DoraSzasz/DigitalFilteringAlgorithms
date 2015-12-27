
// LFP_Demo_DialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LFP_Demo_Dialog.h"
#include "LFP_Demo_DialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLFP_Demo_DialogDlg dialog




CLFP_Demo_DialogDlg::CLFP_Demo_DialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLFP_Demo_DialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLFP_Demo_DialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_ctlMyTabControl);
}

BEGIN_MESSAGE_MAP(CLFP_Demo_DialogDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CLFP_Demo_DialogDlg::OnTcnSelchangeTab1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLFP_Demo_DialogDlg message handlers

BOOL CLFP_Demo_DialogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_brush.CreateSolidBrush(RGB(205, 215, 150)); // color white brush 

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect tabRect;

	m_ctlMyTabControl.GetWindowRect(tabRect);

	// Set the size and location of the child windows based on the tab control

	m_rSettingsRect.left = 13;
	m_rSettingsRect.top = 44;
	m_rSettingsRect.right = tabRect.Width() - 7;
	m_rSettingsRect.bottom = tabRect.Height() - 38;

	// Create the child windows for the main window class

	m_dFilterDlg.Create(IDD_DIALOG1, this);
	m_dCorrelDlg.Create(IDD_DIALOG2, this);
	m_dPowerDlg.Create(IDD_DIALOG3, this);
	
	// This is redundant with the default value, considering what OnShowWindow does

	ShowWindowNumber(0);

	// Set the titles for each tab

	TCITEM tabItem;
	tabItem.mask = TCIF_TEXT;

	tabItem.pszText = _T("  &Filter   ");
	m_ctlMyTabControl.InsertItem(0, &tabItem);

	tabItem.pszText = _T("  Correlate   ");
	m_ctlMyTabControl.InsertItem(1, &tabItem);

	tabItem.pszText = _T("  Power Spectrum    ");
	m_ctlMyTabControl.InsertItem(2, &tabItem);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLFP_Demo_DialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLFP_Demo_DialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLFP_Demo_DialogDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// When the dialog is shown, display the first window

	if (bShow)
	{
		ShowWindowNumber(0);
	}
}

void CLFP_Demo_DialogDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Get the number of the currently selected tab, and show its window

	ShowWindowNumber(m_ctlMyTabControl.GetCurFocus());

	// Do something with the "formal parameters" so 

	// the compiler is happy in warning level 4

	pNMHDR = NULL;
	pResult = NULL;
}

void CLFP_Demo_DialogDlg::ShowWindowNumber(int number)
{
	// This example uses four windows

	int windowCount = 3;

	// Validate the parameter

	if ((number >= 0) && (number < windowCount))
	{
		// Create and assign pointers to each window

		CDialog *m_dPointer[3];

		m_dPointer[0] = &m_dFilterDlg;
		m_dPointer[1] = &m_dCorrelDlg;
		m_dPointer[2] = &m_dPowerDlg;

		// Hide every window except for the chosen one

		for (int count = 0; count < windowCount; count++)
		{
			if (count != number)
			{
				m_dPointer[count]->ShowWindow(SW_HIDE);
			}
			else if (count == number)
			{
				// Show the chosen window and set it's location

				m_dPointer[count]->SetWindowPos(&wndTop, m_rSettingsRect.left,
					m_rSettingsRect.top, m_rSettingsRect.right,
					m_rSettingsRect.bottom, SWP_SHOWWINDOW);

				m_ctlMyTabControl.SetCurSel(count);
			}
		}
	}
}

HBRUSH CLFP_Demo_DialogDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	/*
	** No need to do this!
	**
	** HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	*/

	/*
	** Return the white brush.
	*/
	return m_brush;
}
