// probdist.hxx
//
// Base class for all types of probability density functions. This class has two derived 
// classes, namely ContinuousDistribution and DiscreteDistribution which in turn have a 
// number of derived classes of practical interest.
//
// All member functions in this class are private so that it is not possible to create 
// instances of the class.
//
// Copyright (C) Datasim Education BV 1994-2004

#ifndef ProbabilityDistribution_HXX
#define ProbabilityDistribution_HXX


template <class Domain, class Range> class ProbabilityDistribution
{
public:
      // Constructor and destructor
      ProbabilityDistribution();
      ProbabilityDistribution(const ProbabilityDistribution<Domain, Range>& t2);
      virtual ~ProbabilityDistribution();

	  ProbabilityDistribution<Domain, Range>& operator = (const ProbabilityDistribution<Domain, Range>& p2);

};

#endif