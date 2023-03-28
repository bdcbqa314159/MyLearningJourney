// EOptionExact.cpp
//
// Class that represents exact solutions to European options.
//
//	Last modification dates:
//	2002-12-7 DanielDuffy first code
//	2002-12-8 DD tested call and put options for a range of Euro types
//	Some new functions for interoperability
//	2002-12-10 DD almost finished with the code for the European exact option formulae.
// 
// (C) Datasim Component Technology BV 2003
//

#ifndef ExactEuropeanOption_cpp
#define ExactEuropeanOption_cpp

#include "EOptionExact.hpp"
#include <math.h>
#include <iostream>

/*
public:	// Public property section
	Property<string, double> r;		// Interest rate
	Property<string, double> sig;	// Volatility
	Property<string, double> K;		// Strike price
	Property<string, double> T;		// Expiry date
	Property<string, double> U;		// Current underlying price (e.g. stock, forward)
	Property<string, double> b;		// Cost of carry

	Property<string, double> otyp;	// Option name (call, put)
	Property<string, double> unam;	// Name of underlying asset
*/

// Kernel Functions (Haug)
double ExactEuropeanOption::CallPrice() const
{

	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;
	double d2 = d1 - tmp;


	return (U() * exp((b()-r())*T()) * N(d1)) - (K() * exp(-r() * T())* N(d2));

}

double ExactEuropeanOption::PutPrice() const
{

	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;
	double d2 = d1 - tmp;
	return (K() * exp(-r() * T())* N(-d2)) - (U() * exp((b()-r())*T()) * N(-d1));

}

double ExactEuropeanOption::CallDelta() const
{
	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;


	return exp((b()-r())*T()) * N(d1);
}

double ExactEuropeanOption::PutDelta() const
{
	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;

	return exp((b()-r())*T()) * (N(d1) - 1.0);
}

double ExactEuropeanOption::CallGamma() const
{
	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;
	double d2 = d1 - tmp;

	return ( n(d1) * exp((b()-r())*T()) ) / (U() * tmp);
}

double ExactEuropeanOption::PutGamma() const
{
	return CallGamma();
}


double ExactEuropeanOption::CallVega() const
{
	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;

	return (U() * exp((b()-r())*T()) * n(d1) * sqrt(T()) );
}

double ExactEuropeanOption::PutVega() const
{
	return CallVega();
}

double ExactEuropeanOption::CallTheta() const
{

	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;
	double d2 = d1 - tmp;

	double t1 =  (U() * exp((b()-r())*T() ) * n(d1) * sig() * 0.5 )/ sqrt(T());
	double t2 =  (b()-r())*(U() * exp((b()-r())*T()) * N(d1));
	double t3 =  r() * K() * exp(-r() * T()) * N(d2);

	return -(t1 + t2 + t3);
}


double ExactEuropeanOption::PutTheta() const
{

	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;
	double d2 = d1 - tmp;

	double t1 =  (U() * exp( (b()-r())*T() ) * n(d1) * sig() * 0.5 )/ sqrt(T());
	double t2 =  (b()-r())*(U() * exp((b()-r())*T()) * N(-d1));
	double t3 =  r() * K() * exp(-r() * T()) * N(-d2);

	return t2 + t3 - t1;
}

double ExactEuropeanOption::CallRho() const
{

	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;
	double d2 = d1 - tmp;

	if (b() != 0.0)
		return T() * K() * exp(-r() * T()) * N(d2);
	else
		return - T() * CallPrice();

}


double ExactEuropeanOption::PutRho() const
{
	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;
	double d2 = d1 - tmp;

	if (b() != 0.0)
		return - T() * K() * exp(-r() * T()) * N(-d2);
	else
		return - T() * PutPrice();
}


double ExactEuropeanOption::CallCoc() const
{

	double tmp = sig() * sqrt(T());
	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;

	return T() * U() * exp( (b()-r())*T() ) * N(d1);
}


double ExactEuropeanOption::PutCoc() const
{
	double tmp = sig() * sqrt(T());
	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;

	return - T() * U() * exp((b()-r())*T()) * N(-d1);
}

double ExactEuropeanOption::CallElasticity(double percentageMovement) const		
{

	return (CallDelta() * U()) /  percentageMovement;
}

double ExactEuropeanOption::PutElasticity(double percentageMovement) const
{
	return (PutDelta() * U()) /  percentageMovement;
}

