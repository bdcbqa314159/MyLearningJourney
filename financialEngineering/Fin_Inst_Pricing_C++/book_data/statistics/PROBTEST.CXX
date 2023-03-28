// cnstest.cxx
// Test program for continuous distributions
// (C) Datasim bv 1992

#include "unifdist.hxx"
#include "expodist.hxx"

main()
{
	// Uniform distribution
	UNIFDIST linseg(0.0, 2.0);      // Interval of interest
	cout << linseg;
	
	// An example of an exponential distribution. The following
	// piece of code calculates the probability that a random
	// variable of exponential type execced its expected value.
	// The exact value is exp( - 1.0).
	cout << "Exact value: " << exp(-1.0) << "\n";
	EXPODIST test(2.0); 
	double res = (test > test.expected());
	cout << "Approximate value " << res < "\n";

	return 0;
}
