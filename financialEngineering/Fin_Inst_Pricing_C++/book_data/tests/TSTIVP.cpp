// testivp.cpp
//
// Testing new Function classes.
//

#include "detfunction.cpp"
#include "ivp.cpp"
#include <iostream>
#include <math.h>


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
	Vector<double, int> point(2);
	point[1] = 10.0;
	point[2] = 20.0;

	// Vector-valued functions; first create an array of functions
	VectorValuedFunction<double, double, int> vvfun(2);


	ScalarValuedFunction<double, double, int> myfunA;
	myfunA.function(typical2);
	cout << "A: " << myfunA.calculate(point);
	cout << endl; cout << endl;
	ScalarValuedFunction<double, double, int> myfunB;
	myfunB.function(typical3);
	cout << "B: " << myfunB.calculate(point);
	cout << endl; cout << endl;

	vvfun.function(1, myfunA);
	vvfun.function(2, myfunB);

	// Now evaluate the function in n-dimensional space
	Vector<double, int> result2(2);
	
	result2 = vvfun.calculate(point);

	cout << "range dim vvfun " << vvfun.RangeDimension() << endl;

	for (int j = result2.MinIndex(); j <= result2.MaxIndex(); j++)
	{
		cout << "vvfun " << endl << result2[j] << endl;
	}

	// Now create IVP stuff
	IVP<double, int> ivp(2);

	ivp.Start(0.0);
	ivp.Final(1.0);

	ivp.RightHandSide(vvfun);
	ivp.InitialCondition(point);

	cout << "Now calculating RHS" << endl;

	Vector<double, int> res = ivp.CalculateRHS(point);

	for (j = res.MinIndex(); j <= res.MaxIndex(); j++)
	{
		cout << endl << res[j] << endl;
	}

	if (ivp.ConsistentIVP() == true)
		cout << "Good IVP\n";
	else
		cout << "Bad IVP\n";

	return 0;

}
