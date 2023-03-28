// unifdist.hxx
//
// This class represents continuous random variables which can assume
// all values in a certain interval. The density function of such a
// distribution is constant over the interval of definition.
//
// This is a one-dimensional uniform distribution function. Higher 
// dimensional versions are possible.
//
//
// Copyright (C) Datasim Education BV 1994-2004

#ifndef Uniform_HXX
#define Uniform_HXX

#include "cnsdist.cxx"

template <class T> class Uniform : public ContinuousDistribution<T, T>
{ // The Uniform probability function (uniform distribution in one
  // dimension).

private:

	T a;	// Lower end of interval
	T b;	// Upper 

public:
	// Constructors
	Uniform();								// On unit interval [0,1]
	Uniform(const T& left, const T& right); // On interval [left, right]

	// Selector member functions
	T expected() const;
	T variance() const;

	T pdf(const T& x) const;
	T cdf(const T& x) const;

	// Calculating probabilities
	T probability (const T& upper, const T& lower) const;

	ContinuousDistribution<T, T>* clone() const { return new Uniform<T> (*this); }

};

#endif
