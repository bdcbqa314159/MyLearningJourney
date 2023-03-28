// cnsdist.hxx
//
// Header file for abstract base class for continuous probability
// distributions.
// 
// A continuous distribtution is described by a so-called probability density
// function (pdf). This is a positive whose integral on the real line is 1 and
// the probability that a continuous random variable is in an interval [a, b] is 
// given by the integral of the pdf with limits a and b.
// The cumulative density function == cdf(x) is calculated by integrating pdf
// from minus infinity to x, i.e. cdf(x) = Prob(X <= x).
//
// Copyright (C) Datasim Component Technology BV 1994-2000

#ifndef CNSDIST_HXX
#define CNSDIST_HXX

#include "probdist.cxx"
#include <math.h>

template <class Domain, class Range> class ContinuousDistribution: public ProbabilityDistribution<Domain, Range>
{ // Abstract base class for continuous probability distributions

	
private:
		
		
public:
	// Constructors
	ContinuousDistribution(); 
	ContinuousDistribution(const ContinuousDistribution<Domain, Range>& d2);

	virtual ~ContinuousDistribution();

	// Selector member functions
	virtual Range pdf(const Domain& x) const = 0;
	virtual Range cdf(const Domain& x) const = 0;

	// Selectors
	virtual Range expected() const = 0;
	virtual Range variance() const = 0;
	virtual Range std() const { return ::sqrt(variance()); } // inline


};

#endif
