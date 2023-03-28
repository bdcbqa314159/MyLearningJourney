// BasicExcelPresentation.cpp
//
// Implementation of Presentation activity.
// Creates charts of the functions in MS Excel.
//
// Datasim Education BV (c) 2003
// 
// Modification dates:
// 23 July 2003 - MB - Started.
// 29 July 2003 - MB - Using shared ExcelDriver instance.
// 2003-9-15 DD Simplifiued version

#include <iostream>
#include <string>
#include <list>
using namespace std;

#include "Vector.cpp"
#include "ExcelDriver.cpp"

// Create Excel spreadsheet and show values.
void Present( const Vector<double, int> & x, const Vector<double, int> & function, 
{
	try
	{
		// Excel is invisible initially.
		cout << "Creating Excel output, please wait a moment..." << endl;

		// Create and initialize excel.
		ExcelDriver & excel = ExcelDriver::Instance();
	
		// Create list with function + derivatives and their labels.
		list<Vector<double, int> > functions;
		list<string> labels;
		functions.push_back(function);
		labels.push_back("Function");

		// Display list of function + derivatives in single chart.
		excel.CreateChart(x, labels, functions, "General Function");

	}
	catch( string error )
	{
		cout << error << endl;
	}
}