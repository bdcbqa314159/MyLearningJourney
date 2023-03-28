// tstiter6.cxx
//
// Program to show use of more exotic types of output iterators:
//
//	1. back_insert_iterator
//	2. front_insert_iterator
//	3. insert_iterator
//	4. raw_storage_iterator
//
// Application areas:
//
//	Batch processing of sequences to produce other sequences
//
// (C) Datasim Education 1998

#include "common.hxx"
#include "point.hxx"

void print(const vector<int>& l)
{  // Print the contents of a vector. Notice the presence of a constant iterator.
	
	if (l.empty())
	{
		cout << "Vector is empty\n";
		return;
	}

	cout << endl << "Size of vector is " << l.size() << "\n[";

	// We must use a const iterator here, otherwise we get a compiler error.
	vector<int>::const_iterator i;


	
	for (i = l.begin(); i != l.end(); ++i)
	{
			cout << *i << ",";

	}

	cout << "]\n";
}

void print(const list<int>& l)
{
	cout << endl << "Size of list is " << l.size() << endl << "[";

	list<int>::iterator i;
	
	for (i = l.begin(); i != l.end(); ++i)
	{
			cout << *i << ",";

	}

	cout << "]\n";

}

int main()

{

	int myarr [] = {1, 2, 3, 4}; // Standard C++ array

// 1. back_insert_iterator: allows insertion at the end of its
// associated container

	// Iterator is constructed with an associated container object
	vector<int> myvec;
	back_insert_iterator<vector<int> > mybiter (myvec);
	print(myvec);

	// Now copy the array to the vector via the back iterator. This is a 
	// 'data flow' operation
	copy(myarr, myarr + 4, mybiter);

	print(myvec);

// 2. front_insert_iterator: allows insertion at the front of its
// associated container

	// Iterator is constructed with an associated container object
	list<int> mylist;
	front_insert_iterator<list<int> > myfiter (mylist);
	print(mylist);

	// Now copy the vectorto the list via the back iterator. This is a 
	// 'data flow' operation
	copy(myvec.begin(), myvec.end(), myfiter);

	print(mylist);

// 3. insert_iterator: the ability to insert items using an auxiliary 
// iterator. N.B.Make sure that the auxiliary iterator is initialised!
	vector<int> vec2(myvec);
	print(vec2);
	list<int>::iterator listit = mylist.begin();
	++listit;
	insert_iterator<list<int> > myiiter(mylist, listit);

	print(mylist);

	copy(vec2.begin(), vec2.end(), myiiter);

	print(mylist);


// 4. raw_storage_iterator: the ability to directly construct objects in raw
// storage. This is a sort of Proxy object.

	// In this example ref is a Proxy object to parr and ref is initialised by the 
	// raw storage iterator.
	
	Point* parr = new Point[5];	// Allocate raw memory
	Point* ref = parr;

	raw_storage_iterator<Point*, Point> r(ref);

	for (int i = 0; i < 5; i++)
	{
		*r++ = Point(i, i); // Equivalent to creating an object at location 

	}

	for (i = 0; i < 5; i++)
	{
		cout << *parr++ << endl;
	}

	cout << "Printing the reference \n";
	for (i = 0; i < 5; i++)
	{
		cout << ref[i] << endl;
	}


	return 0;
}

