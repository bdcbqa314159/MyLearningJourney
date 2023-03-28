// cnstest.cxx
//
// Test program for continuous distributions
//
// (C) Datasim Education BV 1992-2004

#include "unifdist.cxx"
#include <iostream>
using namespace std;

int main()
{
	// Uniform distribution
	Uniform<double> linseg(0.0, 2.0);	// Interval of interest
	cout << "Mean value: " << linseg.expected() << endl;
	cout << "Variance: " << linseg.variance();

	return 0;
}
