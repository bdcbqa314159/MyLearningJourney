// Binomial.hxx
//
// The binomial probability distribution. Models occurrence or 
// non-ocurrence of events.
//
// Copyright (C) Datasim Education BV 1994-2000

#ifndef Binomial_HXX
#define Binomial_HXX

#include "discdist.hxx"

template <class T, class I> class Binomial : public DiscreteDistribution<T, I>
{

private:

      T p;				// Probability of success on each trial
      I N;				// The number of trials(N repetitions of an experiment)

public :
      // Constuctor
      Binomial(const T& prob, const I& ntrial);

      // Selector
      T pdf(int k) const; // Probability that an event occurs k times
      T expected() const;
      T variance() const;
};

#endif
