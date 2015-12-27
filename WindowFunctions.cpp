#include "stdafx.h"
#include "WindowFunctions.h"
/*
	Description:
		See Oppenheim & Schafer, Digital Signal Processing, 
	p. 242 (1st ed.).It returns the "Index"-th sample of a Hamming 
	window function kernel of length "Length".
	Parameters:
		Index  - the index of the sample required
		Length - the kernel length of the windowing function
	Returns: a double representing the "Index"-th sample of a
			 Hamming window function kernel of length "Length".	
*/
double CHammingWindow::GetElement(int Index, int Length) const
{
	double a = 2.0* M_PI / (Length-1), w;
	w = 0.54 - 0.46*cos(a*Index);
	return	w;
};
/*
	Description:
		 See Oppenheim & Schafer, Digital Signal Processing,
	p. 242 (1st ed.).It returns the "Index"-th sample of a Hann
	(Hanning) window function kernel of length "Length"
	Parameters:
		Index  - the index of the sample required.
		Length - the kernel length of the windowing function
	Returns: a double representing the "Index"-th sample of a 
			 Hann(Hanning) window function kernel of length "Length".	
*/
double CHannWindow::GetElement(int Index, int Length) const
{
	double a = 2.0 * M_PI/(Length-1), w;
	w = 0.5 - 0.5*cos(a * Index);
	return w;
}
/*
	Description:
		See Press, Flannery, Teukolsky, & Vetterling, Numerical 
	Recipes in C, p. 442 (1st ed.).It returns the "Index"-th
	sample of a Parzen window function kernel of length "Length".
	Parameters:
		Index  - the index of the sample required.
		Length - the kernel length of the windowing function
	Returns: a double representing the "Index"-th sample of a
			 Parzen window function kernel of length "Length".	
*/
double CParzenWindow::GetElement(int Index, int Length) const
{
	double a = (Length-1)/2.0, w;
	if ((w = (Index-a)/(a+1)) > 0.0) 
		w = 1 - w;
	else 
		w = 1 + w;
	return w;
}
/*
	Description:
		See Press, Flannery, Teukolsky, & Vetterling, Numerical 
	Recipes in C, p. 442 (1st ed.).It returns the "Index"-th
	sample of a Square window function kernel of length "Length".
	Parameters:
		Index  - the index of the sample required.
		Length - the kernel length of the windowing function
	Returns: a double representing the "Index"-th sample of a
			 Square window function kernel of length "Length".	
*/
double CSquareWindow::GetElement(int Index, int Length) const
{
	return (1.0);
}
/*
	Description:
	See Oppenheim & Schafer, Digital Signal Processing, p. 242 
	(1st ed.).It returns the "Index"-th sample of a Blackman 
	window function kernel of length "Length".
	Parameters:
		Index - the index of the sample required.
		Length - the kernel length of the windowing function
	Returns: a double representing the "Index"-th sample of a
			 Blackman window function kernel of length "Length".	
*/

//double CBlackmanWindow::GetElement(int Index, int Length) const
//{
//	double a = 2.0*M_PI/(Length-1), w;
//	w = 0.42 - 0.5*cos(a*Index) + 0.08*cos(2*a*Index);
//	return w;
//}
///*
//	Description:
//	See Harris, F.J., "On the use of windows for harmonic 
//	analysis with the discrete Fourier transform", Proc. 
//	IEEE, Jan. 1978.It returns the "Index"-th sample of a 
//	Blackman-Harris window function kernel of length "Length".
//	Parameters:
//		Index - the index of the sample required.
//		Length - the kernel length of the windowing function
//	Returns: a double representing the "Index"-th sample of a
//			 Blackman-Harris window function kernel of length "Length".	
//*/
//double CBlackmanHarrisWindow::GetElement(int Index, int Length) const
//{
//	double a = 2.0*M_PI/(Length-1), w;
//	w = 0.35875 - 0.48829*cos(a*Index) + 0.14128*cos(2*a*Index) - 0.01168*cos(3*a*Index);
//	return w;
//}
///*
//	Description:
//		It returns the "Index"-th sample of a Bartlett window 
//	function kernel of length "Length".
//	Parameters:
//		Index - the index of the sample required.
//		Length - the kernel length of the windowing function
//	Returns: a double representing the "Index"-th sample of a
//			 Bartlett window function kernel of length "Length".	
//*/
//double CBartlettWindow::GetElement(int Index, int Length) const
//{
//	double a = 2.0/(Length-1), w;
//	if ((w = Index*a) > 1.0) w = 2.0 - w;
//	return w;
//}
///*
//	Description:
//		See Press, Flannery, Teukolsky, & Vetterling, Numerical 
//	Recipes in C, p. 442 (1st ed.) or p. 554 (2nd ed.).It returns
//	the "Index"-th sample of a Welch window function kernel of 
//	length "Length".
//	Parameters:
//		Index - the index of the sample required.
//		Length - the kernel length of the windowing function
//	Returns: a double representing the "Index"-th sample of a
//			 Welch window function kernel of length "Length".	
//*/
//double CWelchWindow::GetElement(int Index, int Length) const
//{
//	double a = (Length-1)/2.0, w;
//	w = (Index-a)/(a+1);
//	w = 1 - w*w;
//	return w;
//}