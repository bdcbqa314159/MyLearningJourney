// Excel driver class.
//
// Datasim Education BV (c) 2003
// 
// Modification dates:
// 23 July 2003 - MB - Started.
// 29 July 2003 - MB - Added support for PropertySets.
//					 - Writing chart data in vertical direction.
//					 - Added Instance() method which returns an ExcelDriver singleton.

// Office 2000 - local typelibraries.
#import "mso9.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL") 
#import "vbe6ext.olb" no_namespace rename("Property", "PropertyVB") 
#import "Excel9.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL")  no_dual_interfaces

// STL list class.
#include <list>
using namespace std;

// Datasim container classes.
#include "Vector.cpp"
#include "NumericMatrix.cpp"
#include "SimplePropertySet.cpp"

// Excel driver class definition.
// Contains functionality to add charts and matrices.
// Hides all COM details. COM exceptions are re-thrown
// as STL strings.
class ExcelDriver
{
private:
	// Private member data.
	Excel::_ApplicationPtr xl;		// Pointer to Excel.
	long curDataColumn;				// Current column of 'Chart Data'

	// Writes label and vector to cells in horizontal direction.
	void ToSheetHorizontal( Excel::_WorksheetPtr sheet,
					long sheetRow, long sheetColumn,
					string label,
					const Vector<double, int> & values )
	{
		// Get cells.
		Excel::RangePtr pRange=sheet->Cells;
	
		// First cell contains the label.
		Excel::RangePtr item = pRange->Item[sheetRow][sheetColumn];
		item->Value = label.c_str();
		sheetColumn++;

		// Next cells contain the values.
		for(int i=values.MinIndex(); i <= values.MaxIndex(); i++)
		{
			Excel::RangePtr item = pRange->Item[sheetRow][sheetColumn];
			item->Value = values[i];			
			sheetColumn++;
		}
	}

	// Writes label and vector to cells in vertical direction.
	void ToSheetVertical( Excel::_WorksheetPtr sheet,
					long sheetRow, long sheetColumn,
					string label,
					const Vector<double, int> & values )
	{
		// Get cells.
		Excel::RangePtr pRange=sheet->Cells;
	
		// First cell contains the label.
		Excel::RangePtr item = pRange->Item[sheetRow][sheetColumn];
		item->Value = label.c_str();
		sheetRow++;

		// Next cells contain the values.
		for(int i=values.MinIndex(); i <= values.MaxIndex(); i++)
		{
			Excel::RangePtr item = pRange->Item[sheetRow][sheetColumn];
			item->Value = values[i];			
			sheetRow++;
		}
	}

	// Throw COM error as string.
	void ExcelDriver::ThrowAsString( _com_error & error )
	{
		bstr_t description = error.Description();
		if( !description )
		{
			description = error.ErrorMessage();
		}
		throw string(description);
	}

	// Returns row from matrix as vector.
	Vector <double, int> createVector(const Matrix<double,int>& mat, int row)
	{
		int nCols = mat.Columns();

		Vector<double, int> result (nCols, mat.MinColumnIndex());
		for (int i = mat.MinColumnIndex(); i <= mat.MaxColumnIndex(); i++)
		{
			result[i] = mat(row, i);
		}

		return result;
	}

public:
	// Constructor. Starts Excel in invisible mode.
	ExcelDriver()
		: curDataColumn(1)
	{
		try
		{
			// Initialize COM Runtime Libraries.
			CoInitialize(NULL);

			// Start excel application.
			xl.CreateInstance(L"Excel.Application");
			xl->Workbooks->Add(Excel::xlWorksheet);

			// Rename "Sheet1" to "Chart Data".
			Excel::_WorkbookPtr pWorkbook = xl->ActiveWorkbook;
			Excel::_WorksheetPtr pSheet = pWorkbook->Worksheets->GetItem("Sheet1");
			pSheet->Name = "Chart Data";
		}
		catch( _com_error & error )
		{
			ThrowAsString(error);
		}
	}

