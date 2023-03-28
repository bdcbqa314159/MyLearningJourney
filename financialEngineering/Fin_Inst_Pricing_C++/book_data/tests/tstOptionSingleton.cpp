// tstOptionSingleton.cpp
//
// Test program for the Singleton pattern with Option classes
//
// (C) Datasim Component Technology BV 20003
//

#include "simplepropertyset.cpp"
#include "singleton.cpp"
#include <iostream>

class EuropeanOption
{ // For test cases only. Real class is more extensive

public:
	EuropeanOption () { attributes = SimplePropertySet<string, double>(); }

	SimplePropertySet<string, double> attributes;

	void setProperties (const SimplePropertySet<string,double>& pset)
	{
		attributes = pset;
	}
	
	void print()
	{
		SimplePropertySet<string,double>::const_iterator it;

		cout << "\nPrinting normal option\n";
		for (it= attributes.Begin(); it!= attributes.End(); it++)
		{ 
	
				cout << (*it).name() << ", " << (*it)() << endl;
		}
	}
};


class UniqueOption: public Singleton<EuropeanOption>
{ // Singleton class this is essentially a prototype for all European options
public:
		static void configure (const SimplePropertySet<string,double>& pset)
		{ // Function to customise the member data of unique option

			(instance() -> attributes) = pset;
		}

		static void print()
		{

			SimplePropertySet<string,double>::const_iterator it;
			EuropeanOption* eo = instance();

			cout << "\nPrinting Unique option\n";

			for (it= eo->attributes.Begin(); it!=eo->attributes.End(); it++)
			{ 
	
				cout << (*it).name() << ", " << (*it)() << endl;
			}
		}
};


void myPset(SimplePropertySet<string,double>& myDefaultSet)
{ // My property set that is default for my European option class
  // You can customise this to suit your own needs and wants

	Property<string, double> r;		// Interest rate
	Property<string, double> sig;	// Volatility
	Property<string, double> K;		// Strike price
	Property<string, double> T;		// Expiry date
	Property<string, double> U;		// Current underlying price (e.g. stock, forward)
	Property<string, double> b;		// Cost of carry


	r = Property<string, double> ("Interest rate", 0.08);
	sig= Property<string, double> ("Volatility",0.30);
	K = Property<string, double>("Strike Price", 65.0);
	T = Property<string, double>("Expiry date", 0.25);
	U = Property<string, double>("Underlying Asset", 60.0);		
	b = Property<string, double>("Cost of carry rate", r());	

	myDefaultSet.add(r);
	myDefaultSet.add(sig);
	myDefaultSet.add(K);
	myDefaultSet.add(T);
	myDefaultSet.add(U);
	myDefaultSet.add(b);


}

void yourPset(SimplePropertySet<string,double>& myDefaultSet)
{ // Another property set that is default for my European option class
  // You can customise this to suit your own needs and wants

	Property<string, double> r;		// Interest rate
	Property<string, double> sig;	// Volatility
	Property<string, double> K;		// Strike price
	Property<string, double> T;		// Expiry date
	Property<string, double> U;		// Current underlying price (e.g. stock, forward)
	Property<string, double> b;		// Cost of carry


	r = Property<string, double> ("R", 0.08);
	sig= Property<string, double> ("V",0.30);
	K = Property<string, double>("S", 65.0);
	T = Property<string, double>("E", 0.25);
	U = Property<string, double>("U", 60.0);		
	b = Property<string, double>("B", r());	

	myDefaultSet.add(r);
	myDefaultSet.add(sig);
	myDefaultSet.add(K);
	myDefaultSet.add(T);
	myDefaultSet.add(U);
	myDefaultSet.add(b);


}



int main()
{ // All options are European



	SimplePropertySet<string,double> myDefaultSet;
	myPset(myDefaultSet);
	UniqueOption::configure(myDefaultSet);

	UniqueOption::print();

	SimplePropertySet<string,double> yourDefaultSet;
	yourPset(yourDefaultSet);
	UniqueOption::configure(yourDefaultSet);

	UniqueOption::print();

	// Now copy all default parameters to a 'normal' object
	EuropeanOption eo;
	eo.setProperties(yourDefaultSet);
	eo.print();

	return 0;


}
