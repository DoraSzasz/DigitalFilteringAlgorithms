#pragma once

#include <RealFFT/FFTReal.h>
/*
		Abstract class used as an interface for all the filters applied to real-time or recorded signals. 
	It contains the methods for time and frequency convolution(the majority of filters are filtering the signal using one of 
	these convolutions ).
*/

class CSFilter
{
public:
	enum	CONVOLUTION_TYPE	{	NO_CONVOLUTION ,
									TIME_BASED_CONVOLUTION , 
									FREQUENCY_BASED_CONVOLUTION 
								};

protected:
	double*					m_vdInput				;			//the input of the filter

	int						m_nKernelLen			;			//length of the filter kernel

	int						m_nISignalLen			;			//length of the input signal

	int						m_nSamplingRate			;			// the rate at which the signal is sampled

	int						m_nFFTLen				;			//length of the Fourier Transform used for the FFT Convolution

	double					*m_vdFreqResp			;			//the frequency response of the filter

	double					*m_vdKernel				;			//pointer to the filter kernel
																//which is a signal of length m_nKernelLen

	ffft::FFTReal<double>	*m_RealFFTObj			;			//the FFT object, it is created when the length of the FFT is set
																//once the object is created, it is more efficient to be reused
																//at every convolution of the kernel

	CONVOLUTION_TYPE		m_eConvolutionType		;			//member variable which tells us if the convolution is a time based or
																//a frequency based one


public:								//methods
							CSFilter            (const int nKernelLen, 
												const int nSamplingRate,
												const int FFTLen /* = 0 */ );
							
							CSFilter			();

	bool					AttachInput			(double* Input , const int ISignalLen ) ;

	//the filter member function can't be run successfully until an input is attached
	virtual double*			Filter				() throw(...) ;

	/*bool					DetachInput			() ;
	
	const int				GetFFTLen			() const throw() ;
	
	const int				GetKernelLen		() const throw() ;
	
	bool					SetConvolutionType	( const CONVOLUTION_TYPE ConvolutionType );
	
	bool					SetFFTLen			( const int FFTLen ) throw() ;
	
	bool					SetKernelLen		( const int nKernelLen ) ;
	
	bool					SetSamplingRate		( const int nSamplingRate );*/

	virtual					~CSFilter			() ;

protected:
	bool					CreateFreqResp		() ;

	bool					FFTConvolve(const int SignalLen, 
										double* InputSignal, 
										double* PrevSignal, 
										double*& OABuffer, 
										double*& OutputSignal );


};