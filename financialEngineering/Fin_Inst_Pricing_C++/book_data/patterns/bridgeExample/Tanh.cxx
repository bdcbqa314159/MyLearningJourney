// tanh.cxx
// Integration of functions in one dimension by the TANH rule
//
// (C) Datasim bv 1992

#include <cmath>
#include "interval.hxx"
#include "tanh.hxx"


double integrate (double (*func) (double x), const INTERVAL& tr, int N)
{ // Integration in one dimension by the TANH rule.

	// Kick down to the low level Fortran way of doing things.
	double A = tr.start();
	double B = tr.end();

	double res = 0.0;
	double nd = double(N);
	double incr = tr.length() / nd;
	for (double x = A + (0.5 * incr); x < B; x += incr)
	       res += tanh(func(x) * 0.5 * incr);

	   return 2.0 * res;
}


double myfuncx (double x)
{ return log(x) / (1.0 - x); }


double difficult (double x)
{ return (sqrt(1.0-x)) * sqrt(1.0-x) * exp(x); }

double normal_func(double x)
{ // Needed for Black-Scholes

	return exp(- x*x*0.5);
}

		
