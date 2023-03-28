// expodist.hxx
//
// The class of exponential distribution functions. Applied to the area
// of reliability theory, failure laws and computer networks.
//
// Copyright (C) Datasim Education BV 1994-2000

#ifndef EXPODIST_HXX
#define EXPODIST_HXX

#include "gammdist.cxx"

template <class T> class Exponential : public Gamma<T>
{ // The exponential probability function. There is no need for a state
  // description since it is inherited from the gamma distribution.

public:
	Exponential() {}

	// Constructors 
	Exponential(const T& t);

	// Not all member functions are needed since they are all automatically
	// inherited from Gamma

	// We redefine the cdf() function because of its simplicity. 
	// The pdf is inherited from Gamma
	T cdf(const T& t) const;

	T expected() const;
	T variance() const;

	ContinuousDistribution<T, T>* clone() const { return new Exponential<T> (*this); }

};

#endif
