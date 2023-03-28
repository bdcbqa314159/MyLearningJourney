// ivpsolver.hpp
//
// Solvers for initial value problems
//
// (C) Datasim Component Technology BV 2003
//

#ifndef IVPSolver_hpp
#define IVPSolver_hpp


#include "ivp.cpp"
#include "vector.cpp"

enum FDMType {EEuler, IEuler, Box, Trap, Fitted, FittedBox, ExtrapEuler, PC};		// Basic one-step schemes


template <class V, class I> class  ScalarIVPSolver
{ // Set of finite difference to solve scalar initial
  // value problems

private:
	
	ScalarIVP<V>* ivp;		// Pointer to 'parent'

	FDMType typ;			// Which scheme?

	I N;					// The number of subdivision of interval in IVP 

	ScalarIVPSolver(const  ScalarIVPSolver<V,I>& source); 
	ScalarIVPSolver<V,I>& operator = (const  ScalarIVPSolver<V,I>& source);

	// Help functions (Strategy) and redundant data
	V k;					// Step length; redundant data but is efficient				
	Vector<V, I> res;		// Will contain the results of the calculations

	void eeuler();
	void ieuler();
	void box();
	void trap();
	void fitted();
	void fittedbox();
	void extrapeuler();
	void predictorCorrector();


public:
	ScalarIVPSolver();
	ScalarIVPSolver(ScalarIVP<V>& source, FDMType type);
	
	virtual ~ScalarIVPSolver();
 	
	// Modifier functions
	void steps(const I& Nsteps);
	void setType(FDMType type);

	// Output
	V stepSize() const;

	// N.B. !!! Resulting output of size N+1 and start index 1 !!!!!!1
	Vector<V, I> result();		// The result of the calculation

		
};



#endif
