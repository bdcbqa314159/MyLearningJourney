// TestTridiagonalMatrix.cpp
//
// Test a tridiagonal matrix
//
// (C) Datasim Eduction BV 2004

#include "tridiagonalmatrix.hpp"
#include "arraymechanisms.hpp"


int main()
{
	size_t J = 10;

	// First test case, trivial solution == 1 (the sanity check)
	// Constructors with size, start index and value (Diagonals of matrix)
	Vector<double, int> a(J-1,	2,	0.0);			// J -1 elements, start index == 2
	Vector<double, int> b(J,	1,	1.0);
	Vector<double, int> c(J-1,	1,	0.0);

	TriDiagonalMatrix<double, int> TriMat(a, b, c);

	Vector<double, int> U(TriMat.dimension(), 1, 1.0);

	Vector<double, int> X = TriMat * U;

	Vector<double, int> RHS(TriMat.dimension(), 1, 1.0);
	
	Vector<double, int> Solution = TriMat.solve(RHS);
	print (Solution);

//	print(X);

	TriDiagonalMatrix<double, int> TriMat2(10, 0.0, 1.0, 0.0);
	Vector<double, int> Solution2 = TriMat2.solve(RHS);
	print (Solution2);

	return 0;
}
