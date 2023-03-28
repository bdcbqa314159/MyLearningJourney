// FunctionObjects.cxx
//
// Example program for STL function objects.
// The functions shown are:
// greater<T>
// count_if
// sort with custom compare funtion
// bind2nd function adapter
//
// (C) Datasim Education BV  1998

#include "common.hxx"

const int COMPARE=10000;

void print(const vector<int>& v)
{ // Print the vector

	// Create vector iterator
	vector<int>::const_iterator i;
	
	// Print every integer in the vector
	for (i=v.begin(); i!=v.end(); i++) cout<<*i<<",";
	cout<<endl<<endl;
}

bool bigger(int i)
{ // My own bigger function uses STL greater function object

	greater<int> g;
	return g(i, COMPARE);
}

bool mycompare(int x, int y)
{ // My strange compare function for sorting.
  // First all odd numbers from low to high, then all even numbers from low to high

	if (x%2==y%2) return (x<y);

	if (x%2==1) return true;
	
	return false;
}
void main()
{
	// Create vectors and fill with random numbers
	vector<int> v1;
	int i;
	for (i=0; i<10; i++) v1.push_back(rand());

	cout<<"Random list"<<endl;
	print(v1);

	// Count numbers greater than 1000 using my bigger function
	i=count_if(v1.begin(), v1.end(), bigger);
	cout<<"Using my bigger function"<<endl;
	cout<<"There are "<<i<<" elements greater than "<<COMPARE<<endl<<endl;

	// Count numbers greater than 1000 using greater function object and bind2nd function adapter
	// With the bind2nd adapter we can use a binary function object where an unary function object is expeced
	i=count_if(v1.begin(), v1.end(), bind2nd(greater<int>(), COMPARE));
	cout<<"Using bind2nd function adapter"<<endl;
	cout<<"There are "<<i<<" elements greater than "<<COMPARE<<endl<<endl;

	// Sort list using my compare function
	cout<<"Sort the list using my compare function"<<endl;
	cout<<"First all odd numbers from low to high, then all even numbers from low to high"<<endl;
	sort(v1.begin(), v1.end(), mycompare);
	print(v1);

	// Transform the list
	vector<int> v2(v1.size());
	cout<<endl<<"Transform the list using the negate function as argument"<<endl;
	transform(v1.begin(), v1.end(), v2.begin(), negate<int>());
	print(v2);
}