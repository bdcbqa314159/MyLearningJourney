// Implementation of Registration activity.
//
// Datasim Education BV (c) 2003
// 
// Modification dates:
// 23 July 2003 - MB - Started.
// 29 July 2003 - MB - Reading data from Excel into SimplePropertySet.
// 31 July 2003 

#include <iostream>
using namespace std;

// Initialize A, B and N with values from user.
void Registration(double& A, double& B, int& N)
{

		// Version 0.01

		cout << "Give lower value of interval: ";
		cin >> A;

		cout << "Give upper value of interval: ";
		cin >> B;

		cout << "Give number of subdivisions:  ";
		cin >> N;

}