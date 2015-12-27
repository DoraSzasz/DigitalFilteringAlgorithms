#pragma once

#include "SFilter.h"
#include "WindowFunctions.h"

/*
		This is a HIGH-PASS WINDOWED-SINC FILTER, it is a high performance
		filter regarding the frequency band separatation , it is not recommended for
		time domain analysis.
*/

class CHPFilter1: public CSFilter
{
private:						//Attributes
	int				m_dCutoffFreq;				//the cutoff frequency , must not be greater than half of the 
												//sampling frequency(niquist frequency)
public:							//Member functions
					CHPFilter1			( const int KernelLen, const int SamplingRate, const int CutoffFreq, CWindowFunction* Window );
	double			*CreateKern			( const int KernelLen, const int SamplingRate, const int CutoffFreq, CWindowFunction* Window );
					~CHPFilter1			();
};
