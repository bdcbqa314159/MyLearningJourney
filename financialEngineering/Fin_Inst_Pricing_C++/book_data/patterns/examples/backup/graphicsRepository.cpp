// graphicsRepository.cpp
//
// Class that allows us to display values of functions in some
// medium.
//
// This class uses a Visitor for the display functionality. The 
// results are displayed in some medium (that we implement as a 
// Strategy).
//
// Last modification dates;
//
//	2003-9-13 DD kick-off
//
//
// (C) Datasim Education BV 2003

#ifndef GraphicsRepository_cpp
#define GraphicsRepository_cpp



#include "range.cpp"
#include "graphicsrepository.hpp"
#include "arraymechanisms.cpp"

#include <string>
#include <iostream>

using namespace std;

#include "graphicsrepositoryvisitor.hpp"

Vector<double, int> functionValues (double (*f)(double x), Range<double> range, int numSteps)
{ 
	
	Vector<double, int> myMesh = range.mesh(numSteps);

	Vector<double, int> result(myMesh.Size(), myMesh.MinIndex());
	

	for (int i = result.MinIndex(); i <= result.MaxIndex(); i++)
	{

		result[i] = (*f)(myMesh[i]);
	}

	return result;

	cout << "debug ";
	print (result);
}

GraphicsRepository::GraphicsRepository(double (*fp)(double x), const Range<double>& myRange, int numberSteps)
{
		title = "Graph of function";
		hAxis = "XAXIS";
		vAxis = "YAXIS";

		nSteps = numberSteps;
		interval = myRange;
		f = fp;

		array = functionValues(f, interval, nSteps);
	
}

// Choosing a new function
void GraphicsRepository::function(double (*fp)(double x)) 
{
		f = fp; 
}

void GraphicsRepository::range (const Range<double>& myRange)
{
		interval = myRange;
}
	

string GraphicsRepository::Title() const 
{
	return title;
}
	
string GraphicsRepository::XAxisTitle() const 
{
		return hAxis;
}

string GraphicsRepository::YAxisTitle() const 
{
		return vAxis;
}

Range<double>& GraphicsRepository::getInterval() 
{
		return interval;
}

int GraphicsRepository::numberSteps() 
{
		return nSteps;
}

Vector<double, int> GraphicsRepository::graphValue() const 
{
		return array;
}

void GraphicsRepository::accept(GraphicsRepositoryVisitor& v)
{ // Extending functionality (Visitor)

		// Dispatch the Visitor sub-contractor. JIT 
		// creation of the vector of values!

		array = functionValues(f, interval, nSteps);

		v.visit(*this);
}



#endif

