// logndistdist.cxx
//
// Last modification dates:
//
// 1999-1-5: DD Kick-off and templated functionality
// 2000-6-24 DD final version (formulas from Bhansali)
//
// Copyright (C) Datasim Education BV 1994-1999

#include "logndist.hxx"


template <class T> LogNormal<T>::LogNormal(const T& mean, const T& variation)
{
	mu = mean;
	sigma = variation;
}


template <class T> T expected(const LogNormal<T>& u)
{
	return MISCFUN::exp(mu + (sigma*sigma)* 0.5);
      
}

template <class T> variance(const LogNormal<T>& u)
{

	// Can be optimised
	T r1 = MISCFUN::exp(2.0 * mu + sigma*sigma);
	T r2 = MISCFUN::exp(sigma*sigma) - T(1.0);

	return r1 * r2;
      
}


template <class T> T LogNormal<T>::pdf(const T& x) const
{ // The density function 


	T r1 = (log(x) - mu)/(sigma*sigma);
	r1 *= r1;

	r1 = MISCFUN::exp(-0.5 * r1);


	T r2 = sqrt(6.28) * sigma * x;

	return r1 * r2;

}

/*
template <class T> T LogNormal<T>::cdf(const T& x) const
{ 


	// later as an erf function
}

*/