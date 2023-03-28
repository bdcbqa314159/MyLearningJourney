// BVPmechanisms.cpp
//
// Classes for two-point boundary value problems and related 
// applications.
//
// Last modification dates:
//
//	DD 2003-1-18 kick-off code
//	DD 2003-8-21 new function classes (from chapter 9 of the DD book)
//
// (C) Datasim Education BV 2003
//

#ifndef BVP_CPP
#define BVP_CPP

#include "BVPmechanisms.hpp"

/*

		AtomicDFunction<V,V>  a0;			// Coefficient of second derivative
		AtomicDFunction<V,V>  a1;			// Coefficient of first derivative
		AtomicDFunction<V,V>  a2;			// Coefficient of zero derivative
		AtomicDFunction<V,V>  f;				// Coefficient of inhomogeneous term

		Range<V> dom;			// The interval of interest

		V LBC;					// Left boundary condition
		V RBC;					// Right boundary condition
*/



template <class V>	BoundaryValueProblem<V>::BoundaryValueProblem( V (*diffusion) (const V& x),  V (*convection) (const V& x),  
							V (*zero) (const V& x),  V (*RHS) (const V& x),
							const Range<V>& domain, const V& leftBC, const V& rightBC)
{

	a0 = AtomicDFunction<V,V> (diffusion);
	a1 = AtomicDFunction<V,V> (convection);
	a2 = AtomicDFunction<V,V> (zero);
	f = AtomicDFunction<V,V> (RHS);

	dom = domain;

	LBC = leftBC;
	RBC = rightBC;
	
}

template <class V>	BoundaryValueProblem<V>::BoundaryValueProblem(const AtomicDFunction<V,V> & diffusion, const AtomicDFunction<V,V> & convection,
								const AtomicDFunction<V,V> & zero, const AtomicDFunction<V,V> & RHS,
								const Range<V>& domain, const V& leftBC, const V& rightBC)
{

	a0 = diffusion;
	a1 = convection;
	a2 = zero;
	f = RHS;

	dom = domain;

	LBC = leftBC;
	RBC = rightBC;
	
}

// Selector for the entities of interest
template <class V> AtomicDFunction<V,V>  BoundaryValueProblem<V>::Diffusion() const
{

		return a0;
}


template <class V> AtomicDFunction<V,V>  BoundaryValueProblem<V>::Convection() const
{
		return a1;
}


template <class V> AtomicDFunction<V,V>  BoundaryValueProblem<V>::ZeroTerm() const
{
		return a2;
}


template <class V> AtomicDFunction<V,V>  BoundaryValueProblem<V>::F() const
{
		return f;
}


template <class V> Range<V> BoundaryValueProblem<V>::Domain() const
{
		return dom;
}


template <class V> V BoundaryValueProblem<V>::LeftBC() const
{
		return LBC;
}


template <class V> V BoundaryValueProblem<V>::RightBC() const
{
		return RBC;
}



#endif