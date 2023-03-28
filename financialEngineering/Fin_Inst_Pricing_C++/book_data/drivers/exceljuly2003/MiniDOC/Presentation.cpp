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
void Present( const Vector<double, int> & x, const Vector<double, int> & function, 
			  const Vector<double, int> & delta, const Vector<double, int> & gamma,
			  const Vector<double, int> & N_result, const Vector<double, int> & n_result,
			  const Vector<double, int> & european, const Vector<double, int> & digital,
				const Vector<double, int> & turningPoint)
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
		functions.push_back(delta);
		functions.push_back(gamma);
		labels.push_back("Function");
		labels.push_back("Delta");
		labels.push_back("Gamma");

		// Display list of function + derivatives in single chart.
		excel.CreateChart(x, labels, functions, "Function and Derivatives");

		// Create other charts.
		excel.CreateChart(x, n_result, "n", "X", "Y");
		excel.CreateChart(x, N_result, "N (integrated)");
		excel.CreateChart(x, european, "European Type");
		excel.CreateChart(x, digital, "Digital Type");
		excel.CreateChart(x, turningPoint, "Turningpoint Type");

		// Create numeric matrix.
		NumericMatrix<double> matrix(2, 4, 1, 1);		// 2 rows, 4 columns, start indeces = 1
		matrix(1, 1) = 1;
		matrix(1, 2) = 2;
		matrix(1, 3) = 3;
		matrix(1, 4) = 4;
		matrix(2, 1) = 5;
		matrix(2, 2) = 6;
		matrix(2, 3) = 7;
		matrix(2, 4) = 8;

		// Create matrix labels.
		list<string> rowLabels;
		rowLabels.push_back("R1");
		rowLabels.push_back("R2");
		list<string> columnLabels;
		columnLabels.push_back("C1");
		columnLabels.push_back("C2");
		columnLabels.push_back("C3");
		columnLabels.push_back("C4");
		
		// Display matrix in excel.
		excel.AddMatrix("MyMatrix", matrix, rowLabels, columnLabels);
	}
	catch( string error )
	{
		cout << error << endl;
	}
}