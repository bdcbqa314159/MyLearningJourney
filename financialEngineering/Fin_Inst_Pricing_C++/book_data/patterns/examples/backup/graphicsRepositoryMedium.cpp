// graphicsRepositoryMedium.cpp
//
// Class that allows us to display values of functions in some
// medium.
//
// This class uses a Visitor for the display functionality. The 
// results are displayed in some medium (that we implement as a 
// Strategy).
//
// (C) Datasim Education BV 2003

#ifndef GraphicsRepositoryMedium_cpp
#define GraphicsRepositoryMedium_cpp



#include "GraphicsRepositoryMedium.hpp"
#include "vector.cpp"
#include "BasicExcelPresentation.hpp"
#include "arraymechanisms.cpp"	

#include <string>
using namespace std;




////////////////////////// Hardware Display Strategies //////////////////////////////////////////



GraphicsMedium::GraphicsMedium()
{
	
}


ExcelGraphicsMedium::ExcelGraphicsMedium() 
{
	
}

void ExcelGraphicsMedium::display (GraphicsRepository& grObject)
{ // Display the graph in Excel. An extreme form of Information
  // Hiding.


	// 1. Create the Excel Driver object
	// 2. Build and display Excel chart


	Range<double> range = grObject.getInterval();
	Vector<double, int> xArr = range.mesh(grObject.numberSteps());

		
	Present(xArr, grObject.graphValue(), grObject.Title(), grObject.Title());

}

DebugGraphicsMedium::DebugGraphicsMedium() 
{
	
}

void DebugGraphicsMedium::display (GraphicsRepository& grObject)
{ // Display the graph in user screen. An extreme form of Information
  // Hiding.


	// 1. Create the Excel Driver object
	// 2. Build and display Excel chart


	Range<double> range = grObject.getInterval();
	Vector<double, int> xArr = range.mesh(grObject.numberSteps());

		
	print(xArr);
	print(grObject.graphValue());

}

#endif

