// testmatrixprofile2.cpp
//
// POC program to test different kinds of matrix structure. 
// In this case we use the STL vector class. This code has 
// NOT been optimised for performance.
//
// (C) Datasim Education BV 2003
//

#include <vector>
//#include <iostream.h>

/*
template <class V> void print (vector<vector<V> >& mat)
{

	vector<V>::const_iterator it;

	for (it = mat.begin(); it != mat.end(); it++)
	{
		print (mat[j]);
	
	}

}
*/
template <class T> void print(const vector<T>& v)
{  // Print the contents of a vector. Notice the presence of a constant iterator.
/*	
	cout << endl << "Size of vector is " << v.size() << "\n[";

	// We must use a const iterator here, otherwise we get a compiler error.
	vector<T>::const_iterator i;
	
	for (i = v.begin(); i != v.end(); ++i)
	{
			cout << *i << ",";

	}

	cout << "]\n";*/
}


int main()
{
/*	int N = 3;

	// Upper triangular
	vector <vector<double> > upper(N, 1);

	int size = N;
	for (int j = 1; j <= N; j++)
	{
		upper[j] = vector<double, int>(size, j);
		size--;
	}

	upper[1][1] = 1.0;
	upper[1][2] = 6.0;
	upper[1][3] = 5.0;
	upper[2][2] = 2.0;
	upper[2][3] = 4.0;
	upper[3][3] = 3.0;


	// Lower triangular
	vector <vector<double> > lower(N, 1);

	size = 1;
	for (j = 1; j <= N; j++)
	{
		lower[j] = vector<double>(size, 1);
		size++;
	}

	lower[1][1] = 1.0;
	lower[2][1] = 6.0;
	lower[3][1] = 5.0;
	lower[2][2] = 2.0;
	lower[3][2] = 4.0;
	lower[3][3] = 3.0;

	// !! Upper and lower triangular matrices can be used as symmetric matrices

	// Band matrix

	int K = 4; // band width; the number of diagonal elements will be 2K + 1

	// Lower triangular
	vector <vector<double> > lower(N, 1);

	lower[1] = vector<double> (
	size = 1;
	for (j = 2; j <= N; j++)
	{
		lower[j] = vector<double, int>(size, 1);
		size++;
	}
	print (lower); */

	return 0;
}

 
