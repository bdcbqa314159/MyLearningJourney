
/**************************************************************************
 *             Functions.hpp --  by R. Mirani - 1/5/2002                  *
 *                                                                        *
 *     Contains all functions: No stochastics, Exact Solution, Euler,     *
 *        Fitted Euler, Implicit Euler, Crank Nicolson, Fitted CK,        *
 *     Double Fitted CK, Richardson, Milstein and Predictor Corrector     *
 *                                                                        *
 **************************************************************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "range.cpp"
#include "Vector.cpp"
#include "math.h"

enum PROCESSES { GEOMETRIC, SQUARE_ROOT, MEAN_REVERTING };

enum METHODS { EXACT,
               EULER,
               FITTED_EULER,
               IMPLICIT_EULER,
               CRANK_NICOLSON,
               FITTED_CRANK_NICOLSON,
							 MILSTEIN,
							 FITTED_MILSTEIN,
							 FITTED_PREDICTOR_CORRECTOR,
							 PREDICTOR_CORRECTOR,
							 END_OF_METHODS};
							

class Functions{

public:

	// constructor
	Functions();
	
	// destructor
	~Functions();
	
	// Perform the run
	bool PerformRun(double & y,                    // perform the run
	                const int & Process,
                  const int & Method,
				      		const int & steps,
				      		const Range<double> & t_range,
					        const Vector<double,int> & v,
						      double (*a_function)(double),
						      double (*b_function)(double),
						      double (*c_function)(double));
		
	// retrieve the results stored in the vectors Time_Axis and Y_Axis
	void GetResults(Vector<double,int> & Time,Vector<double,int> & Y);
				
private:
	bool flag;                        // false in no run ever performed
	
	Vector<double,int> * Time_Axis;   // stores the values at the time axis
	Vector<double,int> * Y_Axis;      // stores the results at the Y-axis
	int process;      	 			        // process used
  int method;                       // method used
	int timestep;                     // current timestep
  Range<double> T_interval;         // time interval of interest
	Vector<double,int> Normal;        // Vector with (0,k) normally distributed variables
	double k;                         // timestep size
	double time;                      // current time
	
private:	
	void Initialize(const int & Process,		// initializes all the variables
                  const int & Method,
						      const int & steps,
						      const Range<double> & t_range,
					        const Vector<double,int> & v,
						      double (*a_function)(double),
						      double (*b_function)(double),
						      double (*c_function)(double));

	bool Finished(void) const;	      // check if end of run has been reached
	void advance(double & y);			    // advance to next timestep
	
/*	const double (*a)(double);	      // Drift function pointer
	const double (*b)(double);        // Diffusion function pointer
	const double (*c)(double);        // Mean reverting function pointer !! const NOT WORK */

	double (*a)(double);	      // Drift function pointer
	double (*b)(double);        // Diffusion function pointer
	double (*c)(double);        // Mean reverting function pointer
	
	
	bool CanNotPerform(void);               // check if combination method+process is possible
	bool DoNotRun(void);                    // called if current method can not perform current process

	
	/**********************************************/
	/*   A WHOLE BUNCH OF MATHEMATICAL FUNCTIONS  */
	/**********************************************/
	
	double Compute(const double & y,         // compute the next y with the given variables
					  		 const double & alpha,
                 const double & xi,
                 const double & eta,
                 const double & Q,
                 const double & W,
                 const bool & flag,
                 const bool & flag_t);

	double Factor1(const double & y,        // explicit factor
                 const double & alpha,
                 const double & xi,
                 const double & Q,
                 const double & W,
                 const bool & flag,
                 const bool & flag_t);

	double Factor2(const double & alpha,    // implicit factor
                 const double & xi,
                 const double & W,
                 const bool & flag,
                 const bool & flag_t);
	double Factor3(const double & eta);     // additional factor for mean reverting
	
	double Part1(const double & alpha,      // first part of factor 1 and 2
               const double & T,
               const bool & flag);

	double Part2(const double & alpha,      // second part of factor 1 and 2
               const double & xi,
               const double & W,
               const double & T,
               const bool & flag);

	double Part3(const double & xi,         // third part of factor 1 and 2
               const double & T,
               const bool & flag_t);

	double Sigma(const double & t);         // fitting factor
	
	double Sigma_t(const double & t);       // Noise fitting factor
	
	double Pow(const double & y,            // my own power function
	           const double & factor);
	
	/***************************************/
	/*             THE METHODS             */
	/***************************************/
	
	void No_Stochastics(double & y);	      // Wiener process is ignored

	void Exact_Solution(double & y);	      // Analytical solution for geometric process
			
	void Euler(double & y);						      // The Euler method
			
	void Fitted_Euler(double & y);          // The Fitted Euler method
				
	void Implicit_Euler(double & y);        // The Implicit Euler method
	
	void Crank_Nicolson(double & y);        // The Crank-Nicolson method
		
	void Fitted_Crank_Nicolson(double & y); // The Fitted Crank-Nicolson method

	void Double_Fitted(double & y);         // The Double Fitted Crank-Nicolson method

	void Milstein(double & y);              // The Milstein method

	void Fitted_Milstein(double & y);       // The Fitted Milstein method
	
	void Fitted_Predictor_Corrector(double &y); // The Fitted Predictor Corrector Method
	
	void Predictor_Corrector(double & y);   // The Predictor Corrector method
	
};

#endif
