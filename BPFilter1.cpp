#include <stdafx.h>
#include <new>
#include "BPFilter1.h"
#include "LPFilter1.h"
#include "HPFilter1.h"
///*
//	Description:
//		The constructor for the BPFilter1(BAND-PASS WINDOWED-SINC FILTER) class.
//	Parameters:
//		KernelLen	 - The length of the kernel , it must be an ODD NUMBER!!!
//		SamplingRate - The sampling rate of the input signal that will pass
//						through this filter
//		PassBandFreq - the first frequency corner, under this level the frequencies are cut
//					   and the higher frequencies pass
//		StopBandFreq - the second frequency corner, below this level frequencies pass and
//					   above this level the frequencies are cut
//		Window		 - The window function used with this type of filters.
//*/
//CBPFilter1::CBPFilter1( const int KernelLen, const int SamplingRate, const int PassBandFreq,const int StopBandFreq, CWindowFunction* Window )
//{
//	this->m_nSamplingRate   =	SamplingRate;
//	this->m_nFFTLen			=	0;
//	this->m_RealFFTObj		=	NULL;
//	this->m_vdFreqResp		=	NULL;
//	this->m_vdKernel		=	NULL;
//	this->m_nPassBandFreq	=	0;
//	this->m_nStopBandFreq	=	0;
//	this->m_nKernelLen		=	0;
//
//	this->ChangeState( FILTER_CONSTRUCTED );
//	
//	CreateKern( KernelLen ,SamplingRate, PassBandFreq, StopBandFreq, Window );
//}
//
//double* CBPFilter1::CreateKern( const int KernelLen, const int SamplingRate, const int PassBandFreq,const int StopBandFreq, CWindowFunction* Window )
//{
//	//the first frequency must be smaller than the second frequency 
//	//such that a band of passed frequencies exists
//	if(PassBandFreq >= StopBandFreq)
//	{
//		this->ChangeState( FILTER_CONSTRUCTED );
//		return NULL;
//	}
//
//	CSFilter *LowPassFilter		=	new CLPFilter1(KernelLen,SamplingRate,PassBandFreq,Window);
//	CSFilter *HighPassFilter	=	new CHPFilter1(KernelLen,SamplingRate,StopBandFreq,Window);
//	
//	try
//	{
//		if( this->m_vdKernel !=  NULL )
//			delete[] m_vdKernel;
//		
//		this->m_vdKernel		=	new double[ KernelLen ];
//		this->m_nPassBandFreq	=	PassBandFreq;
//		this->m_nStopBandFreq	=	StopBandFreq;
//		this->m_nKernelLen		=	KernelLen	;
//		
//		if (LowPassFilter->GetState() != KERNEL_CONSTRUCTED || HighPassFilter->GetState() != KERNEL_CONSTRUCTED)
//			throw std::bad_alloc();
//		
//		double *temp1, *temp2;					//pointers used to acces the kernels of the high and low pass filters
//
//		temp1 = LowPassFilter->GetKernel();		//pointer to the kernel of the low pass filter
//		temp2 = HighPassFilter->GetKernel();	//pointer to the kernel of the high pass filter
//		
//		//the two kernels are added and spectral inversion is applied
//		for( int i = KernelLen - 1;  i >= 0 ; i--)
//			m_vdKernel[ i ] =0 -( temp1[ i ] + temp2[ i ] );
//
//		m_vdKernel[ KernelLen / 2 ] = m_vdKernel[ KernelLen / 2 ] + 1;
//	}
//	catch (std::bad_alloc &ba)
//	{
//		this->ChangeState( FILTER_CONSTRUCTED )	;
//		
//		delete LowPassFilter;
//		delete HighPassFilter;
//
//		return NULL;
//	}
//	
//	this->ChangeState( KERNEL_CONSTRUCTED );
//	
//	delete LowPassFilter;
//	delete HighPassFilter;
//	
//	return m_vdKernel;
//}
//
//CBPFilter1::~CBPFilter1()
//{
//	switch (m_eFilterState)
//	{
//
//	case FILTER_CONSTRUCTED:
//		break;
//
//	case KERNEL_CONSTRUCTED:
//		
//		delete[] m_vdKernel;
//		
//		break;
//	
//	case FFT_OBJ_CONSTRUCTED:
//		
//		delete[] m_vdKernel;
//		delete m_RealFFTObj;
//		
//		break;
//	
//	case FREQ_RESP_CONSTRUCTED:
//		
//		delete[] m_vdKernel;
//		delete m_RealFFTObj;
//		delete[] m_vdFreqResp;
//		
//		break;
//	}
//}