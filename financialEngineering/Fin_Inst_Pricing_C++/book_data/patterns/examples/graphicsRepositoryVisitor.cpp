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
#include "arraymechanisms.cpp"
#include "vector.cpp"
#include "range.cpp"

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
	// to the medium. Next version.
}

TransformRepositoryVisitor::TransformRepositoryVisitor(GraphicsMedium& myMedium) : GraphicsRepositoryVisitor (myMedium)
{

}

void TransformRepositoryVisitor::visit(GraphicsRepository& grObject)
{ // Calculate and send the results to Graphics medium

	list<double> myList;

	Vector<double, int> tmp = grObject.graphValue();

	double myMax = maxValue(tmp);
	double myMin = minValue(tmp);

	Range<double> range = grObject.getInterval();
	double myIntegral = sum(tmp) / range.spread();

	myList.push_back(myMax);
	myList.push_back(myMin);
	myList.push_back(myIntegral);

	gm -> display (myList);
}



#endif

