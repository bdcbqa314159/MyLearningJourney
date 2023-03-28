
#ifndef ExcelDriverGlobals_cpp
#define ExcelDriverGlobals_cpp

#include "ExcelDriver.hpp"
// #include "Parameters.hpp"

#include <cstdio>

// Global functions for sending vectors and matrices to Excel
template <class TV, class TI>
// void Process(ExcelDriver& xl, const NumericMatrix<TV, TI>& matrix, const Parameters<TV>& param)
void Process(ExcelDriver& xl, const NumericMatrix<TV, TI>& matrix, double lower, double upper, double nsteps)

{ // Send numeric matrix to excel

	TI rowIndex;
	TI columnIndex;
	int row;
	int column;

	try
	{
		// First fill the range
	// xl.FillRange((double)param.LowerLimit(), (double)param.UpperLimit(), (double)param.NumberOfSteps());
	xl.FillRange(lower, upper, nsteps);

		// Get active sheet and its range
		Excel::_WorksheetPtr pSheet=xl.Application()->ActiveSheet;
		Excel::RangePtr pRange=pSheet->Cells;

		// Get max row and column index
		TI maxRow=matrix.MaxRowIndex();
		TI maxColumn=matrix.MaxColumnIndex();

		// Send all matrix values to the sheet
		// values begin in row 2
		row=2;
		for (rowIndex=matrix.MinRowIndex(); rowIndex<=maxRow; rowIndex++)
		{ // Do all rows

			// Fill series (row) text
			((Excel::RangePtr)pRange->Item[(double)row][(double)1])->Value=SerieText(param, row-1).c_str();
			
			// Do columns. Values start in column 2
			column=2;
			for (columnIndex=matrix.MinColumnIndex(); columnIndex<=maxColumn; columnIndex++)
			{ // Fill all columns
	
				((Excel::RangePtr)pRange->Item[(double)row][(double)column])->Value=(double)matrix(rowIndex, columnIndex);
				column++;
			}
			row++;
		}
	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

template <class TV, class TI>
// void Process(ExcelDriver& xl, const Vector<TV, TI>& vector, const Parameters<TV>& param, int serie=1)
void Process(ExcelDriver& xl, const Vector<TV, TI>& vector, double lower, double upper, double nsteps, int serie=1)

{ // Send vector to excel

	TI columnIndex;
	int column;
	int row=serie+1;		// The row to use is the serie+1

	try
	{
		// First fill the range
//		xl.FillRange((double)param.LowerLimit(), (double)param.UpperLimit(), (double)param.NumberOfSteps());
		xl.FillRange(lower, upper, nsteps);

		// Get active sheet and its range
		Excel::_WorksheetPtr pSheet=xl.Application()->ActiveSheet;
		Excel::RangePtr pRange=pSheet->Cells;

		// Get column index
		TI maxColumn=vector.MaxIndex();

		// Fill row name
		((Excel::RangePtr)pRange->Item[(double)row][(double)1])->Value=SerieText(param, serie).c_str();
		
		// Do columns. Values start in column 2
		column=2;
		for (columnIndex=vector.MinIndex(); columnIndex<=maxColumn; columnIndex++)
		{ // Fill all columns

			((Excel::RangePtr)pRange->Item[(double)row][(double)column])->Value=(double)vector[columnIndex];
			column++;
	}
	}	
	catch(_com_error&)
	{ // For now ignore error
	}
}

/*
template <class TV>
std::string SerieText(const Parameters<TV>& param, int serie)
{ // Determine the series text from the parameter object and the current series
  // First serie=1
// TODO: Invent a better double to string conversion

	std::string result;
	TV val;
	char str[256];

	// Determine the current serie
	if (param.SizeK()>1){val=param.K(serie-1); result="K=";}
	else if (param.SizeS()>1){val=param.S(serie-1); result="S=";}
	else if (param.Sizet()>1){val=param.t(serie-1); result="t=";}
	else if (param.Sizer()>1){val=param.r(serie-1); result="r=";}
	else if (param.Sizev()>1){val=param.v(serie-1); result="v=";}
	else return "";

	// Convert serie value to string
	sprintf(str, "%f", val);
	return (result + std::string(str));
}

template <class TV>
std::string ChartTitleText(const Parameters<TV>& param)
{ // Determine the chart title text. eg. K=50, t=0.4, ...
// TODO: Invent a better double to string conversion

	std::string result;
	char str[256];

	if (param.SizeK()==1) 
	{
		sprintf(str, "%f", param.K());
		result=result + "K=" + std::string(str) + ", ";
	}

	if (param.SizeS()==1) 
	{
		sprintf(str, "%f", param.S());
		result=result + "S=" + std::string(str) + ", ";
	}

	if (param.Sizet()==1) 
	{
		sprintf(str, "%f", param.t());
		result=result + "t=" + std::string(str) + ", ";
	}

	if (param.Sizer()==1) 
	{
		sprintf(str, "%f", param.r());
		result=result + "r=" + std::string(str) + ", ";
	}

	if (param.Sizev()==1) 
	{
		sprintf(str, "%f", param.v());
		result=result + "v=" + std::string(str) + ", ";
	}

	return result.substr(0, result.size()-2);
}

template <class TV>
std::string CategoryText(const Parameters<TV>& param)
{ // Determine the category text from the parameter object

	if (param.SizeK()==0) return "Strike price (K)";
	if (param.SizeS()==0) return "Current stock price (S)";
	if (param.Sizet()==0) return "Time to expiration (t)";
	if (param.Sizer()==0) return "Interest rate";
	if (param.Sizev()==0) return "Volatility (v)";
	return "Unknown";
}


*/

#endif
