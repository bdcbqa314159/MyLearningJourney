// test_2dfun.cpp
// 
// Program to test function classes with two variables
//
// (C) Datasim Component Technology BV 2004
//

#include "detfunction.cpp"
#include <iostream.h>

int addition(const pair<double, double>& p) 
{

	return (int) (p.first + p.second);
}

int multiplication(const pair<double, double>& p) 
{

	return (int) (p.first * p.second);
}

int main()
{

	// A two-variable function representing addition
	TwoVarDFunction<double, double, int> myfun;
	myfun.function(addition);
	cout << "Add 1 and 2: " << myfun.calculate(1.0, 2.0) << endl;


	// A two-variable function representing multiplication
	TwoVarDFunction<double, double, int> myfun2;
	myfun2.function(multiplication);
	cout << "Multiply 20 and 2: " << myfun2.calculate(20.0, 2.0) << endl;

	return 0;
}
