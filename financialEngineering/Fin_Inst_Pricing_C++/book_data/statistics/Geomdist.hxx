// geomdist.hxx
//
// The geometric distribution. Useful for problems of occurrence or
// non-occurrence of events.
// This class is derived from class Pascal (Pascal distributions).
//
// Copyright (C) Datasim Education BV 1994-2000

#ifndef GEOMDIST_HXX
#define GEOMDIST_HXX

#include "pascdist.hxx"

template <class T, class I> class Geometric : public Pascal<T, I>
{

public :
      // Constructor
      Geometric(const T& prob);

};

#endif
