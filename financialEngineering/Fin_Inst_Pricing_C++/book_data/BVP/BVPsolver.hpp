// BVPsolver.hpp
//
// 
// Numerical methods for solving boundary value problems
//
// (C) Datasim Education BV 2002
//

#ifndef BVPSolver_HPP
#define BVPSolver_HPP

#include "BVPmechanisms.hpp"
#include "vector.cpp"


template <class V, class I> class BoundaryValueProblemSolver
{
private:
		BoundaryValueProblem<V>* src;	// All relevant info is here
		I J;							// Number of subdivisions
public:
	BoundaryValueProblemSolver() {}
	BoundaryValueProblemSolver(BoundaryValueProblem<V>& source, const I& JJ) 
	{ src = &source;
		J = JJ; }

	virtual ~BoundaryValueProblemSolver() {}

	// Set the necessary discrete quantities

	Vector<V,I> solve();
};

#endif