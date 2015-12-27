#include "stdafx.h"
#include <stddef.h>
#include "SFilter.h"
#include <new>

using ffft::FFTReal;

//the empty constructor
CSFilter::CSFilter()
	:m_vdInput(NULL),
	m_nKernelLen(0), 
	m_nSamplingRate(0), 
	m_nFFTLen(0), 
	m_vdFreqResp(NULL), 
	m_vdKernel(NULL), 
	m_RealFFTObj(NULL) 
{

}

CSFilter::CSFilter( const int nKernelLen, 
					const int nSamplingRate, 
					const int FFTLen /* = 0 */ )
{
	m_nKernelLen		= nKernelLen		;
	m_nSamplingRate		= nSamplingRate		;
	m_nFFTLen			= FFTLen			;
	m_RealFFTObj		= new FFTReal<double>(FFTLen);

}

CSFilter::~CSFilter()
{

}

bool	CSFilter::AttachInput(double* Input , const int ISignalLen)
{
	assert(ISignalLen > 0 );

	m_nISignalLen	= ISignalLen;
	m_vdInput		= Input;
	
	return true;
}

//This can be done only after the FFT object is created and 
//the length of the FFT is set. The length of the FFT must be equal to
//the length of the kernel padded with 0 .
bool CSFilter::CreateFreqResp()
{
	//if there already exists a frequency response in the filter
	//it will be deleted so we can create the new frequency response
	if( m_vdFreqResp	!=	NULL )
	{
		delete[] m_vdFreqResp;
	}
	//memory is allocated for the new frequency response
	try
	{
		m_vdFreqResp = new double[ m_nFFTLen ];
	}
	catch (std::bad_alloc &ba)
	{	//if the allocation fails the frequency response pointer will be set to NULL
		//and the state of the filter goes to FFT_OBJ_CONSTRUCTED, a new creation of 
		//the frequency being required
		return false;
	}
	//the FFT is used to create the frequency response of the kernel
	m_RealFFTObj->do_fft( m_vdFreqResp , m_vdKernel );
	//the state of the filter is set to FREQ_RESP_CONSTRUCTED
	//now the FFTConvolution can be used
	return true;
}

