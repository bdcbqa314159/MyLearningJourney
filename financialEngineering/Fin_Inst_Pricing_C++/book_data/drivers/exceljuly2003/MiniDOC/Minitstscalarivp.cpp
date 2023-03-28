// tstscalarivp.cpp
//
// Testing Scalar IVP schmes. Output in Excel.
//
// (C) Datasim Education BV 2003
//

#include "ivpsolver.cpp"
#include "vector.cpp"
#include "arraymechanisms.cpp"
#include <math.h>
#include <list>
#include <string>
#include <iostream>
using namespace std;

#include "exceldriver.hpp"

void printOneExcel(const Vector<double, int> & x,						
					const Vector<double, int>& functionResult,
					const string& title)
{ 
	// N.B. Excel has a limit of 8 charts; after that you get a run-time error

	cout << "Starting Excel\n";

	ExcelDriver & excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!

	excel.CreateChart(x, functionResult, title, "X", "Y");

	
}

	
void printInExcel(const Vector<double, int>& x,							// X array
					const list<string>& labels,							// Names of each vector
					const list<Vector<double, int> >& functionResult)	// The list of Y values
{ // Print a list of Vectors in Excel. Each vector is the output of
  // a finite difference scheme for a scalar IVP

	cout << "Starting Excel\n";

	ExcelDriver & excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!


	// Don't make the string names too long!!
	excel.CreateChart(x, labels, functionResult, string("FDM Scalar IVP"),
						string("Time Axis"), string ("Value"));


}





double RHS(const double& d)
{
	return ::sin(d);
}

double a(const double& d)
{
	return 5.0;
}



int main()
{
	// The continuous problem
	Range<double> r(0.0, 1.0);
	ScalarIVP<double> ivp1(r, 1.0);
	ivp1.Rhs(RHS);
	ivp1.Coeff(a);

	int N;
	cout << "Number of Steps: ";
	cin >> N;


	// Stuff for Excel output
	Vector<double, int> x = r.mesh(N);				// Length N+1, start index 1
	print(x);
	list<string> labels;							// Names of each vector
	list<Vector<double, int> > functionResult;		// The list of Y values

	ScalarIVPSolver<double, int> ivpSol(ivp1, EEuler);		// Explicit Euler
	ivpSol.steps(N);

	labels.push_back("EEuler");
	Vector<double, int> res = ivpSol.result();		// Length N+1, start index 1
	functionResult.push_back(res);



	ivpSol.setType(Fitted);
	labels.push_back(string("Fitted"));
	res = ivpSol.result();
	functionResult.push_back(res);


	ivpSol.setType(IEuler);
	labels.push_back(string("IEuler"));

	res = ivpSol.result();
	functionResult.push_back(res);

	ivpSol.setType(PC);
	labels.push_back(string("PredCorr"));

	res = ivpSol.result();
	functionResult.push_back(res);

	printInExcel(x, labels, functionResult);

	int j;
	cin >> j;

	return 0;
}
