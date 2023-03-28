//#include "..//DPS2//DisableWarning4786.h"

#include "ExcelSolutionFormatter.h"

#include "Option.h"
#include "Solution.h"
#include "ExcelDriver.hpp"

#include <string>
using namespace std;

namespace
{

// Writes vector to cells in horizontal direction.
static void ToExcelSheet
( Excel::_WorksheetPtr pSheet
, long sheetRow
, long sheetColumn
, const DoubleVector & _vector
)
{
	try
	{
		Excel::RangePtr pRange=pSheet->Cells;
		
		const int size = _vector.size();
		for(int i=0; i < size; i++)
		{
			Excel::RangePtr item = pRange->Item[sheetRow][sheetColumn];
			item->Value = _vector[i];			
			sheetColumn++;
		}
	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

// Writes string to a cell on the sheet.
static void ToExcelSheet
( Excel::_WorksheetPtr pSheet
, long sheetRow
, long sheetColumn
, const char * pString
)
{
	try
	{
		Excel::RangePtr pRange=pSheet->Cells;
		Excel::RangePtr item = pRange->Item[sheetRow][sheetColumn];
		item->Value = pString;			
	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

}

void ExcelSolutionFormatter::Format
( const TStandardPropertySet & option
, const TStandardPropertySet & solution 
) const
{
	try
	{
		// Get vectors from solution.
		DoubleVector s;
		DoubleVector premium;
		DoubleVector delta;
		DoubleVector gamma;

		solution.GetValue( Solution::S, s );
		solution.GetValue( Solution::Premium, premium );
		solution.GetValue( Solution::Delta, delta );
		solution.GetValue( Solution::Gamma, gamma );

		// Create an Excel object
		ExcelDriver xl;

		// Open Excel and add workbook
		xl.OpenExcel();
		xl.AddWorkbook();

		// Get active sheet.
		Excel::_WorksheetPtr pSheet=xl.Application()->ActiveSheet;

		// Write values to sheet.
		ToExcelSheet(pSheet,1,2,s);
		ToExcelSheet(pSheet,2,1,"t=0.000000");
		ToExcelSheet(pSheet,2,2,premium);

		ToExcelSheet(pSheet,4,2,s);
		ToExcelSheet(pSheet,5,1,"t=0.000000");
		ToExcelSheet(pSheet,5,2,delta);

		ToExcelSheet(pSheet,7,2,s);
		ToExcelSheet(pSheet,8,1,"t=0.000000");
		ToExcelSheet(pSheet,8,2,gamma);

		// Create charts.

		// Create parameters text.
		string parametersText;
		char tempString[256];
		
		double K = option.GetDouble(Option::K);
		double rate = option.GetDouble(Option::r);
		double sigma = option.GetDouble(Option::sigma);
	
		string contractType = option.GetString(Option::UIName);
		
		sprintf(tempString, "%.4f", K);
		parametersText= "K=" + std::string(tempString) + ", ";
	
		sprintf(tempString, "%.4f", rate);
		parametersText=parametersText + "r=" + string(tempString) + ", ";

		sprintf(tempString, "%.4f", sigma);
		parametersText=parametersText + "sigma=" + string(tempString) + ", ";

		// Option price.
		string title1 = contractType + string(" (Premium)\n") + parametersText;
		const string category1 = "Stock price (S)";
		const string value1 = "Option price";
		xl.CreateChart(1, 2, s.size(), title1, category1, value1);
		xl.SetActiveSheet("Sheet1");

		// 1st derivative.
		string title2 = contractType + string(" (Delta)\n") + parametersText;
		const string category2 = "Stock price (S)";
		const string value2 = "Delta";
		xl.CreateChart(4, 2, s.size(), title2, category2, value2);
		xl.SetActiveSheet("Sheet1");

		// 2nd derivative.
		const string title3 = contractType + string(" (Gamma)\n") + parametersText;
		const string category3 = "Stock price (S)";
		const string value3 = "Gamma";
		xl.CreateChart(7, 2, s.size(), title3, category3, value3);
		xl.SetActiveSheet("Sheet1");

	}
	catch(_com_error&)
	{ // For now ignore error
	}
	
}