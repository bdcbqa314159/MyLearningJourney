// portfolio.hpp
//
// Classes for option strategies, portfolios and other derivatives.
//
// This code is for demonstration purposes. You need to augment it
// with canonical information in general. 
//
// (C) Datasim Education BV 2004
//
//

#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP


#include "europeanoption2.hpp"
#include "range.cpp"
#include "vector.cpp"

class PortfolioThing
{ // Base class for all derivative products

};

class OptionStrategy: public PortfolioThing
{
public:

		Vector<double, int> payoffGraph(const Range<double>& interval,
											int numberIntervals);		
		virtual double payoff(double StockPrice) const = 0;

										
};	


class Spread: public OptionStrategy
{ // Take a position in two or more options of the same type

private:


protected:

		EuropeanOption* f;
		EuropeanOption* s;



public:
	Spread(EuropeanOption& first, EuropeanOption& second);

};


class BullSpread: public Spread
{ // One long call and one short call

private:

		// Redundant data
		double X1;				// Smaller strike price
		double X2;				// Larger strike price


public:
	BullSpread(EuropeanOption& first, EuropeanOption& second);


	double payoff(double StockPrice) const;


};



#endif