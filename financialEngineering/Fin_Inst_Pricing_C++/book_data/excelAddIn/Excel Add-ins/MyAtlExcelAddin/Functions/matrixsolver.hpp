// matrixsolver.hpp
//
// Solver for linear (matrix) systems of equations. The solver solves the
//
//			Ax = b
//
// where A is a given input matrix and b is a given input vector. The vector 
// x is the desired result.
//
// (C) Datasim Component Technology BV 2000-2003
//
//
//
#ifndef MatrixSolver_hpp
#define MatrixSolver_hpp

/// Base class for all matric solvers ////

#include "numericmatrix.cpp"

template <class V, class I, class S> class MatrixSolver
{
protected:
		NumericMatrix<V, I, S>* AA;	// The known matrix
		Vector<V, I, S>* bb;		// RHS vector
		Vector<V, I, S> x;			// Unknown vector

public:
		// Constructors
		MatrixSolver();
		MatrixSolver (const MatrixSolver<V,I,S>& s2);
		MatrixSolver (const NumericMatrix<V,I,S>& A, const Vector<V,I,S>& b);
		virtual ~MatrixSolver();

		MatrixSolver<V,I,S>& operator = (const MatrixSolver<V,I,S>& i2);

		// Results
		virtual Vector<V,I,S> solve() = 0;
};

//////////////////////////////////////////////////////////////////////////////////////

template <class V, class I, class S> class DirectMatrixSolver: public MatrixSolver<V,I,S>
{ // Class of direct matrix solvers

private:
	
public:
		// Constructors
		DirectMatrixSolver();
		DirectMatrixSolver (const DirectMatrixSolver<V,I,S>& s2);
		DirectMatrixSolver (const NumericMatrix<V,I,S>& A, const Vector<V,I,S>& b);
		virtual ~DirectMatrixSolver();

		DirectMatrixSolver<V,I,S>& operator = (const DirectMatrixSolver<V,I,S>& i2);
};

///////////////////////////////////////////////////////////////////////////////////////

template <class V, class I, class S> class IterativeMatrixSolver: public MatrixSolver<V,I,S>
{ // Abstract base class for solving Ax = b using iterative methods

protected:
		// Other parameters
	//	VectorNormType<V,I,S> norm;	// Which norm to use for convergence
		V tol;						// Tolerance
		I MAXiterations;				// How many iterations to use before reject
		Vector<V,I, S> X0;			// Initial estimate

		// Local variables
		V local_iterations;			// Current number of iterations

public:
		// Constructors
		IterativeMatrixSolver();
		IterativeMatrixSolver (const IterativeMatrixSolver<V,I,S>& s2);
		IterativeMatrixSolver (const NumericMatrix<V,I,S>& A, const Vector<V,I,S>& b,
					const V& omega, const V& tolerance, const I& number_iterations,
					const Vector<V,I,S>& initialX);
		virtual ~IterativeMatrixSolver();

		IterativeMatrixSolver<V,I,S>& operator = (const IterativeMatrixSolver<V,I,S>& i2);

		// Changing parameters
	//	virtual void norm(const NormType<V,I> new_norm);	// Choose the norm

		// Results
		virtual I iterations() const;						// How many iterations did it take?

};


template <class V, class I, class S> class JacobiSolver: public IterativeMatrixSolver<V,I,S>
{ // The Jacobi iterative method for solving Ax = b

public:
		JacobiSolver();
		JacobiSolver (const JacobiSolver<V,I,S>& s2);
		JacobiSolver (const NumericMatrix<V,I,S>& A, const Vector<V,I,S>& b,
					const V& omega, const V& tolerance, const I& number_iterations);
		virtual ~JacobiSolver();

		JacobiSolver<V,I,S>& operator = (const JacobiSolver<V,I,S>& i2);

		// Changing parameters
	//	virtual void norm(const NormType<V,I> new_norm);	// Choose the norm

		// Results
		Vector<V,I,S> solve();

};


/*
template <class V, class I, class S> class GaussSeidelSolver: public IterativeMatrixSolver
{ // The Gauss Seidel iterative method for solving Ax = b


}

*/




#endif