// DDCommandFactory.hpp
//
// Comamnd derived class for Continuous Distributions factories
//
// (C) Datasim Education BV 1998-2003

#ifndef DDCommandFactory_hpp
#define DDCommandFactory_hpp

#include "cnsdistfactory.hpp"
#include <iostream>
using namespace std;

class DDCommandFactory : public CnsDistFactory
{
private:
public: // !!! inline functions
	// Constructors and destructor
	DDCommandFactory() {}								// Default constructor
	DDCommandFactory(const DDCommandFactory& source) {}	// Copy constructor
	virtual ~DDCommandFactory() {}						// Destructor

	virtual ContinuousDistribution<double, double> * CreateUniform()
	{
		return new Uniform<double>(10.0, 21.0);
	}

	virtual ContinuousDistribution<double, double> * CreateGamma() 
	{
	
		double r, a;

		cout << "maken van een ding" << endl;

		// Input point
		cout<<"Geef r: ";
		std::cin>>r;
		std::cout<<"Geef a: ";
		std::cin>>a;

		return new Gamma<double> (r, a);
	}

	virtual ContinuousDistribution<double, double> * CreateExponential()
	{

		return new Exponential<double> (12.0);

	}


	// Operators
	DDCommandFactory& operator = (const DDCommandFactory& source);
};

#endif // DDCommandFactory_hpp
