#pragma once

#include "SFilter.h"
#include "WindowFunctions.h"
/*
		This is a LOW-PASS WINDOWED-SINC FILTER, it is a high performance
	filter regarding the frequency band separation , it is not recommended for
	time domain analysis.
*/
class CLPFilter1 : public CSFilter
{
private:						//Attributes
	int		m_dCutoffFreq			;			//the cutoff frequency , must not be greater than half of the 
												//sampling frequency(Niquist frequency)
public:
				CLPFilter1(	const int KernelLen,
							const int SamplingRate,
							const int CutoffFreq,
							const int FFTLen,
							CWindowFunction* Window );
	
	double*		CreateKern(const int CutoffFreq, CWindowFunction* Window);
	double*		getKernel();
	~CLPFilter1();
};
