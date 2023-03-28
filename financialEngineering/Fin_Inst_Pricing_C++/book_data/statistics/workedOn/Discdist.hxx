// discdist.hxx
//
// Abstract Base Class for discrete probability distributions. This has two underlying 
// types:
//
//	T: the calculated values
//	I: the values in the random variables
//
// Copyright (C) Datasim Education BV 1994-2000

#ifndef DISCDIST_HXX
#define DISCDIST_HXX

#include "probdist.cxx"

template <class T, class I> class DiscreteDistribution : public ProbabilityDistribution<I, T>
{

private:

public :
      DiscreteDistribution();
      virtual T pdf(const I& k) const = 0;
      virtual T cdf(const I& k) const;
		
	  virtual T expected() const = 0;					// Expectation
	  virtual T variance() const = 0;					// Variance

	  T probability (const I& k) const;					// Probabily that random variable has value k

};

#endif
