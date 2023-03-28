// testMatrixFunction.cpp
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

int addition(const pair<double, double>& p) 
{

	return (int) (p.first + p.second);
}

int multiplication(const pair<double, double>& p) 
{

	return (int) (p.first * p.second);
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

	// Array of functions
	FunctionArray myFunArr(2);
	myFunArr[1] = myfun;
	myFunArr[2] = myfun2;
	
	Array<double, int> arr = calculate(myFunArr, 1.0, 2.0);
	
	print (arr);

	return 0;
}