	// Destructor.
	virtual ~ExcelDriver()
	{
		// Undo initialization of COM Runtime Libraries.
		CoUninitialize();
	}

	// Access to single, shared instance of ExcelDriver (singleton).
	static ExcelDriver & Instance()
	{
		static ExcelDriver singleton;
		return singleton;
	}

	// Create chart with a number of functions. The arguments are:
	//  x:			vector with input values
	//  labels:		labels for output values
	//  vectorList: list of vectors with output values.
	//  chartTitle:	title of chart
	//  xTitle:		label of x axis
	//  yTitle:		label of y axis
	void CreateChart(const Vector<double, int> & x, const list<string> & labels, const list<Vector<double, int> > & vectorList, 
					const std::string& chartTitle, const std::string& xTitle = "X", const std::string& yTitle = "Y")
	{
		try
		{
			// Check # labels vs. # vectors.
			if( labels.size() != vectorList.size() )
			{
				throw "Number of labels must equal number of vectors.";
			}

			// Activate sheet with numbers.
			Excel::_WorkbookPtr pWorkbook = xl->ActiveWorkbook;
			Excel::_WorksheetPtr pSheet = pWorkbook->Worksheets->GetItem("Chart Data");
			
			// Calculate range with source data.
			// The first row contains the labels shown in the chart's legend.
			long beginRow = 1;
			long beginColumn = curDataColumn;
			long endRow = x.Size() + 1;								// +1 to include labels.
			long endColumn = beginColumn + vectorList.size();		// 1st is input, rest is output.

			// Write label + input values to cells in vertical direction.
			ToSheetVertical(pSheet, 1, curDataColumn, xTitle, x);		// X values.
			curDataColumn++;

			// Write label + output values to cells in vertical direction.
			list<Vector<double, int> >::const_iterator vectorIt;
			list<string>::const_iterator labelIt = labels.begin();
			for( vectorIt = vectorList.begin(); vectorIt != vectorList.end(); vectorIt++ )
			{
				// Get label and row index.
				string label = *labelIt;
				
				// Add label + output values to Excel.
				ToSheetVertical(pSheet, 1, curDataColumn, label, *vectorIt);

				// Advance row and label.
				curDataColumn++;
				labelIt++;
			}			
			
			// Create range objects for source data.
			Excel::RangePtr pBeginRange = pSheet->Cells->Item[beginRow][beginColumn];
			Excel::RangePtr pEndRange = pSheet->Cells->Item[endRow][endColumn];
			Excel::RangePtr pTotalRange = pSheet->Range[(Excel::Range*)pBeginRange][(Excel::Range*)pEndRange];
			
			// Create the chart and sets its type
			Excel::_ChartPtr pChart=xl->ActiveWorkbook->Charts->Add();
			pChart->ChartWizard((Excel::Range*)pTotalRange, (long)Excel::xlXYScatter, 6L, (long)Excel::xlColumns, 1L, 1L, true, chartTitle.c_str(), xTitle.c_str(), yTitle.c_str());
			pChart->ApplyCustomType(Excel::xlXYScatterSmooth);
			pChart->Name = chartTitle.c_str();

			// Make all titles visible again. They were erased by the ApplyCustomType method.
			pChart->HasTitle=true;
			pChart->ChartTitle->Text=chartTitle.c_str();

			Excel::AxisPtr pAxis = pChart->Axes((long)Excel::xlValue, Excel::xlPrimary);
			pAxis->HasTitle = true;
			pAxis->AxisTitle->Text = yTitle.c_str();
			
			pAxis=pChart->Axes((long)Excel::xlCategory, Excel::xlPrimary);
			pAxis->HasTitle = true;
			pAxis->AxisTitle->Text = xTitle.c_str();

			// Add extra row space to make sheet more readable.
			curDataColumn++;
		}
		catch( _com_error & error )
		{
			ThrowAsString(error);
		}
	}

