// EOptionExact.hpp
//
// Class that represents exact solutions to European options.
//
// (C) Datasim Component Technology BV 2003
//

#ifndef ExactEuropeanOption_hpp
#define ExactEuropeanOption_hpp

#include "property.cpp"
#include "simplepropertyset.cpp"
#include "vector.cpp"

#include <string>
using namespace std;

class Option
{ // Abstract base class for the options in this book
public:

	virtual double Price() const = 0;

};

class ExactEuropeanOption : public Option
{
private:

	void init();	// Initialise all default values
	void copy(const ExactEuropeanOption& o2);

	// 'Kernel' functions for option calculations
	double CallPrice() const;
	double PutPrice() const;
	double CallDelta() const;
	double PutDelta() const;
	double CallGamma() const;
	double PutGamma() const;
	double CallVega() const;
	double PutVega() const;
	double CallTheta() const;
	double PutTheta() const;
	double CallRho() const;
	double PutRho() const;
	double CallCoc() const;
	double PutCoc() const;
	double CallElasticity(double percentageMovement) const;
	double PutElasticity(double percentageMovement) const;
	double CallStrike() const;	// As a functions of the strike price dc/dK FIRST derivative
	double PutStrike() const;
	double CallSecondStrike() const;	// As a functions of the strike price: SECOND derivative
	double PutSecondStrike() const;

	// Gaussian functions
	double n(double x) const;
	double N(double x) const;


public:	// Public property section
	Property<string, double> r;		// Interest rate
	Property<string, double> sig;	// Volatility
	Property<string, double> K;		// Strike price
	Property<string, double> T;		// Expiry date
	Property<string, double> U;		// Current underlying price (e.g. stock, forward)
	Property<string, double> b;		// Cost of carry

	string otyp;	// Option name (call, put)
	string unam;	// Name of underlying asset

	Property<string, double>* curr;		// Points to one specific property

public:	// Public functions
	ExactEuropeanOption();							// Default call option
	ExactEuropeanOption(const ExactEuropeanOption& option2);	// Copy constructor
	ExactEuropeanOption (const string& optionType);	// Create option type
	ExactEuropeanOption (const string& optionType, const string& underlying);	// Create option type
	virtual ~ExactEuropeanOption();	

	ExactEuropeanOption& operator = (const ExactEuropeanOption& option2);

	// Functions that calculate option price and sensitivities
	double Price() const;
	double Delta() const;
	double Gamma() const;
	double Vega() const;
	double Theta() const;
	double Rho() const;
	double Coc() const;										// Cost of carry
	double Elasticity(double percentageMovement) const;		// Elasticity

	// Other useful 'higher-level' functions

	// The option's defining parameters
	SimplePropertySet<string, double> properties() const;

	// Now give all values and sensitivities in a propertyset
	SimplePropertySet<string, double> propertylist() const;
	Vector<double> graph(const string& sensitivity_type, const string& property,
					const Vector<double> parameter_range);

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

};


#endif