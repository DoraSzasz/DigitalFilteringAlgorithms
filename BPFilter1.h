#pragma once

#include "SFilter.h"
#include "WindowFunctions.h"
/*
		This is a BAND-PASS WINDOWED-SINC FILTER, it is a high performance
		filter regarding the frequency band separatation , it is not recommended for
		time domain analysis.
*/
class CBPFilter1 : public CSFilter
{
private:
	int					m_nPassBandFreq;		//the first frequency corner, under this level the frequencies are cut
												//and the higher frequencies pass
	int					m_nStopBandFreq;		//the second frequency corner, below this level frequencies pass and
												//above this level the frequencies are cut
public:
						CBPFilter1				( const int KernelLen, const int SamplingRate, const int PassBandFreq,const int StopBandFreq, CWindowFunction* Window );
	double				*CreateKern				( const int KernelLen, const int SamplingRate, const int PassBandFreq,const int StopBandFreq, CWindowFunction* Window );
						~CBPFilter1				();
};
