#include "stdafx.h"
#include "MyDefinitions.h"

namespace MyMath
{
	
	bool IsPowOfTwo(int n)
	{
		assert(n > 0);

		return  ((n & -n) == n);
	}
	

	int NextPow2Greater	( int Number )
	{
		if( Number == 0)
			return 1;

		Number--;

		for ( int i = 1 ; i < sizeof( int ) * CHAR_BIT ;  i <<= 1 )
			Number= Number | Number >> i;

		return Number + 1;
	}

}