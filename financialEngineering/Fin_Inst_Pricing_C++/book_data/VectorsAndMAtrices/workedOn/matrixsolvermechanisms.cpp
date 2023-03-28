// matrixsolvermechanisms.cpp
//
// Classes and functions for solving linear systems of equations 
// (numerical linear algebra).
//
// Modification Dates:
//
//	DD 2003-1-14 First code (tridiagonal)
//	DD 2003-1-16 DD small corrections: still to code 2 member functions
//	DD 2003-8-2 LU decomposition of tridiagonal systems; 2 functions
//	(Boolean checks added)
//  DD 2003-8-5 Matrix iterative solvers (Jacobi, Gauss Seidel)
//	DD 2003-8-21 Debugging and good testing
//	DD 2003-9-1 Debugging Jacobi
//	DD 2004-4-10 New implementation using the Template Method pattern
//	DD 2004-4-11 Implement PSOR as a derived class. Lots of reuse
//
// (C) Datasim Education BV 2003-2004

#ifndef MatrixSolverMechanisms_CPP
#define MatrixSolverMechanisms_CPP

#include "matrixsolvermechanisms.hpp"
#include "arraymechanisms.hpp"
#include <iostream>
#include <algorithm>


template <class V, class I> void LUTridiagonalSolver<V,I>::calculateBetaGamma()
{ // Calculate beta and gamma


	// Constructor derived from Array (size, startIndex [,value])
	beta = Vector<V,I> (J, 1);
	gamma = Vector<V,I> (J - 1, 1);

	beta[1] = b[1];
	gamma[1] = c[1] / beta[1];

	for (I j = 2; j <= J - 1; j++)
	{
		beta[j] = b[j] - (a[j] * gamma[j-1]);
		gamma[j] = c[j]/beta[j];

	}

	beta[J] = b[J] - (a[J] * gamma[J-1]);
}

template <class V, class I> void LUTridiagonalSolver<V,I>::calculateZU()
{ // Calculate z and u

	z = Vector<V,I> (J, 1);
	u = Vector<V,I> (J, 1);

	// Forward direction
	z[1] = r[1] / beta[1];

	for (I j = 2; j <= J; j++)
	{
		z[j] = (r[j] - (a[j]*z[j-1]) ) / beta[j];
	
	}

	// Backward direction
	u[J] = z[J];

	for (I i = J - 1; i >= 1; i--)
	{
		u[i] = z[i] - (gamma[i]*u[i+1]);
	
	}

}
	

template <class V, class I> LUTridiagonalSolver<V,I>::LUTridiagonalSolver()
{
	
	a = Vector<V,I> (1);
	b = Vector<V,I> (2);
	c = Vector<V,I> (1);
	r = Vector<V,I> (2);

	J = r.Size();

}

template <class V, class I>	LUTridiagonalSolver<V,I>::LUTridiagonalSolver(const Vector<V,I>& lower, const Vector<V,I>& diagonal, const Vector<V,I>& upper, const Vector<V,I>& RHS)
{

	a = lower;
	b = diagonal;
	c = upper;
	r = RHS;

	J = r.Size();
}

template <class V, class I>	LUTridiagonalSolver<V,I>::LUTridiagonalSolver(const LUTridiagonalSolver<V,I>& source) 
{

	a = source.a;
	b = source.b;
	c = source.c;
	r = source.r;

	J = source.J;
}

	
template <class V, class I> LUTridiagonalSolver<V,I>::~LUTridiagonalSolver()
{

}
 	
// Assignment operator 
template <class V, class I>	LUTridiagonalSolver<V,I>& LUTridiagonalSolver<V,I>::operator = (const LUTridiagonalSolver<V,I>& source)
{
	
	if (this == &source)
		return *this;

	a = source.a;
	b = source.b;
	c = source.c;
	r = source.r;

	J = source.J;

}


