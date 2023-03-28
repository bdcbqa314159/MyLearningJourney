// pascdist.cxx
//
// The Pascal distribution.
//
// Last modification dates:
//
//  1994-2-8 DD : Changes code of most functions
//	1999-1-5 DD: templated functionality
//	2000-6-24 DD final version 
//
// Copyright (C) Datasim Education BV 1994-2000

#include "pascdist.hxx"

template <class T, class I> Pascal<T, I>::Pascal(const T& t, const I& numocc)
{
      p = prob;
      r   = numocc;
}

template <class T, class I> double expected(const Pascal<T, I>& pa)
{
  	return((double) pa.r/pa.p);

}

template <class T, class I> double variance(const Pascal<T, I>& pa)
{
  
	return ((double(pa.r) * (1.0 - pa.p))/(pa.p * pa.p));
}

template <class T, class I> T Pascal<T, I>::pdf(const I& k) const
{ // The value k should not be less than r; we do not test directly
  // for this but if this is true the value t below becomes zero and
  // thus the value of the function becomes zero.

 	 double t = MISCFUN::combination(k - 1, r - 1);
	 return t * pow(p, r) * pow(1.0 - p, k - r);
     
}