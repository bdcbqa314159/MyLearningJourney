// Poisson.hxx
//
// The Poisson distribution. This is used for the simulation of arrivals
// in queueing systems.
//
// Copyright (C) Datasim BV Education 1994-1999


#ifndef Poisson_HXX
#define Poisson_HXX

#include "discdist.cxx"

template <class T, class I> class Poisson: public DiscreteDistribution<T, I>
{

private:

	T lam;

public:
	// Constructors
	Poisson(const T& lambda);

	// Selectors
	T expected() const;						// Expectation
	T variance() const;						// Variance
	T pdf(const I& k) const;				// Probability density function
};

#endif
