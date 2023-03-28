// TestBC.cpp
// 
// Test Bridge implementation of Bridge.
//
// (C) Datasim Education BV 2008
//
#include "Ode.hpp"
#include "BCImpl.hpp"

#include "MatrixMechanisms.cpp"


int main()
{

	Dirichlet d (-1.0);
	Neumann n(2.0);

	long N = 6;
	Fdm fdm(d, n, N);

	print( fdm.A);

	return 0;
}
