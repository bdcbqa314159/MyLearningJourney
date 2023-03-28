// CDOPrintVisitor.cpp
//
// Shape visitor that prints the shapes
//
// 4 november 1998	RD	Started
// 2004-1-28 DD for CDO
//
// (C) Datasim Education BV 1998

#include "CDOPrintVisitor.hpp"
#include "Common.hpp"

// Constructors and Destructor
CDOPrintVisitor::CDOPrintVisitor(): CDOVisitor()
{ // Default constructor
}

CDOPrintVisitor::CDOPrintVisitor(const CDOPrintVisitor& source): CDOVisitor(source)
{ // Copy constructor
}

CDOPrintVisitor::~CDOPrintVisitor()
{ // Destructor
}


// The visit functions
void CDOPrintVisitor::Visit(Option& p)
{ // Visit point

	cout << "Option \n";

	// Print all option stuff

	cout << "Option Price etc: " << p.Price() << endl;
	cout << "Option Price etc: " << p.Delta() << endl;


}


void CDOPrintVisitor::Visit(CDO& sc)
{ // Visit CDO composite

	// Since we must print information between shapes we cannot just call the base visitor function

	CDO::iterator it;

	std::cout<<"CDO(";
	// Send all shapes in the composite to the visitor
	for (it=sc.Begin(); it!=sc.End(); it++)
	{
		// Separate shapes with comma
		if (it!=sc.Begin()) std::cout<<", ";
		(*it)->Accept(*this);
	}

	std::cout<<")";
}



// Operators
CDOPrintVisitor& CDOPrintVisitor::operator = (const CDOPrintVisitor& source)
{ // Assignment

	// Exit if same object
	if (this==&source) return *this;

	// Call base assignment
	CDOVisitor::operator = (source);

	return *this;
}