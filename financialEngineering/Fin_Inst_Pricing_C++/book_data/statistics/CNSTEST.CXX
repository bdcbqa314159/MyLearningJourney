// cnstest.cxx
// Test program for continuous distributions. Shows also how operator
// overloading
// (C) Datasim bv 1992

#include "unifdist.hxx"

main()
{
	// Uniform distribution
	UNIFDIST linseg(0.0, 2.0);	// On interval [0.0, 2.0]
	cout << linseg;
	cout << "\npdf is " << linseg.pdf(1.0);	// Constant pdf!

	// Two equivalent representations of the same result
	cout << "\ncdf at -0.5 = " << linseg.cdf(-0.5);
	double cdf_op = linseg <= -0.5;
	cout << "\ncdf_op at -0.5 = " << cdf_op;

	// Two equivalent representations of the same result
	cout << "\ncdf at 1.0 = " << linseg.cdf(1.0);
	cdf_op = linseg <= 1.0;
	cout << "\ncdf_op at 1.0 = " << cdf_op;

	// Two equivalent representations of the same result
	cout << "\ncdf at 3.0 = " << linseg.cdf(3.0);
	cdf_op = linseg <= 3.0;
	cout << "\ncdf_op at 3.0 = " << cdf_op;

	cout << "\nExpected value = " << linseg.expected();
	cout << "\nVariance value = " << linseg.variance();

	cout << "\nProbability in range [1, 1.5] = "
	     << linseg.prob(1.0, 1.5);

	return 0;
}
