// erlgdist.hxx
//
// The Erlang probability distribution function. This was invented by the Dane 
// A.K. Erlang and was used to model congestion in telephone systems. The idea
// behind the distribution uses the insight that arguments used for exponential 
// distributions can also be applied to certain non-exponential distributions.
// In particular, we consider k service stages where each stage is modelled as
// an exponential p.d.f. An Erlang random variable is the sum of k mutually 
// independent, exponentially distributed random variables.
//
// In general we are interested in the time needed to observe k phenomena.
//
// Copyright (C) Datasim Education BV 1994-2000

#ifndef Erlang_HXX
#define Erlang_HXX

#include "cnsdist.hxx"

template <class T, class I> class Erlang : public ContinuousDistribution<T>
{ // The Erlang probability function 

private:

		T mu;		// Exponential service rate
		I k;		// Shape parameter, corresponds to the number of stages
					// in the Erlang service

		// The redundant value mu * k is called the scale parameter in some approaches
		T combi;

public:
	// Constructors
	Erlang(const T& serive_rate, const T& number_of_stages); 

	// Selector member functions
	friend T expected(const Erlang<T,I>& u);
	friend T variance(const Erlang<T,I>& u);
	T pdf(const T& x) const;
	T cdf(const T& x) const;

};

#endif
