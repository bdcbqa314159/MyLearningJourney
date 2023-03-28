// test_new.cpp
//
// Testing new Function classes.
//

#include "detfunction.cpp"
#include "vector.cpp"
#include <iostream>
#include <math.h>
#include "ivp.cpp"


double add(const Vector<double>& arr)
{
	return arr[1] + arr[2];
}


// Functions with 1 parameter
double BSexp(const double& d) // Black Scholes
{

	return (::exp(d));
}

double first (const double& t)
{

		return 1.0;
}

double second (const double& t)
{

		return t;
}

double third (const double& t)
{

		return t*t;
}

double firstA (const Vector<double>& t)
{

		return 1.0;
}

double secondA (const Vector<double>& t)
{

		return t[1] + t[2];
}

double thirdA (const Vector<double>& t)
{

		return (t[1] + t[2]) * (t[1] + t[2]);
}

int typical(const Vector<double>& vec)
{ // Scalar-valued function

	return vec[1]* 0.25 + vec[2] * 0.25;
}

double typical2(const Vector<double, int>& vec)
{ // Scalar-valued function

	return vec[1]* 0.5 + vec[2] * 0.5;
}

double typical3(const Vector<double, int>& vec)
{ // Scalar-valued function

	return vec[1]* 1.0 + vec[2] * 1.0;
}

int main()
{


	// Scalar-valued functions
	Vector<double> point(2);
	point[1] = 2.0;
	point[2] = 2.0;

	// Vector-valued functions; first create an array ofthree functions
	VectorValuedFunction<double, double, int> vvfun(2);

	ScalarFunction<Vector<double, int>, double, int> interim;
	interim.function(typical2);


	ScalarValuedFunction<double, double, int> myfunA;
	myfunA.function(interim);
//	cout << "A: " << myfunA.calculate(point);
	cout << endl; cout << endl;

	ScalarFunction<Vector<double, int>, double, int> interim2;
	interim2.function(typical3);



	ScalarValuedFunction<double, double, int> myfunB;
	myfunB.function(interim2);
	cout << "B: " << myfunB.calculate(point);
	cout << endl; cout << endl;
	vvfun.function(1, myfunA);
	vvfun.function(2, myfunB);

	// Now evaluate the function in n-dimensional space
	Vector<double, int> result2(2);
	
	result2 = vvfun.calculate(point);

	for (int j = result2.MinIndex(); j <= result2.MaxIndex(); j++)
	{
		cout << endl << result2[j] << endl;
	}

	// Now create IVP stuff
	IVP<double, int> ivp(1);

	ivp.Start(0.0);
	ivp.Final(1.0);


	return 0;

}
