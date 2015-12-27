#pragma once

#include "SFilter.h"
#include "WindowFunctions.h"

/*
		This is a BAND-STOP WINDOWED-SINC FILTER, it is a high performance
		filter regarding the frequency band separatation , it is not recommended for
		time domain analysis.
*/

class CBSFilter1 : public CSFilter
{
private:		//Attributes
	int						m_nStopBandFreq;		//the first frequency corner, below this level frequencies pass and
													//above this level the frequencies are cut
	int						m_nPassBandFreq;		//the first frequency corner, under this level the frequencies are cut
													//and the higher frequencies pass
public:			//Member functions
							CBSFilter1		( const int KernelLen, const int SamplingRate, const int StopBandFreq, const int PassBandFreq, CWindowFunction* Window );
	double					*CreateKern		( const int KernelLen, const int SamplingRate, const int StopBandFreq, const int PassBandFreq, CWindowFunction* Window );
							~CBSFilter1		();
};
