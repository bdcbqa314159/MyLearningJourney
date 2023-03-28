// pascal.hxx
//
// The Pascal distribution. Used in asking questions about experiments
// which are continued until a prticular event occurred r times.
// This is a generalisation of the geometric distribution.
//
// Copyright (C) Datasim Education BV 1994-2000

#include "discdist.hxx"

template <class T, class I> class Pascal: public DiscreteDistribution<T, I>
{ // The Pascal Distribution

      T p;		// Probability that an event occurs
      I r;		// Number of defects

// Whereas the geometric distribution deals with the occurrence or
// non-occurrence of some events, the Pascal distribution deals with the
// question of how many times an event occurs.

public:
      // Constructor
      Pascal(const T& prob, const I& Nitems);

      // Selectors
      T pdf(const I& k) const;
      friend T expected(const Pascal<T, I>& p);
      friend T variance(const Pascal<T, I>& p);

};
