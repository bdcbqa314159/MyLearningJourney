// Main function.
//
// Datasim Education BV (c) 2003
// 
// Modification dates:
// 23 July 2003 - MB - Started.
// 29 July 2003 - MB - Using SimplePropertySet for input values A, B and N.
// 31 July 2003 DD special cases

#include <iostream>
#include <string>
using namespace std;

#include "Vector.cpp"
//#include "ddregistration.cpp"
#include "ddconversion.cpp"
#include "ddpresentation.cpp"

// Runs Registration, Conversion and Presentation activities.
int main()
{
	double A, B;
	int N;

	// Run Registration activity.
	Registration(A, B, N);

	cout << "A etc " << A << ", " << B << ", " << N << endl;

	// Create vectors.
	Vector<double, int> x(N+1);
	Vector<double, int> n_result(N+1);
	Vector<double, int> N_result(N+1);

	// Run Conversion activity.
	Conversion(A, B, N, x, n_result, N_result);

	cout << "display " << endl;

	// Run Presentation activity.
	Presentation(x, n_result, N_result);

	// Wait for input.
	cout << "Press ANY key co continue: ";
	string abc;
	cin >> abc;

	return 0;
}