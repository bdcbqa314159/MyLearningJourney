// testChapter6.cpp
//
// Sample program to show how to use the classes in Chapter 6.
// Array and Matrix.
//
// (C) Datasim Component Technology BV 2003
//

#include <iostream>
#include "numericmatrix.cpp"
#include "matrix.cpp"
using namespace std;


template <class V, class I> void print(const Array<V,I>& v)
{

	cout << "\n\nMinIndex: " << v.MinIndex() << " , MaxIndex: " << v.MaxIndex() << endl;

	cout << "\nARR:[";
	for (I j = v.MinIndex(); j <= v.MaxIndex(); j++)
	{
		cout << v[j] << ",";
	
	}

	cout << "]";
}


template <class V, class I> void print(const Matrix<V,I>& m)
{

	cout << "\n\nMinRowIndex: " << m.MinRowIndex() << " , MaxRowIndex: " << m.MaxRowIndex() << endl;
	cout << "MinColumnIndex: " << m.MinColumnIndex() << " , MaxColumnIndex: " << m.MaxColumnIndex() << endl;

	cout << "\nMAT:[";
	for (I i = m.MinRowIndex(); i <= m.MaxRowIndex(); i++)
	{
		cout << "\nRow " << i << " (";
		for (I j = m.MinColumnIndex(); j <= m.MaxColumnIndex(); j++)
		{
			cout << m(i, j) << ",";
		}
		cout << ")";
	}

	cout << "]";
}

int main()
{

	// Create some arrays
	Array<double, int> arr1(10);			// Start index = 1
	Array<double, int> arr2(10, -1);		// Start index = -1

	// An array with 10 elements,starting at 0 and all values == 3.14
	Array<double, int> arr3(10, 0, 3.14);

	print (arr1);
	print (arr2);
	print (arr3);


	// Matrices
	Matrix<double, int> m1(10, 10);				// 10 rows and 2 columns
	Matrix<double, int> m2(10, 10, -2, 0);		// 10 rows and 2 columns, new start indices


	print (m1);
	print (m2);


	// 10 rows and 2 columns, values = 3.14
	Matrix<double, int> m3(10, 10);	
	for (int i = m3.MinRowIndex(); i <= m3.MaxRowIndex(); i++)
	{
		for (int j = m3.MinColumnIndex(); j <= m3.MaxColumnIndex(); j++)
		{
			m3(i,j) = 3.14;
		}
	}


	print (m3);


	return 0;
}
