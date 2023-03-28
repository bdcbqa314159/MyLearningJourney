// tstiter2.cxx
//
// Test of iterators using the 'find' algorithm:
//
//	1. Ordinary pointers
//	2. List iterators
//	3. ostream iterators (write values into an output stream). 
//
// (C) Datasim Education 1998
//

#include "common.hxx"

void print(const list<int>& l)
{
	cout << endl << "Size of list is " << l.size() << endl;

	list<int>::iterator i;
	
	for (i = l.begin(); i != l.end(); ++i)
	{
			cout << *i << ",";

	}

	cout << endl;
}

int main()
{ // Musser page 53

	int a[10] = {12, 3, 25, 7, 11, 213, 7, 123, 29, -31};

	// Ordinary pointers
	int b[10];
	copy (&a[0], &a[10], &b[0]);


	// List iterator
	list<int> list1;
	for (int i = 0; i < 10; i++)
	{
		list1.push_back(a[i]);
	}

	// Print list separated by new line
	ostream_iterator<int> out (cout, "\n");		

	copy (list1.begin(), list1.end(), out);

	// Print list separated by comma
	ostream_iterator<int> out2(cout, ",");
	copy (&b[0], &b[10], out2);


	return 0;
}