//  Weibull.cxx
//
// Last modification dates:
//
// 1994-2-7 DD Commonality filtered to base class CNSDIST
// 1999-1-5 DD templated functionality
// 2000-6-24 DD final version
//
// Copyright (C) Datasim Education BV 1994-2000

#include "weibdist.hxx"
#include "miscfun.hxx"

template <class T> Weibull<T>::Weibull(const T& alpha, const T& beta)
{
      a = alpha;
      b  = beta;
     
}

template <class T> T expected(const Weibull<T>& w)
{ // Uses the gamma function for non-integral values

	double beta2 = 1.0 /w.b;
	double res1 = 1.0 / pow(w.a, beta2);
	return res1 * MISCFUN::gamma(1.0 + beta2);
}

template <class T> T variance(const Weibull<T>& w)
{ // Uses the gamma function for non-integral values

	double beta2 = 2.0 / w.b;
	double res1 = 1.0 / pow(w.a, beta2);
	double res2 = MISCFUN::gamma(1.0 + beta2);
	double res3 = MISCFUN::gamma(1.0 + (0.5 * beta2));

	return res1 * (res2 - (res3 * res3));
}

template <class T> T Weibull<T>::pdf(const T& t) const
{
      // Precondition
      if (t < 0.0)
		return T(0.0);

      double par = pow(t, b - 1.0);
      double par2 = par * t;
      return (a * b) * par * exp(- (a * par2));
}

template <class T> T Weibull<T>::cdf(const T& x) const
{
      if (x < 0.0)
	 return 0.0;

      double par = pow(x, b);
      return(1.0 - exp(- a * par));
}

template <class T> T Weibull<T>::reliability(const T& t) const
{ // The reliability function for the Weibull distribution

	double tmp = pow(t, b);
	return exp(- a * tmp);
}


template <class T> T Weibull<T>::failure_rate(const T& t) const
{ // The failure rate of the distribution


	// return pdf(t) / reliability (t);

	return (a * b) * pow(t, b - 1.0);
}

