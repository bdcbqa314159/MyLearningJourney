// CDOVisitor.cpp
//
// Base class for all CDO visitors
//
// 16 september 1998	RD	Started
// 28 January 2004 DD For CF
// (C) Datasim Education BV 1998-2004

#include "CDOVisitor.hpp"

// Constructors and Destructor
CDOVisitor::CDOVisitor()
{ // Default constructor
}

CDOVisitor::CDOVisitor(const CDOVisitor& source)
{ // Copy constructor
}

CDOVisitor::~CDOVisitor()
{ // Destructor
}


void CDOVisitor::Visit(CDO& sc)
{ // Visit CDO composite
  // Override in subclasses to add extra behaviour

	CDO::iterator it;

	// Send all CDOs in the composite to the visitor
	for (it=sc.Begin(); it!=sc.End(); it++)
	{
		(*it)->Accept(*this);
	}
}


// Operators
CDOVisitor& CDOVisitor::operator = (const CDOVisitor& source)
{ // Assignment

	return *this;
}
