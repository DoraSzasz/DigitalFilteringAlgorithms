// AddWinFctDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LFP_Demo_Dialog.h"
#include "AddWinFctDlg.h"
#include "MyDefinitions.h"


// CAddWinFctDlg dialog

IMPLEMENT_DYNAMIC(CAddWinFctDlg, CDialog)

//CAddWinFctDlg::CAddWinFctDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CAddWinFctDlg::IDD, pParent),m_FilterDlg(NULL)
//{
//
//}

CAddWinFctDlg::CAddWinFctDlg(CDialog* filterDialog,CWnd* pParent /*=NULL*/)
: CDialog(CAddWinFctDlg::IDD, pParent)
{
	m_FilterDlg=filterDialog;

}

CAddWinFctDlg::~CAddWinFctDlg()
{
}

void CAddWinFctDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbWindowType);
}


BEGIN_MESSAGE_MAP(CAddWinFctDlg, CDialog)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CAddWinFctDlg::OnCbnDropdownCombo1)
	ON_BN_CLICKED(IDOK, &CAddWinFctDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddWinFctDlg message handlers

void CAddWinFctDlg::OnCbnDropdownCombo1()
{
	// TODO: Add your control notification handler code here
	if(m_cbWindowType.GetCount() == 0)
	{
		CRect lprect;
		m_cbWindowType.GetWindowRect( &lprect );
		lprect.bottom = lprect.top + 4 * m_cbWindowType.GetItemHeight( -1 ) + lprect.Height();
		m_cbWindowType.SetWindowPos(NULL, 0, 0, lprect.Width(), lprect.Height(), SWP_NOMOVE | SWP_NOZORDER );

		for(int i=4;	i<8;	i++)
		{
			m_cbWindowType.AddString(filterNames[i]);
		}
	}
}

void CAddWinFctDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int FilterId = m_cbWindowType.GetCurSel() + 4 ;


	//we check if the length of the kernel is a power of two and if 
	//a filter type has been selected from the drop-down list

	if(FilterId >= 4 )
	{
		CFilterDlg* filterDlg;
		filterDlg=dynamic_cast<CFilterDlg*>(m_FilterDlg);
		filterDlg->AddWindowToList(FilterId);
		OnOK();
	}
}