double ExactEuropeanOption::CallStrike() const
{ // As a function of the strike price

	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;
	double d2 = d1 - tmp;

	return - exp(-r() * T()) * N(d2);
}

double ExactEuropeanOption::PutStrike() const
{
	double tmp = sig() * sqrt(T());
	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;
	double d2 = d1 - tmp;

	return exp(-r() * T()) * N(-d2);
}

double ExactEuropeanOption::CallSecondStrike() const
{ // As a function of the strike price

	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;
	double d2 = d1 - tmp;

	return ( n(d2) * exp(-r()* T()) )/( K() * sig() * sqrt(T()) );
}

double ExactEuropeanOption::PutSecondStrike() const
{
	double tmp = sig() * sqrt(T());

	double d1 = ( log(U()/K()) + (b() + (sig()*sig())*0.5 ) * T() )/ tmp;
	double d2 = d1 - tmp;

	return ( n(d2) * exp(-r()* T()) )/( K() * sig() * sqrt(T()) );		
}

/////////////////////////////////////////////////////////////////////////////////////

void ExactEuropeanOption::init() 
{	// Initialise all default values

	// Prototypical property names and values (hard-coded)
	r = Property<string, double> ("Interest rate", 0.08);
	sig= Property<string, double> ("Volatility",0.30);
	K = Property<string, double>("Strike Price", 65.0);
	T = Property<string, double>("Expiry date", 0.25);
	U = Property<string, double>("Underlying Asset", 60.0);		// U == stock in this case
	b = Property<string, double>("Cost of carry rate", r());	// Black and Scholes stock option model (1973)
	otyp = "C";													// European Call Option
	unam = "Stock Option with no Dividend";


}

void ExactEuropeanOption::copy(const ExactEuropeanOption& o2)
{

	r = Property<string,double>(o2.r);
	sig = Property<string,double>(o2.sig);	
	K = Property<string,double>(o2.K);
	T = Property<string,double>(o2.T);
	U = Property<string,double>(o2.U);
	b = Property<string,double>(o2.b);
	
	otyp = o2.otyp;
	unam = o2.unam;

	
}

ExactEuropeanOption::ExactEuropeanOption() 
{ // Default call option

	init();
}

ExactEuropeanOption::ExactEuropeanOption(const ExactEuropeanOption& o2)
{ // Copy constructor

	copy(o2);
}

ExactEuropeanOption::ExactEuropeanOption (const string& optionType)
{	// Create option type

	init();
	otyp = optionType;

	// Finger trouble option
	if (otyp == "c")
		otyp = "C";

}


ExactEuropeanOption::ExactEuropeanOption (const string& optionType, const string& underlying)
{ // Create option type

	init();
	otyp = optionType;
	unam = underlying;
}

ExactEuropeanOption::~ExactEuropeanOption()
{

}


ExactEuropeanOption& ExactEuropeanOption::operator = (const ExactEuropeanOption& option2)
{

	if (this == &option2) return *this;

	copy (option2);

	return *this;
}

// Functions that calculate option price and sensitivities
double ExactEuropeanOption::Price() const 
{

	cout << "European option\n";

	if (otyp == "C")
	{
		return CallPrice();
	}
	else
		return PutPrice();

}

double ExactEuropeanOption::Delta() const 
{
	if (otyp == "C")
		return CallDelta();
	else
		return PutDelta();

}


double ExactEuropeanOption::Gamma() const 
{
	if (otyp == "C")
		return CallGamma();
	else
		return PutGamma();

}

double ExactEuropeanOption::Vega() const 
{
	if (otyp == "C")
		return CallVega();
	else
		return PutVega();

}

double ExactEuropeanOption::Theta() const 
{
	if (otyp == "C")
		return CallTheta();
	else
		return PutTheta();

}

double ExactEuropeanOption::Rho() const 
{
	if (otyp == "C")
		return CallRho();
	else
		return PutRho();

}


double ExactEuropeanOption::Coc() const 
{ // Cost of carry

	if (otyp == "C")
		return CallCoc();
	else
		return PutCoc();

}

double ExactEuropeanOption::Elasticity(double percentageMovement) const
{ // Elasticity

	if (otyp == "C")
		return CallElasticity(percentageMovement);
	else
		return PutElasticity(percentageMovement);

}

