
#ifndef RANDOM_H
#define RANDOM_H

#include "Vector.cpp"
#include "ran.h"

#include <math.h>
//#include <unistd.h> Linux

class Random{

public:
	Random();
	~Random();
	
	// Fills Vector v with iNumber normally distributed numbers
	void Normal (Vector<double,int> & v,
							 const int & iNumber,
							 const double & Mu,
							 const double & Var);

private:						
	// Draws two normally distributed random numbers with Polar Marsaglia method
	void PolarMarsaglia (double & N1, double & N2);

	// Initializes the Seed with the clock
	void InitSeed (t_seed & Seed);
};

#endif
