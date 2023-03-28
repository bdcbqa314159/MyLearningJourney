// testChapter6A.cpp
//
// Sample program to show how to use the classes in Chapter 6.
// Vector and NumericMatrix.
//
// (C) Datasim Component Technology BV 2003
//

#include <iostream>
#include "numericmatrix.cpp"
#include "matrix.cpp"
#include "vector.cpp"
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
	Vector<double, int> vec1(10, 1, 2.0);	// Start index = 1, value 2.0
	Vector<double, int> vec2(10, 1, 3.0);	// Start index = 1, value 3.0


	Vector<double, int> vec3 = vec1 + vec2;
	Vector<double, int> vec4 = vec1 - vec2;

	Vector<double, int> vec5 = vec1 - 3.14;
	
		
	print (vec1);
	print (vec2);
	print (vec3);
	print (vec4);
	print (vec5);

	// Matrices
	NumericMatrix<double, int> m1(10, 10);				// 10 rows and 2 columns
	NumericMatrix<double, int> m2(10, 10, -2, 0);		// 10 rows and 2 columns, new start indices


	print (m1);
	print (m2);


	int rowstart = 1;
	int colstart = 1;
	NumericMatrix<double, int> m3(3, 3, rowstart, colstart);	
	for (int i = m3.MinRowIndex(); i <= m3.MaxRowIndex(); i++)
	{	
		for (int j = m3.MinColumnIndex(); j <= m3.MaxColumnIndex(); j++)
		{
			m3(i, j) = 1.0 /(i + j -1.0);
		}

	
	}

	
	print (m3);


	return 0;
}
