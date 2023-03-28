// testPSOR.cpp
//
// Testing PSOR method (used with FDM for American options)
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
	// Ingredient of problem, this is
	//
	//	Ax >= b, x >= c
	//	(x - c).(Ax - b) == 0 (inner product)
	//

	NumericMatrix<double, int> A(10, 10, 1, 1);		// The matrix to be inverted
	setDiagonal(A, 2.0);
	print(A);

	Vector<double, int> b(10, 1, 1.0);			// The right-hand side vector
	print(b);

	// Constraint stuff
	Vector<double, int> c(10, 1, 1.0);		
	Vector<double, int> v0 = c + 1.0;
	print(c); print(v0);

	PSORSolver<double, int> mySolver(A, b, c);
	
	/* virtual void initParameters(const V& tolerance, const V& SORFactor,
	const I& maxIter, NormType ntype,IterativeType itype);	// hook */
	mySolver.startVector(v0);	
	mySolver.initParameters(0.01, 1.0, 100, L2, Jacobi);

	mySolver.solve();
	Vector<double, int> res = mySolver.result();
	cout << "\nSolution for PSOR: \n"; print(res);
	cout << "\nNumber of iterations: " << mySolver.NumberIterations();
	if (mySolver.status() == false)
		cout << "\nStatus false";
	else
		cout << "\nStatus true";

	// Now test matrix iterative solvers using tridiagonal matrices

	int J = 10;
	Vector<double, int> a2(J-1,	2,	0.0);			// J-1 elements, start index == 2
	Vector<double, int> b2(J,	1,	2.0);
	Vector<double, int> c2(J-1,	1,	0.0);
	Vector<double, int> r2(J, 1, 1.0);				// Right-hand side
	Vector<double, int> constraintVector(J, 1, 1.0);			

	NumericMatrix<double, int> m2 = createMatrix(a2, b2, c2);		
	print(m2);
	print(r2);

	PSORSolver<double, int> mySolver2(m2, r2, constraintVector);

	v0 = r2 + 1.0;		// Linear offset
	mySolver2.startVector(v0);	
	mySolver2.initParameters(0.01, 1.0, 100, L2, Jacobi);

	mySolver2.solve();
	Vector<double, int> result3 = mySolver2.result();

	print(result3);
	cout << "\nNumber of iterations: " << mySolver2.NumberIterations();
	if (mySolver2.status() == false)
		cout << "\nStatus false";
	else
		cout << "\nStatus true";


	return 0;
	
}
