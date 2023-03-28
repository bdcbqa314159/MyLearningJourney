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

	return 1.0/(x + 0.0001);
}


int main()
{

	GraphicsRepository myRep(func, Range<double> (-4.0, 4.0));

	// Define the current graphics medium
	GraphicsMedium* myMedium = new ExcelGraphicsMedium;
	GraphicsMedium* myMedium2 = new DebugGraphicsMedium;

	// Define current visitor 
	GraphicsRepositoryVisitor* myVis = new DisplayRepositoryVisitor(*myMedium);
	GraphicsRepositoryVisitor* myVis2 = new DisplayRepositoryVisitor(*myMedium2);
	GraphicsRepositoryVisitor* myVis3 = new TransformRepositoryVisitor(*myMedium2);

	int k;
	cout << "Which output? 1) Console display 2) Numeric integral 3) Excel\n";
	cin >> k;


	if (k == 1)
		myVis2 -> visit(myRep);
	if (k == 2)
		myVis3 -> visit(myRep);
	if (k == 3) // ha ha! Excel
		myVis -> visit(myRep);

	// Clean up your rubbish
	delete myMedium;
	delete myMedium2;
	delete myVis;
	delete myVis2;
	delete myVis3;


	return 0;
}

