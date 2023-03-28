// Exponential.cxx
//
// Code file for exponential distributions
//
// Last modification dates:
//
//  1994-2-8 DD Cosmetic changes
//	1999-1-5 DD templated version
//	2000-6-23 DD final version
//
// Copyright (C) Datasim Education BV 1994-2000

#ifndef EXPODIST_CXX
#define EXPODIST_CXX

#include "expodist.hxx"

template <class T> Exponential<T>::Exponential(const T& par) : Gamma<T> (par, 1)
{

}

template <class T> T Exponential<T>::cdf(const T& x) const
{ // We redefine the cdf() here because it is simpler than the
  // inheritance from the gamma distribution

	if (x > T(0.0))
	 return 1.0 - exp(-alpha() * x);

	return T(0.0);

}

template <class T> T Exponential<T>::expected () const
{
	return 1.0 /a;
}

template <class T> T Exponential<T>::variance () const
{

	return 1.0 /(a * a);
}



#endif