// CommandFactory.hpp
//
// Comamnd derived class for Continuous Distributions factories
//
// (C) Datasim Education BV 1998-2003

#ifndef CommandFactory_hpp
#define CommandFactory_hpp

#include "cnsdistfactory.hpp"
#include <iostream>
using namespace std;

class CommandFactory : public CnsDistFactory
{
private:
public: // !!! inline functions
	// Constructors and destructor
	CommandFactory() {}								// Default constructor
	CommandFactory(const CommandFactory& source) {}	// Copy constructor
	virtual ~CommandFactory() {}						// Destructor

	virtual ContinuousDistribution<double, double> * CreateUniform()
	{
		return new Uniform<double>(0.0, 1.0);
	}

	virtual ContinuousDistribution<double, double> * CreateGamma() 
	{
	
		double r, a;

		cout << "Creating a Gamma distribution" << endl;

		// Input point
		cout<<"Input r: ";
		std::cin>>r;
		std::cout<<"Input a: ";
		std::cin>>a;

		return new Gamma<double> (r, a);
	}

	virtual ContinuousDistribution<double, double> * CreateExponential()
	{

		return new Exponential<double> (2.0);

	}


	// Operators
	CommandFactory& operator = (const CommandFactory& source);
};

#endif // CommandFactory_hpp