// Integrity checks
template <class V, class I> bool LUTridiagonalSolver<V,I>::validIndices() const
{ // Indices and bound according to the algorithm?

	if (r.MinIndex() != 1 || b.MinIndex() != 1 || c.MinIndex() != 1)
		return false;

	if (a.MinIndex() != 2)
		return false;

	if (r.MaxIndex() != b.MaxIndex() || a.MaxIndex() != r.MaxIndex())
		return false;

	if (c.MaxIndex() != r.maxIndex() - 1)
		return false;

	return true;
}

template <class V, class I> bool LUTridiagonalSolver<V,I>::diagonallyDominant() const
{
	if (fabs(b[1]) < fabs(c[1]))
		return false;

	if (fabs(b[J]) < fabs(a[J]))
		return false;

	for (I j = 2; j <= J-1; j++)
	{
		if (fabs(b[j]) < fabs(a[j]) + fabs(c[j]) )
			return false;
	}

	
	return true; 
}


// Calculate the solution to Au = r
template <class V, class I> Vector<V,I> LUTridiagonalSolver<V,I>::solve()
{
	calculateBetaGamma();		// Calculate beta and gamma
	calculateZU();				// Calculate z and u

	return u;
	
}

////////////////////////////////////////////////////////////////////
//
// Double Sweep
//
////////////////////////////////////////////////////////////////////
//
// The Balayage method
//
// (C) Datasim Component Technology BV 2000-2004
//
// 24.07.2000 S changed into AS - Array structure (JT)
// 2002-1-8 DD Remove namespace, improved array indexing
// 2002-4-8 DD Indexing improvements, improve usability
// 2003-1-16 DD Clean up and testing
// 2003-8-2 DD incorprated int matrixsolvermechanisms



// Constructors and destructor
template <class V, class I, class AS> 
DoubleSweep<V,I>::DoubleSweep()
{ 
			// empty OK
}


template <class V, class I, class AS> 
DoubleSweep<V,I>::DoubleSweep (const DoubleSweep<V,I>& s2)
{ 

			// empty OK
}

template <class V, class I, class AS>
DoubleSweep<V,I>::DoubleSweep(const Vector<V,I>& lower, const Vector<V,I>& diagonal, 
								 const Vector<V,I>& upper,
								 const Vector<V,I>& RHS, const V& bc_left, 
								 const V& bc_right)
{

	a = lower;
	b = diagonal;
	c = upper;
	f = RHS;

	left = bc_left;
	right = bc_right;
}

template <class V, class I, class AS> 
DoubleSweep<V,I>::~DoubleSweep()
{
			// empty OK
}

template <class V, class I, class AS> 
DoubleSweep<V,I>& DoubleSweep<V,I>::operator = (const DoubleSweep<V,I>& source)
{ 
	a = source.a;
	b = source.b;
	c = source.c;
	RHS = source.RHS;

	left = source.left;
	right = source.right;
}


// result 


template <class V, class I, class AS> 
 Vector<V,I> DoubleSweep<V,I>::solve()
{ // Code to actually create the solution to the tridiagonal system

	size_t N =  a.Size() + 1;

	Vector<V,I> U( N + 1, 0 ); // start index = 0; this vector will 'contain' the result
	U[0] = left;
	U[N] = right;

	Vector<V,I> L(N, 0);	// [0, N-1]
	L[0] = 0.0;

	I j;
	for (j = L.MinIndex() + 1; j <=  L.MaxIndex(); j++ )
	{// L
		
		L[j] = ( -c[j] ) / ( b[j] + ( a[j] *	L[j-1] ) );
	}

	Vector<V,I> K(N, 0);	// [0, N-1]	
	K[0] = left;

	for (j = K.MinIndex() + 1; j <= K.MaxIndex(); j++ )
	{// K

		K[j] = ( f[j] - ( a[j] * K[j-1] ) ) / ( b[j] + ( a[j] * L[j-1] ) );
	}


	for (j = N - 1; j >= 1; j-- )
	{// U

		U[j] = ( L[j] * U[j + 1] ) + K[j];

	}
	
	return U;

}


