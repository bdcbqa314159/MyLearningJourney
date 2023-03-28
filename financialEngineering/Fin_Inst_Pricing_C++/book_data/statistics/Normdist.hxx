// normdist.hxx
//
// The normal probability distribution. This distribution arises in many situations
// in daily life. For example, this is an important distribution in risk management.
// The standardized normal distribution N(0,1) can be created by the default constructor.
//
// This distribution is defined on an infinite interval. Some other distributions are
// defined on a semi-infinite interval.
//
// Copyright (C) Datasim Component Technology BV 1994-2000

#ifndef Normal_HXX
#define Normal_HXX

#include "cnsdist.cxx"

template <class Domain, class Range> class Normal: public ContinuousDistribution<Domain, Range>
{

private:
	Domain mu;
	Domain sigma;

public:
	// Constructors
	Normal();		// Standard normal distribution (mean == 0 and variance == 1
	Normal(const Domain& m, const Domain& s);		// Mean == m, variance == s
	Normal (const Normal<Domain, Range>& n2);
	virtual ~Normal();

	// Selectors
    Range expected(const Normal<Domain, Range>& n);
    Range variance(const Normal<Domain, Range>& n);
	Range expected() const;
    Range variance() const;


	Range pdf(const Domain& x) const;

	ContinuousDistribution<T, T>* clone() const;

};

#endif
