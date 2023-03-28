// poisdist.cxx
//
// The Poisson distrubution.
//
// Last modification dates:
//
//	1994 kick-off
//	1999-1-5 DD templated version
//	2000-6-24 DD final version 
//	2003-9-14 DD expected() and variance() are member functions
//
// Copyright (C) Datasim Education BV 1994-2003

#ifndef ProbabilityDistribution_CXX
#define ProbabilityDistribution_CXX

#include "poisdist.hxx"
#include "miscfun.hxx"
#include <math.h>

template <class T, class I> Poisson<T, I>::Poisson(const T& t)
{
   lam = t;
}

template <class T, class I> T Poisson<T, I>::expected() const
{

	return lam;
}

template <class T, class I> T Poisson<T, I>::variance() const
{
      return lam;
}

template <class T, class I> T Poisson<T, I>::pdf(const I& k) const
{

	return (::exp (-lam) * pow(lam,k))/MISCFUN::fact(k);
}


#endif