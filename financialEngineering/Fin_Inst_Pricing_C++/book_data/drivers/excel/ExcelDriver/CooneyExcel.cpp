
#include "defs.h"
#include "CooneyExcel.hpp"
#include <cstdio>

struct StartOle {
    StartOle() { CoInitialize(NULL); }
    ~StartOle() { CoUninitialize(); }
} _inst_StartOle;

CooneyExcel::CooneyExcel()
{ // Default constructor
}

CooneyExcel::CooneyExcel(int rows, int columns): m_matrix(rows, columns)
{ // Construct
}

CooneyExcel::~CooneyExcel()
{ // Destructor
}

void CooneyExcel::AddSerie(double* data, int row)
{ // Add serie to matrix

	int column;
	int index=0;
	int maxcolumn=m_matrix.MaxColumnIndex();
	int pointerindex=0;
	for (column=m_matrix.MinColumnIndex(); column<=maxcolumn; column++, index++)
	{
		m_matrix(row, column)=data[index]; 
	}
}

// Global functions for sending vectors and matrices to Excel
bool CooneyExcel::ToExcel(struct Params& param, struct SolSettings& setting)
{ // Send numeric matrix to excel

	try
	{
		// Create an Excel object
		ExcelDriver xl;

		// Open Excel and add workbook
		xl.OpenExcel();
		xl.AddWorkbook();

		// Fill data
		FillNormal(param, setting, xl);
		FillDelta1(param, setting, xl);
		FillDelta2(param, setting, xl);
		FillDelta3(param, setting, xl);

		// Create a chart
		xl.CreateChart(1, m_matrix.Rows(), m_matrix.Columns(), ChartTitleText(param, setting), CategoryText(param), ValueText(param));
		xl.SetActiveSheet("Sheet1");
		xl.CreateChart(param.NT+3, m_matrix.Rows(), m_matrix.Columns()-2, ChartTitleText(param, setting) + "\n(Centered differences)", CategoryText(param), "Delta");
		xl.SetActiveSheet("Sheet1");
		xl.CreateChart(2*(param.NT+2)+1, m_matrix.Rows(), m_matrix.Columns()-2, ChartTitleText(param, setting) + "\n(Approximation to second derivative)", CategoryText(param), "Gamma");
		xl.SetActiveSheet("Sheet1");
		xl.CreateChart(3*(param.NT+2)+1, m_matrix.Rows(), m_matrix.Columns()-1, ChartTitleText(param, setting) + "\n(One-side difference)", CategoryText(param), "Epsilon");
		xl.SetActiveChart(ValueText(param));
		return true;
	}
	catch(_com_error&)
	{ // For now ignore error

		return false;
	}
}

