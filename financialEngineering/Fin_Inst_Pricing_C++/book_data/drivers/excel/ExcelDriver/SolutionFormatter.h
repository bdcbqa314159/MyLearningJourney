#ifndef SolutionFormatter_h
#define SolutionFormatter_h

#include "StandardPropertySet.h"

// Interface for solution formatters.
class SolutionFormatter
{
public:
	// Format solution in some medium.
	virtual void Format( const TStandardPropertySet & option, const TStandardPropertySet & solution ) const = 0;
};

#endif // SolutionFormatter_h