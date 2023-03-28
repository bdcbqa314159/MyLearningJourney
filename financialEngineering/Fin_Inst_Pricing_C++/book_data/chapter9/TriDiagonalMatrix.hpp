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
{ // Create a matrix based on the diagonal elements of a tridiagonal matrix; bit wasteful of
  // space but who cares! I've got a Pentium with a giga of memory


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


NumericMatrix<V, I> matrix() const
{
	NumericMatrix<V, I> result(diagonal.Size(), diagonal.Size(), 1, 1);

	// All values set to 0
	init(result, V(0.0));

	result(result.MaxRowIndex(), result.MaxColumnIndex()) = diagonal[diagonal.MaxIndex()];
	result(result.MaxRowIndex(), result.MaxColumnIndex() -1) = lower[lower.MaxIndex()];

	result(1, 1) = diagonal[diagonal.MinIndex()];
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


Vector<V, I> operator + (const Vector<V, I>* v) const
{ // Multiply a vector and a tridiagonal matrix


	NumericMatrix<V, I> m(a, b, c);

	return m * v;
}

// Solver
Vector<V, I> solve(const Vector<V, I>& RHS)
{ // An encapsulation of LU decomposition

	!!!

	return result;
}



#endif


