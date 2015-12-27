// AddFilterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LFP_Demo_Dialog.h"
#include "MyDefinitions.h"
#include "AddFilterDlg.h"
#include "FilterDlg.h"


// CAddFilterDlg dialog

IMPLEMENT_DYNAMIC(CAddFilterDlg, CDialog)

CAddFilterDlg::CAddFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddFilterDlg::IDD, pParent)
{

}

CAddFilterDlg::CAddFilterDlg(CDialog* pCallerDialog, CWnd* pParent/*=NULL*/)
	: CDialog(CAddFilterDlg::IDD, pParent)
{
	m_dCallerDialog = pCallerDialog;
}

CAddFilterDlg::~CAddFilterDlg()
{
}

void CAddFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ctlComboBox);
	DDX_Control(pDX, IDC_EDIT_PASS, m_ctlPassEdit);
	DDX_Control(pDX, IDC_EDIT_CUTOFF, m_ctlEditCutoff);
}


BEGIN_MESSAGE_MAP(CAddFilterDlg, CDialog)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CAddFilterDlg::OnCbnDropdownComboFilterType)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddFilterDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &CAddFilterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddFilterDlg message handlers

void CAddFilterDlg::OnCbnDropdownComboFilterType()
{
	// TODO: Add your control notification handler code here
	if(m_ctlComboBox.GetCount() == 0)
	{
		CRect lprect;
		m_ctlComboBox.GetWindowRect( &lprect );
		lprect.bottom = lprect.top + 4 * m_ctlComboBox.GetItemHeight( -1 ) + lprect.Height();
		m_ctlComboBox.SetWindowPos(NULL, 0, 0, lprect.Width(), lprect.Height(), SWP_NOMOVE | SWP_NOZORDER );

		for(int i=0;	i < 4;	i++ )
		{
			m_ctlComboBox.AddString( filterNames[ i ] );
		}
	}

}

void CAddFilterDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	int selectedItem=m_ctlComboBox.GetCurSel();
	
	switch(selectedItem)
	{
	case -1:
		m_ctlEditCutoff.EnableWindow(false);
		m_ctlPassEdit.EnableWindow(false);
		break;

	case 0:
		m_ctlEditCutoff.EnableWindow( true );
		m_ctlPassEdit.EnableWindow( false );
		break;

	case 1:
		m_ctlEditCutoff.EnableWindow( false );
		m_ctlPassEdit.EnableWindow( true );
		break;

	case 2:

	case 3:
		m_ctlEditCutoff.EnableWindow( true );
		m_ctlPassEdit.EnableWindow( true );
		break;

	default:
		m_ctlEditCutoff.EnableWindow( false );
		m_ctlPassEdit.EnableWindow( false );
		break;
	}
}

void CAddFilterDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	int selectedItem=m_ctlComboBox.GetCurSel();
	
	int filterParam[3]={-1, -1, -1 };

	CString textInput;
	CFilterDlg* filterDlg;
	
	switch(selectedItem)
	{

	case -1:
		return;
		break;
	case 0:
		filterParam[ 0 ] = selectedItem;

		m_ctlEditCutoff.GetWindowText(textInput);
		filterParam[ 2 ] = _ttoi( textInput );

		filterParam[ 1 ] = 0;
		
		if( filterParam[ 0 ] < 0  || filterParam[ 2 ] <= 0)
			return;
		
		filterDlg=dynamic_cast<CFilterDlg*>(m_dCallerDialog);
		filterDlg->AddFilterToList( filterParam );

		OnOK();
		break;

	case 1:
		filterParam[ 0 ] = selectedItem;

		m_ctlPassEdit.GetWindowText(textInput);
		filterParam[ 1 ] = _ttoi( textInput );

		filterParam[ 2 ] = 0;

		if( filterParam[ 0 ] < 0  || filterParam[ 1 ] <= 0)
			return;


		filterDlg=dynamic_cast<CFilterDlg*>(m_dCallerDialog);
		filterDlg->AddFilterToList( filterParam );

		OnOK();
		break;

	case 2:
		filterParam[ 0 ] = selectedItem;

		m_ctlPassEdit.GetWindowText(textInput);
		filterParam[ 1 ] = _ttoi( textInput );
		
		m_ctlEditCutoff.GetWindowText(textInput);
		filterParam[ 2 ] = _ttoi( textInput );

		if( filterParam[ 0 ] < 0  || filterParam[ 1 ] <= 0 || filterParam[ 2 ] <= filterParam[ 1 ] )
			return;


		filterDlg=dynamic_cast<CFilterDlg*>(m_dCallerDialog);
		filterDlg->AddFilterToList( filterParam );
		
		OnOK();
		break;

	case 3:
		filterParam[ 0 ] = selectedItem;

		m_ctlPassEdit.GetWindowText(textInput);
		filterParam[ 1 ] = _ttoi( textInput );

		m_ctlEditCutoff.GetWindowText(textInput);
		filterParam[ 2 ] = _ttoi( textInput );

		if( filterParam[ 0 ] < 0  || filterParam[ 1 ] <= 0 || filterParam[ 2 ] <= filterParam[ 1 ] )
			return;


		filterDlg=dynamic_cast<CFilterDlg*>(m_dCallerDialog);
		filterDlg->AddFilterToList( filterParam );

		OnOK();
		break;
		
	default:
			break;
	}

	
	
}
