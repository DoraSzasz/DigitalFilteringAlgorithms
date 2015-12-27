#include <stdafx.h>
#include <new>
#include "LPFilter1.h"

/*
	Description:
		The constructor for the LPFilter1(LOW-PASS WINDOWED-SINC FILTER) class.
	Parameters:
		KernelLen	 - The length of the kernel , it must be an ODD NUMBER!!!
		SamplingRate - The sampling rate of the input signal that will pass
						through this filter
		CutoffFreq	 - The cutoff frequency for the filter
		Window		 - The window function used with this type of filters.
*/
CLPFilter1::CLPFilter1(const int KernelLen,
					   const int SamplingRate,
					   const int CutoffFreq,
					   const int FFTLen,
					   CWindowFunction* Window ):CSFilter(KernelLen, SamplingRate, FFTLen )
{
	this->m_vdFreqResp		=	NULL;
	this->m_vdKernel		=	NULL;
	
	CreateKern( CutoffFreq, Window );
}
double* CLPFilter1::getKernel()
{
	return m_vdKernel;
}

double* CLPFilter1::CreateKern(const int CutoffFreq, CWindowFunction* Window)
{
	double sum = 0 ;
	//the cutoff frequency must be greater than 0 and smaller or 
	//equal with half of the sampling rate(Niquist frequency)
	if(CutoffFreq < 0 || CutoffFreq > m_nSamplingRate / 2 )
		return NULL;
	try
	{
		double fracCutoffFreq =( double ) CutoffFreq / m_nSamplingRate;		//the cutoff frequency as a fraction of the sampling rate
		if( this->m_vdKernel !=  NULL )
			delete[] m_vdKernel;
		this->m_vdKernel	= new double[ m_nFFTLen ];
		this->m_dCutoffFreq = CutoffFreq ;
		this->m_nKernelLen	= m_nKernelLen	 ;
		for(int i = 0; i <= ( m_nKernelLen - 1 ); i++)
		{
			if (i- (( m_nKernelLen - 1 ) / 2) == 0 )
				m_vdKernel[ i ] = 2 * M_PI * fracCutoffFreq;
			else
				m_vdKernel[ i ] = sin( 2.0 * M_PI * fracCutoffFreq * (i - (( m_nKernelLen - 1 ) / 2))) / ( i - ( m_nKernelLen - 1 )/2);
			m_vdKernel[ i ] = m_vdKernel[ i ] * ( Window->GetElement( i, m_nKernelLen ) );
		}
		
		//normalization of the low pass filter for unity gain at DC
		for(int i = 0; i < m_nKernelLen; i++ )
			sum = sum + m_vdKernel[ i ];
		for(int i = 0; i < m_nKernelLen; i++ )
			m_vdKernel[ i ] = m_vdKernel[ i ] / sum;

		for(int i = m_nKernelLen; i<m_nFFTLen; i++ )
			m_vdKernel[ i ] = 0.0;
	}
	catch (std::bad_alloc &ba)
	{
		return NULL;
	}

	return m_vdKernel;
}

CLPFilter1::~CLPFilter1()
{
	delete[] m_vdKernel;
	delete m_RealFFTObj;
	delete[] m_vdFreqResp;
}