//////////////// Iterative Matrix Solvers //////////////////////////////////
// Constructors and destructor
template <class V, class I>
MatrixIterativeSolver<V,I>::MatrixIterativeSolver()
{
	
}


template <class V, class I>
MatrixIterativeSolver<V,I>::MatrixIterativeSolver (const MatrixIterativeSolver<V,I>& s2)
{
	// empty
}


template <class V, class I>
	MatrixIterativeSolver<V,I>::MatrixIterativeSolver(NumericMatrix<V,I>& myA, Vector<V,I>& myRHS)
{

		m_A = &myA;
		m_b = &myRHS;

		
		//V m_tol;						// Tolerance for convergence of sequence
		//NormType m_normType;			// Norm for stopping criterion
		//I m_maxiter;					// Maximum number of iterations
		//V m_omega;					// Relaxation factor to speed convergence
		

		m_tol = 0.001; // Should be good enough for most purposes
		m_normType = L2;
		m_iterativeType = Jacobi;
		m_maxiter = 1000;
		m_omega = 2.0;
		m_currVector = Vector<V,I>(m_A -> Rows(), m_A -> MinRowIndex(), 0.0);
		m_NextVector = Vector<V,I>(m_A -> Rows(), m_A -> MinRowIndex(), 1220.0);

		m_status = false;
}


template <class V, class I>
MatrixIterativeSolver<V,I>::~MatrixIterativeSolver()
{

}



// Assignment operator
template <class V, class I>
MatrixIterativeSolver<V,I>& MatrixIterativeSolver<V,I>::operator = (const MatrixIterativeSolver<V,I>& i2)
{

	
}

template <class V, class I>
void MatrixIterativeSolver<V,I>::initParameters(const V& tolerance, const V& SORFactor,
							const I& maxIter, NormType ntype, IterativeType itype)
{
		m_tol = tolerance; // Should be good enough for most purposes
		m_normType = ntype;
		m_iterativeType = itype;
		m_maxiter = maxIter;
		m_omega = SORFactor;

		m_status = false;
		k = 0;
}	



// Vector at level k+1 and
template <class V, class I>
	void MatrixIterativeSolver<V,I>::CalculateNextVector()
{
	if (m_iterativeType == GaussSeidel)
	{
			calcGaussSeidel();
	}
	if (m_iterativeType == Jacobi)
	{
		calcJacobi();
	}
}

template <class V, class I>
void MatrixIterativeSolver<V,I>::startVector(const Vector<V, I>& startV)
{ // hook

	m_currVector = startV;
}



// Result
template <class V, class I>
	void MatrixIterativeSolver<V,I>::solve()
{// Implement the basic Template Method sequence here

	/*
	// Initialisation
	virtual void startVector(const Vector<V, I>& startV);	// hook
	virtual void initParameters(const V& tolerance, const V& SORFactor,
							const I& maxIter);	// hook
	// Give vector at level k
	virtual Vector<V, I> currentVector() const;	// hook
	// Vector at level k+1 and
	virtual Vector<V,I> CalculateNextVector() = 0; // PVMF
	// Which test for tolerance?
	virtual bool insideTolerance(NormType t) const = 0;	// PVMF
	*/

	k = 0;

contIter:	
	CalculateNextVector();	// Calculates the vector at iteration k+1

	if (insideTolerance() == false)
	{
		k++;
		if (k >= m_maxiter)
		{		
			m_status = false;
			return;
		}

		m_currVector = m_NextVector;

		goto contIter;

	}

	// Everything OK
	m_status = true;
}

// Which test for tolerance?
template <class V, class I> bool
	MatrixIterativeSolver<V,I>::insideTolerance() const
{

	double currTol;
	if (m_normType == L2)
	{
		currTol = l2Norm(m_currVector, m_NextVector);	// Arraymechanism!
	}

	if (m_normType == LInfinity)
	{
		currTol = lInfinityNorm(m_currVector, m_NextVector);	// Arraymechanism!

	}

	bool result = false;
	if (currTol <= m_tol)
		result = true;

	return result;
}

