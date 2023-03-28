// tstlist1.cxx
//
// Simplest test case for a list (see Musser page 141-143)
//
// (C) Datasim Education BV 1998

#include "common.hxx"

list<char> makelist(char* s)
{ // Creates STL list with characters from a null terminated string

	list<char> result;	// Create empty list

	// Add every character to the list
	while (*s != '\0')
	{
		result.push_back(*s++);
	}

	return result;
}

void print(const list<char>& l)
{ // Print the list

	cout << endl << "Size of list is: " << l.size() << endl;

	// Create list iterator
	list<char>::iterator i;
	
	// Print every character in the list
	for (i = l.begin(); i != l.end(); ++i)
	{
			cout << *i;
	}

	cout << endl;
}

int main()
{
	// Make two lists
	list<char> list1 = makelist("Boris O'Toole"), list2;
	print(list1);

	
	// Adding elements list 1 to list 2. List 2 same as list 1
	list<char>::iterator i;
	for (i = list1.begin();	i != list1.end(); ++i)
	{
			list2.push_back(*i);
	}
	print(list2);


	// Set all character of list 2 to 'O'
	list2 = list<char> (list2.size(), 'O');	
	print(list2);


	// Push elements of list 1 in front of list 2. List 2 is reversed version of list 1
	list2 = list<char>();				// Clean slate	
	for (i = list1.begin(); i != list1.end(); ++i)
	{
			list2.push_front(*i);
	}
	print(list2);


	// Reverse list 1 with the STL reverse algorithm
	reverse(list1.begin(), list1.end());
	print(list1);

	return 0;
}