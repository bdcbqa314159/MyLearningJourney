// CnsDistGammaMain.cpp
//
// Test program for basic distribution hierarchy. Gamma onlu
//
// (C) Datasim Education BV 1998-2003

#include "probdist.cxx"
#include "cnsdist.cxx"
#include "gammdist.cxx"

#include <string>
using namespace std;

// The student has to make this class
#include "CommandFactory.hpp" // Create continuous distributions from comand line


void print(const ContinuousDistribution<double, double>& dis)
{
	cout << "Mean value: " << dis.expected() << " Variance: " << dis.variance() << endl;
}


CnsDistFactory* CreateFactory()
{
	// Normally you would have to make a choice which factory
	// to instantiate, for example in a GUI radio button box
	// This is the function whetre the real choice is made.

	return new CommandFactory();
}

void main()
{
	// Create the current factory
	CnsDistFactory* myFactory = CreateFactory();

	// Pointer to current continuous distribution
	ContinuousDistribution<double, double>* myDist;

	myDist = myFactory->CreateGamma();

	
	print (*myDist); // We have no knowledge of derived classes!


	delete myDist;

	delete myFactory;
}
