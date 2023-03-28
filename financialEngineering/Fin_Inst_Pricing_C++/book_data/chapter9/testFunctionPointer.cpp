// testFunctionPointer.cpp
//
// Simple test program to show how to define and use
// function pointers.
//
// (C) Datasim Education BV 2003
//

#include <iostream.h>

double add(double x, double y)
{

	cout << "** Adding two numbers: " << x << ", " << y << endl;

	return x + y;

}

double multiply(double x, double y)
{

	cout << "** Multiplying two numbers: " << x << ", " << y << endl;

	return x * y;

}

double subtract(double x, double y)
{

	cout << "** Subtracting two numbers: " << x << ", " << y << endl;

	return x - y;

}

void genericFunction (double myX, double myY, double (*f) (double x, double y))
{ // A function that delivers two variables myX and MyY to the function pointer 'f'
  // This is a potentially reusable function

	// Call the function with myX and myY
	double result = (*f)(myX, myY);

	cout << "Result is: " << result << endl;
}


int main()
{

	double x = 3.0;
	double y = 2.0;

	genericFunction(x, y, add);
	genericFunction(x, y, multiply);
	genericFunction(x, y, subtract);



	return 0;
}