//bool CSFilter::SetFFTLen(const int FFTLen)
//{
//	//test if the length of the FFT is smaller or equal with the length of the 
//	//kernel and if it is a power of 2
//	if(FFTLen <= m_nKernelLen || ((-FFTLen & FFTLen) == FFTLen) == false )
//		return false;
//	//if the kernel already has this size the function returns true
//	if( FFTLen == m_nFFTLen )
//	{
//		//the state of the filter is set to the FFT_OBJ_CONSTRUCTED
//		this->ChangeState( FFT_OBJ_CONSTRUCTED );
//		//we call the function that creates the frequency response of the filter kernel
//		this->CreateFreqResp();
//		return true;
//	}
//	//the kernel array is reallocated to the new size, if the 
//	//reallocation fails , false is returned and the array 
//	//that represents the kernel doesn't change
//	double *temp;
//	temp = ( double* ) realloc( m_vdKernel, FFTLen * sizeof( double ) );
//	if ( temp == NULL )
//		return false;
//	else
//		this->m_vdKernel = temp	;
//	//if the FFTLen if greater than the previous FFT length , the elements
//	//that are added must be set to 0. If the length of the new FFT is smaller than
//	//the length of the previous FFT then this step is not necessary because the extra
//	//elements will be removed when the reallocation of the kernel will occur
//	if(FFTLen > m_nFFTLen)
//	{
//		//if the FFTlen has already been set the portion of the kernel between the previous
//		//length to the new length must be set to zero
//		for(int i =(m_nFFTLen > m_nKernelLen? m_nFFTLen: m_nKernelLen ) ; i < FFTLen; i++ )
//			m_vdKernel[i] = 0.0;
//	}
//	//if a FFT object doesn't exist , a new one is created
//	if (this->m_RealFFTObj == NULL )
//	{
//		m_RealFFTObj = new FFTReal<double>(FFTLen);
//	}
//	//if there exists a FFT object , but the length is different than the length of the current 
//	//object the old FFT object is deleted and a new one of correct length is created,
//	if(this->m_RealFFTObj->get_length() != FFTLen )
//	{
//		delete m_RealFFTObj;
//		m_RealFFTObj = new FFTReal<double>(FFTLen);
//	}
//	this->m_nFFTLen = FFTLen;
//	//the state of the filter is set to the FFT_OBJ_CONSTRUCTED
//	//state in which the filter can not perform FFT convolution until the
//	//frequency response of the filter is created
//	this->ChangeState( FFT_OBJ_CONSTRUCTED );
//	//we call the function that creates the frequency response of the filter kernel.
//	//The frequency response is used for the FFTConvolution
//	this->CreateFreqResp();
//
//	return true;
//}
//
//FilterState CSFilter::GetState() const
//{
//	return m_eFilterState;
//}
///*
//		Method for convolving(passing a signal through the filter) the input signal with the kernel of 
//	the filter using a FFT(Fast Fourier Transform).
//	Input:
//		SignalLen	- The length of the input signal.
//		
//		InputSignal	- The input signal that will be convolved(passed through the filter)
//
//		PrevSignal	- Pointer to the overlap-add buffer of the previous piece of signal.The 
//					  length must be equal with the length of the kernel minus 1.This is used
//					  when the input signal is a piece of a longer signal that has been cutted
//					  into smaller pieces. If the input signal is the entire signal or it is the
//					  first piece of the signal , then PrevSignal must be NULL.
//		
//		OABuffer	- The overlap-add buffer of the current piece of the signal(PrevSignal for the next piece). 
//					  The length must be equal with the length of the kernel minus 1. If this signal is the entire signal
//					  or if this piece of signal is the last piece then the OABuffer must be concatenated to the output signal.
//					  If the OABuffer pointer is NULL then the method will allocate an array of m_nKernelLen-1 samples.
//	  OutputSignal	-The buffer for the output signal. If the pointer is NULL then an array of m_nFFTLen elements will be created
//					 but only the first SignalLen elements are useful.If the pointer is not NULL then the array must be of length
//					 m_nFFTLen.
//*/
double* CSFilter::Filter ()
{
	;
	double *FinalOutputSignal = new double[m_nISignalLen + m_nKernelLen -1];
	double *OutputSignal , *OABuffer = new double[m_nKernelLen - 1 ];
	bool notFirst=false;
	
	int SignalLen = m_nFFTLen/2;
	int currentIndex = SignalLen;

	while(currentIndex <= m_nISignalLen)
	{
		if(currentIndex!=0)
			notFirst = true;

		double *InputSignalFreq;	//this will point to the frequency representation of the input signal
		
		OutputSignal = new double[ m_nFFTLen ];

		for(int i = SignalLen - 1 ; i>=0; i--)
			OutputSignal[ i ] = m_vdInput[ i + currentIndex ] ;

		for(int i = SignalLen; i < m_nFFTLen; i++)
			OutputSignal[ i ] = 0.0;

		InputSignalFreq		=	new double[ m_nFFTLen ]		;
		m_RealFFTObj->do_fft(InputSignalFreq , OutputSignal);

		double temp;
		for( int i = 1; i < m_nFFTLen/2; i++ )
		{
			temp = InputSignalFreq[i]* m_vdFreqResp[i] - InputSignalFreq[i + m_nFFTLen/2] * m_vdFreqResp[i + m_nFFTLen/2];
			OutputSignal[m_nFFTLen/2 + i] = InputSignalFreq[i] * m_vdFreqResp[i + m_nFFTLen/2] + InputSignalFreq[i + m_nFFTLen/2] * m_vdFreqResp[i];		
			OutputSignal[i] = temp;
		}
		OutputSignal[ 0 ]				=	InputSignalFreq[ 0 ] * m_vdFreqResp[ 0 ];
		OutputSignal[ m_nFFTLen / 2 ]	=	InputSignalFreq[ m_nFFTLen / 2 ] * m_vdFreqResp[ m_nFFTLen / 2 ];
		//we transform the convoluted signal back to the time domain
		m_RealFFTObj->do_ifft(OutputSignal , InputSignalFreq);
		//we rescale(divide each element with the length of the FFT) the output signal because it is scaled when we use 
		//forward fourier transform + inverse fourier transform 
		m_RealFFTObj->rescale(InputSignalFreq);
		delete[] OutputSignal;
		OutputSignal = InputSignalFreq;
		
		//the samples that were previously saved in the overlap-add buffer are added to the signal
		if(notFirst == true )
			for(int i = 0; i < m_nKernelLen-1; i++ )
				OutputSignal[ i ]	= OutputSignal[ i ] + OABuffer[ i ];

		for(int i = 0; i < m_nKernelLen-1; i++ )
			OABuffer[ m_nKernelLen - 2 - i ]	=	OutputSignal[ m_nFFTLen - 1 - i ];
		

		

		for(int i = 0 ; i < SignalLen ; i++ )
			FinalOutputSignal[ i + currentIndex ] = OutputSignal[ i ];

		currentIndex = currentIndex + SignalLen;
		delete[] OutputSignal;
	}
	currentIndex = currentIndex - SignalLen;
	
	if(currentIndex < m_nISignalLen )
	{
		if(currentIndex!=0)
			notFirst = true;

		double *InputSignalFreq;	//this will point to the frequency representation of the input signal
		
		OutputSignal = new double[ m_nFFTLen ];

		for(int i = SignalLen; i>=0; i--)
			OutputSignal[ i ] = m_vdInput[ i + currentIndex ] ;

		for(int i = SignalLen; i < m_nFFTLen; i++)
			OutputSignal[ i ] = 0.0;

		InputSignalFreq		=	new double[ m_nFFTLen ]		;
		m_RealFFTObj->do_fft(InputSignalFreq , OutputSignal);

		double temp;
		for( int i = 1; i < m_nFFTLen/2; i++ )
		{
			temp = InputSignalFreq[i]* m_vdFreqResp[i] - InputSignalFreq[i + m_nFFTLen/2] * m_vdFreqResp[i + m_nFFTLen/2];
			OutputSignal[m_nFFTLen/2 + i] = InputSignalFreq[i] * m_vdFreqResp[i + m_nFFTLen/2] + InputSignalFreq[i + m_nFFTLen/2] * m_vdFreqResp[i];		
			OutputSignal[i] = temp;
		}
		OutputSignal[ 0 ]				=	InputSignalFreq[ 0 ] * m_vdFreqResp[ 0 ];
		OutputSignal[ m_nFFTLen / 2 ]	=	InputSignalFreq[ m_nFFTLen / 2 ] * m_vdFreqResp[ m_nFFTLen / 2 ];
		//we transform the convoluted signal back to the time domain
		m_RealFFTObj->do_ifft(OutputSignal , InputSignalFreq);
		//we rescale(divide each element with the length of the FFT) the output signal because it is scaled when we use 
		//forward fourier transform + inverse fourier transform 
		m_RealFFTObj->rescale(InputSignalFreq);
		delete[] OutputSignal;
		OutputSignal = InputSignalFreq;
		
		//the samples that were previously saved in the overlap-add buffer are added to the signal
		if(notFirst == true )
			for(int i = 0; i < m_nKernelLen-1; i++ )
				OutputSignal[ i ]	= OutputSignal[ i ] + OABuffer[ i ];

		for(int i = 0; i < m_nKernelLen-1; i++ )
			OABuffer[ m_nKernelLen - 2 - i ]	=	OutputSignal[ m_nFFTLen - 1 - i ];
		

		

		for(int i = 0 ; i < SignalLen ; i++ )
			FinalOutputSignal[ i + currentIndex ] = OutputSignal[ i ];

		currentIndex = currentIndex + SignalLen;
		delete[] OutputSignal;



	}




	return NULL;
}

