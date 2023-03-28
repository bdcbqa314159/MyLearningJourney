// tstiter7.cxx
//
// Using more iterators.
//
//	0. Reverse iterators
//	1. Forward iterators. It is possible to save a forward iterator
//	   so that it can be used in multipass algorithms.
//	2. Bidirectional iterators.
//	3. Random access iterators.
//
// (C) Datasim Education 1998

#include "common.hxx"

void print(const vector<double>& l)
{  // Print the contents of a vector. Notice the presence of a constant iterator.
	
	cout << endl << "Size of vector is " << l.size() << "\n[";

	// We must use a const iterator here, otherwise we get a compiler error.
	vector<double>::const_iterator i;

	for (i = l.begin(); i != l.end(); ++i)
	{
			cout << *i << ",";

	}

	cout << "]\n";
}

void random_example()
{ // Example of using a random access iterator

	vector<double> vec(5, 2.0);

	vector<double>::iterator i = vec.end();

	i -= 3; (*i) = 3.1415;

	i = vec.begin(); (*i) = 1.0;

	i += 3;	(*i) = 1./3;

	i = vec.end();//  (*i) = 5.0; run-time error
	i -= 1; (*i) = 5.0;

	print(vec);

}

int main()
{

	int myarr[] = {1, 2, 3, 4, 5, 6, 7, 99};

// Reverse iterator
	vector<int> myvec(myarr, myarr + 5);
	vector<int>::reverse_iterator ri;

	for (ri = myvec.rbegin(); ri != myvec.rend(); ri++)
	{ // Prints the elements starting from the end

		cout << (*ri) << endl;
	}

	/* Does not work because reverse iterator does not have begin(), end()
	for (ri = myvec.begin(); ri != myvec.end(); ri++)
	{ // Prints the elements starting from the start

		cout << (*ri) << endl;
	}
	*/


	random_example();

	return 0;
}
