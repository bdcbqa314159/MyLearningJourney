// TstVectorSTLvector.cpp
//
// Examples to show how sequence containers (vector) work.
//
// (C) Datasim Education BV 2003
//

#include <math.h>
#include <vector>
#include <string>
#include <iostream.h>
#include "arraymechanisms.hpp" // Conversion stuff here
using namespace std;

////////////////////////// Print functions ////////////////////////////////////////////////
template <class T> void print(const vector<T>& l)
{  // A generic print function for vectors
	
	cout << endl << "Size of STL vector is " << l.size() << "\n[";

	// We must use a const iterator here, otherwise we get a compiler error.
	vector<T>::const_iterator i;
	for (i = l.begin(); i != l.end(); ++i)
	{
			cout << *i << ",";

	}

	cout << "]\n";
}

template <class V, class I> void print(const Vector<V,I>& v)
{

	cout << "\nDatasim Vector\nMinIndex: " << v.MinIndex() << " , MaxIndex: " << v.MaxIndex() << endl;

	cout << "\nARR:[";
	for (I j = v.MinIndex(); j <= v.MaxIndex(); j++)
	{
		cout << v[j] << ",";
	
	}

	cout << "]";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

// Functions for testing in Excel as well

double EuropeanType(double t)
{

	if (t <= 0.5)
		return 1.0;

	double x = t - 0.5;
	return ::exp(-x*x*0.5);
}

double DigitalType(double t)
{

	if (t <= 0.5)
		return 1.0;

	double x = t - 0.5;
	return ::exp(-x);
}

double TurningPointType(double t)
{

	if (t <= 0.5)
		return ::exp(t);

	return ::exp(-t);

}

int main()
{


	size_t n = 10;
	double val = 3.14;
	vector<double> vector2(n, val);	// Create n copies of val

	cout << "Size of vector2 " << vector2.size() << endl;

	print(vector2);

	Vector<double, int> myVec1 = createDatasimVector(vector2);
	print(myVec1);

	// Access elements of the vector by using the indexing operator []
	// Change some values here and there
	vector2[0] = 2.0;
	vector2[1] = 456.76;

	int last_element= vector2.size() - 1;
	vector2[last_element] = 55.66;

	print(vector2);

	myVec1 = createDatasimVector(vector2);
	print(myVec1);

	// Random mutation
	myVec1[5] = 999.999;

	vector<double> yetAnotherSTLvector = createSTLvector(myVec1);
	print(yetAnotherSTLvector);

	return 0;
}
