// HyperGeometric.hxx
//
// Hypergeometric distribution.
// Distribution in which samples are not replaced.
// When the number of samples (represented by the variable N in the
// private part of the class) is large, this distribution may be
// approximated by the binomial distribution.
//
// The typical scenario is as follows: consider a lot of N items of which
// r are defective. Choose n items from the lot at random (without replacement).
// What is the probability that k defective items are found.
// 
// Copyright (C) Datasim Education BV 1994-2000

#ifndef HyperGeometric_HXX
#define HyperGeometric_HXX

#include "discdist.cxx"

template <class T, class I> class HyperGeometric: public DiscreteDistribution<T, I>
{

      I N;             // The lot of items from which to choose
      I r;             // The number of defective items in the lot
      I n;             // The number chosen without replacement

	  // Redundant probabilities
	  T p, q;

public:
	// Constructor (creating instances of HyperGeometric)
	HyperGeometric(const I& Nlot, const I& ndef, const I& noreplace);

	// Choosing a new batch on n items from the lot
	void new_batch(const I& new_batch);

	// Member functions
	T pdf(const I& k) const;			// Probability function
	friend T expected(const HyperGeometric<T, I>& h);	// Expected value
	friend T variance(const HyperGeometric<T, I>& h);	// Variance
};

#endif