bool CSFilter::FFTConvolve(const int SignalLen, double* InputSignal, double* PrevSignal, double*& OABuffer, double*& OutputSignal )
{
	double *InputSignalFreq;	//this will point to the frequency representation of the input signal

	//we allocate memory for the output signal which will be first used as a source for
	//creating the frequency response of the input signal
	try
	{
		//if the output signal it's null , a new array will be created 
		if(OutputSignal == NULL)
			OutputSignal = new double[ m_nFFTLen ];
		//the input signal will be copied into the output signal array
		//because a power of 2 length is needed in the input signal frequency representation creation
		for(int i = SignalLen; i>=0; i--)
			OutputSignal[ i ] = InputSignal[ i ];
		//the output array is padded with 0 . It is necessary for the FFT
		for(int i = SignalLen; i < m_nFFTLen; i++)
			OutputSignal[ i ] = 0.0;
	}
	catch (std::bad_alloc &ba)
	{
		OutputSignal = NULL;
		return false;
	}
	try
	{	//we allocate memory for the frequency response of the input signal
		//and we create the response with the FFT object
		InputSignalFreq		=	new double[ m_nFFTLen ]		;
		m_RealFFTObj->do_fft(InputSignalFreq , OutputSignal);
	}
	catch (std::bad_alloc &ba)
	{
		delete[] OutputSignal		;
		OutputSignal	=	NULL	;
		return false;
	}
	//complex multiplication of the frequencies
	//(x + yi)(u + vi) = (xu – yv) + (xv + yu)i.
	double temp;
	for( int i = 1; i < m_nFFTLen/2; i++ )
	{
		temp = InputSignalFreq[i]* m_vdFreqResp[i] - InputSignalFreq[i + m_nFFTLen/2] * m_vdFreqResp[i + m_nFFTLen/2];
		OutputSignal[m_nFFTLen/2 + i] = InputSignalFreq[i] * m_vdFreqResp[i + m_nFFTLen/2] + InputSignalFreq[i + m_nFFTLen/2] * m_vdFreqResp[i];		
		OutputSignal[i] = temp;
	}
	OutputSignal[ 0 ]				=	InputSignalFreq[ 0 ] * m_vdFreqResp[ 0 ];
	OutputSignal[ m_nFFTLen / 2 ]	=	InputSignalFreq[ m_nFFTLen / 2 ] * m_vdFreqResp[ m_nFFTLen / 2 ];
	//we transform the convoluted signal back to the time domain
	m_RealFFTObj->do_ifft(OutputSignal , InputSignalFreq);
	//we rescale(divide each element with the length of the FFT) the output signal because it is scaled when we use 
	//forward fourier transform + inverse fourier transform 
	m_RealFFTObj->rescale(InputSignalFreq);
	delete[] OutputSignal;
	OutputSignal = InputSignalFreq;
	if(OABuffer == NULL)
	{
		try
		{
			OABuffer = new double[ m_nKernelLen - 1 ];
		}
		catch (std::bad_alloc &ba)
		{
			delete[] OutputSignal		;
			OutputSignal	=	NULL	;
			OABuffer		=	NULL	;
			return false;
		}
	}
	//the samples that will overlap the next segment are saved in the overlap-add buffer
	for(int i = 0; i < m_nKernelLen-1; i++ )
		OABuffer[ m_nKernelLen - 2 - i ]	=	OutputSignal[ m_nFFTLen - 1 - i ];
	//the samples that were previously saved in the overlap-add buffer are added to the signal
	if(PrevSignal != NULL )
		for(int i = 0; i < m_nKernelLen-1; i++ )
			OutputSignal[ i ]	= OutputSignal[ i ] + PrevSignal[ i ];
	return true;
}

