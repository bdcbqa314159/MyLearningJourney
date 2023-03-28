// tanh.cxx
// Integration of functions in one dimension by the TANH rule
//
// (C) Datasim bv 1992 - 1998
//
// Modification dates:
//
//	1999-1-25 DD Simpler Interval class

#include <math.h>
#include <iostream.h>
#include "interval.hxx"
#include "Tanh.hxx"
#include <limits>
		
main()
{
	double dd;

	INTERVAL i2(-1.0, 1.0); // Interval [-1, 1]
	
	double z = -5000;
	for (; z<=0; z +=10)
	{ // Integral should converge to 1/2!
		i2 = INTERVAL(z, -700.0);
		dd = integrate(normal_func, i2, 5000);
		cout << "[" << z << "," << dd / sqrt(2.0 * 3.1415) << "]" << endl;
		

	}
	
	return 0;
}
