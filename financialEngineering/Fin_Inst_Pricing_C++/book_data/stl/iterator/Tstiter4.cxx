// tstiter4.cxx
//
// Test of bidirectional and random access iterators. We shall use both in-place
// and copy version of the 'reverse' algorithm. We use an insert iterator for the copy
// version.
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


bool mycomp(const char* a, const char* b)
{
	return ::strcmp (a, b) < 0 ? 1: 0;
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

	// Now reverse the elements in the list (current object is modified)
	reverse(list1.begin(), list1.end());
	print(list1);

	// Reverse the original list and place it in a second list
	list<int> list2;
	list<int>::iterator it1 = list2.begin();
	insert_iterator<list<int> > it2(list2, it1);
	reverse_copy(list1.begin(), list1.end(), it2);
	print(list2);

	// Random iterators (we need sorted containers)
	int v1[100];
	for (int ii = 0; ii < 100; ii++)
	{
		v1[ii] = ii;
	}

	// A bit of mutation
	v1[4] = 7;
	v1[6] = 3;


	bool found = binary_search(v1, v1 + 100, 13);

	if (found == true)
		cout << "OK, value found\n";
	else
		cout << "Not found, something rotten\n";


	// Binary search with your own compare function
	char* labels[] = { "aa", "bb", "ff", "ss", "zz"};

	const unsigned count = sizeof(labels)/sizeof(labels[0]);
	if (binary_search(labels, labels + count, "ff", mycomp))
		cout << "OK, string value found\n";
	else
		cout << "Not found, something rotten\n";

	if (binary_search(labels, labels + count, "xx", mycomp))
		cout << "Not OK, string value found\n";
	else
		cout << "OK, Not found\n";

	return 0;
}