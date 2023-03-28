// testmatrixprofile3.cpp
//
// POC program to test different kinds of matrix structure.
// The classes used are from STL.
//
// (C) Datasim Education BV 2003
//

#include <vector>
#include <string>
#include <iostream>

using namespace std;

template <class V> void print (vector<vector<V> >& mat)
{

	vector<vector<V> >::const_iterator i;
	
	// Print every vector in the matrix
	for (i = mat.begin(); i!=mat.end(); i++)
	{
		
		print (*i);
	}

	cout << endl;
}

template <class V> void print(const vector<V>& v)
{

	cout << "\nV:[";

	vector<V>::const_iterator i;
	
	// Print every value in the vector
	for (i = v.begin(); i!=v.end(); i++)
	{
		
		cout << (*i) << ",";
	}


	cout << "]";
}


int main()
{
	int N = 3;

	// Triangular matrix
	vector <vector<double> > upper(N);

	// Create vector iterator
	vector<vector<double> >::iterator i;
	
	// Print every value in the vector
	int size = N;

	// Create temporary vector 'tmp'
	vector<double> tmp(size);

	for (i = upper.begin(); i!=upper.end(); i++)
	{
		
		(*i) = tmp;
	
		size--;
		tmp = vector<double>(size);
	}

	upper[0][0] = 1.0;
	upper[0][1] = 6.0;
	upper[0][2] = 5.0;
	upper[1][0] = 2.0;
	upper[1][1] = 4.0;
	upper[2][0] = 3.0;

	print(upper);

	// Create a 'full' matrix
	vector<vector<int> > myMat(5);	// 5 rows

	myMat[0] = vector<int>(5,1);	// 5 elements in vector with value 1
	myMat[1] = vector<int>(5,2);
	myMat[2] = vector<int>(5,3);
	myMat[3] = vector<int>(5,4);
	myMat[4] = vector<int>(5,5);

	print(myMat);


	// Matrices with character values
	vector<vector<char> > myCharMat(5);	// 5 rows

	myCharMat[0] = vector<char>(5,'A');	// 5 elements in vector with value 'A'
	myCharMat[1] = vector<char>(4,'B');
	myCharMat[2] = vector<char>(3,'C');
	myCharMat[3] = vector<char>(2,'D');
	myCharMat[4] = vector<char>(1,'E');

	print(myCharMat);

	return 0;

}

