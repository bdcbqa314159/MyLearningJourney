// probdist.cxx
//
// Base class Domain,  class Range for probability density functions.
// This class Domain,  class Range has two derived class Domain,  class Rangees, namely continuous distibutions 
// and discrete distibutions which in turn have a number of derived
// class Domain,  class Rangees of practical interest.
//
// Last modification dates:
//
//	1994-11-6 DD last modifications
//	1999-1-5 DD template class Domain,  class Range now
//	2000-6-23 DD final 
//	2001-11-12 DD Domain and Range
//
// (C) Datasim Education BV 1994-2000

#ifndef ProbabilityDistribution_CXX
#define ProbabilityDistribution_CXX

#include "probdist.hxx"

template <class Domain, class Range> ProbabilityDistribution<Domain, Range>::ProbabilityDistribution()
{
}

template <class Domain, class Range> ProbabilityDistribution<Domain, Range>::ProbabilityDistribution(const ProbabilityDistribution<Domain, Range>& p2)
{
}

template <class Domain, class Range> ProbabilityDistribution<Domain, Range>::~ProbabilityDistribution()
{

}


template <class Domain, class Range> ProbabilityDistribution<Domain, Range>& ProbabilityDistribution<Domain, Range>::operator = (const ProbabilityDistribution<Domain, Range>& p2)
{

}

#endif
