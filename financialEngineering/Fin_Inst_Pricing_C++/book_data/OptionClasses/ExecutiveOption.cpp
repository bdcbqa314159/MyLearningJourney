// ExecutiveOption.cpp
//
// Class that represents exact solutions to European options.
//
//	Last modification dates:
//	2002-12-7 DanielDuffy first code
//	2002-12-8 DD tested call and put options for a range of Euro types
//	Some new functions for interoperability
//	2002-12-10 DD almost finished with the code for the European exact option formulae.
//	2002-12-28 DD Executive options
//	2003-114 DD class now derived from an Option base class
//
// (C) Datasim Component Technology BV 2003
//

#include "ExecutiveOption.hpp"
#include <math.h>
#include <iostream>


ExecutiveOption::ExecutiveOption() 
{ // Default call option

	jrate = Property<string, double> ("Jump rate", 0.15);
	base = Property<string, ExactEuropeanOption> ("European stock with continuous dividend", ExactEuropeanOption() );
	
}

ExecutiveOption::ExecutiveOption(const ExecutiveOption& o2)
{ // Copy constructor

	jrate = o2.jrate;
	base = o2.base;

}

ExecutiveOption::ExecutiveOption (double jump_rate, const ExactEuropeanOption& base_option)
{
	jrate = Property<string, double> ("Jump rate", jump_rate);
	base = Property<string, ExactEuropeanOption> ("European stock with continuous dividend", base_option);
	
}

ExecutiveOption::~ExecutiveOption()
{

}


ExecutiveOption& ExecutiveOption::operator = (const ExecutiveOption& o2)
{

	if (this == &o2) return *this;

	jrate = o2.jrate;
	base = o2.base;

	return *this;
}

// Functions that calculate option price and sensitivities
double ExecutiveOption::Price() const 
{

	cout << "An executive option\n";
	double expT = base().T();

	return exp(-jrate() * expT) * (base().Price());

}

