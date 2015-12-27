// FilterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LFP_Demo_Dialog.h"
#include "FilterDlg.h"
#include "MyDefinitions.h"
#include "stdio.h"
#include "LPFilter1.h"
#include "WindowFunctions.h"


// CFilterDlg dialog

IMPLEMENT_DYNAMIC(CFilterDlg, CDialog)

CFilterDlg::CFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterDlg::IDD, pParent)
	, m_nFilterLen(0)
	, m_nFFTLen(0)
	, m_sInputFileName(_T(""))
	, m_vdInputSignal(NULL)
{

}

CFilterDlg::~CFilterDlg()
{
}

void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctlListBox);
	DDX_Control(pDX, IDC_EDIT_FILTER_LEN, m_ctlEditFilterLen);
	DDX_Control(pDX, IDC_EDIT_FFT_LEN, m_ctlEditFFTLen);
	DDX_Control(pDX, IDC_BUTTON2, m_btAddWindowFct);
	DDX_Control(pDX, IDC_BUTTON1, m_btAddFilter);
	DDX_Control(pDX, IDC_BUTTON3, m_btRemoveItem);
	DDX_Control(pDX, IDC_BUTTON4, m_btFilter);
	DDX_Control(pDX, IDC_BUTTON6, m_btSetInputFile);
	DDX_Control(pDX, IDC_STATIC_SIGNAL_INFO, m_ctlSignalInfoTextBox);
	DDX_Control(pDX, IDC_EDIT_INPUT_FILE, m_ctlInputFileEditBox);
}


BEGIN_MESSAGE_MAP(CFilterDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CFilterDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CFilterDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CFilterDlg::OnBnClickedButtonAddFilter)
	ON_EN_CHANGE(IDC_EDIT_FILTER_LEN, &CFilterDlg::OnEnChangeEditFilterLen)
	ON_EN_CHANGE(IDC_EDIT_FFT_LEN, &CFilterDlg::OnEnChangeEditFftLen)
	ON_BN_CLICKED(IDC_BUTTON6, &CFilterDlg::OnBnClickedSetInputFile)
END_MESSAGE_MAP()


// CFilterDlg message handlers

void CFilterDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CAddWinFctDlg dlg(this);
	dlg.DoModal();
	
}

void CFilterDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	/*CLPFilter1* lpf;
	lpf=new CLPFilter1(1023,1000,100,32,new CHammingWindow());
	
	double *out;

	FILE *fout;

	fout=fopen("out.txt","w");
	for(int i = 0;i<32;i++)
	{
		fprintf(fout,"%3.14Lf\n",out[i] );
	}*/

}

void CFilterDlg::AddWindowToList( int WindowId )
{
	if( m_ctlListBox.GetCount() == 0 )
	{
		m_ctlEditFFTLen.SetReadOnly(TRUE);
		m_ctlEditFilterLen.SetReadOnly(TRUE);
	}
	m_ctlListBox.AddString( filterNames[ WindowId ] );
}

void CFilterDlg::AddFilterToList( int* FilterProp )
{
	if( m_ctlListBox.GetCount() == 0 )
	{
		m_ctlEditFFTLen.SetReadOnly(TRUE);
		m_ctlEditFilterLen.SetReadOnly(TRUE);
	}
	m_ctlListBox.AddString(filterNames[ FilterProp[ 0 ] ]);
}

void CFilterDlg::OnBnClickedButtonAddFilter()
{
	// TODO: Add your control notification handler code here
	CAddFilterDlg dlg(this);

	dlg.DoModal();
}

void CFilterDlg::OnEnChangeEditFilterLen()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString text;
	m_ctlEditFilterLen.GetWindowText(text);
	
	int FilterLen	= -1;

	FilterLen		= _ttoi( text );

	if(FilterLen > 2 && FilterLen % 2 == 1)
	{		
		m_nFFTLen		= MyMath::NextPow2Greater( 2 * FilterLen - 1);
		m_nFilterLen	= FilterLen;
		
		text.Format("%d",m_nFFTLen);
		
		m_ctlEditFFTLen.EnableWindow(TRUE);
		m_ctlEditFFTLen.SetWindowText(text);

		m_btAddFilter.EnableWindow(TRUE);
		m_btAddWindowFct.EnableWindow(TRUE);

	}
	else
	{
		m_ctlEditFFTLen.SetWindowText("");

		m_ctlEditFFTLen.EnableWindow(FALSE);
		m_btAddFilter.EnableWindow(FALSE);
		m_btAddWindowFct.EnableWindow(FALSE);
	}
}
void CFilterDlg::OnEnChangeEditFftLen()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
	CString text;

	int FilterLen	= -1;
	int FFTLen		= -1;

	m_ctlEditFilterLen.GetWindowText(text);
	FilterLen		= _ttoi( text );

	m_ctlEditFFTLen.GetWindowText(text);
	FFTLen			= _ttoi( text );

	if (FFTLen > 0 && FFTLen >= (2 * FilterLen - 1 ) && MyMath::IsPowOfTwo(FFTLen))
	{
		m_btAddFilter.EnableWindow(TRUE);
		m_btAddWindowFct.EnableWindow(TRUE);

		m_nFFTLen	= FFTLen;
	}
	else
	{
		m_btAddFilter.EnableWindow(FALSE);
		m_btAddWindowFct.EnableWindow(FALSE);
	}
}

void CFilterDlg::OnBnClickedSetInputFile()
{
	CString inputText;

    char* fileName = NULL;
	FILE* inFile;

	m_ctlInputFileEditBox.GetWindowText( inputText );

	if( inputText.IsEmpty() )
		return;
	
	fileName=inputText.GetBuffer(inputText.GetLength());

	if ((inFile=fopen(fileName,"r"))==NULL)
	{
		return;
	}
	else
	{
		int		sampleRate , nrOfSamples;
		double  signalLength;

		fscanf_s(inFile,"%d",&sampleRate);
		fscanf_s(inFile,"%d",&nrOfSamples);

		m_vdInputSignal = new double[ nrOfSamples ];

		for( int i=0; i < nrOfSamples; i++ )
			fscanf_s(inFile,"%Lf", &m_vdInputSignal[ i ]);
		signalLength = static_cast<double>(nrOfSamples/sampleRate);
		
		m_sInputFileName =""+inputText;

		inputText.Format("Sample Rate: %d\nSignal Length: %3.3Lf s",sampleRate,signalLength);
		m_ctlSignalInfoTextBox.SetWindowText(inputText);
		m_ctlInputFileEditBox.SetReadOnly(TRUE);
		m_ctlEditFilterLen.EnableWindow(TRUE);
		m_btSetInputFile.EnableWindow(FALSE);
	}


	


}
