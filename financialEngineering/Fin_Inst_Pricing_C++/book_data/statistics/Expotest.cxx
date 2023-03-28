// expotest.cxx
// A simple test of the exponential distribution. The program computes
// the probability that a random variable exceeds its expected value.
// This is independent of the variable and should be equal to
// 1.0/exp(-1.0);
//
// (C) Datasim bv 1992

#include <iostream.h>
#include <math.h>
#include "expodist.cxx"

main()
{

	cout << "The exact answer is: " << 1.0/exp(-1.0) << "\n";
	Exponential<double> var1(1.0);
	Exponential<double> var2(2.0);

	double res1 = expected(var1);
	double res2 = expected(var2);

	cout << "Approximate results: " << res1 << " " << res2 << "\n";

	return 0;
}
