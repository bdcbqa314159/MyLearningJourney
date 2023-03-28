// chisdist.hxx
//
//	The Chi-Square distribution. This is a special case of the Gamma
//	distribution (Alpha, r) with alpha = 0.5 and r = n * 0.5 where n is 
//	a natural number. We say that this is a chi-square distribution with n 
//	degrees of freedom.
//
// Copyright (C) Datasim Education BV 1994-2000

#ifndef ChiSquare_HXX
#define ChiSquare_HXX

#include "gammdist.hxx"

template <class T> class ChiSquare : public Gamma<T>
{ // The ChiSquare probability function 

private:

	// Number of degrees of freedom in private state of class Gamma

public:
	// Constructors
	ChiSquare();      
	ChiSquare(int degree_of_freedom); 


};

#endif
