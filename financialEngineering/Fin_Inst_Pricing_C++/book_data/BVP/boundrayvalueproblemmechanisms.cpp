// boundaryvalueproblemmechanisms.cpp
//
// Classes for two-point boundary value problems and related 
// applications.
//
// Last modification dates:
//
//	DD 2003-1-18 kick-off code
//
// (C) Datasim Education BV 2003
//

#ifndef BVP_CPP
#define BVP_CPP

#include "BVPmechanisms.hpp"

/*

		ScalarFunction<V,V> a0;			// Coefficient of second derivative
		ScalarFunction<V,V> a1;			// Coefficient of first derivative
		ScalarFunction<V,V> a2;			// Coefficient of zero derivative
		ScalarFunction<V,V> f;			// Coefficient of inhomogeneous term

		Range<V> dom;			// The interval of interest

		V LBC;					// Left boundary condition
		V RBC;					// Right boundary condition
*/

template <class V>	BoundaryValueProblem<V>::BoundaryValueProblem(const ScalarFunction<V,V>& diffusion, const ScalarFunction<V,V>& convection,
								const ScalarFunction<V,V>& zero, const ScalarFunction<V,V>& RHS,
								const Range<V> domain, const V& leftBC, const V& rightBC)
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
template <class V> ScalarFunction<V,V> BoundaryValueProblem<V>::Diffusion() const
{

		return a0;
}


template <class V> ScalarFunction<V,V> BoundaryValueProblem<V>::Convection() const
{
		return a1;
}


template <class V> ScalarFunction<V,V> BoundaryValueProblem<V>::ZeroTerm() const
{
		return a2;
}


template <class V> ScalarFunction<V,V> BoundaryValueProblem<V>::F() const
{
		return f;
}


template <class V> Range<V> BoundaryValueProblem<V>::Domain() const
{
		return dom;
}


template <class V>V BoundaryValueProblem<V>::LeftBC() const
{
		return LBC;
}


template <class V>V BoundaryValueProblem<V>::RightBC() const
{
		return RBC;
}



#endif