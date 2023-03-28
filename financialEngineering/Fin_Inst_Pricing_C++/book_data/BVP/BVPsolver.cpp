// BVPsolver.cpp
//
// Numerical methods for solving boundary value problems
// 
// Last modification dates:
//
//	DD 2003-1-18 kick-off code
//
//
// (C) Datasim Education BV 2003
//

#ifndef BVPSolver_CPP
#define BVPSolver_CPP

#include "bvpsolver.hpp"
#include "doublesweep.cpp"

// Set the necessary discrete quantities

template <class V, class I> Vector<V,I> BoundaryValueProblemSolver<V,I>::solve()
{
	
		Vector<V, I> xarr(J-1,1);
		V h = src -> Domain().length() / V(J);
		V h2 = h*h;

		xarr[1] = h;
		for (I j = xarr.MinIndex() + 1; j <= xarr.MaxIndex(); j++)
		{
			xarr[j] = xarr[j-1] + h;
		}

		V a0x, a1x, a2x;
		// Create the 3 vectors for the tridiagonal matrix
		Vector<V,I> a(J-1, 1), b(J-1, 1), c(J-1,1), f(J-1,1);

		for (j = a.MinIndex(); j <= a.MaxIndex(); j++)
		{
			a0x = src -> Diffusion().calculate(xarr[j]);
			a1x = src -> Convection().calculate(xarr[j]);
			a2x = src -> ZeroTerm().calculate(xarr[j]);
	
			a[j] = (a0x/h2) + (a1x/h)*0.5;
			b[j] = a2x - (2.0*a0x)/h2;
			c[j] = (a0x/h2) - (a1x/h)*0.5;
	
		}

		DoubleSweep<V, I> solver(a, b, c, f, src -> LeftBC(), src -> RightBC());

		Vector<V,I> result = solver.solve();

		return result;

				
}


#endif