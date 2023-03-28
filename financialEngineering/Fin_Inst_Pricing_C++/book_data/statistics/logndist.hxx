// logndist.hxx
// 
// The lognormal probability distribution. A random variable X 
// is N(mu, sigma^2). Define the random variable Y by
//
//			Y = exp(X)
//
// Then Y is lognormally distributed.
// 
// Copyright (C) Datasim Education BV 1994-2000

#ifndef LogNormal_HXX
#define LogNormal_HXX

#include "cnsdist.hxx"

template <class T> class LogNormal : public ContinuousDistribution<T>
{ // The LogNormal probability function 

private:
	
		T mu;	// Mean value
		T sig;	// Variation

public:
	// Constructors
	LogNormal(const T& mean, const T& sigma); 

	// Selector member functions
	friend T expected(const LogNormal<T>& u);
	friend T variance(const LogNormal<T>& u);
	T pdf(const T& x) const;
	T cdf(const T& x) const;

};

#endif
