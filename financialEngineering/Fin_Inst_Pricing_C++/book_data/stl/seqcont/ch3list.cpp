// ch3list.cpp
//
// Examples to show how sequence containers (list) work.
//
// (C) Datasim Education BV 2003
//

#include <list>
#include <string>
#include <iostream.h>

using namespace std;

int main()
{

	// Create list instances
	list<int> list1;			// Empty list

	size_t n = 10;
	double val = 3.14;
	list<double> list2(n, val);	// Create n copies of val

	list<double> list3(list2);	// Create a copy of list2

	cout << "Size of list1 " << list1.size() << endl;
	cout << "Size of list2 " << list2.size() << endl;
	cout << "Size of list3 " << list3.size() << endl;


	// We iterate over the elements of list 3 and print its elements
	// Create list iterator
	list<double>::const_iterator i;
	
	// Print every character in the list
	for (i = list2.begin(); i != list2.end(); ++i)
	{
			cout << *i << ",";
	}

	cout << endl;


	// Now populate a new list with the elements of list2;add to end of list
	list<double> list4;
	for (i = list2.begin();	i != list2.end(); ++i)
	{
			list4.push_back(*i);
	}


	// Print every character in the list
	for (i = list4.begin(); i != list4.end(); ++i)
	{
			cout << *i << ",";
	}

	cout << endl;

	return 0;
}
