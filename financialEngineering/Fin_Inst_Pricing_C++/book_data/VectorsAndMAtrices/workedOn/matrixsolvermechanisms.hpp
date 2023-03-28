// matrixsolvermechanisms.hpp
//
// Classes and functions for solving linear systems of equations 
// (numerical linear algebra). We use:
//
//	Direct methods (Double Sweep, LU decomposition)
//	Iterative methods (Jacobi, Gauss Seidel)
//
// (C) Datasim Education BV 2003

#ifndef MatrixSolverMechanisms_HPP
#define MatrixSolverMechanisms_HPP

#include "vector.cpp"			// Arrays with mathematical properties
#include "numericmatrix.cpp"	// Matrices with numerical properties


template <class V, class I> class LUTridiagonalSolver
{ // Solve tridiagonal matrix equation
private:

	// Defining arrays (input)
	Vector<V,I> a;	// The lower-diagonal array [2..J]
	Vector<V,I> b;	// The diagonal array [1..J] "baseline array"
	Vector<V,I> c;	// The upper-diagonal array [1..J-1]
	Vector<V,I> r;	// The right-hand side of the equation Au = r [1..J]

	// Work arrays

	// Coefficients of Lower and Upper matrices: A = LU
	Vector<V,I> beta;	// Range [1..J]
	Vector<V,I> gamma;	// Range [2..J-1]
	// Solutions of temporary and final problems
	Vector<V,I> z;		// Range [1..J]
	Vector<V,I> u;		// Range [1..J]

	I J;	// Largest index

	void calculateBetaGamma();		// Calculate beta and gamma
	void calculateZU();				// Calculate z and u
	

public:
	LUTridiagonalSolver();
	LUTridiagonalSolver(const Vector<V,I>& lower_A, const Vector<V,I>& diagonal_B, const Vector<V,I>& upper_C, const Vector<V,I>& rhs_R);
	LUTridiagonalSolver(const LUTridiagonalSolver<V,I>& source); 
	
	virtual ~LUTridiagonalSolver();
 	
	// Assignment operator 
	LUTridiagonalSolver<V,I>& operator = (const LUTridiagonalSolver<V,I>& source);

	// Integrity checks
	bool validIndices() const;	// Indices and size bound OK?
	bool diagonallyDominant() const;

	// Calculate the (final) solution to Au = r
	Vector<V,I> solve();

};

////////// Double Sweep method /////////////////////////////////
// The Godunov Balayage method for solving tridiagonal systems. We
// should be careful with start and end indices. The solution vectors
// are a pair of with range:
//
//		first: [0..J] vector including the 'end' values
//		second: [1..J-1] vector excluding the 'end' values
//
// The input arrays have the following bounds:
//
//	Vector<V,I> aa;	// The lower-diagonal array [1..J]
//	Vector<V,I> bb;	// The diagonal array [1..J]
//	Vector<V,I> cc;	// The upper-diagonal array [1..J]
//	Vector<V,I> ff;	// The right-hand side of the equation Au = ff [1..J]
//
// The programmer may choose which one is more appropriate. 
//
// (C) Datasim Component Technology BV 2000-2003

#include "Vector.cpp"
#include "numericmatrix.cpp"


template <class V, class I>
class DoubleSweep
{ // The Balayage method from Godunov

private:
	
	// The vectors
	Vector<V,I> a, b, c, f;
	V left;		// Left boundary condition
	V right;	// Right boundary condition

public:
	// Constructors and destructor
	DoubleSweep();							
	DoubleSweep (const DoubleSweep<V,I>& s2);	
	
	// Create members to initialise input for AU = F, A = (a,b,c)

	DoubleSweep(const Vector<V,I>& lower, const Vector<V,I>& diagonal, 
				const Vector<V,I>& upper,
				const Vector<V,I>& RHS, const V& bc_left, const V& bc_right);
	virtual ~DoubleSweep();

	// Assignment operator
	DoubleSweep<V,I>& operator = (const DoubleSweep<V,I>& i2);

