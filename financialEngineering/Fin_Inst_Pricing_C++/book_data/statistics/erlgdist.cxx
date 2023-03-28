// erlgdist.cxx
//
// Erlang probability distribution.
//
// Last modification dates:
//
// 1999-1-5: DD Kick-off and templated functionality
// 2000-6-23 DD final version
//
// Copyright (C) Datasim Education BV 1994-1999

#include "erlgdist.hxx"


template <class T, class I> Erlang<T,I>::Erlang(const T& service_rate, const T& number_of_stages)
{
	mu = service_rate;
	k = number_of_stages;

	combi = mu * k;
}



template <class T, class I> T expected(const T& u)
{
      // Use numerical integration
}

template <class T, class I> variance(const T& u)
{
      // Use numerical integration
}

template <class T, class I> T Erlang<T,I>::pdf(const T& x) const
{ // The density function 

	
	return MISCFUN::pow(combi, k) * MISCFUN::pow(x, k-1) * exp(-combi * x) / MISCFUN::gamma(k);

	
}



