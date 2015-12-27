#include <stdafx.h>
#include "HPFilter1.h"
#include <new>
///*
//	Description:
//		The constructor for the HPFilter1(HIGH-PASS WINDOWED-SINC FILTER) class.
//	Parameters:
//		KernelLen	 - The length of the kernel , it must be an ODD NUMBER!!!
//		SamplingRate - The sampling rate of the input signal that will pass
//						through this filter
//		CutoffFreq	 - The cutoff frequency for the filter
//		Window		 - The window function used with this type of filters.
//*/
//CHPFilter1::CHPFilter1(const int KernelLen,const int SamplingRate,const int CutoffFreq, CWindowFunction* Window)
//{
//	this->m_nSamplingRate   =	SamplingRate;
//	this->m_nFFTLen			=	0;
//	this->m_RealFFTObj		=	NULL;
//	this->m_vdFreqResp		=	NULL;
//	this->m_vdKernel		=	NULL;
//	this->ChangeState( FILTER_CONSTRUCTED );
//	CreateKern( KernelLen ,SamplingRate, CutoffFreq, Window );
//}
//
//double* CHPFilter1::CreateKern(const int KernelLen ,const int SamplingRate , const int CutoffFreq, CWindowFunction* Window)
//{
//	//At first a low pass filter kernel is created then
//	//spectral inversion is used to create a high pass filter 
//
//	double sum = 0 ;
//	//the cutoff frequency must be greater than 0 and smaller or 
//	//equal with half of the sampling rate(niquist frequency)
//	if(CutoffFreq < 0 || CutoffFreq > SamplingRate / 2 )
//		return NULL;
//	try
//	{
//		double fracCutoffFreq =( double ) CutoffFreq / SamplingRate;		//the cutoff frequency as a fraction of the sampling rate
//		
//		if( this->m_vdKernel !=  NULL )
//			delete[] m_vdKernel;
//		
//		this->m_vdKernel	= new double[ KernelLen ];
//		this->m_dCutoffFreq = CutoffFreq ;
//		this->m_nKernelLen	= KernelLen	 ;
//		
//		for(int i = 0; i <= ( KernelLen - 1 ); i++)
//		{
//			if (i- (( KernelLen - 1 ) / 2) == 0 )
//				m_vdKernel[ i ] = 2 * M_PI * fracCutoffFreq;
//			else
//				m_vdKernel[ i ] = sin( 2.0 * M_PI * fracCutoffFreq * (i - (( KernelLen - 1 ) / 2))) / ( i - ( KernelLen - 1 )/2);
//			
//			m_vdKernel[ i ] = m_vdKernel[ i ] * ( Window->GetElement( i, KernelLen ) );
//		}
//
//		//normalization of the Low pass filter for unity gain at DC
//		for(int i = 0; i < m_nKernelLen; i++ )
//			sum = sum + m_vdKernel[ i ];
//
//		for(int i = 0; i < m_nKernelLen; i++ )
//			m_vdKernel[ i ] = m_vdKernel[ i ] / sum;
//		
//		//spectral inversion of the low pass filter kernel 
//		//into a high pass filter kernel
//		for(int i=0; i < KernelLen; i++)
//			m_vdKernel[ i ] = -1.0 * m_vdKernel[ i ];
//		m_vdKernel[ KernelLen / 2 ] = m_vdKernel[ KernelLen / 2 ] + 1 ;
//	}
//	catch (std::bad_alloc &ba)
//	{
//		this->ChangeState( FILTER_CONSTRUCTED )	;
//		return NULL;
//	}
//	this->ChangeState( KERNEL_CONSTRUCTED );
//	return m_vdKernel;
//}
//
//CHPFilter1::~CHPFilter1()
//{
//	switch (m_eFilterState)
//	{
//	case FILTER_CONSTRUCTED:
//		break;
//	case KERNEL_CONSTRUCTED:
//		delete[] m_vdKernel;
//		break;
//	case FFT_OBJ_CONSTRUCTED:
//		delete[] m_vdKernel;
//		delete m_RealFFTObj;
//		break;
//	case FREQ_RESP_CONSTRUCTED:
//		delete[] m_vdKernel;
//		delete m_RealFFTObj;
//		delete[] m_vdFreqResp;
//		break;
//	}
//}