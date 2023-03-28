// gammtst.cxx
// Program to test the gamma function and the incomplete gamm function
// (C) Datasim bv 1992

#include "miscfun.hxx"
#include "constant.hxx"

main()
{
	// First tests; using integers and comparing with the
	// corresponding factorial values. We include negative
	// values of the argument in order to show how the preconditions
	// in the code work.
	for (int j = -3; j <= 12; j++)
		cout << j << ", " << MISCFUN::gamma (double (j)) << ", " << MISCFUN::gamma(j) << "\n";

	// Second tests; the incomplete gamma function for a specific
	// parameter value. The results should be monotonic, starting at
	// 0.0 and evolving to a value of 1.0.
	double a;
	double x = 0.0;
	double increment = 2.0;
	cout << "Incomplete gamma function, give value of parameter " << "\n";
	cin >> a;
	for (double start = 0.0; start <= 14.0; start += increment)
	{
		cout << x << ", " << MISCFUN::gamma(a, x) << "\n";
	    x += increment;
	}

	return 0;

}