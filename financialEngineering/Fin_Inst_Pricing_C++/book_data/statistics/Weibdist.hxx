// Weibdist.hxx
//
// The Weibull probability distribution. This is of use in testing the
// reliability of systems (e.g. semiconductor devices and software
// engineering).
//
// Copyright (C) Datasim Education BV 1994-2000

#ifndef Weibull_HXX
#define Weibull_HXX

#include "cnsdist.hxx"

template <class T> class Weibull: public ContinuousDistribution<T>
{ // The Weibull distribution.

private:
	// The parameters alpha and beta must be positive
	T a;
	T b;

public:
	// Constructor
	Weibull(const T& alpha, const T& beta);

	// Selector functions
	friend T expected(const Weibull<T>& w);
	friend T variance(const Weibull<T>& w);
	T pdf(const T& t) const;
	T cdf(const T& t) const;

	// Special functions pertaining to Weibull
	T reliability(const T& t) const;
	T failure_rate(const T& t) const;	// The failure rate (hazard function) Z(t)



};

#endif
