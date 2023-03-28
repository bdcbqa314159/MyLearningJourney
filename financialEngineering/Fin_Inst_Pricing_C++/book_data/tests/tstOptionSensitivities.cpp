// tstOptionSensitivities.cpp
//
// Test program for the sennsitivities European options
//
// (C) Datasim Component Technology BV 20003
//

#include "EuropeanOption2.hpp"
#include <iostream>

int main()
{ // All options are European

	EuropeanOption futureOption("C", "Future Option");
	futureOption.U(105.0);
	futureOption.K(100.0);
	futureOption.T(0.5);
	futureOption.r(0.10);
	futureOption.sig(0.36);
	futureOption.b( 0.0);

	// Calculate all interesting values
	SimplePropertySet<string,double> r = futureOption.propertylist();

	// Iterate over the result and print the values
	SimplePropertySet<string,double>::const_iterator it;

	cout << "\nDump the parameters, call prices ... \n";

	for (it=r.Begin(); it!=r.End(); it++)
	{ 

		cout << (*it).name() << ", " << (*it)() << endl;
	}

	// We now examine the values when the option is a put
	futureOption.toggle();

	// !! Recalculate the prices again
	r = futureOption.propertylist();

	cout << "\nPut prices ...\n";
	for (it=r.Begin(); it!=r.End(); it++)
	{ 

		cout << (*it).name() << ", " << (*it)() << endl;
	}

	return 0;
}
