#pragma once

#include "SFilter.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif /*_USE_MATH_DEFINES*/

#include <math.h>
/*
	Abstract class used as an interface for all the windowing 
	classes
*/
class CWindowFunction: public CSFilter
{
public:
	virtual double GetElement(int Index, int Length) const =0;
};

class CHammingWindow: public CWindowFunction
{
public:
	double GetElement(int Index, int Length) const;
};

class CHannWindow: public CWindowFunction
{
	double GetElement(int Index, int Length) const;
};

class CParzenWindow: public CWindowFunction
{
	double GetElement(int Index, int Length) const;
};

class CSquareWindow: public CWindowFunction
{
	double GetElement(int Index, int Length) const;
};

//
//class CBlackmanWindow: public CWindowFunction
//{
//	double GetElement(int Index, int Length) const;
//};
//
//class CBlackmanHarrisWindow: public CWindowFunction
//{
//	double GetElement(int Index, int Length) const;
//};
//
//class CBartlettWindow: public CWindowFunction
//{
//	double GetElement(int Index, int Length) const;
//};
//
//class CWelchWindow: public CWindowFunction
//{
//	double GetElement(int Index, int Length) const;
//};
