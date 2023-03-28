// BVPmechanisms.hpp
//
// Classes for two-point boundary value problems and related 
// applications. 
// Note that we focus exclusively on Dirichlet boundary conditions.
//
// (C) Datasim Education BV 2003
//

#ifndef BVP_HPP
#define BVP_HPP

#include "detfunction.cpp"
#include "range.cpp"


template <class V> class BoundaryValueProblem
{ // Class that models two-point boundary value problems with Dirichlet BC
public:
		AtomicDFunction<V,V>  a0;	// Coefficient of second derivative
		AtomicDFunction<V,V>  a1;	// Coefficient of first derivative
		AtomicDFunction<V,V>  a2;	// Coefficient of zero derivative
		AtomicDFunction<V,V>  f;		// Coefficient of inhomogeneous term

		Range<V> dom;			// The interval of interest

		V LBC;					// Left boundary condition
		V RBC;					// Right boundary condition

public:
	BoundaryValueProblem() {}
		BoundaryValueProblem( V (*diffusion) (const V& x),  V (*convection) (const V& x),  
							V (*zero) (const V& x),  V (*RHS) (const V& x),
							const Range<V>& domain, const V& leftBC, const V& rightBC);

		BoundaryValueProblem(const AtomicDFunction<V,V>& diffusion, const AtomicDFunction<V,V>& convection,
							const AtomicDFunction<V,V>& zero, const AtomicDFunction<V,V>& RHS,
							const Range<V>& domain, const V& leftBC, const V& rightBC);

		virtual ~BoundaryValueProblem() {}

		// Selector for the entities of interest
		AtomicDFunction<V,V> Diffusion() const;
		AtomicDFunction<V,V> Convection() const;
		AtomicDFunction<V,V> ZeroTerm() const;
		AtomicDFunction<V,V> F() const;

		Range<V> Domain() const;

		V LeftBC() const;
		V RightBC() const;
};


#endif