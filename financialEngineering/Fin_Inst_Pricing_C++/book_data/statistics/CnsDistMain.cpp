// CnsDistMain.cpp
//
// Test program for basic shape hierarchy
//
// (C) Datasim Education BV 1998-2003

#include "probdist.cxx"
#include "cnsdist.cxx"
#include "unifdist.cxx"
#include "gammdist.cxx"
#include "expodist.cxx"

#include <string>
using namespace std;

// The student has to make this class
#include "CommandFactory.hpp" // Create continuous distributions from comand line
#include "DDCommandFactory.hpp" // Create continuous distributions from comand line


void print(const string& type, const ContinuousDistribution<double, double>& dis, double x)
{
	cout << "\n ****************** Distribution type: " << type << endl;
	cout << "Mean value: " << dis.expected() << " Variance: " << dis.variance() << endl;
	cout << "pdf: " << dis.pdf(x) << " cdf: " << dis.cdf(x) << endl;
}


CnsDistFactory* CreateFactory()
{
	// Normally you would have to make a choice which factory
	// to instantiate, for example in a GUI radio button box

	cout << "1. Command, 2. DD\n";
	int k;
	cin >> k;
	if (k == 1)
		return new CommandFactory();

	if (k == 2)
		return new DDCommandFactory();



}

void main()
{
	CnsDistFactory* Factory;

	Factory = CreateFactory();

	ContinuousDistribution<double, double>* d1;
	ContinuousDistribution<double, double>* d2;
	ContinuousDistribution<double, double>* d3;


	d1 = Factory->CreateUniform();
	d2 = Factory->CreateGamma();
	d3 = Factory->CreateExponential();

	double x = 3.0;
/*
	cout << (*d1).pdf(x) << (*d1).cdf(x) << endl;
	cout << (*d2).pdf(x) << (*d2).cdf(x) << endl;
	cout << (*d3).pdf(x) << (*d3).cdf(x) << endl;
*/


	print (string("Uniform"), *d1, x);
	print (string("Gamma"), *d2, x);
	print (string("Exponential"), *d3, x);


	delete d1;
	delete d2;
	delete d3;

	delete Factory;
}
