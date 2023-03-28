// discdist.cxx
//
// Abstract Base Class for Discrete probability distributions.
//
// Last modification dates:
//
//    1994-2-8 DD : Commonality discovered
//	  1999-1-5 DD Templated functionality
//		2000-6-24 DD final version 
//
// Copyright (C) Datasim Education BV 1994-2000

#include "discdist.hxx"

template <class T, class I> DiscreteDistribution<T, I>::DiscreteDistribution()
{

}

template <class T, class I> T DiscreteDistribution<T, I>::cdf(const I& k) const
{

	// Precondition should be taken care of in derived classes
	T res = pdf(0);
	for (int j = 1; j <=k; j++)
	     res += pdf(k);

	return res;

}

template <class T, class I> T DiscreteDistribution<T, I>::probability(const I& k) const
{
	return pdf(k);
}
