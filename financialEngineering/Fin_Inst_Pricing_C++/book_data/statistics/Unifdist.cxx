// unifdist.cxx
//
// Last modification dates:
//
// 1994-2-7: DD Commonality relegated to ContinuousDistribution
// 1999-1-5: DD templated functionality
// 2000-6-23: DD final version
// 2003-8-27 DD review
//
// Copyright (C) Datasim Education BV 1994-2004


#ifndef Uniform_CXX
#define Uniform_CXX

#include "unifdist.hxx"

template <class T> Uniform<T>:: Uniform()
{
      a = 0.0;
      b  = 1.0;
}

template <class T> Uniform<T>::Uniform(const T& aa, const T& bb)
{
      a = aa;
      b = bb;

}

template <class T> T Uniform<T>::expected() const
{
      return((a + b) * 0.5);
}

template <class T> T Uniform<T>::variance() const
{
      double t = a - b;
      return((t*t)/12.0);
}

template <class T> T Uniform<T>::pdf(const T& x) const
{ // The density function (is independent of the position in the
  // interval)

	if (x < a || x > b)
		return 0.0;

	return (1.0/(b - a));
}

template <class T> T Uniform<T>::cdf(const T& x) const
{ // The cdf function

	if (x < a)
		return 0.0;

	if (x >= b)
		return 1.0;

	return (x - a) / (b - a);
}


// Calculating probabilities
template <class T> T Uniform<T>::probability (const T& xUpp, const T& xLow) const
{

	return (xUpp - xLow) / (b - a);
}
#endif