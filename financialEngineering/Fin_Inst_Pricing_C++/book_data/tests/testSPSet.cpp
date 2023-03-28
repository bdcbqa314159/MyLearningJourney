// testSpSet.cpp
//
// Testing PSet
//

#include "simplepropertyset.cpp"


int main()
{

	SimplePropertySet<int, double> pset;
	
	Property<int, double> element;

	pset.add(element);

	return 0;
}
