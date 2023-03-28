// Implementation of Conversion activity.
//
// Datasim Education BV (c) 2003
// 
// Modification dates:
// 23 July 2003 - MB - Started.
// 29 July 2003 - MB - Reading the input values A, B and N from SimplePropertSet.

#include <iostream>
#include <cmath>
using namespace std;

#include "Vector.cpp"
#include "SimplePropertySet.cpp"

// Function (x-1)^3
double function(double x)
{
	return (x-1)*(x-1)*(x-1);
}

// First derivative.
double firstDerivative(double x)
{
	return 3 * (x-1)*(x-1);
}

// Second derivative.
double secondDerivative(double x)
{
	return 6 * (x-1);
}

//////////// Gaussian functions /////////////////////////////////

double n(double x) 
{ 
	double A = 1.0/sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);
}

// The approximation to the cumulative normal distribution
double _N(double x)
{ 
	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;

	double k = 1.0/(1.0 + (0.33267 * x));
	
	if (x >= 0.0)
	{
		return 1.0 - n(x)* (a1*k + (a2*k*k) + (a3*k*k*k));
	}
	else
	{
		return 1.0 - _N(-x);
	}
}

double EuropeanType(double t)
{
	if (t <= 0.5)
		return 1.0;

	double x = t - 0.5;
	return ::exp(-x*x*0.5);
}

double DigitalType(double t)
{
	if (t <= 0.5)
		return 1.0;

	double x = t - 0.5;
	return ::exp(-x);
}

double TurningPointType(double t)
{
	if (t <= 0.5)
		return ::exp(t);

	return ::exp(-t);
}

// Calculates a number of functions with N values
// ranging from A to B. The returned vectors are:
//  x: generated input values
//  function_result: (x-1)^3
//  delta: first derivative of (x-1)^3
//  gamma: second derivative of (x-1)^3
//  n_result: n function
//  N_result: N function
//  european: EuropeanType function
//	digital: DigitalType function
//	turningPoint: TurningPointType function
//
void Calculate( const SimplePropertySet<string, double> & input, 
			    Vector<double, int> & x, Vector<double, int> & function_result, 
			    Vector<double, int> & delta, Vector<double, int> & gamma,
				Vector<double, int> & n_result, Vector<double, int> & N_result,
				Vector<double, int> & european, Vector<double, int> & digital,
				Vector<double, int> & turningPoint)
{
	// Get values from input.
	double A = input.value("A")();
	double B = input.value("B")();
	int N = (int) input.value("N")();

	// Step size.
	double h = (B-A)/N;

	// Calculate input values and call functions.
	double current = A;
	for (int i = x.MinIndex(); i <= x.MaxIndex(); i++)
	{
		// Call functions and set values in vectors.
		x[i] = current;
		function_result[i] = function(current);
		delta[i] = firstDerivative(current);
		gamma[i] = secondDerivative(current);
		n_result[i] = n(current);
		N_result[i] = _N(current);
		european[i] = EuropeanType(current);
		digital[i] = DigitalType(current);
		turningPoint[i] = TurningPointType(current);

		// Calculate next value.
		current += h;
	}
}
