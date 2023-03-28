// Implementation of Registration activity.
//
// Datasim Education BV (c) 2003
// 
// Modification dates:
// 23 July 2003 - MB started.

#include <iostream>
#include <string>
using namespace std;

// Office 2000 - local typelibraries. These must be in loacl library ???
#import "mso9.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL") 
#import "vbe6ext.olb" no_namespace rename("Property", "PropertyVB") 
#import "Excel9.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL")  no_dual_interfaces

// Throw COM error as string.
string GetString( _com_error & error )
{
	bstr_t description = error.Description();
	if( !description )
	{
		description = error.ErrorMessage();
	}
	return string(description);
}

// Initialize A, B and N with values from user.
void GetInput(double & A, double & B, int & N)
{
	try
	{
		CoInitialize(NULL);

        // Start Excel, open work book and open sheet.
		Excel::_ApplicationPtr xl;
		xl.CreateInstance(L"Excel.Application");
		Excel::_WorkbookPtr pWorkbook = xl->Workbooks->Open(L"C:\\test.xls");
		Excel::_WorksheetPtr pSheet = pWorkbook->Worksheets->GetItem("Data");

		// Get cells.
		Excel::RangePtr pRange= pSheet->Cells;

		// Get A, B and N values.
		long one = 1; long two = 2; long t = 3;
		A = pRange->Item[one][two];
		B = pRange->Item[two][two];
	//	N = pRange->Item[t][two];
	
		CoUninitialize();
	}
	catch( _com_error & error )
	{
		cout << GetString(error) << endl;
	}
}
