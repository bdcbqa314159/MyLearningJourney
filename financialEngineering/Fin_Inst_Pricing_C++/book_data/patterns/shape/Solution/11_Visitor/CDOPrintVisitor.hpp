// CDOPrintVisitor.hpp
//
// Shape visitor that prints the shapes
//
// (C) Datasim Education BV 1998

#ifndef CDOPrintVisitor_hpp
#define CDOPrintVisitor_hpp

#include "CDOVisitor.hpp"

class CDOPrintVisitor: public CDOVisitor
{
private:

public:
	// Constructors and Destructor
	CDOPrintVisitor();										// Default constructor
	CDOPrintVisitor(const CDOPrintVisitor& source);			// Copy constructor
	virtual ~CDOPrintVisitor();							// Destructor

	// The visit functions
	virtual void Visit(Option& p);						// Visit option
	virtual void Visit(CDO& p);							// Visit option
/*	virtual void Visit(Line& l);						// Visit line
	virtual void Visit(Circle& c);						// Visit circle
	virtual void Visit(ShapeComposite& sc);				// Visit shape composite
	virtual void Visit(NameDecorator& nd);				// Visit name decorator
*/
	// Operators
	CDOPrintVisitor& operator = (const CDOPrintVisitor& source);	// Assignment
};

#endif	// CDOPrintVisitor_hpp