// The option's defining parameters
SimplePropertySet<string, double> ExactEuropeanOption::properties() const
{
	SimplePropertySet<string, double> result;

	result.add (Property<string, double> (r.name(), r() ) );
	result.add (Property<string, double> (sig.name(), sig() ) );
	result.add (Property<string, double> (K.name(), K() ) );
	result.add (Property<string, double> (T.name(), T() ) );
	result.add (Property<string, double> (U.name(), U() ) );
	result.add (Property<string, double> (b.name(), b() ) );

	return result;

}


SimplePropertySet<string, double> ExactEuropeanOption::propertylist() const
{

	SimplePropertySet<string, double> result;

	result.add (Property<string, double> ("Option Value", Price() ) );
	result.add (Property<string, double> ("Delta",Delta() ) );
	result.add (Property<string, double> ("Gamma",Gamma() ) );
	result.add (Property<string, double> ("Vega",Vega() ) );
	result.add (Property<string, double> ("Vega",Theta() ) );
	result.add (Property<string, double> ("Rho",Rho() ) );
	result.add (Property<string, double> ("Cost of Carry",Coc() ) );										// Cost of carry
	
	return result;

}

Vector<double> ExactEuropeanOption::graph(const string& sensitivity_type, const string& property,
					const Vector<double> parameter_range)
{
		curr = &T;		// Default x axis is time T

		if (property == "r")
			curr = &r;
		if (property == "sig")
			curr = &sig;
		if (property == "K")
			curr = &K;
		if (property == "T")
			curr = &T;
		if (property == "U")
			curr = &U;
		if (property == "b")
			curr = &b;

		// Save the value in the 'current' property 
		double memento = (*curr)();


		Vector<double> result (parameter_range.Size(), parameter_range.MinIndex());

		if (sensitivity_type == "Price")
		{
			for (int i = parameter_range.MinIndex(); i <= parameter_range.MaxIndex(); i++)
			{
				(*curr)(parameter_range[i]);
				result[i] = Price();
			}
		}

	

		if (sensitivity_type == "Delta")
		{
			for (int i = parameter_range.MinIndex(); i <= parameter_range.MaxIndex(); i++)
			{
				(*curr)(parameter_range[i]);
				result[i] = Delta();
			}
		}


		if (sensitivity_type == "Gamma")
		{
			for (int i = parameter_range.MinIndex(); i <= parameter_range.MaxIndex(); i++)
			{
				(*curr)(parameter_range[i]);
				result[i] = Gamma();
			}
		}

		if (sensitivity_type == "Vega")
		{
			for (int i = parameter_range.MinIndex(); i <= parameter_range.MaxIndex(); i++)
			{
				(*curr)(parameter_range[i]);
				result[i] = Vega();
			}
		}

	
		if (sensitivity_type == "Theta")
		{
			for (int i = parameter_range.MinIndex(); i <= parameter_range.MaxIndex(); i++)
			{
				(*curr)(parameter_range[i]);
				result[i] = Theta();
			}
		}

		if (sensitivity_type == "Rho")
		{
			for (int i = parameter_range.MinIndex(); i <= parameter_range.MaxIndex(); i++)
			{
				(*curr)(parameter_range[i]);
				result[i] = Rho();
			}
		}

		if (sensitivity_type == "Coc")
		{
			for (int i = parameter_range.MinIndex(); i <= parameter_range.MaxIndex(); i++)
			{
				(*curr)(parameter_range[i]);
				result[i] = Coc();
			}
		}

		// Now restore the old value of the property
		(*curr)(memento);

		return result;

}


// Modifier functions
void ExactEuropeanOption::toggle()
{ // Change option type (C/P, P/C)

	if (otyp == "C")
		otyp = "P";
	else
		otyp = "C";
}


//////////// Gaussian functions /////////////////////////////////

double ExactEuropeanOption::n(double x) const 
{ 

	double A = 1.0/sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);

}

double ExactEuropeanOption::N(double x) const 
{ // The approximation to the cumulative normal distribution


	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;

	double k = 1.0/(1.0 + (0.33267 * x));
	
	if (x >= 0.0)
	{
		return 1.0 - n(x)* (a1*k + (a2*k*k) + (a3*k*k*k));
	}
	else
	{
		return 1.0 - N(-x);
	}

}


#endif