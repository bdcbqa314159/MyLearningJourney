// Ode.cpp
//
// Class for two-point BVP where the boundary conditions
// are delegated to Bridge.
//
// PROTOTYPE
//
// (C) Datasim Education BV 2008

#include "Ode.hpp"
#include "BCImpl.hpp"

Fdm::Fdm(/*double (*RHS) (double x),*/  BCImpl& Left,  BCImpl& Right, 
			 long NSteps)
{

			bcl = &Left;
			bcr = &Right;
			N = NSteps;
			double h = 1.0 / double (N);
			Vector<double, long> mesh(N + 1, 1);
			double val = 0.0;
			for (long i = 1; i <= NSteps + 1; i++)	
			{
				mesh[i] = val;
				val += h;
			}

			A = NumericMatrix<double, long> (N+1, N+1, 1, 1);
			b = Vector<double, long> (N+1, 1);

			// Initialise the matrix in interior
			for (long i = A.MaxRowIndex()+ 1; i <= A.MaxRowIndex()  - 1; ++i)
			{
				for (long j = A.MaxColumnIndex(); j <= A.MaxColumnIndex(); ++j)
				{
					A(i, j) = 0.0;
					A(i, i-1) = 1.0;
					A(i, i) = -2.0;
					A(i, i+1) = 1.0;
				}
			}

			bcl->modify(*this);
			bcr->modify(*this);
}