	// Result; this is a vector in range [1, J-1]
	Vector<V,I> solve();
};


////// Family of iterative matrix solvers /////////////
/* 
	We use the Template Method Pattern (Gamma 1995, GOF) to set
	up the sequence of actions to be taken in order to arrive at
	a solution. This will be a combination of pure virtual functions
	(PVMF MUST be overridden in derived classes) and default virtual 
	functions(or hooks VMF) that may be overridden in derived classes.
	Specialisations will be Jacobi and Gauss-Seidel, for example.

	The steps are (first rough cut):

			1. Initialise the start vector (VMF)
			2. Initilaise any default parameters (VMF)
			
			L1:
				3. Calculate the next vector (k+1)
				4. Calculate the difference (Strategy, L2, Linfinity) VMF
				5. Check status:
						a) Converged, then give Vector result
						b) Too many iterations, CRASH OUT, STOP
						c) Else, go to label L1

	(Remark: we use labels, humble apologies to OO purism. Everything is 
	 relative.)


*/

enum NormType {L2, LInfinity};				// L2 is default
enum IterativeType {Jacobi, GaussSeidel};	// Jacobi is default

template <class V, class I>
	 class MatrixIterativeSolver
{ // Abstract base class for all matrix iterative solvers

protected:	// So that PSOR can access the data

		// Input to class
		NumericMatrix<V, I>* m_A;		// The matrix to be inverted
		Vector<V, I>* m_b;				// The right-hand side vector
		V m_tol;						// Tolerance for convergence of sequence
		NormType m_normType;			// Norm for stopping criterion
		I m_maxiter;					// Maximum number of iterations
		V m_omega;						// Relaxation factor to speed convergence
		IterativeType m_iterativeType;	// Jacobi, Gauss Seidel
		bool m_status;					// Status of process
		I k;							// Current number of iterations

		MatrixIterativeSolver();							
		MatrixIterativeSolver (const MatrixIterativeSolver<V,I>& s2);	
		// Assignment operator
		MatrixIterativeSolver<V,I>& operator = (const MatrixIterativeSolver<V,I>& i2);

		// Temporary work space
		Vector<V, I> m_currVector;		// The solution at level k
		Vector<V,I> m_NextVector;		// The solution at level k+1

		// Nitty-gritty functions
		void calcJacobi();
		void calcGaussSeidel();

public:
		
	// Constructors and destructor (Solve Ax = b)
	MatrixIterativeSolver(NumericMatrix<V, I>& A, Vector<V, I>& b);							
	virtual ~MatrixIterativeSolver();


	// Initialisation
	virtual void startVector(const Vector<V, I>& startV);	// hook
	virtual void initParameters(const V& tolerance, const V& SORFactor,
							const I& maxIter, NormType ntype,IterativeType itype);	// hook

	// Vector at level k+1 and
	virtual void CalculateNextVector();

	// Which test for tolerance?
	virtual bool insideTolerance() const;	

	// Result; note that this vector INCLDUES BOTH end conditions (values)
	virtual void solve();
	virtual Vector<V, I> result() const;
	virtual bool status() const;				// Succeeded or not
	virtual I NumberIterations() const;
};


template <class V, class I> class PSORSolver : public MatrixIterativeSolver<V,I>
{ // The Projected SOR method

private:

	// Ingredient of problem, this is
	//
	//	Ax >= b, x >= c
	//	(x - c).(Ax - b) == 0 (inner product)
	//

	Vector<V, I>* m_c;			// The lower-bound on the solution

	Vector<V,I> m_YVector;

	PSORSolver ();
	PSORSolver (const PSORSolver<V,I>& s2);
	// Assignment operator
	PSORSolver<V,I>& operator = (const PSORSolver<V,I>& i2);

public:
	PSORSolver(NumericMatrix<V, I>& A, Vector<V, I>& b, Vector<V,I>& c);
	virtual ~PSORSolver();


	// Vector at level k+1 and
	virtual void CalculateNextVector();	// PSOR has a very special way

};


#endif