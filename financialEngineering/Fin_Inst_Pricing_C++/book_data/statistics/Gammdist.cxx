// gammdist.cxx
//
// Code file for the gamma distribution.
//
// Last modification dates:
//
// 1994-2-8 DD: Commonality filtered out
// 1994-11-6: DD name changed
// 1999-1-5: DD new and templated functionality 
// 2000-6-23 DD final version 
//
// Copyright (C) Datasim Education BV 1994-2003

#ifndef GAMMA_CXX
#define GAMMA_CXX

#include "gammdist.hxx"
#include "miscfun.hxx"

template <class T> Gamma<T>::Gamma()
{
	T t(1.0);		// Assume this
	a = t;
	r = t;
}

template <class T> Gamma<T>::Gamma(const Gamma<T>& g2)
{

	a = g2.a;
	r = g2.r;
}

template <class T> Gamma<T>::Gamma(const T&  alpha, const T&  rint)
{ // The essential state of a Gamma distribution random element.
  // Both defining parameters must be positive.

	a = alpha;
	r = rint;
}

template <class T> T Gamma<T>::expected() const
{
	   return (r/a);
}

template <class T> T Gamma<T>::variance() const
{
	   return (r/(a*a));
}

template <class T> T Gamma<T>::pdf(const T&  x) const
{
	// Precondition: Check for valid input

	if ( x == T(0.0))
		
		return T(0.0);
      
	return a * pow(a*x, r - 1) * exp(- x)/MISCFUN::gamma(r);
  
}

template <class T> T Gamma<T>::cdf(const T&  x) const
{

	return 0.0;	/// !!! TEMP

  
}

// Accessing the parameters
template <class T> T Gamma<T>::alpha() const
{
	return a;
}

template <class T> T Gamma<T>::rcoeff() const
{
	return r;
}


/* 
template <class T> T Gamma<T>::cdf(const T&  x) const
{ // Meyer p. 195; the cdf of Gamma can be written as a sum of pdfs of
  // the Poisson distribution. Note that this is valid only when the
  // parameter r is a positive integer (which in most cases is usually
  // true).

      T  res = 0.0;
      T  t = a * x;
      Poisson<T, int> pois_dist(t);		// int is 'dummy'

      // Take into account that r needs to be integral; what we
      // do is convert it to an integer and use this value.
      int ir = int(r);
      for (int k = 0; k <= ir-1; k++)
	  res += pois_dist.pdf(k);

      return 1.0 - res;
}


// Other functions
template <class T> T Gamma<T>::probability(const T& a, const T& b) const
{ // Probability of being in interval [a,b]

	return T();
}

*/

#endif