void CooneyExcel::FillNormal(struct Params& param, struct SolSettings& setting, ExcelDriver& xl)
{ // Fill Excel sheet with normal data

	try
	{
		// Send matrix to active excel sheet
		int rowIndex;
		int columnIndex;
		int row;
		int column;

		// First fill the range
		xl.FillRange(param.h, param.S, param.NS-1, 1);

		// Get active sheet and its range
		Excel::_WorksheetPtr pSheet=xl.Application()->ActiveSheet;
		Excel::RangePtr pRange=pSheet->Cells;

		// Get max row and column index
		int maxRow=m_matrix.MaxRowIndex();
		int maxColumn=m_matrix.MaxColumnIndex();

		// Send all matrix values to the sheet
		// values begin in row 2
		row=2;
		for (rowIndex=m_matrix.MinRowIndex(); rowIndex<=maxRow; rowIndex++)
		{ // Do all rows

			// Fill series (row) text
			((Excel::RangePtr)pRange->Item[(double)row][(double)1])->Value=SerieText(param, row-1).c_str();
			
			// Do columns. Values start in column 2
			column=2;
			for (columnIndex=m_matrix.MinColumnIndex(); columnIndex<=maxColumn; columnIndex++)
			{ // Fill all columns
	
				((Excel::RangePtr)pRange->Item[(double)row][(double)column])->Value=(double)m_matrix(rowIndex, columnIndex);
				column++;
			}
			row++;
		}
	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

void CooneyExcel::FillDelta1(struct Params& param, struct SolSettings& setting, ExcelDriver& xl)
{ // Fill Excel sheet with delta data 1

	try
	{
		// Send matrix to active excel sheet
		int rowIndex;
		int columnIndex;
		int row;
		int column;
		int serie;
		double val;

		// First fill the range. 0 is not calculated and the first and the last do not have the required neighbour
		xl.FillRange(2*param.h, param.S-param.h, param.NS-1-2, param.NT+3);

		// Get active sheet and its range
		Excel::_WorksheetPtr pSheet=xl.Application()->ActiveSheet;
		Excel::RangePtr pRange=pSheet->Cells;

		// Get max row and column index
		int maxRow=m_matrix.MaxRowIndex();
		int maxColumn=m_matrix.MaxColumnIndex();

		// Send all matrix values to the sheet
		// values begin in row param.NT+4
		row=param.NT+4;
		serie=1;
		for (rowIndex=m_matrix.MinRowIndex(); rowIndex<=maxRow; rowIndex++, serie++)
		{ // Do all rows

			// Fill series (row) text
			((Excel::RangePtr)pRange->Item[(double)row][(double)1])->Value=SerieText(param, serie).c_str();
			
			// Do columns. Values start in column 2
			column=2;
			for (columnIndex=m_matrix.MinColumnIndex()+1; columnIndex<maxColumn; columnIndex++)
			{ // Fill all columns
	
				val=(m_matrix(rowIndex, columnIndex+1)-m_matrix(rowIndex, columnIndex-1)) / (2*param.h);
				((Excel::RangePtr)pRange->Item[(double)row][(double)column])->Value=val;
				column++;
			}
			row++;
		}

	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

void CooneyExcel::FillDelta2(struct Params& param, struct SolSettings& setting, ExcelDriver& xl)
{ // Fill Excel sheet with delta data 2

	try
	{
		// Send matrix to active excel sheet
		int rowIndex;
		int columnIndex;
		int row;
		int column;
		int serie;
		double val;

		// First fill the range. 0 is not calculated and the first and the last do not have the required neighbour
		xl.FillRange(2*param.h, param.S-param.h, param.NS-1-2, 2*(param.NT+2)+1);

		// Get active sheet and its range
		Excel::_WorksheetPtr pSheet=xl.Application()->ActiveSheet;
		Excel::RangePtr pRange=pSheet->Cells;

		// Get max row and column index
		int maxRow=m_matrix.MaxRowIndex();
		int maxColumn=m_matrix.MaxColumnIndex();

		// Send all matrix values to the sheet
		// values begin in row param.NT+4
		row=2*(param.NT+2)+2;
		serie=1;
		for (rowIndex=m_matrix.MinRowIndex(); rowIndex<=maxRow; rowIndex++, serie++)
		{ // Do all rows

			// Fill series (row) text
			((Excel::RangePtr)pRange->Item[(double)row][(double)1])->Value=SerieText(param, serie).c_str();
			
			// Do columns. Values start in column 2
			column=2;
			for (columnIndex=m_matrix.MinColumnIndex()+1; columnIndex<maxColumn; columnIndex++)
			{ // Fill all columns
	
				val=(m_matrix(rowIndex, columnIndex+1) - 2*m_matrix(rowIndex, columnIndex) + m_matrix(rowIndex, columnIndex-1)) / (param.h*param.h);
				((Excel::RangePtr)pRange->Item[(double)row][(double)column])->Value=val;
				column++;
			}
			row++;
		}

	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

void CooneyExcel::FillDelta3(struct Params& param, struct SolSettings& setting, ExcelDriver& xl)
{ // Fill Excel sheet with delta data 3

	try
	{
		// Send matrix to active excel sheet
		int rowIndex;
		int columnIndex;
		int row;
		int column;
		int serie;
		double val;

		// First fill the range. 0 is not calculated and the first does not have the required neighbour
		xl.FillRange(2*param.h, param.S-param.h, param.NS-1-1, 3*(param.NT+2)+1);

		// Get active sheet and its range
		Excel::_WorksheetPtr pSheet=xl.Application()->ActiveSheet;
		Excel::RangePtr pRange=pSheet->Cells;

		// Get max row and column index
		int maxRow=m_matrix.MaxRowIndex();
		int maxColumn=m_matrix.MaxColumnIndex();

		// Send all matrix values to the sheet
		// values begin in row param.NT+4
		row=3*(param.NT+2)+2;
		serie=1;
		for (rowIndex=m_matrix.MinRowIndex(); rowIndex<=maxRow; rowIndex++, serie++)
		{ // Do all rows

			// Fill series (row) text
			((Excel::RangePtr)pRange->Item[(double)row][(double)1])->Value=SerieText(param, serie).c_str();
			
			// Do columns. Values start in column 2
			column=2;
			for (columnIndex=m_matrix.MinColumnIndex(); columnIndex<maxColumn; columnIndex++)
			{ // Fill all columns
	
				val=(m_matrix(rowIndex, columnIndex+1) - m_matrix(rowIndex, columnIndex)) / (param.h);
				((Excel::RangePtr)pRange->Item[(double)row][(double)column])->Value=val;
				column++;
			}
			row++;
		}

	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

std::string CooneyExcel::SerieText(struct Params& param, int serie)
{ // Determine the series text from the parameter object and the current series
  // First serie=1
// TODO: Invent a better double to string conversion

	std::string result;
	double val;
	char str[256];

	val=(serie-1)*param.k;

	// Convert serie value to string
	sprintf(str, "t=%f", val);
	return (result + std::string(str));
}


std::string CooneyExcel::ChartTitleText(struct Params& param, struct SolSettings& setting)
{ // Determine the chart title text. eg. K=50, t=0.4, ...

	std::string result;
	char str[256];

	// Determine scheme
	switch (setting.scheme)
	{
		case EXACT:
			result=result + "Exact solution";
			break;
		case IMP:
			result=result + "Fully implicit scheme";
			break;
		case DUFF:
			result=result + "Fitted Duffy scheme";
			break;
		case CN:
			result=result + "Crank-Nicholson scheme";
			break;
		case FITTCN:
			result=result + "Fitted Crank-Nicholson scheme";
			break;
		default:
			result=result + "Unknown scheme";
			break;
	}
	
	// Determine method
	switch (setting.method)
	{
		case ITER:
			result=result + " - Iterative BiCGSTAB solver\n";
			break;
		case BALA:
			result=result + " - Direct Balayage solver\n";
			break;
		default:
			result=result + "\n";
			break;
	}

	// Determine parameters
	sprintf(str, "%.4f", param.K);
	result=result + "K=" + std::string(str) + ", ";


	sprintf(str, "%.4f", param.rate);
	result=result + "r=" + std::string(str) + ", ";

	sprintf(str, "%.4f", param.sigma);
	result=result + "sigma=" + std::string(str) + ", ";

	return result.substr(0, result.size()-2);
}

std::string CooneyExcel::CategoryText(struct Params& param)
{ // Determine the category text from the parameter object

	return "Stock price (S)";
}

std::string CooneyExcel::ValueText(struct Params& param)
{ // Determine value text

	switch (param.contract)
	{
	case EUROCALL:
		return "European Call Value";
		break;
	case EUROPUT:
		return "European Put Value";
		break;
	case AMERCALL:
		return "American Call Value";
		break;
	case AMERPUT:
		return "American Put Value";
		break;
	default:
		return "Unknown";
		break;
	}
}
