// PowerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LFP_Demo_Dialog.h"
#include "PowerDlg.h"


// CPowerDlg dialog

IMPLEMENT_DYNAMIC(CPowerDlg, CDialog)

CPowerDlg::CPowerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPowerDlg::IDD, pParent)
{

}

CPowerDlg::~CPowerDlg()
{
}

void CPowerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPowerDlg, CDialog)
END_MESSAGE_MAP()


// CPowerDlg message handlers
