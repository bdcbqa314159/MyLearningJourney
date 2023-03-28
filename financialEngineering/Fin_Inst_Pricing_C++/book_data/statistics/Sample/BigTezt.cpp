// BigTest.cxx
//
// Test program for continuous distributions
//
// (C) Datasim Education BV 1992-2004

#include "unifdist.cxx"
#include "gammdist.cxx"
#include "expodist.cxx"
#include "miscfun.hxx"

#include <iostream>
using namespace std;

void print(const ContinuousDistribution<double, double>& dis, double x)
{
	cout << "Mean value: " << dis.expected() << " Variance: " << dis.variance() << endl;
	cout << "pdf: " << dis.pdf(x) << " cdf: " << dis.cdf(x) << endl;
}


	
int main()
{
	// Uniform distribution
	Uniform<double> linseg(0.0, 2.0);	// Interval of interest
	print(linseg, 3.0);

	// Gamma distribution
	Gamma<double> g(2.0, 3.9);
	print(g, 3.0);

	// Exponential distribution

	cout << "The exact answer is: " << 1.0/exp(-1.0) << "\n";
	Exponential<double> var1(1.0);
	Exponential<double> var2(2.0);

	print(var1, 3.0);
	print(var2, 3.0);


	return 0;

}
