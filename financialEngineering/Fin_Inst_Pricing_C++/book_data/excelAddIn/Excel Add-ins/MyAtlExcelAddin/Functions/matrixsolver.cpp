// matrixsolver.cpp
//
// Solver for linear (matrix) systems of equations. The solver solves the
//
//			Ax = b
//
// where A is a given input matrix and b is a given input vector. The vector 
// x is the desired result.
//
// (C) Datasim Component Technology BV 2000
//
//	Last modification dates:
//
//	2000-7-20 DD kick-off code, Jasmin to fill in the details
//	2003-1-18 DD code for the classes
//

/*
		NumericMatrix<V, I, S>* AA{  }	// The known matrix
		Vector<V, I, S>* bb{  }			// RHS vector
		Vector<V, I, S> x{  }			// Unknown vector
*/

#ifndef MatrixSolver_cpp
#define MatrixSolver_cpp

#include "matrixsolver.hpp"

// ** MatrixSolver **

// Constructors
template <class V, class I, class S> MatrixSolver<V,I,S>::MatrixSolver()
{

	AA = 0;
	bb = 0;
	xx = Vector<V,I>(1,1);

}

template <class V, class I, class S> MatrixSolver<V,I,S>::MatrixSolver (const MatrixSolver<V,I,S>& s2)
{ 

	AA = source.AA;
	bb = source.bb;
	xx = source.xx,
}

template <class V, class I, class S> MatrixSolver<V,I,S>::MatrixSolver (const NumericMatrix<V,I,S>& A, const Vector<V,I,S>& b)
{ 

	AA = &A;
	bb = &b;
}

template <class V, class I, class S> MatrixSolver<V,I,S>::~MatrixSolver()
{ 

}

template <class V, class I, class S> MatrixSolver<V,I,S>& MatrixSolver<V,I,S>::operator = (const MatrixSolver<V,I,S>& i2)
{ 

	if (this == &source)
		return *this;

	AA = source.AA;
	bb = source.bb;
	xx = source.xx,

	return *this;
}

// ** DirectMatrixSolver **

// Constructors
template <class V, class I, class S> DirectMatrixSolver<V,I,S>::DirectMatrixSolver() : MatrixSolver<V.I.S> ()
{  

}

template <class V, class I, class S> DirectMatrixSolver<V,I,S>::DirectMatrixSolver (const DirectMatrixSolver<V,I,S>& s2) : MatrixSolver<V.I.S> (s2)
{  

}

template <class V, class I, class S> DirectMatrixSolver<V,I,S>::DirectMatrixSolver (const NumericMatrix<V,I,S>& A, const Vector<V,I,S>& b) : MatrixSolver<V.I.S> (A, b)
{ 

}

template <class V, class I, class S> DirectMatrixSolver<V,I,S>::~DirectMatrixSolver()
{ 


}

template <class V, class I, class S> DirectMatrixSolver<V,I,S>& DirectMatrixSolver<V,I,S>::operator = (const DirectMatrixSolver<V,I,S>& i2)
{

	if (this == &source)
		return *this;

	MatrixSolver<V,I,S>::operator = (source);

	return *this;
}


// ** IterativeMatrixSolver **

// Constructors
template <class V, class I, class S> IterativeMatrixSolver<V,I,S>::IterativeMatrixSolver() : MatrixSolver<V.I.S> ()
{  

}


template <class V, class I, class S> IterativeMatrixSolver<V,I,S>::IterativeMatrixSolver (const IterativeMatrixSolver<V,I,S>& s2): MatrixSolver<V.I.S> (2)
{  

}

template <class V, class I, class S> IterativeMatrixSolver<V,I,S>::IterativeMatrixSolver (const NumericMatrix<V,I,S>& A, const Vector<V,I,S>& b,
			const V& omega, const V& tolerance, const I& number_iterations,	const Vector<V,I,S>& initialX) : MatrixSolver<V.I.S> (A, b)
{ 

	// Assign the parameters specific to iterative methods
}


template <class V, class I, class S> IterativeMatrixSolver<V,I,S>::~IterativeMatrixSolver()
{

}


template <class V, class I, class S> IterativeMatrixSolver<V,I,S>& IterativeMatrixSolver<V,I,S>::operator = (const IterativeMatrixSolver<V,I,S>& i2)
{
	if (this == &source)
		return *this;

	MatrixSolver<V,I,S>::operator = (source);

	// Assign the parameters specific to iterative methods


	return *this;
}

/*
template <class V, class I, class S> IterativeMatrixSolver<V,I,S>:: void norm(const NormType<V,I> new_norm)
{  }	// Choose the norm
*/
// Results
template <class V, class I, class S> I IterativeMatrixSolver<V,I,S>::iterations() const
{  }						

///////////////////////////////////////////////////////////////////////////////////////////////////////////

// ** JacobiSolver **
template <class V, class I, class S> JacobiSolver<V,I,S>::JacobiSolver() : IterativeMatrixSolver<V,I,S> ()
{

}

template <class V, class I, class S> JacobiSolver<V,I,S>::JacobiSolver (const JacobiSolver<V,I,S>& s2) : IterativeMatrixSolver<V,I,S> (s2)
{  

}

template <class V, class I, class S> JacobiSolver<V,I,S>::JacobiSolver (const NumericMatrix<V,I,S>& A, const Vector<V,I,S>& b,
			const V& omega, const V& tolerance, const I& number_iterations) : IterativeMatrixSolver<V,I,S> (A, b. omega, number_iterations)
{  

}

template <class V, class I, class S> JacobiSolver<V,I,S>:: ~JacobiSolver()
{  

}

template <class V, class I, class S> JacobiSolver<V,I,S>& JacobiSolver<V,I,S>::operator = (const JacobiSolver<V,I,S>& i2)
{  

	if (this == &source)
		return *this;

	IterativeMatrixSolver<V,I,S>::operator = (source);

	return *this;	
}

/*
// Changing parameters
template <class V, class I, class S> JacobiSolver<V,I,S>:: void norm(const NormType<V,I> new_norm)
{  

}
*/
// Results
template <class V, class I, class S>  Vector<V,I,S> JacobiSolver<V,I,S>::solve()
{  

}


/*
template <class V, class I, class S> class GaussSeidelSolver: public IterativeMatrixSolver
{ // The Gauss Seidel iterative method for solving Ax = b


}

*/





#endif