#pragma once
const int LOW_PASS_FILTER_ID			=0;
const int HIGH_PASS_FILTER_ID			=1;
const int BAND_PASS_FILTER_ID			=2;
const int BAND_STOP_FILTER_ID			=3;

const int SQUARE_WINDOW_ID				=4;
const int HANN__WINDOW_ID 				=5;
const int HAMMING_WINDOW_ID				=6;
const int PARZEN_WINDOW_ID				=7;

const CString	filterNames[]={	"Low Pass Filter",
								"High Pass Filter",
								"Band Pass Filter",
								"Band Stop Filter",
								"Square Window",
								"Hann Window",
								"Hamming Window",
								"Parzen Window"
								};

namespace MyMath
{
	//checks if an int is a power of two
	bool IsPowOfTwo(int n);

	//returns the first power of two greater than the given input
	int NextPow2Greater	( int Number );
}