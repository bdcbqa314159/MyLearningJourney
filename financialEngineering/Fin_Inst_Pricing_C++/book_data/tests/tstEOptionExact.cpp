// tstEOptionExact.cpp
//
// Test program for the exact solutions of European options
//
// (C) Datasim Component Technology BV 20003
//

#include "EOptionExact.hpp"
#include <iostream>

int main()
{ // All options are European

	// Call option on a stock
	ExactEuropeanOption callOption;
	cout << "Call option on a stock: " << callOption.Price() << endl;
	
	// Put option on a stock index
	ExactEuropeanOption indexOption("P", "Index Option");
	indexOption.U(100.0);
	indexOption.K(95.0);
	indexOption.T(0.5);
	indexOption.r(0.10);
	indexOption.sig(0.20);

	double q = 0.05;		// Dividend yield
	indexOption.b( indexOption.r() - q );

	cout << "Put option on an index: " << indexOption.Price() << endl;

	// Call and put options on a future
	ExactEuropeanOption futureOption("P", "Future Option");
	futureOption.U(19.0);
	futureOption.K(19.0);
	futureOption.T(0.75);
	futureOption.r(0.10);
	futureOption.sig(0.28);

	futureOption.b( 0.0);

	cout << "Put option on a future: " << futureOption.Price() << endl;

	// Now change over to a call on the option
	futureOption.toggle();
	cout << "Call option on a future: " << futureOption.Price() << endl;


	// Call option on currency
	ExactEuropeanOption currencyOption("C", "Currency Option");
	currencyOption.U(1.56);
	currencyOption.K(1.60);
	currencyOption.T(0.5);
	currencyOption.r(0.06);
	currencyOption.sig(0.12);

	double rf = 0.08;		// risk-free rate of foreign currency
	currencyOption.b( currencyOption.r() - rf );

	cout << "Call option on a currency: " << currencyOption.Price() << endl;

	////////   NOW CALCULATIONS OF SENSITIVITIES //////////////////////////////////

	// Call and put options on a future: Delta and Elasticity
	ExactEuropeanOption futureOption2("P", "Future Option");
	futureOption2.U(105.0);
	futureOption2.K(100.0);
	futureOption2.T(0.5);
	futureOption2.r(0.10);
	futureOption2.sig(0.36);

	futureOption2.b( 0.0);

	cout << "Delta on a put future: " << futureOption2.Delta() << endl;

	// Now change over to a call on the option
	futureOption2.toggle();
	cout << "Delta on a call future: " << futureOption2.Delta() << endl;

	futureOption2.toggle(); // Back to put
	cout << "Elasticity on a put future: " << futureOption2.Elasticity(7.6767) << endl;

	// Stock Option: Gamma
	ExactEuropeanOption stockOption("C", "Stock Option");
	stockOption.U(55.0);
	stockOption.K(60.0);
	stockOption.T(0.75);
	stockOption.r(0.10);
	stockOption.sig(0.30);

	stockOption.b(stockOption.r());

	cout << "Call Gamma on a stock option: " << stockOption.Gamma() << endl;
	cout << "Call Vega on a stock option: " << stockOption.Vega() << endl;

	stockOption.toggle();

	cout << "Put Gamma on a stock option: " << stockOption.Gamma() << endl;
	cout << "Put Vega on a stock option: " << stockOption.Vega() << endl;

	// Calculating theta of a European stock index
	ExactEuropeanOption indexOption2("P", "Index Option");
	indexOption2.U(430.0);
	indexOption2.K(405.0);
	indexOption2.T(0.0833);	// One month expiration
	indexOption2.r(0.07);
	indexOption2.sig(0.20);

	double divYield = 0.05;		// Dividend yield, 5% per annum
	indexOption2.b( indexOption2.r() - divYield );

	cout << "Put Theta on a stock index: " << indexOption2.Theta() << endl;
	
	indexOption2.toggle();

	cout << "Call Theta on a stock index: " << indexOption2.Theta() << endl;

	// Stock Option: Rho
	ExactEuropeanOption stockOption2("C", "Stock Option");
	stockOption2.U(72.0);
	stockOption2.K(75.0);
	stockOption2.T(1.0);
	stockOption2.r(0.09);
	stockOption2.sig(0.19);

	stockOption2.b(stockOption2.r());

	cout << "Call Rho on a stock option: " << stockOption2.Rho() << endl;

	stockOption2.toggle();

	cout << "Put Rho on a stock option: " << stockOption2.Rho() << endl;

	// Calculating Cost of Carry of a European stock index
	ExactEuropeanOption indexOption3("P", "Index Option");
	indexOption3.U(500.0);
	indexOption3.K(490.0);
	indexOption3.T(0.222225);
	indexOption3.r(0.08);
	indexOption3.sig(0.15);

	double divYield3 = 0.05;		// Dividend yield, 5% per annum
	indexOption3.b( indexOption3.r() - divYield3 );

	cout << "Put Cost of Carry on a stock index: " << indexOption3.Coc() << endl;
	
	indexOption3.toggle();

	cout << "Call Cost of Carry on a stock index: " << indexOption3.Coc() << endl;

	// Put everything into a property set
	SimplePropertySet<string, double> allprops = indexOption3.properties();

	// Now iterate in the list
	SimplePropertySet<string,double>::const_iterator ci;

	cout << "\nDump the values \n";

	for (ci=allprops.Begin(); ci!=allprops.End(); ci++)
	{ 

		cout << (*ci).name() << ", " << (*ci)() << endl;
	}

	string sensitivity_type = "Delta";
	string property = "T";
	Vector<double> parameter_range(12);
	parameter_range[1] = 0.25;
	for (int i = parameter_range.MinIndex() + 1; i <=parameter_range.MaxIndex(); i++)
	{
		parameter_range[i] += parameter_range[i-1] + 0.0833;
	}

	Vector<double> gg = indexOption3.graph(sensitivity_type, property, parameter_range);

	for (i = gg.MinIndex(); i <= gg.MaxIndex(); i++)
	{
		cout << gg[i] << endl;

	}

	SimplePropertySet<string,double> r = futureOption2.properties();

	SimplePropertySet<string,double>::const_iterator ci2;

	cout << "\nDump the parameters \n";

	for (ci2=r.Begin(); ci2!=r.End(); ci2++)
	{ 

		cout << (*ci2).name() << ", " << (*ci2)() << endl;
	}

	return 0;
}
