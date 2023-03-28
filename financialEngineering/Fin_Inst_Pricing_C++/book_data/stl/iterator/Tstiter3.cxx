// tstiter3.cxx
//
// Test of forward iterators. A forward iterator is one that can both
// read and write in one direction.
//
// Forward iterators can be used with built-in types and STL-defined types such 
// as lists and deques.
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

	list<int> list1;
	for (int i = 0; i < 10; i++)
	{
		list1.push_back(a[i]);
	}

	print(list1);

	// Now replace all occurrences of one value by another value
	replace (list1.begin(), list1.end(), 7, 0);
	print(list1);

	// No effect on list because old value is gone
	replace (list1.begin(), list1.end(), 7, 0);
	print(list1);

	return 0;
}