//		Method for convolving(passing a signal through the filter) the input signal with the kernel of 
//	the filter using a time based aproach.
//	Input:
//		SignalLen	- The length of the input signal.
//		
//		InputSignal	- The input signal that will be convolved(passed through the filter)
//
//		PrevSignal	- Pointer to the overlap-add buffer of the previous piece of signal.The 
//					  length must be equal with the length of the kernel minus 1.This is used
//					  when the input signal is a piece of a longer signal that has been cutted
//					  into smaller pieces. If the input signal is the entire signal or it is the
//					  first piece of the signal , then PrevSignal must be NULL.
//		
//		OABuffer	- The overlap-add buffer of the current piece of the signal(PrevSignal for the next piece). 
//					  The length must be equal with the length of the kernel minus 1. If this signal is the entire signal
//					  or if this piece of signal is the last piece then the OABuffer must be concatenated to the output signal.
//					  If the OABuffer pointer is NULL then the method will allocate an array of m_nKernelLen-1 samples.
//
//	  OutputSignal	- The buffer for the output signal. If the pointer is NULL then an array of m_nKernelLen+SignalLen-1 elements will be created
//					 but only the first SignalLen elements are useful.If the pointer is not NULL then the array must be of length
//					 m_nKernelLen+SignalLen-1.
//*/
//bool CSFilter::Convolve( const int SignalLen, double* InputSignal,double* PrevSignal, double*& OABuffer, double*& OutputSignal )
//{
//	if (this->GetState() < KERNEL_CONSTRUCTED )
//	{
//		return false;
//	}
//	try
//	{
//		OutputSignal = new double[ SignalLen + m_nKernelLen - 1 ];
//		for (int i= SignalLen + m_nKernelLen - 2; i >= 0; i-- )
//			OutputSignal[ i ] = 0 ;
//	}
//	catch(std::bad_alloc &ba)
//	{
//		OutputSignal = NULL;
//		return false;
//	}
//	//the convolution of the input with the kernel
//	//Y[I%+J%] = Y[I%+J%] + X[I%]*H[J%]
//	for(int i = 0 ;i < SignalLen; i++)
//		for(int j= 0; j < m_nKernelLen; j++)
//			OutputSignal[ i + j ] = OutputSignal[ i + j ] + InputSignal[ i ] * m_vdKernel[ j ];
//	if (PrevSignal != NULL )
//	{
//		for(int i = 0 ; i < m_nKernelLen-1; i++ )
//			OutputSignal[i] = OutputSignal[i] + PrevSignal[i] ;
//	}
//	for(int i = 0 ; i < m_nKernelLen-1; i++ )
//		OABuffer[i] = OutputSignal[SignalLen+i];
//	return true;
//}
//
////returns a pointer to the array containing the kernel of the filter
//double* CSFilter::GetKernel() const
//{
//	return m_vdKernel;
//}
//
////returns the length of the fast fourier transform object
//int CSFilter::GetFFTLen() const
//{
//	return m_nFFTLen;
//}