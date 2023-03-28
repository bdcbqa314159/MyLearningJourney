// ExecutiveOption.hpp
//
// Class that represents executive options. These are similar
// to standard stock options with continuous yield. There is
// an extra parameter called teh jump rate 'lambda' per year.
//
// (C) Datasim Component Technology BV 2003
//

#ifndef ExecutiveOption_hpp
#define ExecutiveOption_hpp

#include "eoptionexact.hpp"


class ExecutiveOption : public Option
{
private:

	// 'Kernel' functions for option calculations
	double CallPrice() const;
	double PutPrice() const;
	

public:	// Properties
	Property<string, double> jrate;				// Jump rate
	Property<string, ExactEuropeanOption> base;		// Object inheritance

public:	// Public functions
	ExecutiveOption();							// Default call option
	ExecutiveOption(const ExecutiveOption& option2);	// Copy constructor
	ExecutiveOption (double jump_rate, const ExactEuropeanOption& base_option);
	virtual ~ExecutiveOption();	

	ExecutiveOption& operator = (const ExecutiveOption& option2);

	// Functions that calculate option price and sensitivities
	double Price() const;

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

};


#endif