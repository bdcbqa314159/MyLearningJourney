// miscfun.hxx
//
// Header file for miscellaneous functions which act as server
// functions in the statistics classes. This class will be superseded
// by more specific classes. The functionality offered here can be used in
// areas such as mathematical physics and in the solution of second order
// differential equations.
//
// (C) Datasim Education BV 1992-2003

#ifndef MISCFUN_HXX
#define MISCFUN_HXX

class MISCFUN
{ // Class of miscellaneous functions which can be applied in
  // different circumstances.


private:
	// Miscfun has no member data since it is not needed.
	// The values returned by its member functions are more
	// important.

	// Member functions which are not directly needed by client
	// software since they represent implementation details about
	// how certain values should be calculated.

	// A function which help to calculate intermediate values
	// in the incomplete gamma function depending on the relative
	// sizes of the arguments a and x.
//	static double gamma_series(double a, double x);

public:
	// Constructors
	MISCFUN();                        // Empty constructor

	// Factorials and combinatorial functions
	static double fact(int n);               // The factorial of an integer
	static double combination(int n, int k); // Number of combinations of n items taking k at a time

	// Complete and incomplete gamma functions. Note that we use function
	// overloading for the function 'gamma'.
	static double gamma(int k);              // The gamma function = (k-1)!

	
	static double gamma(double r);           // The gamma function

	/*
	static double gamma(double a, double x); // Incomplete gamma function
	static double gammac(double a, double x);
					  // Complement of incomplete gamma function

	// The beta function
	static double beta(double z, double w);

	// Error functions
	static double erf(double x);             // Error function
	static double erfc(double x);            // Complementary error function */
/*
	// Other functions
	static pow(double x, double k);			// x^ k
	static exp(double x);					// Exponential function
*/
};

#endif



