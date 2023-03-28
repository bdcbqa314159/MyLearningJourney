// tesSet1.cpp
//
// Testing Set class.
//
// (C) Datasim Education BV 2004
//

#include "Set.cpp"

template <class T> void print(const Set<T>& l, const string& name)
{  // Print the contents of a Set. Notice the presence of a constant iterator.
	
	cout << endl << name << ", size of set is " << l.Size() << "\n[ ";

	set<T>::const_iterator i;

	for (i = l.Begin(); i != l.End(); ++i)
	{
			cout << *i << " ";

	}

	cout << "]\n";
}

int main()
{
	Set<int> first;				// Default constructor

	// Only unique (new elements) added
	first.Insert(1);
	first.Iinsert(2);
	first.Insert(3);
	print (first, "First set");


	return 0;
}
