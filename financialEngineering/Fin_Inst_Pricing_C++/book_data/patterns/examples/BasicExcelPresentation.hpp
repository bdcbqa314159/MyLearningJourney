// BasicExcelPresentation.cpp
//
// Implementation of Presentation activity.
// Creates charts of the functions in MS Excel.
//


#include "Vector.cpp"
#include "ExcelDriver.cpp"

// Create Excel spreadsheet and show values.
void Present( const Vector<double, int> & x, const Vector<double, int> & function,
			 				const string& chartTitle, const string& cellTitle); 
