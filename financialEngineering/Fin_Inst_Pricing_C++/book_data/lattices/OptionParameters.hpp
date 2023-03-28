// OptionParameters.hpp
//
// Simple structure to hold attributes for options
//
// (C) Datasim Education BV 2004

#ifndef OptionParameters_hpp
#define OptionParameters_hpp

class OptionParameters
{
public:

	double r;		// Interest rate
	double vol;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double U;		// Current underlying price (e.g. stock, forward)
	double b;		// Cost of carry


};

#endif
