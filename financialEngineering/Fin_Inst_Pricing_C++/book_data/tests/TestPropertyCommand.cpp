// TestPropertyCommand.cpp
//
// Testing Command patterns with properties
//
// (C) Datasim Component Technology BV 2003
//

#include "PropertyCommand.cpp"
#include "EOptionExact.hpp"
#include <iostream>
#include "Entity.cpp"
#include <string>

SimplePropertySet<string, double> CallDelta(const SimplePropertySet<string, double>& s) 
{

	cout << "\nNow executing the function\n";

	// double tmp = sig() * sqrt(T());

	Property<string, double> first = s.value("Expiry date");
	Property<string, double> second = s.value("Strike Price");
	
	
	SimplePropertySet<string, double> result;

	result.add(first);
	result.add(second);


	return result;
}

int main()
{

	// ** Set up the Basic Class

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


	// ** Set up the command object for the Basic Class
	PropertyCommand<string, double> cmd("Sort of Delta", CallDelta);
	//cmd.supplier(&callOption);


	//** Now execute the function
	SimplePropertySet<string, double> result = cmd.execute(callOption.properties());
	
	cout << "Number of properties " << result.Count() << endl;

	Property<string, double> p = result.value("Expiry date");
	cout << "Name + value " << p.name() << ", " << p() << endl;

	Property<string, double> p2 = result.value("Strike Price");
	cout << "Name + value " << p2.name() << ", " << p2() << endl;

	// Black belt (3rd Dan) stuff
	Entity<string, double> myEnt;
	myEnt.props = indexOption.properties();
	cout << "????????????????????????????????????????\n";

//	myEnt.execute(cmd);

	PropertyCommand<string, double> cmd1("Sort of Delta", CallDelta);
	//cmd1.supplier(&myEnt);

	SimplePropertySet<string, double> result1 = cmd1.execute(myEnt.properties());
	
	cout << "Number of properties " << result1.Count() << endl;


	cout << "????????????????????????????????????????\n";


	EntityCategory<int, double> ec(999);

	Entity<int, double> e1(123);
	Entity<int, double> e2(266);

	// Categories
	e1.category(ec); e2.category(ec);

	// Properties
	Property<int, double> p1 (1);
	p1(0.9);

	Property<int, double> p22 (2);
	p22(0.8);

	Property<int, double> p3 (3);
	p3(0.7);

	e1.props.add(p1);
	e1.props.add(p22);
	e1.props.add(p3);
	e1.props.add(p22);


	cout << "number of props in e1 " << e1.props.Count() << endl;

	return 0;
}

