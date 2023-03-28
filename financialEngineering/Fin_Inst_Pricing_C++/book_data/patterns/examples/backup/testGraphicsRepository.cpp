// testGraphicsRepository.hpp
//
// Test program for ...
//
// Class that allows us to display values of functions in some
// medium.
//
// This class uses a Visitor for the display functionality. The 
// results are displayed in some medium (that we implement as a 
// Strategy).
//
// (C) Datasim Education BV 2003
//
//

#include <math.h>
#include <iostream>
#include "graphicsrepositorymedium.hpp"

double func(double x)
{

	return 1.0/(x + 0.01);
}


int main()
{

	GraphicsRepository myRep(func, Range<double> (-4.0, 4.0));
//	myRep.range(Range<double> (-2.0, 3.0));

	// Define the current graphics medium
	GraphicsMedium* myMedium = new ExcelGraphicsMedium;
	GraphicsMedium* myMedium2 = new DebugGraphicsMedium;

	// Define current visitor 
	GraphicsRepositoryVisitor* myVis = new DisplayRepositoryVisitor(*myMedium);


	cout << "Now displaying ...";

	// Now display the current graphics object on the current medium
	myVis -> visit(myRep);

	delete myMedium;
	delete myMedium2;
	delete myVis;

	return 0;
}

