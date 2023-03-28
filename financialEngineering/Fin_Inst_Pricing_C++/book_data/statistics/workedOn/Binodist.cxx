// Binomial.cxx
//
// The binomial probability distribution.
//
// Last modification dates:
//
// 1994-2-7 DD Member functions edited
//	1999-1-5 DD templated functionality
//	2000-6-24 DD final version 
//
// Copyright (C) Datasim Education BV 1994-1999

#include "binodist.hxx"

template <class T, class I> Binomial<T, I>::Binomial(const T& prob, const I& ntrial)
{
       p = prob;
       N = ntrial;
}

template <class T, class I> T Binomial<T, I>::pdf(int k) const
{
	 double tmp = MISCFUN::combination(N,k);   // n!/(k!(n-k)!)
	 return (tmp * pow(p,k) * pow(1.0 - p, N - k));
}

template <class T, class I> T expected(const Binomial<T, I>& b)
{ // The expected value of the binomial distribution.

	return double (b.N) * b.p;
}

template <class T, class I> variance(const Binomial<T, I>& b)
{
	return b.N * b.p * ( 1.0 - b.p); 	// TEMP
}