template <class V, class I>
Vector<V, I> MatrixIterativeSolver<V,I>::result() const
{
	return m_NextVector;
}

template <class V, class I>
 bool MatrixIterativeSolver<V,I>::status() const
{ // Succeeded or not

	return m_status;
}

template <class V, class I>
I MatrixIterativeSolver<V,I>::NumberIterations() const
{

	return k;
}

/// PSOR
template <class V, class I>
PSORSolver<V,I>::PSORSolver() : MatrixIterativeSolver<V,I> ()
{
		
}

template <class V, class I>
PSORSolver<V,I>::PSORSolver(NumericMatrix<V, I>& A, Vector<V, I>& b, Vector<V,I>& c)
: MatrixIterativeSolver<V,I> (A, b)
{
		m_c = &c;
		m_YVector = Vector<V,I>(m_A -> Rows(), m_A -> MinRowIndex(), 0.0);

}

template <class V, class I>
PSORSolver<V,I>::PSORSolver(const PSORSolver<V,I>& s2)
: MatrixIterativeSolver<V,I> ()
{

}

template <class V, class I>
PSORSolver<V,I>::~PSORSolver()
{
		
}
template <class V, class I>
	PSORSolver<V,I>& PSORSolver<V,I>::operator = (const PSORSolver<V,I>& i2)
{

}


// Vector at level k+1 
template <class V, class I>
 void PSORSolver<V,I>::CalculateNextVector()
{ // PSOR has a very special way

	V tmp1(0.0), tmp2(tmp1);

	for (I j = m_A->MinRowIndex(); j <= m_A->MaxRowIndex(); j++)
	{
		tmp1 = tmp2  = V(0.0);
		for (I i = m_A->MinColumnIndex(); i <= j-1; i++)
		{

			tmp1 += (*m_A)(j,i) * m_YVector[i];
		}

		for (i = j+1; i <= m_A->MaxColumnIndex(); i++)
		{

			tmp2 += (*m_A)(j,i) * m_currVector[i];
		}

		m_YVector[j] = (-tmp1 -tmp2 + (*m_b)[j]) / (*m_A)(j, j);


		// Now PSOR correction term
		tmp1 = (1.0 - m_omega)* m_currVector[j] + (m_omega*m_YVector[j]);
	
		// m_NextVector[j] = max(m_c[j], tmp1);
		if (tmp1 > (*m_c)[j])
			m_NextVector[j] = tmp1;
		else
			m_NextVector[j] = (*m_c)[j];


	}

}


// Nitty-gritty functions
template <class V, class I>
	void MatrixIterativeSolver<V,I>::calcJacobi()
{

	V tmp;
	
	for (I j = m_A->MinRowIndex(); j <= m_A->MaxRowIndex(); j++)
	{
		tmp = V(0.0);
		for (I i = m_A->MinColumnIndex(); i <= m_A->MaxColumnIndex(); i++)
		{
			
			if (i != j)
			{

				tmp += (*m_A)(j,i) * m_currVector[i];
			}
		}

	
		m_NextVector[j] = (-tmp + (*m_b)[j]) / (*m_A)(j, j);
	}
}


template <class V, class I>
	void MatrixIterativeSolver<V,I>::calcGaussSeidel()
{
	V tmp1(0.0), tmp2(tmp1);

	for (I j = m_A->MinRowIndex(); j <= m_A->MaxRowIndex(); j++)
	{
		tmp1 = tmp2  = V(0.0);
		for (I i = m_A->MinColumnIndex(); i <= j-1; i++)
		{

			tmp1 += (*m_A)(j,i) * m_NextVector[i];
		}

		for (i = j+1; i <= m_A->MaxColumnIndex(); i++)
		{

			tmp2 += (*m_A)(j,i) * m_currVector[i];
		}

		m_NextVector[j] = (-tmp1 -tmp2 + (*m_b)[j]) / (*m_A)(j, j);
	}
}

	
#endif