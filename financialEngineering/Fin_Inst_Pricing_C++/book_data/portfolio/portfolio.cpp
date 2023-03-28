// portfolio.cpp
//
// Classes for option strategies, portfolios and other derivatives.
//
// This code is for demonstration purposes. You need to augment it
// with canonical information in general. 
//
// (C) Datasim Education BV 2004
//
//


#include "portfolio.hpp"


Vector<double, int> OptionStrategy::payoffGraph(const Range<double>& interval,
											int numberIntervals)
{	

	// This is an application of the Template Method pattern because the 
	// the graph is calculated at each Stock value by calling the payoff()
	// function in the derived classes (the so-called variant part of the
	// algorithm.)
	// The invariant part of the algorithm is the looping in the interval.


	// The vector of stock prices
	Vector<double, int> SArr = interval.mesh(numberIntervals);

	// The vector containing payoff for each stock price
	Vector<double, int> result (SArr.Size(), SArr.MinIndex());

	// Now calculate the payoff array
	for (int j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{

		result[j] = payoff(SArr[j]);
	}
	
	return result;
}

		

Spread::Spread(EuropeanOption& first, EuropeanOption& second)
{

		f = &first;
		s = &second;
}




BullSpread::BullSpread(EuropeanOption& first, EuropeanOption& second) 
							: Spread(first,second)
{

	X1 = f ->K;
	X2 = s ->K;
}



double BullSpread::payoff(double S) const
{ // Based on Hull's book


		if (S >= X2)
			return X2 - X1;
		if (S <= X1)
			return 0;

		// In the interval [X1, X2]
		return S - X1;
}

/*
double BearSpread::payoff(double S) const
{ // Based on Hull's book


		if (S >= X2)
			return -(X2 - X1);
		if (S <= X1)
			return 0;

		// In the interval [X1, X2]
		return -(S - X1);
}


double ButterflySpread::payoff(double S) const
{ // Based on Hull's book


		if (S < X1)
			return 0.0;

		if (S > X3)
			return 0.0;

		if (X1 < S & S < X2)
			return S - X1;

		if (X2 < S & S < X3)
			return X3 - S;

}

 */