// Main function.
//
// Datasim Education BV (c) 2003
// 
// Modification dates:
// 23 July 2003 - MB - Started.
// 29 July 2003 - MB - Using SimplePropertySet for input values A, B and N.

#include <iostream>
#include <string>
using namespace std;

#include "Vector.cpp"
#include "SimplePropertySet.cpp"

// Forward declaration of functions that implement activities.

void GetInput(SimplePropertySet<string, double> & input);

void Calculate( const SimplePropertySet<string, double> & input, 
			    Vector<double, int> & x, Vector<double, int> & function_result, 
			    Vector<double, int> & delta, Vector<double, int> & gamma,
				Vector<double, int> & n_result, Vector<double, int> & N_result,
				Vector<double, int> & european, Vector<double, int> & digital,
				Vector<double, int> & turningPoint);

void Present( const Vector<double, int> & x, const Vector<double, int> & function, 
			  const Vector<double, int> & delta, const Vector<double, int> & gamma,
			  const Vector<double, int> & N_result, const Vector<double, int> & n_result,
			  const Vector<double, int> & european, const Vector<double, int> & digital,
				const Vector<double, int> & turningPoint);

// Runs Registration, Conversion and Presentation activities.
int main()
{
	// Declare variables.
	SimplePropertySet<string, double> input;
	input.add( Property<string, double>("A", 0.0) );
	input.add( Property<string, double>("B", 1.0) );
	input.add( Property<string, double>("N", 10.0) );

	// Run Registration activity.
	GetInput(input);
	int N = (int) input.value("N")();

	cout << "A: " << input.value("A")() << endl;
	cout << "B: " << input.value("B")() << endl;
	cout << "N: " << input.value("N")() << endl;

	// Create vectors.
	Vector<double, int> x(N+1);
	Vector<double, int> function(N+1);
	Vector<double, int> delta(N+1);
	Vector<double, int> gamma(N+1);
	Vector<double, int> n_result(N+1);
	Vector<double, int> N_result(N+1);
	Vector<double, int> european(N+1);
	Vector<double, int> digital(N+1);
	Vector<double, int> turningPoint(N+1);

	// Run Conversion activity.
	Calculate(input, x, function, delta, gamma, n_result, N_result, european, digital, turningPoint);

	// Run Presentation activity.
	Present(x, function, delta, gamma, n_result, N_result, european, digital, turningPoint);

	// Wait for input.
	string abc;
	cin >> abc;

	return 0;
}