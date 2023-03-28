// numIntegrator.cpp
//
//
// Last modification dates;
//
//	2003-11-28 DD kick-off
//
//
// (C) Datasim Education BV 2004

#ifndef NumIntegrator_cpp
#define NumIntegrator_cpp



#include "range.cpp"
#include "NumIntegrator.hpp"
std;



NumIntegrator::NumIntegrator(double (*fp)(double x), const Range<double>& myRange, 
									IntegratorImp& implementor, int numberSteps)
{
		title = "Graph of function";
		hAxis = "XAXIS";
		vAxis = "YAXIS";

		nSteps = numberSteps;
		interval = myRange;
		f = fp;

		imp = &implementor;	
}

// Choosing a new function
void NumIntegrator::function(double (*fp)(double x)) 
{
		f = fp; 
}

void NumIntegrator::range (const Range<double>& myRange)
{
		interval = myRange;
}
	


Range<double>& NumIntegrator::getInterval() 
{
		return interval;
}

int NumIntegrator::numberSteps() 
{
		return nSteps;
}



double NumIntegrator::value()
{ // Get the approximate value of the integral

	
	return imp -> vakue(*this);
}



#endif

