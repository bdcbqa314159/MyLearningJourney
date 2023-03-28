// TestIterators.cxx
//
// Test program to test the following iterators;
// - Bidirectional Random access iterators
// - Reverse iterators
// - Const iterators
//
// (C) Datasim Education 1998

#include "common.hxx"
#include "Point.hxx"

vector<Point> makevector(int size)
{ // Creates STL vector with points

	vector<Point> result;	// Create empty vector

	for (int i=1; i<=size; i++)
	{
		result.push_back(Point(i,i));
	}

	return result;
}

void print(const vector<Point>& l)
{ // Print the vector

	cout<<"Size of vector is: "<<l.size()<<endl;

	// Create vector iterator
	vector<Point>::const_iterator i;
	
	// Print every character in the vector
	for (i=l.begin(); i!=l.end(); i++)
	{
		cout<<(*i)<<" ";
	}

	cout<<endl;
}

void main()
{
	// Create a vector with characters
	vector<Point> vector1=makevector(5);	

	// Create bidirectional iterator
	vector<Point>::iterator bi;

	// Traverse forward
	cout<<"Tranverse forward"<<endl;
	bi=vector1.begin();		// Set iterator
	while (bi!=vector1.end()) cout<<(*bi++)<<" ";
	cout<<endl<<endl;;

	// Traverse backward
	cout<<"Traverse backward"<<endl;
	bi=(vector1.end());
	do
	{
		cout<<(*--bi)<<" ";
	}
	while (bi!=vector1.begin());
	cout<<endl<<endl;

	// Traverse random
	cout<<"Traverse random"<<endl;
	bi=vector1.begin();
	cout<<*bi<<" ";				// First element
	cout<<*(bi+=3)<<" ";		// 1+3 is 4th element
	cout<<*(bi-=1)<<" ";		// 4-1 is third element
	cout<<bi[-1]<<" ";			// 3-1 is second element
	cout<<bi[1]<<endl<<endl;	// 3+1 is fourth element

	// Create ridirectional iterator
	vector<Point>::reverse_iterator ri;

	// Traverse reverse forward
	cout<<"Tranverse reverse forward"<<endl;
	ri=vector1.rbegin();		// Set iterator
	while (ri!=vector1.rend()) cout<<(*ri++)<<" ";
	cout<<endl<<endl;;

	// Traverse reverse backward
	cout<<"Traverse reverse backward"<<endl;
	ri=(vector1.rend());
	do
	{
		cout<<(*--ri)<<" ";
	}
	while (ri!=vector1.rbegin());
	cout<<endl<<endl;

	// Traverse reverse random
	cout<<"Traverse reverse random"<<endl;
	cout<<*ri<<" ";				// First element
	cout<<*(ri+=3)<<" ";		// 1+3 is 4th element
	cout<<*(ri-=1)<<" ";		// 4-1 is third element
	cout<<ri[-1]<<" ";			// 3-1 is second element
	cout<<ri[1]<<endl<<endl;	// 3+1 is fourth element

	// Change element
	cout<<"Change first element with mutable iterator"<<endl;
	bi=vector1.begin();
	*bi=Point(99,99);
	print(vector1);

	// Change element with const iterator
	cout<<"Change first element with const iterator"<<endl;
	vector<Point>::const_iterator ci;
	ci=vector1.end();
	ci--;
//	*ci=Point(88,88);	// Compiler error
	cout<<*ci<<endl;
}