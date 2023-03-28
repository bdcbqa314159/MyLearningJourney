// testMatIterative.cpp
//
// Testing matrix iterative solvers (Jacobi, Gauss-Seidel,
// SOR)
//
// (C) Datasim Education BV 2003-2004

#include "matrixsolvermechanisms.cpp"
#include "vector.cpp"
#include <iostream>
#include "arraymechanisms.cpp"
#include "matrixmechanisms.cpp"
using namespace std;


int main()
{
	
	NumericMatrix<double, int> A(10, 10);		// The matrix to be inverted
	setDiagonal(A, 2.0);
	print(A);

	Vector<double, int> b(10, 1, 1.0);			// The right-hand side vector
	print(b);


	MatrixIterativeSolver<double, int> mySolver(A, b);
	
	/* virtual void initParameters(const V& tolerance, const V& SORFactor,
	const I& maxIter, NormType ntype,IterativeType itype);	// hook */

	mySolver.initParameters(0.01, 1.0, 100, L2, Jacobi);

	mySolver.solve();
	Vector<double, int> res = mySolver.result();
	cout << "\nSolution for Jacobi: \n"; print(res);
	cout << "\nNumber of iterations: " << mySolver.NumberIterations();
	if (mySolver.status() == false)
		cout << "\nStatus false";
	else
		cout << "\nStatus true";

	// Now Gauss Seidel
	mySolver.initParameters(0.01, 2.0, 100, L2, GaussSeidel);
	mySolver.solve();
	Vector<double, int> res2 = mySolver.result();

	cout << "\nSolution for GaussSeidel: \n"; print(res2);
	cout << "\nNumber of iterations: " << mySolver.NumberIterations();
	if (mySolver.status() == false)
		cout << "\nStatus false\n";
	else
		cout << "\nStatus true\n";
	
	cout << "BREAK\n";

	// Now test matrix iterative solvers using tridiagonal matrices

	int J = 10;
	Vector<double, int> a2(J-1,	2,	0.0);			// J-1 elements, start index == 2
	Vector<double, int> b2(J,	1,	2.0);
	Vector<double, int> c2(J-1,	1,	0.0);
	Vector<double, int> r2(J, 1, 1.0);				// Right-hand side

	NumericMatrix<double, int> m2 = createMatrix(a2, b2, c2);		
	print(m2);
	print(r2);

	MatrixIterativeSolver<double, int> mySolver2(m2, r2);

	mySolver2.initParameters(0.01, 1.0, 100, L2, Jacobi);
	mySolver2.solve();
	Vector<double, int> result3 = mySolver2.result();

	print(result3);
	cout << "\nNumber of iterations: " << mySolver2.NumberIterations();
	if (mySolver2.status() == false)
		cout << "\nStatus false";
	else
		cout << "\nStatus true";

	// Problem from a BVP
	// A matrix corresponding to boundary value problem u" + u = 0, u(0) = 0, u(1) = 1
	double h =  1.0 / double(J);
	Vector<double, int> A2(J-1,	2,	1.0);			// J -1 elements, start index == 2
	Vector<double, int> B2(J,	1,	-2.0 + (h*h));
	Vector<double, int> C2(J-1,	1,	1.0);

	Vector<double, int> R(J, 1, 0.0);				// Right-hand side
	R[R.MaxIndex()] = - 1.0;
	
	NumericMatrix<double, int> m3 = createMatrix(A2,B2,C2);		
	print(m3);
	print(R);

	MatrixIterativeSolver<double, int> secondSolver(m3, R);

	secondSolver.initParameters(0.0001, 2.0, 10000, LInfinity, GaussSeidel);
	secondSolver.solve();
	Vector<double, int> Result4 = secondSolver.result();

	cout << "Approx Solution" << endl;	print(Result4);
	cout << "\nNumber of iterations: " << secondSolver.NumberIterations();
	if (secondSolver.status() == false)
		cout << "\nStatus false";
	else
		cout << "\nStatus true";

	Vector<double, int> exact(Result4);
	double d = ::sin(1.0);
	double x = h;
	for (int i = exact.MinIndex(); i <= exact.MaxIndex(); i++)
	{
		exact[i] = ::sin(x) / d;
		x += h;
	}
	cout << "\nExact solution";
	print(exact);


	return 0;
	
}
