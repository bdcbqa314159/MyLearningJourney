// Implementation of Conversion activity.
//
// Datasim Education BV (c) 2003
// 
// Modification dates:
// 23 July 2003 - MB - Started.
// 29 July 2003 - MB - Reading the input values A, B and N from SimplePropertSet.
// 31 July 2003 DD special case

#include <iostream>
#include <cmath>
using namespace std;

#include "DDregistration.cpp"
#include "vector.cpp"


//////////// Gaussian functions /////////////////////////////////
double NormalPdf(double x) 
{ // Probability density function (pdf)
	double A = 1.0/sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);
}

double NormalCdf(double x)
{ // The approximation to the cumulative normal distribution (cdf)

	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;

	double k = 1.0/(1.0 + (0.33267 * x));
	
	if (x >= 0.0)
	{
		return 1.0 - NormalPdf(x)* (a1*k + (a2*k*k) + (a3*k*k*k));
	}
	else
	{
		return 1.0 - NormalCdf(-x);
	}
}



// Calculates a number of functions with N values
// ranging from A to B. The returned vectors are:
//  n_result: n function
//  N_result: N function
//

void Conversion(double& A, double& B, int& N,
				Vector<double, int> & x, Vector<double, int> & n_result, Vector<double, int> & N_result)
				
{
	

	// Step size.
	double h = (B-A)/N;

	// Calculate input values and call functions.
	double current = A;
	for (int i = x.MinIndex(); i <= x.MaxIndex(); i++)
	{
		// Call functions and set values in vectors.
		x[i] = current;
		n_result[i] = NormalPdf(current);
		N_result[i] = NormalCdf(current);

		// Calculate next value.
		current += h;
	}
}
