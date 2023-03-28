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

	
void printInExcel(const Vector<double, int>& x,						// X array
					const list<string>& labels,							// Names of each vector
					const list<Vector<double, int> >& functionResult)	// The list of Y values
{ // Print a list of Vectors in Excel. Each vector is the output of
  // a finite difference scheme for a scalar IVP

	cout << "Starting Excel\n";

	ExcelDriver & excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!


	
	excel.CreateChart(x, labels, functionResult, string("FDM Scalar IVP"),
						string("Time Axis"), string ("Value"));

	// Don't make the string names too long!!
//	excel.CreateChart(x, labels, functionResult, "Benchmark FDM", "Time", "FDM Value");


}





/////////////////////////////////////////////////////////////////////////

double ufunc(const double& t)
{
	return t;
}

double myfunc(const double& x, double (*F)(const double& t))
{ // Simulate a nonlinear term

	return (*F)(x) * (*F)(x);
		
}

double RHS(const double& d)
{
//	return ::sin(d);
	return 0.0;
}

double a(const double& d)
{
	return 10.0;
}

// Define special functions

double aEuropeanType(const double& t)
{

	if (t <= 0.5)
		return 0.0;

	return t - 0.5;

}



double aDigitalType(const double& t)
{

	if (t <= 0.5)
		return 0.0;

	return 1.0;
}

double aTurningPointType(const double& t)
{

	if (t < 0.5)
		return -1.0;

	return 1.0;

}

double EuropeanType(const double& t)
{

	if (t <= 0.5)
		return 1.0;

	double x = t - 0.5;
	return ::exp(-x*x*0.5);
}

double DigitalType(const double& t)
{

	if (t <= 0.5)
		return 1.0;

	double x = t - 0.5;
	return ::exp(-x);
}

const double TurningPointType(const double& t)
{

	if (t <= 0.5)
		return ::exp(t);

	return ::exp(-t);

}

int main()
{
	// The continuous problem
	Range<double> r(0.0, 1.0);
	ScalarIVP<double> ivp1(r, 1.0);
	ivp1.Rhs(RHS);
	ivp1.Coeff(a);

//	ivp1.Coeff(aEuropeanType);
//	ivp1.Coeff(aDigitalType);
//	ivp1.Coeff(aTurningPointType);
	
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

	labels.push_back("Explicit Euler");
	Vector<double, int> res = ivpSol.result();		// Length N+1, start index 1
	functionResult.push_back(res);
//	printOneExcel(x, res, "EEuler");


	Vector<double, int> exact(res);
	exact[exact.MinIndex()] = ivp1.startValue();
	
	for (int i = exact.MinIndex(); i <= exact.MaxIndex(); i++)
	{

		double fac = 10.0;
		exact[i] = ::exp(- fac * ivpSol.stepSize() * (i-1));  // a == 1
//		exact[i] = EuropeanType(ivpSol.stepSize() * (i-1)); 
//	    exact[i] = DigitalType(ivpSol.stepSize() * (i-1)); 
//		exact[i] = TurningPointType(ivpSol.stepSize() * (i-1)); 

	//	exact[i] = ::exp(- fac* pow(ivpSol.stepSize() * (i-1), 2) * 0.5);  // a == t
	}

	// Exact solution
	labels.push_back("Exact solution");
	functionResult.push_back(exact);

	ivpSol.setType(Box);
	labels.push_back("Box");
	res = ivpSol.result();
	functionResult.push_back(res);
	printOneExcel(x, res, "Box");
	
	//	print(res);
//	cout << "Error: " << ::max(res, exact) << endl<< endl;


	ivpSol.setType(Trap);
	cout << "Trapezoidal";
//	labels.push_back(string("Trapezoidal"));

	res = ivpSol.result();
	print(res);
//	functionResult.push_back(res);
//	printOneExcel(x, res, "Trap");

//	print(res);
	cout << "Error: " << ::maxValue(res, exact) << endl<< endl;


	ivpSol.setType(Fitted);
	cout << "Duffy fitted";
	labels.push_back(string("Duffy Fitted"));
	res = ivpSol.result();
	functionResult.push_back(res);
//	printOneExcel(x, res, "Duffy");


//	print(res);
	cout << "Error: " << ::maxValue(res, exact) << endl<< endl;


	ivpSol.setType(FittedBox);
	cout << "Fitted box scheme";
//	labels.push_back(string("Fitted box"));

	res = ivpSol.result();
//	functionResult.push_back(res);
//	printOneExcel(x, res, "Fitted Box");

//	print(res);
	cout << "Error: " << ::maxValue(res, exact) << endl<< endl;


	ivpSol.setType(Box);
	cout << "Box";
//	labels.push_back(string("Box"));

	res = ivpSol.result();
//	functionResult.push_back(res);
//	printOneExcel(x, res, "Box");

//	print(res);
	cout << "Error: " << ::maxValue(res, exact) << endl<< endl;


	ivpSol.setType(ExtrapEuler);
	cout << "Extrapolated Euler";
//	labels.push_back(string("Extrapolated Euler"));

	res = ivpSol.result();
//	functionResult.push_back(res);
//	printOneExcel(x, res, "Extrap Euler");

//	print(res);
	cout << "Error: " << ::maxValue(res, exact) << endl<< endl;


	ivpSol.setType(IEuler);
	cout << "Implicit Euler";
	labels.push_back(string("Implicit Euler"));

	res = ivpSol.result();
	functionResult.push_back(res);

//	printOneExcel(x, res, "IEuler");

//	print(res);
	cout << "Error: " << ::maxValue(res, exact) << endl<< endl;

	ivpSol.setType(PC);
	cout << "Predictor Corrector";
	labels.push_back(string("Predictor Corrector"));

	res = ivpSol.result();
	functionResult.push_back(res);
//	printOneExcel(x, res, "Pred Corr");

//	print(res);
//	cout << "Error: " << ::maxValue(res, exact) << endl<< endl;


	// Now stuff it all into Excel
//	printOneExcel(x, res, "EEuler");


	cout << "Size\n";
	cout << labels.size() << ", " << functionResult.size() << endl;

	printInExcel(x, labels, functionResult);

	int j;
	cin >> j;

	return 0;
}
