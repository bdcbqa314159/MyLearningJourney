// tstArrayMechanims.cpp
//
// Examples to show how sequence containers (vector) work.
//
// (C) Datasim Education BV 2003
//

#include "SimplePropertySet.cpp"
#include <string>
#include <iostream>
#include "arraymechanisms.cpp" // Conversion stuff here
using namespace std;

////////////////////////// Print functions ////////////////////////////////////////////////
template <class V, class I> void print(const SimplePropertySet<V, I>& pset)
{  // A generic print function for property sets
	
	cout << endl << "Size of Property Set " << pset.Count() << "\n\n";

	// We must use a const iterator here, otherwise we get a compiler error.
	SimplePropertySet<V,I>::const_iterator i;
	for (i = pset.Begin(); i != pset.End(); ++i)
	{
			cout << (*i).name() << ": " << (*i)() << endl;

	}

	cout << "\n";
}




int main()
{


	// The first 'sanity check' example
	size_t n = 10;
	double val = 1.0;
	Vector<double, int> myVector(10, 1, val);	// Create n copies of val

	print(myVector);

	SimplePropertySet<string, double> ans = allAverages(myVector);

	print(ans);

	n = 10;
	Vector<double, int> myVector2(4);	// Length 4, start index == 1
	myVector2[1] = 1.0; 
	myVector2[2] = -10.0; 
	myVector2[3] = 9.0; 
	myVector2[4] = 2.0; 


	ans = allNorms(myVector2);
	print(ans);

	myVector[3] = 433.0;

	Vector<double, int> myVectorA = reverse(myVector2);
	//print(myVectorA);

	Vector<double, int> myVector3 (10, 0); // Size 10, start index 0
	myVector3[myVector3.MinIndex()] = 999.98;
//	myVector2 = reverse(myVector3);
	print(myVector2);

	// Medians
	cout << "Median " << median(myVector2) << endl;

	Vector<double, int> myVector5(3, 1);	// Length 3, start index == 1
	myVector5[1] = 1.0; 
	myVector5[2] = -10.0; 
	myVector5[3] = 9.0; 

	cout << "Median " << median(myVector5) << endl;


	Vector<double, int> myVector6(3, 0);	// Length 3, start index == 0
	myVector6[0] = 1.0; 
	myVector6[1] = 2343.9;
	myVector6[2] = 9.0; 

	cout << "Median " << median(myVector5) << endl;

	return 0;
}
