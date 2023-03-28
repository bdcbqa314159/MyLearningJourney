// parabolicFDM.hpp
//
// Finite difference method for Parabolic PDE. It is
//  specific to Duffy's fitted scheme.
// 
// (C) Datasim Component Technology BV 2000
//


#ifndef FDM_HPP
#define FDM_HPP


#include "parabolicpde.cpp"
//#include "NumericMatrix.cpp"
#include "doublesweep.hpp"

template <class X, class T, class V> class ParabolicFDM
{ // Finite difference method for solving parabolic PDE
  // X == x-direction value; T == t direction value; V == value space of unknown
private:

	//The function coth
	V coth(const V& x) const;

	// The corresponding PDE (where all the functions are 'hiding')
	ParabolicPDE<X, T, V> pde;

	// Input parameters
	long J;		// Number of x steps
	long N;		// Number of t steps
	V theta;	// Time discretistion (Implicit == 1, CN == 0.5, Explicit == 0)

	// Dynamic attribute
	T current;	// Current time level
	long icurrent;

	// Calculated values
	V h;		// Mesh size in x
	T k;		// Mesh size in t
	
	Vector<X, long> XARR;	// The array of x (S) values
	Vector<T, long> TARR;	// The array of t values

// Matrix coefficients

	// Special functions for setting up tridiagonal matrices
	V A(const X& x, const T& t) const;
	
	// 2002-17-5 RM ::B doesn't need Delta_t
	//V B(const X& x, const T& t, const T& Delta_t) const;
	V B(const X& x, const T& t) const;
	
	V C(const X& x, const T& t) const;
	V F(const X& x, const T& t) const ; // RHS function

	V IC(const X& x) const;	// initial condition
	
	V fitting_factor (const X& x, const T& t) const;

	// Vectors representing the diagonals of the tridiagonal matrix
	// The length of each vectors is [1, N-1]
	Vector<V,long> Adiscrete (const T& t) const;
	Vector<V,long> Bdiscrete(const T& t) const;
	Vector<V,long> Cdiscrete(const T& t) const;
	Vector<V,long> Fdiscrete(const T& t) const; // RHS function

//	NumericMatrix<V,long> mresult;	// The BIG matrix with all values
	
	// The results of the computation; arrays of values in range [1, J-1]
	Vector<V, long> tmp;		// Value at current time level n
	
	// 2002-22-5 RM "next" is not needed
	//Vector<V, long> next;		// Value at next time level n+1
	
	
	Vector<V, long> res;		// End-result

	void init();	// Initialise all arrays/matrices


public:
	ParabolicFDM(const ParabolicPDE<X,T,V>& context, long Xintervals, long Tintervals, 
				const V& time_discretisation_type);

	// The computational scenario
	void start();					// Initial condition specified
	void advance();					// Next time level
	bool finished() const;			// Have we reached t == T?

	Vector<X, long> xarr() { return XARR; }	// The array of x (S) values

	// Results
	Vector<V, long> line() const;			// Current vector output
//	NumericMatrix<V, long> result() const;	// Solution so far
	
};

#endif