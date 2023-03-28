// tstiter1.cxx
//
// Test of iterators using the 'find' algorithm:
//
//	1. Ordinary pointers
//	2. List iterators
//	3. istream iterators (read values from a standard input stream). This uses
//	ptrdiff_t in stddf.h for subtracting two pointers.
//
// (C) Datasim Education 1998

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
{

	int a[10] = {12, 3, 25, 7, 11, 213, 7, 123, 29, -31};

	// Ordinary pointers
	int* ptr = find(&a[0], &a[100], 7);

	cout << "Value: " << (*ptr) << endl;


	// List iterator
	list<int> list1;
	for (int i = 0; i < 10; i++)
	{
		list1.push_back(a[i]);
	}

	list<int>::iterator it = find(list1.begin(), list1.end(), 7);	// Seek value
	
	if (*it == 7 && *(++it) == 11)
		cout << "OK, list element value is found\n";

	*it = 99;
	print(list1);

	// Searching in an input stream
	cout << "Type some characters including an 'x' followed \n" 
		 << "by at least one nonwhite-space character: " << flush;

	istream_iterator<char> in (cin);		
	istream_iterator<char> eos;		
//
	find(in, eos, 'x');

	cout << "First non-white character following first 'x' was " << *(++in) << endl;

	return 0;
}