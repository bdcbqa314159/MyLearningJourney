// testMatrixFunctionII.cpp
// 
// Program to test function classes, in this case in 
// combination with other classes such as Array and Matrix.
//
// (C) Datasim Component Technology BV 2004
//

#include "detfunction.cpp"
#include "array.cpp"
#include "matrix.cpp"
#include <iostream.h>
#include "arraymechanisms.cpp"
#include "simplepropertyset.cpp"
#include "property.cpp"
#include <string>
using namespace std;

double square(const double& x)
{
	return x*x;
}

double mysqrt(const double& x)
{
	return ::sqrt(x);
}

int addition(const pair<double, double>& p) 
{

	return (int) (p.first + p.second);
}

int multiplication(const pair<double, double>& p) 
{

	return (int) (p.first * p.second);
}

double realValuedFunction(const Vector<double, int>& arr)
{

		// Simple test case; return sum of the elements
		
		return sum(arr);
}


typedef Array<TwoVarDFunction<double, double, int>, int> FunctionArray;
Array<double, int> calculate(const FunctionArray& funArr, double first, double second)
{

		Array<double, int> result(funArr.Size());

		for (int i = funArr.MinIndex(); i <= funArr.MaxIndex(); i++)
		{
			result[i] = funArr[i].calculate(first, second);
		}

		return result;
}

typedef SimplePropertySet<string, AtomicDFunction<double, double> > VectorFunction;
Array<double, int> calculate(const VectorFunction& vvfun, double d)
{
		// The class VectorFunction is a typedef for a SimplePropertySet
		
		VectorFunction::const_iterator it;

		Array<double, int> result(vvfun.Count());
		int j = result.MinIndex();

		for (it = vvfun.Begin(); it != vvfun.End(); it++, j++)
		{
			Property<string, AtomicDFunction<double, double> > tmp = (*it);
			result[j] = tmp().calculate(d);
		}

		return result;
}

int main()
{

	// A two-variable function representing addition
	TwoVarDFunction<double, double, int> myfun;
	myfun.function(addition);


	// A two-variable function representing multiplication
	TwoVarDFunction<double, double, int> myfun2;
	myfun2.function(multiplication);

	// Array of functions
	FunctionArray myFunArr(2);
	myFunArr[1] = myfun;
	myFunArr[2] = myfun2;
	Array<double, int> arr = calculate(myFunArr, 1.0, 2.0);
	print (arr);


	// Now Vector functions
	AtomicDFunction<double, double> myfunA; AtomicDFunction<double, double> myfunB;
	myfunA.function(square);
	myfunB.function(mysqrt);
	
	VectorFunction vvFun;
	vvFun.add(Property<string, AtomicDFunction<double, double> >("square", myfunA));
	vvFun.add(Property<string, AtomicDFunction<double, double> >("sqrt", myfunB));

	cout << "\nSize of vector function: " << vvFun.Count() << endl;

	Array<double, int> arr2 = calculate(vvFun, 2.0);
	print(arr2);

	// Real-valued functions
	AtomicDFunction<Vector<double, int>, double> rvFun;
	rvFun.function(realValuedFunction);
	Vector<double, int> myArr(10, 1, 2.0);	// Length 10, start index 1, value 2.0
	print(myArr);
	cout << "Value of RVF: " << rvFun.calculate(myArr) << endl;
	
	return 0;
}
