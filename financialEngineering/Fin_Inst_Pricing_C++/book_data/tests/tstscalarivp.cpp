// tstscalarivp.cpp

#include "ivpsolver.cpp"
#include <math.h>
#include <iostream>
using namespace std;


///////////////////////////////////////////////////////////////////////
template <class V, class I> void print(const Vector<V,I>& v)
{
	
	cout << "\n\n[[Vector: size " << v.Size() << ", Min/Max indices: " << v.MinIndex() << ", " << v.MaxIndex() << endl;

	for (I j = v.MinIndex(); j <= v.MaxIndex(); j++)
	{
		cout << v[j] << ",";
	
	}

	cout << "]]\n";

}

template <class V, class I> void print2(const Vector<V,I>& v)
{
	
	for (I j = v.MinIndex(); j <= v.MaxIndex(); j++)
	{
		cout << fabs(v[j]) << ",";
	
	}
	
	cout << "\n";
	
}

template <class V, class I> V max(const Vector<V,I>& v1, const Vector<V,I>& v2)
{ // L infinity norm of the diference of two vectors

	Vector<V,I>& v3 = v1 - v2;
	cout << "Vector of differences\n";
	print2(v3);

	V res = fabs(v3[v3.MinIndex()]);

	for (I j = v3.MinIndex() + 1; j <= v3.MaxIndex(); j++)
	{
		if (fabs(v3[j]) > res)
			res = fabs(v3[j]);
	}

	return res;
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
	return d*d;
}

double a(const double& d)
{
	return 11.0;
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
	ScalarIVP<double> ivp1(Range<double>(0.0, 1.0), 1.0);

	ivp1.Rhs(RHS);
	ivp1.Coeff(a);
//	ivp1.Coeff(aEuropeanType);
//	ivp1.Coeff(aDigitalType);
//	ivp1.Coeff(aTurningPointType);
	
	// int N = 10;
	int N;
	cout << "Number of Steps: ";
	cin >> N;

	ScalarIVPSolver<double, int> ivpSol(ivp1, EEuler);		// Explicit Euler
	ivpSol.steps(N);

	Vector<double, int> res = ivpSol.result();

	Vector<double, int> exact(res);
	exact[exact.MinIndex()] = ivp1.startValue();
	
	for (int i = exact.MinIndex(); i <= exact.MaxIndex(); i++)
	{

		double fac = 11.0;
		exact[i] = ::exp(- fac * ivpSol.stepSize() * (i-1));  // a == 1
//		exact[i] = EuropeanType(ivpSol.stepSize() * (i-1)); 
//	    exact[i] = DigitalType(ivpSol.stepSize() * (i-1)); 
//		exact[i] = TurningPointType(ivpSol.stepSize() * (i-1)); 

	//	exact[i] = ::exp(- fac* pow(ivpSol.stepSize() * (i-1), 2) * 0.5);  // a == t
	}

	cout << "Exact solution\n";
//	print (exact); 
	
	cout << "\n ***************** Step Size " <<  1.0/N << "*************************\n";

	cout << "Explicit Euler";
//	print(res);
	cout << "Error: " << ::max(res, exact) << endl << endl;

	ivpSol.setType(Trap);
	cout << "Trapezoidal";
	res = ivpSol.result();
//	print(res);
	cout << "Error: " << ::max(res, exact) << endl<< endl;


	ivpSol.setType(Fitted);
	cout << "Duffy fitted";
	res = ivpSol.result();
//	print(res);
	cout << "Error: " << ::max(res, exact) << endl<< endl;


	ivpSol.setType(FittedBox);
	cout << "Fitted box scheme";
	res = ivpSol.result();
//	print(res);
	cout << "Error: " << ::max(res, exact) << endl<< endl;


	ivpSol.setType(Box);
	cout << "Box";
	res = ivpSol.result();
//	print(res);
	cout << "Error: " << ::max(res, exact) << endl<< endl;


	ivpSol.setType(ExtrapEuler);
	cout << "Extrapolated Euler";
	res = ivpSol.result();
//	print(res);
	cout << "Error: " << ::max(res, exact) << endl<< endl;


	ivpSol.setType(IEuler);
	cout << "Implicit Euler";
	res = ivpSol.result();
//	print(res);
	cout << "Error: " << ::max(res, exact) << endl<< endl;

	ivpSol.setType(PC);
	cout << "Predictor Corrector";
	res = ivpSol.result();
//	print(res);
	cout << "Error: " << ::max(res, exact) << endl<< endl;
/*
/*

	NLScalarIVP<double> nl;

//	nl.Rhs(myfunc);
//	cout << nl.RhsCalc(2.0);

	LinearIVP<double, int> linearIVP1;

	if (linearIVP1.ConsistentIVP() == true)
		cout << "whoopee\n";
*/
	int j;
	cin >> j;

	return 0;
}
