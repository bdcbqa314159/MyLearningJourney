// tstExotic.cpp
//
// Test program for the exact solutions of EXOTIC European options
//
// (C) Datasim Component Technology BV 20003
//

#include "ExecutiveOption.hpp"
#include <iostream>

int main()
{ // All options are European

	// 1. Executive options
	
	// Put option on a stock 
	ExactEuropeanOption stockOption("C", "Common Stock Option");
	stockOption.U(60.0);
	stockOption.K(64.0);
	stockOption.T(2.0);		// 2 years
	stockOption.r(0.07);
	stockOption.sig(0.38);

	double q = 0.03;		// Dividend yield
	stockOption.b( stockOption.r() - q );

	cout << "Call Option on Stock: " << stockOption.Price() << endl;

	// Now define an executive option based on the stock option. We clone 
	// the base stock option (copy all properties) and then delegate to it as
	// needed.
	ExecutiveOption eo (0.15, stockOption);

	cout << "Executive Call Option on Stock: " << eo.Price() << endl;


	return 0;
}
