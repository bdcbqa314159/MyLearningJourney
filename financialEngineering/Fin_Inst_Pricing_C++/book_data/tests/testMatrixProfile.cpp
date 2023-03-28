// testmatrixprofile.cpp
//
// POC program to test different kinds of matrix structure.
//
// (C) Datasim Education BV 2003
//

#include "array.cpp"
#include <iostream.h>


template <class V, class I> void print (Array<Array<V, I> >& mat)
{

	for (int j = mat.MinIndex(); j <= mat.MaxIndex(); j++)
	{
		print (mat[j]);
	
	}

}

template <class V, class I> void print(const Array<V,I>& v)
{

	cout << "\nV:[";
	for (I j = v.MinIndex(); j <= v.MaxIndex(); j++)
	{
		cout << v[j] << ",";
	
	}

	cout << "]";
}


int main()
{
	int N = 3;

	// Upper triangular
	Array <Array<double, int> > upper(N, 1);

	int size = N;
	for (int j = 1; j <= N; j++)
	{
		upper[j] = Array<double, int>(size, j);
		size--;
	}

	upper[1][1] = 1.0;
	upper[1][2] = 6.0;
	upper[1][3] = 5.0;
	upper[2][2] = 2.0;
	upper[2][3] = 4.0;
	upper[3][3] = 3.0;


	// Lower triangular
	Array <Array<double, int> > lower(N, 1);

	size = 1;
	for (j = 1; j <= N; j++)
	{
		lower[j] = Array<double, int>(size, 1);
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
	Array <Array<double, int> > lower(N, 1);

	lower[1] = Array<double, int> (
	size = 1;
	for (j = 2; j <= N; j++)
	{
		lower[j] = Array<double, int>(size, 1);
		size++;
	}
	print (lower);
}

