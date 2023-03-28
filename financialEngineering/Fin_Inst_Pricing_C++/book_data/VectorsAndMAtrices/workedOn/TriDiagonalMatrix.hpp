// TriDiagonalMatrix.hpp
//
// Simple class encapsulating tridiagonal matrix information.
//
// (C) Datasim Education BV 2004
//

#ifndef TriDiagonalMatrix_hpp
#define TriDiagonalMatrix_hpp

#include "numericmatrix.cpp"
#include "matrixmechanisms.hpp"
#include "matrixsolvermechanisms.cpp"

// enum TriDiagonalMatrixSolverType {LUDecomposition, DoubleSweep};

template <class V, class I> class TriDiagonalMatrix
{
private:

//	Vector<double, int> a(J-1,	2,	0.0);		// J -1 elements, start index == 2
//	Vector<double, int> b(J,	1,	1.0);
//	Vector<double, int> c(J-1,	1,	0.0);

	Vector<V, I> a; // Lower
	Vector<V, I> b; // Diagonal
	Vector<V, I> c; // Upper

public:
	TriDiagonalMatrix(const Vector<V,I>& lower,	const Vector<V,I>& diagonal, 
												const Vector<V,I>& upper)
{ // Create a tridiagonal matrix with necessary vectors


	// We use the indexing as with LU decomposition routines, i.e.
	//
	//	lower [2, J]
	//	diagonal [1, J]
	//	upper [1, J-1]
	//


	a = lower;
	b = diagonal;
	c = upper;
}

TriDiagonalMatrix(const I& dimension, 
				  const V& lowerVal, const V& diagonalVal, const V& upperVal)
{ // Create a TRIDIAG Toeplitz matrix

	// Size, start index, default values
	a = Vector<V,I> (dimension - 1, 2, lowerVal);
	b = Vector<V,I> (dimension, 1, diagonalVal);
	c = Vector<V,I> (dimension - 1, 1, upperVal);
}



void set_lower(const Vector<V, I>& v)
{
	a = v;
}

void set_diagonal(const Vector<V, I>& v)
{
	b = v;
}

void set_upper(const Vector<V, I>& v)
{
	c = v;
}

I dimension() const
{ // The size (number of rows or columns)

	return b.Size();
}

NumericMatrix<V, I> matrix() const
{
	NumericMatrix<V, I> result(b.Size(), b.Size(), 1, 1);

	// All values set to 0
	init(result, V(0.0));

	result(result.MaxRowIndex(), result.MaxColumnIndex()) = b[b.MaxIndex()];
	result(result.MaxRowIndex(), result.MaxColumnIndex() -1) = lower[lower.MaxIndex()];

	result(1, 1) = b[b.MinIndex()];
	result(1, 2) = upper[upper.MinIndex()];

	for (I i = result.MinRowIndex() + 1; i <= result.MaxRowIndex() - 1; i++)
	{

		cout << "in loop ";
		// Create the diagonal element	
		result(i, i-1)	= lower[i];
		result(i, i)	= diagonal[i];
		result(i, i+1)	= upper[i];
	}

	return result;
}


Vector<V, I> multiply (const Vector<V, I>& v) const
{ // Multiply a vector and a tridiagonal matrix


	NumericMatrix<V, I> m(a, b, c);

	return m * v;
}

Vector<V, I> operator * (const Vector<V, I>& U) const
{ // Multiply a vector and a tridiagonal matrix

	Vector<V, I> result(b.Size(), b.MinIndex());	// Size + start index

	// Extreme I
	result[result.MinIndex()] = b[b.MinIndex()] * U[U.MinIndex()]

								+ c[c.MinIndex()] * U[U.MinIndex() + 1];

	for (I i = result.MinIndex() + 1; i <= result.MaxIndex() - 1; i++)
	{
		result[i] = (a[i]* U[i-1]) + (b[i] * U[i]) + (c[i] * U[i+1]);
	}

	// Extreme I
	result[result.MaxIndex()] = a[b.MaxIndex()] * U[b.MaxIndex() - 1]

								+ b[b.MaxIndex()] * U[b.MaxIndex()];

	return result;
}

// Solver
Vector<V, I> solve(const Vector<V, I>& RHS)
{ // An encapsulation of LU decomposition


	LUTridiagonalSolver<double, int> secondSolver(a, b, c, RHS);
	Vector<double, int> Result = secondSolver.solve();
	return Result;

}


};

#endif


