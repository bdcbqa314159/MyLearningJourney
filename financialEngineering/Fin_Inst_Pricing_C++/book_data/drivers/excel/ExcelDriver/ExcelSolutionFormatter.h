#ifndef ExcelSolutionFormatter_h
#define ExcelSolutionFormatter_h

#include "SolutionFormatter.h"

// Formats solution in Excel.
class ExcelSolutionFormatter : public SolutionFormatter
{
public:
	// Format solution in MS excel.
	void Format( const TStandardPropertySet & option, const TStandardPropertySet & solution ) const;
};

#endif // ExcelSolutionFormatter_h