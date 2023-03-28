// TestArrayMatrixNorms.cpp
//
//	Averages and norms of vectors and matrices
//
// (C) Datasim Education BV 2003-2004
//

#include "SimplePropertySet.cpp"
#include <string>
#include <iostream>
using namespace std;

#include "arraymechanisms.cpp" // Conversion stuff here
#include "matrixmechanisms.cpp" // Conversion stuff here
#include "numericmatrix.cpp"

////////////////////////// Print functions ////////////////////////////////////////////////
template <class V, class I> void print(const SimplePropertySet<V, I>& pset)
{  // A generic print function for property sets
	
	cout << endl << "Size of Property Set " << pset.Count() << "\n\n";

	// We must use a const iterator here, otherwise we get a compiler error.
	SimplePropertySet<V,I>::const_iterator i;
	for (i = pset.Begin(); i != pset.End(); ++i)
	{
			cout << (*i).name() << ": " << (*i)() << endl;

	}

	cout << "\n";
}




int main()
{


	// The first 'sanity check' example
	size_t n = 10;
	double val = 1.0;
	Vector<double, int> myVector(10, 1, val);	// Create n copies of val

	print(myVector);

	SimplePropertySet<string, double> pset = allAverages(myVector);

	print(pset);

	n = 10;
	Vector<double, int> myVector2(4);	// Length 4, start index == 1
	myVector2[1] = 1.0; 
	myVector2[2] = -10.0; 
	myVector2[3] = 9.0; 
	myVector2[4] = 2.0; 


	pset = allNorms(myVector2);
	print(pset);

	myVector[3] = 433.0;

	Vector<double, int> myVectorA = reverse(myVector2);
	//print(myVectorA);

	Vector<double, int> myVector3 (10, 0); // Size 10, start index 0
	myVector3[myVector3.MinIndex()] = 999.98;
//	myVector2 = reverse(myVector3);
	print(myVector2);

	// Medians
	cout << "Median " << median(myVector2) << endl;

	Vector<double, int> myVector5(3, 1);	// Length 3, start index == 1
	myVector5[1] = 1.0; 
	myVector5[2] = -10.0; 
	myVector5[3] = 9.0; 

	cout << "Median " << median(myVector5) << endl;


	Vector<double, int> myVector6(3, 0);	// Length 3, start index == 0
	myVector6[0] = 1.0; 
	myVector6[1] = 2343.9;
	myVector6[2] = 9.0; 

	cout << "Median " << median(myVector5) << endl;

	NumericMatrix<double, int> m(3, 3, 1, 1);	// 3 rows, 3 columns, start indices 1
	SimplePropertySet<string, double> pset2;

	// Set diagonal element
	setDiagonal(m, 1.0);
	print(m);
	pset2 = allNorms(m);
	print(pset2);

	// All values == 2.0
	initMatrix(m, 2.0);
	print(m);
	m(2,2) = 456.0;		// Bit of mutation
	print(m);
	pset2 = allNorms(m);
	print(pset2);

	if (positive(m) == true) 
		cout << "Matrix is positive OK\n";
	else
		cout << "Matrix is NOT positive BAH\n";

	// Tridiagonal matrix
	int J = 3;
	Vector<double, int> a(J-1,	2,	-1.0);	// Lower		// J -1 elements, start index == 2
	Vector<double, int> b(J,	1,	2.0);	// Diagonal
	Vector<double, int> c(J-1,	1,	-1.0);	// Upper

	NumericMatrix<double, int> m2 = createMatrix(a, b, c);
	print(m2);
	pset2 = allNorms(m2);
	print(pset2);

	initMatrix(m, -2.0);
	if (negative(m) == true) 
		cout << "Matrix is negative OK\n";
	else
		cout << "Matrix is NOT negative BAH\n";


	return 0;
}
