// tstintersect.cpp

//

#include <set>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

template <class T> void print(const set<T>& l, const string& name)
{  // Print the contents of a set. Notice the presence of a constant iterator.
	
	cout << endl << name << ", size of set is " << l.size() << "\n[ ";

	set<T>::const_iterator i;

	for (i = l.begin(); i != l.end(); ++i)
	{
			cout << *i << " ";

	}

	cout << "]\n";
}

int main()
{
	set<int> first;				// Default constructor

	// Only unique (new elements) added
	first.insert(1);
	first.insert(2);
	first.insert(3);
	print (first, "First set");

	set<int> second (first);

	second.erase(3);
	second.insert(999);

	print (second, "Second set");

	// Intersecton of two sets
	set<int> myintersect;
	set<int>::iterator	i = myintersect.begin();
	insert_iterator<set<int> > insertiter2(myintersect, i);

	set_intersection(first.begin(), first.end(), second.begin(), second.end(), insertiter2);

	print(myintersect, "Intersection");


	return 0;
}
