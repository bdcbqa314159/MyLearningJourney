// TestExcelDriver.cpp
//
// Testing Excel output functionality
//
// (C) Datasim Education BV 2003

#include "exceldriver.hpp"

int main()
{

		// Initialise COM Runtime
		CoInitialize(NULL);

		ExcelDriver myFirst;

		myFirst.OpenExcel();

		myFirst.AddWorkbook();
		myFirst.SetActiveSheet("Daniel");
		double ll = 0.0;
		double ul = 100;
		double steps = 10;
		int row = 3;
		myFirst.FillRange(ll, ul, steps, row);

		myFirst.CreateChart(1, 10, 10, "hi", "cat", "value");
		
		CoUninitialize();

		return 0;
}