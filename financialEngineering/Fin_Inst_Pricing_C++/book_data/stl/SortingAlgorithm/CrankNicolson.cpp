// CrankNicolson.cpp
//
// Special PDE taht test the Crank-Nicolson scheme.
// This is for testing stability, accuracy and spurious 
// oscillations.
//
// (C) Datasim Education BV 2003
//

#include "matrixsolvermechanisms.cpp"
#include "vector.cpp"
#include "doublesweep.cpp"
#include <iostream.h>

// The input for the PDE

double ic(double x)
{
	//
}

double bcl(double t)
{
	//
}

double bcr(double t)
{
	//
}


int main()
{

int main()
{
	size_t n = 5;

	double h = 0.1;
	double k = 0.1;
	double sig = 0.01;
	double mu = 123.8;

	double beta = (k*sig)/(h*h);
	double gamma = (k*mu*0.5)/h;
	double Acoeff = - beta + gamma;
	double Bcoeff = 1.0 + (2.0*beta);
	double Ccoeff = - (beta + gamma);

	// Constructors with size, start index and value
	// This is the matrix A and RHS r (AU = r)
	Vector<double, int> A(n,	1,	Acoeff);
	Vector<double, int> B(n,	1,	Bcoeff;
	Vector<double, int> C(n,	1,	Ccoeff);
	Vector<double, int> F(n,	1,	0.0);

	cout << "Godunov I ...\n";
	print(A);
	print(B);
	print(C);
	print(F);

	double t = 0.0;

	///////////////////////////////////////////////////////////
	next:
	///////////////////////////////////////////////////////////
	double LHS = bcl(t);
	double RHS = bcr(t);
	DoubleSweep<double, int> Godunov(A, B, C, F, LHS, RHS);
	pair <Vector<double, int>, Vector<double, int> > result2 = Godunov.solve();

	cout << "Godunov II ...\n";
	print(result2.first);
	print(result2.second);

	///////////////////////////////////////////////////////////
	if (t <= 1.0)
		goto next;
	////////////////////////////////////////////////////////////

	return 0;

}
