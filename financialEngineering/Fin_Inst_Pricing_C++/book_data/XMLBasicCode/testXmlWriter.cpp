// tstXmlWriter.cpp
//
// Testing XML Writer 
//
// (C) Datasim Education BV 2003
//

#include "xmlwriter.cpp"
#include "xmlreader.cpp"
#include "entity.cpp"
#include <string>

int main()
{

	XMLWriter<string, double> xmlW, xmlW2;

	// The names in these properties may not contain spaces or funny characters

	Property<string, double> K("StrikePrice", 100.0);	
	Property<string, double> r("InterestRate", 0.06);	
	Property<string, double> T("Expiry", 1);			
	Property<string, double> S("Stock", 120);			
	Property<string, double> U("UnderlyingAsset", 134.2);
	Property<string, double> b("CostOfCarry", 12.0);		


	Entity<string, double> option("EuropeanOption");
	option.AddProperty(K);
	option.AddProperty(r);
	option.AddProperty(T);
	option.AddProperty(S);
	option.AddProperty(U);
	option.AddProperty(b);

	xmlW.visit(option);

	xmlW.Save ("Option.xml");


	// Now read the file back in
	XMLReader<string, double> xmlR;
	xmlR.Load("Option.xml");


	Entity<string, double> option2;
	xmlR.visit(option2);

	SimplePropertySet<string, double> optionParams = option2.properties;

	// Iterate over the result and print the values
	SimplePropertySet<string,double>::const_iterator it;

	cout << "\nDump the parameters, call prices ... \n";

	for (it=optionParams.Begin(); it!=optionParams.End(); it++)
	{ 

		cout << (*it).name() << ", " << (*it)() << endl;
	}

	/*

	SimplePropertySet<string, double> pset;
	pset.add(K);
	pset.add(r);
	pset.add(T);
	pset.add(S);

	xmlW2.visit(pset);

	xmlW2.Save ("BB");
	*/

	return 0;
}
