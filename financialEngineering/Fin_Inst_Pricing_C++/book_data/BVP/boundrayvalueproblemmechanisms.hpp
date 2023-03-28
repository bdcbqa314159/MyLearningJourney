// boundaryvalueproblemmechanisms.hpp
//
// Classes for two-point boundary value problems and related 
// applications.
//
// (C) Datasim Education BV 2003
//

#ifndef BVP_HPP
#define BVP_HPP

#include "detfunction.cpp"


template <class V> typedef ScalarFunction<V,V,int> BVPFunction;

template <class V> class BoundaryValueProblem
{ // Class that models two-point boundary value problems with Dirichlet BC
public:
		BVPFunction a0;			// Coefficient of second derivative
		BVPFunction a1;			// Coefficient of first derivative
		BVPFunction a2;			// Coefficient of zero derivative
		BVPFunction f;			// Coefficient of inhomogeneous term

		Range<V> dom;			// The interval of interest

		V LBC;					// Left boundary condition
		V RBC;					// Right boundary condition

public:
	// other constructors !!!
		BoundaryValueProblem(const BVPFunction& diffusion, const BVPFunction& convection,
								const BVPFunction& zero, const BVPFunction& RHS,
								const Range<V> domain, const V& leftBC, const V& rightBC);

		// Selector for the entities of interest
		BVFunction Diffusion() const;
		BVFunction Convection() const;
		BVFunction ZeroTerm() const;
		BVFunction F() const;

		Range<V> Domain() const;

		V LeftBC() const;
		V RightBC() const;
};


#endif