    // Create chart with a number of functions. The arguments are:
	//  x:			vector with input values
	//  y:			vector with output values.
	//  chartTitle:	title of chart
	//  xTitle:		label of x axis
	//  yTitle:		label of y axis
	void CreateChart(const Vector<double, int> & x, const Vector<double, int> & y, const std::string& chartTitle, const std::string& xTitle = "X", const std::string& yTitle = "Y")
	{ 
		// Create list with single function and single label.
		list<Vector<double, int> > functions;
		list<string> labels;
		functions.push_back(y);
		labels.push_back(chartTitle);
		CreateChart(x, labels, functions, chartTitle, xTitle, yTitle);
	}

	// Add Matrix to the spreadsheet with row and column labels.
	void AddMatrix(string name, const NumericMatrix<double, int> & matrix, const list<string> & rowLabels, const list<string> & columnLabels)
	{
		// Check label count vs. matrix.
		if( matrix.Columns() != columnLabels.size() )
		{
			throw "Count mismatch between # matrix columns and # column labels";
		}
		if( matrix.Rows() != rowLabels.size() )
		{
			throw "Count mismatch between # matrix rows and # row labels";
		}

		// Add sheet.
		Excel::_WorkbookPtr pWorkbook = xl->ActiveWorkbook;
		Excel::_WorksheetPtr pSheet = pWorkbook->Worksheets->Add();
		pSheet->Name = name.c_str();

		// Current indeces in spreadsheet.
		long sheetRow = 1;
		long sheetColumn = 1;
				
		// Add column labels starting at column 2.
		sheetColumn = 2;
		Excel::RangePtr pRange=pSheet->Cells;
		list<string>::const_iterator columnLabelIt;
		for(columnLabelIt = columnLabels.begin(); columnLabelIt != columnLabels.end(); columnLabelIt++)
		{
			Excel::RangePtr item = pRange->Item[sheetRow][sheetColumn];
			item->Value = columnLabelIt->c_str();
			sheetColumn++;
		}

		// Add row labels + values.
		sheetColumn = 1;
		sheetRow = 2;
		list<string>::const_iterator rowLabelIt = rowLabels.begin();
		for( int r = matrix.MinRowIndex(); r <= matrix.MaxRowIndex(); r++ )
		{
			Vector<double, int>	row = createVector(matrix, r);
			ToSheetHorizontal(pSheet, sheetRow, sheetColumn, *rowLabelIt, row);
			rowLabelIt++;
			sheetRow++;
		}
	}

	// Add PropertySet.
	void AddPropertySet(const SimplePropertySet<string, double> & pset)
	{
		// Add sheet.
		Excel::_WorkbookPtr pWorkbook = xl->ActiveWorkbook;
		Excel::_WorksheetPtr pSheet = pWorkbook->Worksheets->Add();
		pSheet->Name = L"Input";

		// Add properties to cells.
		Excel::RangePtr pRange = pSheet->Cells;
		long row = 1;
		for(SimplePropertySet<string, double>::const_iterator it = pset.Begin(); it != pset.End(); ++it, ++row)
		{
			// Set name and value.
			pRange->Item[row][(long)1] = it->name().c_str();
			pRange->Item[row][(long)2] = (*it) ();
		}
	}

	// Get PropertySet. Reads all properties from top to bottom.
	// The properties must be present in the given property set.
	void GetPropertySet(SimplePropertySet<string, double> & pset)
	{
		// Get input sheet.
		Excel::_WorkbookPtr pWorkbook = xl->ActiveWorkbook;
		Excel::_WorksheetPtr pSheet = pWorkbook->Worksheets->GetItem("Input");
		
		// Get values from cells.
		Excel::RangePtr pRange = pSheet->Cells;
		long row = 1;
		while(true)
		{
			// Get name from first column.
			_bstr_t bstrName = pRange->Item[row][1];
			string name = bstrName;
			if( name != "" )
			{
				// Get value from second column.
				double value = (double)pRange->Item[row][2];
				pset.set(name, value);
			}
			else
			{
				break;
			}
			++row;
		}
	}

	// Make Excel window visible.
	void MakeVisible( bool b = true )
	{
		// Make excel visible.
		xl->Visible = b ? VARIANT_TRUE : VARIANT_FALSE;
	}
};