// ch3alg.cpp
//
// Example program which uses the STL sort algorithm to sort a vector
// and the merge algorithm to merge to vectors.
// After that is uses the binary search algorithm to search for an item.
//
// The algorithms can be used in applications for Monte Carlo simulations 
// and the numerical solution of Stochastic Differntial Equations (SDE).
//
// (C) Datasim Education BV 2003

#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

void print(const vector<int>& v)
{ // Print the vector

	// Create vector iterator
	vector<int>::const_iterator i;
	
	cout << "[";

	// Print every integer in the vector
	for (i=v.begin(); i!=v.end(); i++) cout<<*i<<", ";
	cout << "]" << endl;
}

int main()
{
	// Create a 'seed' at the current time so that
	// the random numbers will be different each time 
	// the generator is run
	srand((unsigned) time (NULL));

	int Size = 5;
	// Create vectors and fill with random numbers
	vector<int> v1, v2;
	int i;
	for (i=0; i<= Size; i++) 
		v1.push_back(rand());
	for (i=0; i< Size; i++) 
		v2.push_back(rand());

	cout<<"Two random lists"<<endl;
	print(v1);
	print(v2);

	// Sort the lists
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	cout<<"Two sorted lists"<<endl;
	print(v1);
	print(v2);

	// Merge the two lists to a third list
	vector<int> v3(v1.size()+v2.size());
	cout<<endl<<"Merge the two lists"<<endl;
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	print(v3);

	
	// Search an item in a sorted list
	/*
	if (binary_search(v3.begin(), v3.end(), v3[15])==true) 
		cout<<v3[15]<<" is present in vector 3"<<endl;
	else 
		cout<<v3[15]<<" is not present in vector 3"<<endl;
	*/

	int arr[] = {1, 2, 3, 3, 5, 8};		// Built-in sorted C-style  array
	const int N = sizeof(arr)/sizeof(int);

	for (int j = 1; j <= 10; j++)
	{
		cout << "\nSearching for: " << j << ":";
		if (binary_search(arr, arr+N, j) == true)
			cout << "present";
		else
			cout << "not present";
	}

	return 0;
}

