// Ode.hpp
//
// Class for two-point BVP where the boundary conditions
// are delegated to Bridge.
//
// PROTOTYPE
//
// (C) Datasim Education BV 2008

// #include "BCImpl.hpp"

#ifndef Fdm_hpp
#define Fdm_hpp

class BCImpl;

#include "NumericMatrix.cpp"
#include "Vector.cpp"

class Fdm
{ // u'' = f
private:
	//	double (*f) (double x);	// RHS
		BCImpl* bcl;
		BCImpl* bcr;

		long N;	// number of subdivisions

public:
		NumericMatrix<double, long> A;
		Vector<double, long> b;

public: 
		Fdm(/*double (*RHS) (double x),*/  BCImpl& Left,  BCImpl& Right, 
			 long NSteps);

};

#endif