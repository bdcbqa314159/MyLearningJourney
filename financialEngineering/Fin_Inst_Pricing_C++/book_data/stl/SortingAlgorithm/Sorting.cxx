// Sorting.cxx
//
// Example program which uses the STL sort algorithm to sort a vector
// and the merge algorithm to merge to vectors.
// After that is uses the binary search algorithm to search for an item.
//
// (C) Datasim education BV

#include "common.hxx"

void print(const vector<int>& v)
{ // Print the vector

	// Create vector iterator
	vector<int>::const_iterator i;
	
	// Print every integer in the vector
	for (i=v.begin(); i!=v.end(); i++) cout<<*i<<",";
	cout << endl;
}

void main()
{
	// Create vectors and fill with random numbers
	vector<int> v1, v2;
	int i;
	for (i=0; i<10; i++) v1.push_back(rand());
	for (i=0; i<10; i++) v2.push_back(rand());

	cout<<"Two random lists"<<endl;
	print(v1);
	print(v2);

	// Sort the lists
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	cout<<cout<<"Two sorted list"<<endl;
	print(v1);
	print(v2);

	// Merge the two lists to a third list
	vector<int> v3(v1.size()+v2.size());
	cout<<endl<<"Merge the two lists"<<endl;
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	print(v3);

	// Search an item in a sorted list
	if (binary_search(v3.begin(), v3.end(), v3[15])==true) cout<<v3[15]<<" is aanwezig in vector 3"<<endl;
	else cout<<v3[15]<<" is niet aanwezig in vector 3"<<endl;
}

