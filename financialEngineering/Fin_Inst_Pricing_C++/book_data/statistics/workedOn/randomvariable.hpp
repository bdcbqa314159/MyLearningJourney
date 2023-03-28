// RandomVariable.hpp
//
// Class representing uni-variate and multi-variate random variables. We consider continuous
// and discrete cases. 
//
// (C) Datasim Component Technology BV 2001

#ifndef RandomVariable_HPP
#define RandomVariable_HPP

#include "cnsdist.hxx"



// Class that models random variables. We do not draw a distinction between continuous and 
// discrete variable because each r.v. has an underlying general probability distribution.

template <class Domain, class Range> RandomVariable
{ // A function that associates a value in Range with each point of the sample space Domain
private:

		ProbabilityDistribution<Domain, Range>* type;
public:

};


// Class that models random or stochastic processes
template <class Domain, class Range, class Time> StochasticProcess
{ // Random process class. This is in essence a set of random variables indexed at some time 
  // level in the generic class Time.
private:

		RandomVariable<Domain, Range> r;
		Time t;//??
public:

};

#endif