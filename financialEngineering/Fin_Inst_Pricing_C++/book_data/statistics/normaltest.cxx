// normaltest.cxx
//
// Test functions for the normal distribution
//
// DD 2000-6-24

#include "normdist.cxx"
#include <iostream.h>

int main()
{

	Normal<double> n1(0.0, 1.0);

	// Create a graph of the standard Gaussian random variable

	double start = -10.0;
	int N = 20;

	for (int i = 1; i < N; i++)
	{
		cout << n1.pdf(start) << endl;
		start += 1.0;
	}

	double x;
	cout << "Give value: " << endl;
	cin >> x;


	cout << endl << "CDF  " << n1.cdf(x) << endl;

	cout << endl << "CDF  " << n1.cdf(0.0) << endl;
	cout << endl << "CDF  " << n1.cdf(4.0) << endl;

	return 0;
}
