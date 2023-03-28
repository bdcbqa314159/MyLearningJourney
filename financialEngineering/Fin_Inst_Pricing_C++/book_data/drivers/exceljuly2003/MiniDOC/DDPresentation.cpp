// Implementation of Presentation activity.
// Creates charts of the functions in MS Excel.
//
// Datasim Education BV (c) 2003
// 
// Modification dates:
// 23 July 2003 - MB - Started.
// 29 July 2003 - MB - Using shared ExcelDriver instance.

#include <iostream>
#include <string>
#include <list>
using namespace std;

#include "Vector.cpp"
#include "NumericMatrix.cpp"
#include "ExcelDriver.cpp"

// Create Excel spreadsheet and show values.
void Presentation( const Vector<double, int> & x, 
			  const Vector<double, int> & n_result, const Vector<double, int> & N_result)
			 
{
	try
	{
		// Excel is invisible initially.
		cout << "Creating Excel output, please wait a moment..." << endl;

		// Create and initialize excel.
		ExcelDriver & excel = ExcelDriver::Instance();
	
		excel.MakeVisible(true);		// Default is INVISIBLE!

		cout << " instance \n";

		// Create list with function + derivatives and their labels.
		list<Vector<double, int> > functions;
		list<string> labels;
		functions.push_back(n_result);
		functions.push_back(N_result);

		labels.push_back("pdf");
		labels.push_back("cdf");

		cout << "chart I\n";

		// Display list of function + derivatives in single chart.
		excel.CreateChart(x, labels, functions, "Combined Functions");

		cout << "chart II\n";

		// Create other charts on another sheet

		excel.CreateChart(x, n_result, "n", "X", "Y");
		excel.CreateChart(x, N_result, "N (integrated)");
	
		// Create numeric matrix. Another test
		NumericMatrix<double> matrix(2, 4, 1, 1);		// 2 rows, 4 columns, start indices = 1
		matrix(1, 1) = 1; matrix(1, 2) = 2;	matrix(1, 3) = 3;
		matrix(1, 4) = 4; matrix(2, 1) = 5; matrix(2, 2) = 6;
		matrix(2, 3) = 7; matrix(2, 4) = 8;

		// Create matrix labels.
		list<string> rowLabels;
		rowLabels.push_back("R1");
		rowLabels.push_back("R2");
		list<string> columnLabels;
		columnLabels.push_back("C1");
		columnLabels.push_back("C2");
		columnLabels.push_back("C3");
		columnLabels.push_back("C4");

		
		// Display matrix in Excel.
		excel.AddMatrix("MyMatrix", matrix, rowLabels, columnLabels);
	}
	catch( string error )
	{
		cout << error << endl;
	}
}