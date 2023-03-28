// simpleHeatEquation.cpp
//
// This is a program to solve the heat equation on 
// the interval (0, L) with zero Dirichlet boundary
// conditions and an arbitrary initial condition f(x).
//
// The main purpose of this program is to help us see 
// how the following functionality works:
//
//	1. Function mechanisms that map continuous functions 
//	to discrete vectors and matrices.
//	2. New higher level ways of manipulations on vectors
//
// This program also MOTIVATIVES how to set up FDM (albeit 
// with an explicit method) in an easy to follow sequence 
// of steps. When working, you can convert it to nice OO stuff.
//
// This program can be seen as a test of the function mechanisms.
//
// (C) Datasim Education BV 2003-2004

#include "functionmechanisms.cpp"
#include "arraymechanisms.cpp"
#include "commonutilities.cpp"
#include "range.cpp"

#include <list>
#include <string>
using namespace std;

#include "exceldriver.hpp"

///// Group for functions in CONTINUOUS PROBLEM //////
double BCL(double t)
{ // Left boundary condition

	return 0.0;
}

double BCR(double t)
{ // Right boundary condition

	return 0.0;
}

double IC(double x)
{ // Initial condition

	/*
	if (x >= 0.0 && x <= 0.5)
		return 2.0*x;
	

	return 2.0 * (1.0 - x);

	*/

	return x*(1.0 - x);

}

double diffusion(double x, double t)
{ // Coefficient of the second derivative in x

	return 1.0;
}
////////////////////////////////////////////////////////////


///// Simple MESH GENERATOR ////////

// Mesh generation part on a region [0,L] X [0,T]
void createMesh(double L, double T, int NX, int NT, 
				Vector<double, int>& XARR, Vector<double, int>& TARR)
{
	
	Range<double> r1(0.0, L);
	Range<double> r2(0.0, T);

	// These arrays have length NX+1 and NT+1 and they are defined
	// with their extrema values on closed intervals [0,L]X[0,T]
	XARR = r1.mesh(NX);
	TARR = r2.mesh(NT);

}

//////////////////////////////////////////////////////////////////

///// OUTPUT MECHANISMS ///////////////////

// Printing in Excel
void printInExcel(const Vector<double, int>& x,							// X array
					const list<string>& labels,							// Names of each vector
					const list<Vector<double, int> >& functionResult)	// The list of Y values
{ // Print a list of Vectors in Excel. Each vector is the output of
  // a finite difference scheme for a scalar IVP

	cout << "Starting Excel\n";

	ExcelDriver & excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!


	// Don't make the string names too long!!
	excel.CreateChart(x, labels, functionResult, string("Heat Equation in 1d"),
						string("Distance"), string ("Temperature"));


}

////////////////////////////////////////////////////

int main()
{
	// Input
	//	1. All continuous functions and parameters
	//	2. Discrete: number of interval in x and t directions

	// The continuous REGION of interest
	double L = 1.0;
	double T = 1.0;

	int NX = 10;
	int NT = 1000.0;		// Needed for stability of explicit scheme


	// MESH GENERATION stuff
	Vector<double, int> XARR;
	Vector<double, int> TARR;

	createMesh(L, T, NX, NT, XARR, TARR);

	double h = (L - 0.0)/double(NX);
	double k = (T - 0.0)/double(NT);

	cout << "k, h" << k << ", " << h;

	double t = 0.0;	// Current time level

	// The SOLUTION Vectors

	// All kinds of vectors
	Vector<double, int> uPrevious = createDiscreteFunction(IC, XARR);
	Vector<double, int> uNext(uPrevious.Size(), uPrevious.MinIndex());

	// Lists for Excel presentation 
	list<string> labels;						// Names of each vector
	list<Vector<double, int> > profile;			// The list of Y values

	labels.push_back(convertToString(t));
	profile.push_back(uPrevious);
	// End of Excel presentation stuff

	// Calculate coefficient array at current time level (semi-discrete)
	// For more general parabolic equations we shall need more vectors
	// (e.g. convection, free and RHS terms) (as with BS, for example)
	Vector<double, int> coeffARR = createDiscreteFunction(diffusion, XARR, t); 

	//print (coeffARR);

	double tmp;
	double STOPPINGTIME = 0.005;

	// THE BASIC LOOPING ALGORITHM

	L1:		// A label, not OO sorry but it works
	
	// Calculate at level n+1 

	uNext[uNext.MinIndex()] = BCL(0.0);
	uNext[uNext.MaxIndex()] = BCR(L);

	for (int j = uNext.MinIndex() + 1; j <= uNext.MaxIndex() - 1; j++)
	{
		tmp = (k* coeffARR[j]) / (h*h);
	
		uNext[j] = (tmp * uPrevious[j+1]) 
						
					+ ((1.0 - 2.0*tmp) * uPrevious[j])

					+ (tmp * uPrevious[j-1]);
	}

	print (uNext);
	
	t += k;
	labels.push_back(convertToString(t));
	profile.push_back(uNext);

	uPrevious = uNext;

	if (t < STOPPINGTIME) goto L1;

///////////////////////////////////////////////////////////

	// Now send the list of vectors to Excel

	printInExcel(XARR, labels, profile);

	return 0;
}
