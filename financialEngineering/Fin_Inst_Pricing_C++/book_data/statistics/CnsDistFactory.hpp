// CnsDistFactory.hpp
//
// Base class for Continuous Distributions factories
//
// (C) Datasim Education BV 1998-2003

#ifndef CnsDistFactory_hpp
#define CnsDistFactory_hpp

#include "probdist.cxx"
#include "cnsdist.cxx"
#include "unifdist.cxx"
#include "gammdist.cxx"
#include "expodist.cxx"

class CnsDistFactory
{
private:
public:
	// Constructors and destructor
	CnsDistFactory();								// Default constructor
	CnsDistFactory(const CnsDistFactory& source);	// Copy constructor
	virtual ~CnsDistFactory();						// Destructor

	virtual ContinuousDistribution<double, double> * CreateUniform() = 0;
	virtual ContinuousDistribution<double, double> * CreateGamma() = 0;	
	virtual ContinuousDistribution<double, double> * CreateExponential() = 0;


	// Operators
	CnsDistFactory& operator = (const CnsDistFactory& source);
};

#endif // CnsDistFactory_hpp
