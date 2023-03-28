// testLU.cpp
//
// Testing matrix solvers (LU decomposition)
//
// (C) Datasim Education BV 2003-2004

#include "matrixsolvermechanisms.cpp"
#include "vector.cpp"
#include <iostream>
#include "arraymechanisms.cpp"
using namespace std;


int main()
{
	size_t J = 10;

	// First test case, trivial solution == 1 (the sanity check)
	// Constructors with size, start index and value (Diagonals of matrix)
	Vector<double, int> a(J-1,	2,	0.0);			// J -1 elements, start index == 2
	Vector<double, int> b(J,	1,	1.0);
	Vector<double, int> c(J-1,	1,	0.0);

	Vector<double, int> r(J, 1, 1.0);				// Right-hand side
	

	/*print(a);
	print(b);
	print(c);
	print(r);*/

	LUTridiagonalSolver<double, int> mySolver(a, b, c, r);
	Vector<double, int> result = mySolver.solve();
	print(result);

/*
	// A matrix corresponding to boundary value problem u" + u = 0, u(0) = 0, u(1) = 1
	double h =  1.0 / double(J);
	Vector<double, int> A(J-1,	2,	1.0);			// J -1 elements, start index == 2
	Vector<double, int> B(J,	1,	-2.0 + (h*h));
	Vector<double, int> C(J-1,	1,	1.0);

	Vector<double, int> R(J, 1, 0.0);				// Right-hand side
	R[R.MaxIndex()] = - 1.0;
	
	LUTridiagonalSolver<double, int> secondSolver(A, B, C, R);
	Vector<double, int> Result = secondSolver.solve();
//	cout << "Solution" << endl;	print(Result);

	Vector<double, int> exact(Result);
	double d = ::sin(1.0);
	double x = h;
	for (int i = exact.MinIndex(); i <= exact.MaxIndex(); i++)
	{
		exact[i] = ::sin(x) / d;
		x += h;
	}
//	print(exact);

	// Norm of difference
	cout << "l2 norm of difference: " << l2Norm(Result, exact) << endl;
	cout << "l1 norm of difference: " << l1Norm(Result, exact) << endl;
	cout << "l infinity norm of difference: " << lInfinityNorm(Result, exact) << endl;



	// Now testing the Double Sweep method
	// Constructors with size, start index and value
	Vector<double, int> AG(J,	1,	0.0);
	Vector<double, int> BG(J,	1,	2.0);
	Vector<double, int> CG(J,	1,	0.0);
	Vector<double, int> FG(J,	1,	1.0);

	cout << "Godunov I ...\n";
	double LHS = 1.0;
	double RHS = 1.0;
	DoubleSweep<double, int> Godunov(AG, BG, CG, FG, LHS, RHS);
	Vector<double, int> result2 = Godunov.solve();
//	print(result2);

	cout << "Godunov II ...\n";

//	J = 2;
	h =  1.0 / double(J);
	Vector<double, int> A2(J-1,	1,	1.0);			// J elements, start index == 1
	Vector<double, int> B2(J-1,	1,	-2.0 + (h*h));
	Vector<double, int> C2(J-1,	1,	1.0);

	Vector<double, int> R2(J-1, 1, 0.0);				// Right-hand side
	//R2[R2.MaxIndex()] = - 1.0;

	LHS = 0.0;
	RHS = 1.0;
	DoubleSweep<double, int> doubleSweepSolver(A2, B2, C2, R2, LHS, RHS);

	cout << "Arrays A, B, C, RHS \n";
	print(A2);
	print(B2);
	print(C2);
	print(R2);


	Vector<double, int> ResultDS = doubleSweepSolver.solve();
	cout << "Solution" << endl;	print(ResultDS);

	// Realign exact solution because Double Sweep is a bit different
	Vector<double, int> exact2(ResultDS);

	d = ::sin(1.0);
	x = 0.0;
	for (int k = exact2.MinIndex(); k <= exact2.MaxIndex(); k++)
	{
		exact2[k] = ::sin(x) / d;
		x += h;
	}
	cout << "Exact2\n"; print(exact2);

	// Norm of difference
	cout << "l2 norm of difference: " << l2Norm(ResultDS, exact2) << endl;
	cout << "l1 norm of difference: " << l1Norm(ResultDS, exact2) << endl;
	cout << "l infinity norm of difference: " << lInfinityNorm(ResultDS, exact2) << endl;

*/

	return 0;
}
