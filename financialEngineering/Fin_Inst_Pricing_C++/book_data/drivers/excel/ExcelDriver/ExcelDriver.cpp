// ExcelDriver.cpp
//
// Class that enables us to send output to Excel
//
// (C) Datasim Component Technology 2000


#include "ExcelDriver.hpp"

// Constructors & destructor
ExcelDriver::ExcelDriver()
{ // Default constructor
}

ExcelDriver::ExcelDriver(const ExcelDriver& source)
{ // Copy constructor
}

ExcelDriver::~ExcelDriver()
{ // Destructor
}

// Selectors
Excel::_ApplicationPtr ExcelDriver::Application() const
{ // Return Excel application

	return m_pXL;
}

// Modifiers

// Operations
void ExcelDriver::OpenExcel()
{ // Open Excel application

	try
	{
		m_pXL.CreateInstance(L"Excel.Application");
		m_pXL->Visible=VARIANT_TRUE;
	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

void ExcelDriver::CloseExcel()
{ // Close Excel

	try
	{
		m_pXL->Quit();
	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

void ExcelDriver::AddWorkbook()
{ // Add a workbook

	try
	{
		m_pXL->Workbooks->Add((long)Excel::xlWorksheet);
	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

void ExcelDriver::FillRange(double ll, double ul, double steps, int row)
{ // Fill the range values in the active sheet

	int counter;
	double ss=(ul-ll)/steps;	// Step size

	try
	{
		// Retrieve the active sheet and its range object
		Excel::_WorksheetPtr pSheet=m_pXL->ActiveSheet;
		Excel::RangePtr pRange=pSheet->Cells;

		// Fill the range. 10 steps is 11 values. 
		// Start at column 2 since column 1 will be used for series text.
		for (counter=0; counter<=steps; counter++)
		{
			((Excel::RangePtr)pRange->Item[(double)row][(double)(counter+2.0)])->Value=ll+counter*ss;
		}
	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

void ExcelDriver::CreateChart(int startRow, int rows, int columns, const std::string& chartTitle, const std::string& categoryTitle, const std::string& valueTitle)
{ // Create chart. This function assumes that the necessary data is already at the correct place in the active sheet

	Excel::AxisPtr pAxis;
	Excel::AxesPtr pAxes;

	try
	{
		// Determine the range to make a chart of
		Excel::_WorksheetPtr pSheet=m_pXL->ActiveSheet;
		Excel::RangePtr pBeginRange=pSheet->Cells->Item[(long)startRow][1.0];
		Excel::RangePtr pEndRange=pSheet->Cells->Item[(long)(startRow+rows)][(long)(columns+1)];
		Excel::RangePtr pTotalRange=pSheet->Range[(Excel::Range*)pBeginRange][(Excel::Range*)pEndRange];

		// Create the chart and sets its type
		Excel::_ChartPtr pChart=m_pXL->ActiveWorkbook->Charts->Add();
		pChart->Name=valueTitle.c_str();
		pChart->ChartWizard((Excel::Range*)pTotalRange, (long)Excel::xlXYScatter, 6L, (long)Excel::xlRows, 1L, 1L, true, chartTitle.c_str(), categoryTitle.c_str(), valueTitle.c_str());
		pChart->ApplyCustomType(Excel::xlXYScatterSmooth);

		// Make all titles visible again. They were erased by the ApplyCustomType method
		pChart->HasTitle=true;
		pChart->ChartTitle->Text=chartTitle.c_str();

		pAxis=pChart->Axes((long)Excel::xlValue, Excel::xlPrimary);
		pAxis->HasTitle=true;
		pAxis->AxisTitle->Text=valueTitle.c_str();
		
		pAxis=pChart->Axes((long)Excel::xlCategory, Excel::xlPrimary);
		pAxis->HasTitle=true;
		pAxis->AxisTitle->Text=categoryTitle.c_str();

		// Disable legend for now, because there is only 1 'line' in each diagram.
		// Besides this, the legend showed 2 subjects instead of 1 and I don't
		// know what to do about it now. - MB
		pChart->HasLegend = false;
	}
	catch(_com_error&)
	{ // For now ignore error
	}
}

void ExcelDriver::SetActiveSheet(const std::string& name)
{ // Make a sheet active

	Excel::_WorkbookPtr pWorkbook=m_pXL->ActiveWorkbook;
	Excel::_WorksheetPtr pWorksheet=pWorkbook->Worksheets->GetItem(name.c_str());
	pWorksheet->Activate();
}

void ExcelDriver::SetActiveChart(const std::string& name)
{ // Make a chart active

	Excel::_WorkbookPtr pWorkbook=m_pXL->ActiveWorkbook;
	Excel::_ChartPtr pChart=pWorkbook->Charts->GetItem(name.c_str());
	pChart->Activate();
}

// Operators
ExcelDriver& ExcelDriver::operator = (const ExcelDriver& source)
{ // Assignment operator

	return *this;
}