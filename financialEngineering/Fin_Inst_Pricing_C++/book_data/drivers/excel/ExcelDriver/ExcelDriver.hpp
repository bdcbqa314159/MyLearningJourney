// ExcelDriver.hpp
//
// Class that enables us to send output to Excel
//
// (C) Datasim Component Technology 2000

#ifndef ExcelDriver_hpp
#define ExcelDriver_hpp

#include "imports.hpp"

#include "NumericMatrix.hpp"

class ExcelDriver
{
private:
	Excel::_ApplicationPtr m_pXL;

public:
	// Constructors & destructor
	ExcelDriver();
	ExcelDriver(const ExcelDriver& source);
	virtual ~ExcelDriver();

	// Selectors
	Excel::_ApplicationPtr Application() const;

	// Modifiers

	// Operations
	void OpenExcel();
	void CloseExcel();
	void AddWorkbook();
	void FillRange(double ll, double ul, double steps, int row);
	void CreateChart(int startRow, int rows, int columns, const std::string& chartTitle, const std::string& categoryTitle, const std::string& valueTitle);

	void SetActiveSheet(const std::string& name);
	void SetActiveChart(const std::string& name);

	// Operators
	ExcelDriver& operator = (const ExcelDriver& source);
};


#endif
