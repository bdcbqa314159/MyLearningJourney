// doublesweep.hpp
// 
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

#ifndef DOUBLESWEEP_HPP
#define DOUBLESWEEP_HPP

#include "Vector.cpp"

template <class V, class I>
class DoubleSweep
{ // The Balayage method from Godunov

private:
	
	// The vectors
	Vector<V,I> aa, bb, cc, ff;
	V left;		// Left boundary condition
	V right;	// Right boundary condition

public:
	// Constructors and destructor
	DoubleSweep();							
	DoubleSweep (const DoubleSweep<V,I>& s2);	
	
	// Create members to initialise input for AU = F, A = (a,b,c)

	DoubleSweep(const Vector<V,I>& a, const Vector<V,I>& b, 
				const Vector<V,I>& c,
				const Vector<V,I>& f, const V& bc_left, const V& bc_right);
	virtual ~DoubleSweep();

	// Assignment operator
	DoubleSweep<V,I>& operator = (const DoubleSweep<V,I>& i2);

	// Result; this is a vector in range [1, J-1]
	Vector<V,I> solve();
};


#endif
