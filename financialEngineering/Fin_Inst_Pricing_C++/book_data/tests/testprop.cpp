// testprop.cpp

#include "property.cpp"
#include <string>
#include <iostream>
#include "detfunction.cpp"
#include "propertycommandset.cpp"

using namespace std;

double foobar(const double& d)
{
	cout << "BLA\n";
	return 1.0;
}


int main()
{

	// Meta meta model
	Property<string, string> mmmprop("DDP0", "Parameter");
	Property<string, string> mmmprop2("DDP1", "Function");


	// Meta model level
	Property<string, string> metaprop("Parameter", "K");
	Property<string, string> metaprop2("Parameter", "r");
	Property<string, string> metaprop3("Parameter", "T");

	Entity<string, double> ent1;
	ent1.AddProperty(metaprop);

	// Model level
	Property<string, double> prop("K", 150.0);
	Property<string, double> prop2("r", 0.06);
	Property<string, double> prop3("T", 1.0);

	Entity<string, double> ent2;
	AddProperty(prop);


	ScalarFunction<double, double, int> myfunI;
	myfunI.function(foobar);
	Property<string, ScalarFunction<double, double, int> > prop4("FOOBAR", myfunI);

	vector<funType>& Cfunctions;

    int j;
	cin >> j;

	return 0;
}
