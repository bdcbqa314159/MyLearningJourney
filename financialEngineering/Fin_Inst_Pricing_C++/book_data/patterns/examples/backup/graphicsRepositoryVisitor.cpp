// graphicsRepositoryVistor.cpp
//
// Class that allows us to display values of functions in some
// medium.
//
// This class uses a Visitor for the display functionality. The 
// results are displayed in some medium (that we implement as a 
// Strategy).
//
// (C) Datasim Education BV 2003

#ifndef GraphicsRepositoryVisitor_cpp
#define GraphicsRepositoryVisitor_cpp



#include "GraphicsRepositoryVisitor.hpp"

#include "GraphicsRepositoryMedium.hpp"


////////////////////////// Visitors //////////////////////////////////////////

GraphicsRepositoryVisitor::GraphicsRepositoryVisitor(GraphicsMedium& myMedium) 
{

	gm = &myMedium;
}

DisplayRepositoryVisitor::DisplayRepositoryVisitor(GraphicsMedium& myMedium) : GraphicsRepositoryVisitor (myMedium)
{

}

void DisplayRepositoryVisitor::visit(GraphicsRepository& grObject)
{ // This is where we delegate to the hardware medium

	gm -> display (grObject);

	// Another design decision is to send the 'parts' of the graphical object
	// to the medium
}




#endif

