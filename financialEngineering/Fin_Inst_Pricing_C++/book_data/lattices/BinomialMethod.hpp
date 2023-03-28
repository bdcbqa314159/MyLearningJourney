// BinomialMethod.hpp
//
// An encapsulation of the Binomial Method
//
// (C) Datasim Education BV 2004
//

#ifndef BinomialMethod_hpp
#define BinomialMethod_hpp

#include "optionparameters.hpp"
#include "binomialparameters.hpp"
#include "latticemechanisms.cpp"
#include <math.h>

class BinomialMethod
{
private:

		//OptionParameters* optdata;			// Option data here
		//BinomialParameters* data2;		// Binomial related parameters

		// enum ExerciseType {EuropeanExerciseType, AmericanExerciseType};
		// enum OptionType {PutOptionType, CallOptionType};
		ExerciseType etyp;
		OptionType otyp;


		// Redundant data (for possible later retrieval)
		Lattice<double, int> Ulattice;			// Underlying
		Lattice<double, int> Derlattice;		// Derivative quantity

		Vector<double, int> RHS;				// Vector of known payoff function

		double optionPrice;						// Calculated option price


public:
	BinomialMethod (const OptionParameters& optdata, const BinomialParameters& bparam,
							ExerciseType exerciseType, OptionType optionType)
	{

		// 1. Create the basic lattice containing the underlying values (e.g. Stock, interest rate)
		LatticeType lattice = BinomialLatticeType;
		Lattice<double, int> Ulattice(bparam.N, lattice);

		// 2. Now modify the lattice by producing the up and down stuff
		// Later encapsulate this in a Strategy
		double rootValue = optdata.U;	// Stock price now, for example
		double D0 = optdata.b;			// Dividend yield (cost of carry)
		double vol = optdata.vol;		// Volatility
		double r = optdata.r;			// Interest
		double T = optdata.T;			// Time to expiry

		double k = T / bparam.N;

		double e = ::exp((r-D0)*k);
		double sr = ::sqrt(exp(vol*vol*k) - 1.0);


		double up = e * (1.0 + sr);
		double down = e * (1.0 - sr);

		// 3. Call the function from LatticeMechanisms package
		modify(Ulattice, rootValue, up, down);


		// Postcondition: we now have the complete lattice for the underlying asset

		// 4. Now set up the discrete payoff function
		if (optionType == CallOptionType)
		{

			RHS = CallPayOff(optdata.K, Ulattice[Ulattice.MaxIndex()]);
		}
		else // Put
		{

			RHS = PutPayOff(optdata.K, Ulattice[Ulattice.MaxIndex()]);
		}

	
		// 5. Now calculate the lattice of (European) option prices
		double probValue = 0.5;
		double discounting = ::exp(- r*k);

		Derlattice  = Lattice<double, int>(Ulattice);	// Will be initialised in traverse()
		optionPrice = traverse(Ulattice, RHS, probValue, discounting, exerciseType, Derlattice);
	}
	
};


#endif


