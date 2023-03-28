// CDOVisitor.hpp
//
// Base class for all CDO visitors
//
// (C) Datasim Education BV 1998-2004

#ifndef CDOVisitor_hpp
#define CDOVisitor_hpp

#include "Option.hpp"
#include "CDO.hpp"

class CDOVisitor
{
private:
public:
	// Constructors and Destructor
	CDOVisitor();									// Default constructor
	CDOVisitor(const CDOVisitor& source);		// Copy constructor
	virtual ~CDOVisitor();						// Destructor

	// The visit functions
	virtual void Visit(Option& p) = 0;					// Visit option
	virtual void Visit(CDO& sc) = 0;			// Visit CDO composite

	// Operators
	CDOVisitor& operator = (const CDOVisitor& source);	// Assignment
};

#endif	// CDOVisitor_hpp
