// detfunction.hpp
//
// Deterministic functions. This is the base class for all kinds of 
// deterministic functions. Included are:
//
//		Atomic functions
//		Vector functions
//		Vector-valued functions
//		Real-valued functions
//		Vector-valued and matrix-valued functions
//		Functions of another function
//		Lists/arrays of functions
//
// (C) Datasim Component Technology BV 2004
//

#ifndef DFunction_HPP
#define DFunction_HPP

#include "function.cpp"

//altered 1/5/2002 by R. Mirani
//#include "numericmatrix.cpp"
#include "NumericMatrix.cpp"

#include "pair.hpp"

template <class D, class R> class DFunction: public Function <D, R>
{ // Abstract base class for all deterministic functions

public:
	DFunction() {}


};

// Basic building blocks

template <class D, class R> class AtomicDFunction : public DFunction<D, R>
{
private:

		R (*f)(const D& x);		// Hidden classic C-type function

public:
	AtomicDFunction();
	AtomicDFunction (R (*fp)(const D& x));	// Using function objects
	AtomicDFunction(const AtomicDFunction<D, R>& f2);
	virtual ~AtomicDFunction();
	AtomicDFunction<D, R>& operator = (const AtomicDFunction<D, R>& f2);

	virtual R calculate(const D& x) const;

	// Choosing a new function
	void function(R (*fp)(const D& x));

	// Mathematical operations between 2 functions
	// Function <OP> Function
	R add(const AtomicDFunction<D,R>& f2, const D& x) const;	// +

};

template <class D1, class D2, class R> class TwoVarDFunction : public AtomicDFunction<pair<D1, D2>, R>
{ // A class representing a function of two variables. This is useful in PDE.

private:
		
public:
	// Constructors
	TwoVarDFunction();
	
	TwoVarDFunction (R (*fp)(const pair<D1,D2>&));	// 'Normal' C functions as input	
	
	TwoVarDFunction(const TwoVarDFunction<D1,D2,R>& f2);
	virtual ~TwoVarDFunction();

	TwoVarDFunction<D1, D2, R>& operator = (const TwoVarDFunction<D1, D2,R>& f2);

	
	// We need to instantiate both d1 and d2 and give an R!
	R calculate(const D1& d1, const D2& d2) const;

};



#endif