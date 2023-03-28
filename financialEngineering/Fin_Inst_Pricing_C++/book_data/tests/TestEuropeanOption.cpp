// TestEuropeanOption.cpp
//
// Test program for the  solutions of European options
//
// (C) Datasim Component Technology BV 20003
//

#include "EuropeanOption2.hpp"
#include <iostream>

int main()
{ // All options are European

	// Call option on a stock
	EuropeanOption callOption;
	cout << "Call option on a stock: " << callOption.Price() << endl;
	
	// Put option on a stock index
	EuropeanOption indexOption;
	indexOption.otyp = "P";
	indexOption.U = 100.0;
	indexOption.K = 95.0;
	indexOption.T = 0.5;
	indexOption.r = 0.10;
	indexOption.sig = 0.20;

	double q = 0.05;		// Dividend yield
	indexOption.b = indexOption.r - q;

	cout << "Put option on an index: " << indexOption.Price() << endl;

	// Call and put options on a future
	EuropeanOption futureOption;
	futureOption.otyp = "P";
	futureOption.U = 19.0;
	futureOption.K = 19.0;
	futureOption.T = 0.75;
	futureOption.r = 0.10;
	futureOption.sig = 0.28;

	futureOption.b = 0.0;

	cout << "Put option on a future: " << futureOption.Price() << endl;

	// Now change over to a call on the option
	futureOption.toggle();
	cout << "Call option on a future: " << futureOption.Price() << endl;

	return 0;
}
