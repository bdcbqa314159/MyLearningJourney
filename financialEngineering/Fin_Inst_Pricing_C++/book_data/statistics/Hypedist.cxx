// HyperGeometric<T, I>.cxx
//
// The hypergeometric distribution.
//
// Last modification dates:
//
//	1994-2-8 DD Member functions changed
//	1999-1-5 DD templated functionality
//
// Copyright (C) Datasim Education BV 1994-1999

#include "Hypedist.hxx"

template <class T,  class I> HyperGeometric<T, I>::HyperGeometric(const I& nsamp,const I& ndef, const I& noreplace)
{ // Constructor; no input checking is carried out

      N = nsamp;
      r = ndef;
      n = noreplace;

	  p = T(r/N);
	  q = T(1.0) - p;
}

template <class T,  class I> T expected(const HyperGeometric<T, I>& h)
{ // (Meyer page 176)

	return double(h.n) * p;
}

template <class T,  class I> T variance(const HyperGeometric<T, I>& h)
{
     
	 double res = double(h.n) * h.p * h.q * T(h.N - h.n);
	 res = res /T(h.N -1);

	 return res;

}

template <class T,  class I> T HyperGeometric<T, I>::pdf(const I& k) const
{ // Meyer page 175

	double t2 = MISCFUN::combination(r, k);
	double t3 = MISCFUN::combination(N - r, n - k);
	double t4 = MISCFUN::combination(N, n);

	return (t2 * t3) / t4;
}


// Choosing a new batch on n items from the lot
template <class T, class I>	void HyperGeometric<T, I>::new_batch(const I& m)
{
	n = m;

}
