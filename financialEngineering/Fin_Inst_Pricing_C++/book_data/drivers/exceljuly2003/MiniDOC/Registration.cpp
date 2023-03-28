// Implementation of Registration activity.
//
// Datasim Education BV (c) 2003
// 
// Modification dates:
// 23 July 2003 - MB - Started.
// 29 July 2003 - MB - Reading data from Excel into SimplePropertySet.

#include <iostream>
#include <string>
using namespace std;

#include "ExcelDriver.cpp"
#include "SimplePropertySet.cpp"

// Initialize A, B and N with values from user.
void GetInput(SimplePropertySet<string, double> & input)
{
	try
	{
		ExcelDriver & excel = ExcelDriver::Instance();

		// Add property set.
		excel.AddPropertySet(input);
		excel.MakeVisible();		
		
		// Wait...
		cout << "Enter values in Excel spreadsheet." << endl;
		cout << "When done, make sure cursor is not blinking and type a letter followed by Enter.";
		string abc;
		cin >> abc;

		// Get property set.
		excel.GetPropertySet(input);
	}
	catch( string & error )
	{
		cout << error << endl;
	}
}