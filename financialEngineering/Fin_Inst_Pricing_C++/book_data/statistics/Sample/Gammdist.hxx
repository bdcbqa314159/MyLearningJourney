// gammdist.hxx
//
// The Gamma probability distribution. Note that the functions cdf() and 
// probability() are inherited from ContinuousDistribution.
//
// Copyright (C) Datasim Education BV 1994-2000

#ifndef GAMMA_HXX
#define GAMMA_HXX

#include "cnsdist.cxx"

template <class T> class Gamma : public ContinuousDistribution<T, T>
{
protected:

	T  r;
	T  a;

public :
	// Constructors
	Gamma();								// r == 1, a == 1
	Gamma(const Gamma<T>& distrib2);		// Copy constructor
	Gamma(const T&  alpha, const T&  rr);	// Two parameters

	// Accessing the parameters
	T alpha() const;
	T rcoeff() const;

	T  pdf(const T&  x) const;				// Probability density
	T cdf(const T& x) const;

	T expected() const;	// Expected value
	T variance() const;	// Variance

	
	// Other functions
};

#endif
