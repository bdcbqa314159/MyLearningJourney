// test_new.cpp
//
// Testing new Function classes.
//

#include "detfunction.cpp"
#include "vector.cpp"
#include <iostream>
#include <math.h>
#include "simplepropertyset.cpp"

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

		return t + 2;
}

double second (const double& t)
{

		return t;
}
double third (const double& t)
{

		return t*t;
}

int main()
{

	Vector<double> value(2);
	value[1] = 1.0;
	value[2] = 2.0;

	// Domain and range are double precision numbers
	// Functions of one variables
	ScalarFunction<double, double, int> myfunI;
	myfunI.function(first);
	cout << "I: " << myfunI.calculate(2.0);
	cout << endl; cout << endl;

	ScalarFunction<double, double, int> myfunII;
	myfunII.function(first);
	cout << "II: " << myfunII.calculate(2.0);
	cout << endl; cout << endl;

	ScalarFunction<double, double, int> myfunIII;
	myfunIII.function(first);
	cout << "III: " << myfunIII.calculate(2.0);
	cout << endl; cout << endl;

	PrintFunctionVisitor<double, double, int> SFvisitor;
	SFvisitor.visit(myfunII);

	myfunII.accept(SFvisitor);

	VectorFunction<double, double, int> vfun(3);
	vfun.function(1, myfunI);
	vfun.function(2, myfunII);
	vfun.function(3, myfunIII);

	Vector<double, int> result(3);
	result = vfun.calculate(1.0);

	cout << "vector function [" << result.MinIndex() << "," << result.MaxIndex() << "]\n";


	for (int j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		cout << endl << result[j] << endl;
	}


	return 0;

}
