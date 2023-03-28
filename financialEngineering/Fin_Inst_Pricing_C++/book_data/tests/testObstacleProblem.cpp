// testObstacleProblem.cpp
//
// Testing PSOR method (used with FDM for American options)
// In this case we test the time-independent obstacle problem.
//
// (C) Datasim Education BV 2003-2004

#include "matrixsolvermechanisms.cpp"
#include "functionmechanisms.cpp"
#include "vector.cpp"
#include <iostream>
#include "arraymechanisms.cpp"
#include "matrixmechanisms.cpp"
using namespace std;

double forcingTerm(double x)
{
	return (1.0 -x) * (x+1.0);
//	return 1.0;
}

int main()
{
	// Ingredient of problem, this is
	//
	//	Ax >= b, x >= c
	//	(x - c).(Ax - b) == 0 (inner product)
	//


	int J = 10;
	Vector<double, int> a(J-2,	2,	-1.0);			// J-1 elements, start index == 2
	Vector<double, int> b(J-1,	1,	2.0);
	Vector<double, int> c(J-2,	1,	-1.0);
	NumericMatrix<double, int> A = createMatrix(a, b, c);		
	print(A);

	double length = 2.0;	// length of interval
	double h = length / double(J);

	// The constraint vector C
	Range<double> range(-1.0 + h, 1.0 - h);
	Vector<double, int> C = createDiscreteFunction(forcingTerm, range, J-2);
	print(C);

	// The RHS b (in this case zero)
	Vector<double, int> B(J-1,	1,	0.0);
	print(B);

	PSORSolver<double, int> mySolver(A, B, C);
	
	/* virtual void initParameters(const V& tolerance, const V& SORFactor,
	const I& maxIter, NormType ntype,IterativeType itype);	// hook */
	mySolver.startVector(C + 2.0);	
	mySolver.initParameters(0.01, 1.0, 100, L2, Jacobi);

	mySolver.solve();
	Vector<double, int> res = mySolver.result();
	cout << "\nSolution for PSOR: \n"; print(res);
	cout << "\nNumber of iterations: " << mySolver.NumberIterations();
	if (mySolver.status() == false)
		cout << "\nStatus false";
	else
		cout << "\nStatus true";


	return 0;
	
}
