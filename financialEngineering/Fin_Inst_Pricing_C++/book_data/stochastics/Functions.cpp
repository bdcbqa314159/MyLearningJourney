
/**************************************************************************
 *             Functions.cpp --  by R. Mirani - 1/5/2002                   *
 *                                                                        *
 *     Contains all functions: No stochastics, Exact Solution, Euler,     *
 *        Fitted Euler, Implicit Euler, Crank Nicolson, Fitted CK,        *
 *     Double Fitted CK, Richardson, Milstein and Predictor Corrector     *
 *                                                                        *
 **************************************************************************/

#include "Functions.hpp"
#include <iostream.h>
#include <stdlib.h>

Functions::Functions():flag(false){;}

Functions::~Functions()
{
	delete Time_Axis;
	Time_Axis = 0;
	
	delete Y_Axis;
	Y_Axis = 0;
}

bool Functions::Finished(void) const
{ return ( time > T_interval.high() - 0.5*k ); }

bool Functions::PerformRun(double & y,
                           const int & Process,
                           const int & Method,
				      		         const int & steps,
				      		         const Range<double> & t_range,
					                 const Vector<double,int> & v,
						               double (*a_function)(double),
						               double (*b_function)(double),
						               double (*c_function)(double))
{
	// initialize all the variables
	Initialize(Process,Method,steps,t_range,v,a_function,b_function,c_function);

	// check if current process and method can be combined
	if(CanNotPerform())
		return false;
	
	while(!Finished())
		advance(y);
	
	return true;	
}

void Functions::Initialize(const int & Process,
     			                 const int & Method,
							  					 const int & steps,
										  		 const Range<double> & t_range,
										  		 const Vector<double,int> & v,
										  		 double (*a_function)(double),
						          		 double (*b_function)(double),
						          		 double (*c_function)(double))
{
	process = Process;
	method = Method;
	T_interval = t_range;
	Normal = v;
	a = a_function;
	b = b_function;
	c = c_function;	
	timestep = 0;
	k = t_range.spread()/steps;
	time = t_range.low();
	if(flag)
	{
		delete Time_Axis;
		delete Y_Axis;
	}
	Time_Axis = new Vector<double,int>(steps,1);
	Y_Axis = new Vector<double,int>(steps,1);
	flag=true;
}

void Functions::GetResults(Vector<double,int> & Time,Vector<double,int> & Y)
{
	Time = *Time_Axis;
	Y = *Y_Axis;
}

void Functions::advance(double & y)
{
	// increase timestep
	timestep++;
	
	// Set the time to the value at the next timestep
	time = k*timestep;	

	//The integer "method" indicates the method to be used
	switch(method){
	
	case EXACT:
		Exact_Solution ( y );
		break;
				
	case EULER:
		Euler ( y );
	 	break;
	
	case FITTED_EULER:
		Fitted_Euler ( y );
	 	break;
		
	case IMPLICIT_EULER:
		Implicit_Euler ( y );
		break;
		
	case CRANK_NICOLSON:
		Crank_Nicolson ( y );
		break;
		
	case FITTED_CRANK_NICOLSON:
		Fitted_Crank_Nicolson ( y );
		break;
		
	case MILSTEIN:		
		Milstein ( y );
		break;
		
	case FITTED_MILSTEIN:
		Fitted_Milstein ( y );
		break;
		
	case FITTED_PREDICTOR_CORRECTOR:
		Fitted_Predictor_Corrector ( y );	
		break;
		
	case PREDICTOR_CORRECTOR:
		Predictor_Corrector ( y );
		break;
		
	default:
		cout<<"Error: method out of range\n";
		exit(0);
		break;
	}
	
	// Store the values at the x- and y- axis
//	Time_Axis->Element(timestep,time);
//	Y_Axis->Element(timestep,y);

	(*Time_Axis)[timestep] = time;
	(*Y_Axis)[timestep] = y;
}

void Functions::Exact_Solution(double & y)
{
	double factor1,factor2;
	double exp_factor;
	double T;
	
	// time is at middle of the timestep
	T = time - 0.5*k;
	
	factor1 = (a(T) - 0.5 * b(T) * b(T)) * k;
	factor2 = b(T) * Normal[ timestep ];
	exp_factor = exp( factor1 + factor2 );
		
	y = y * exp_factor;
}

void Functions::Euler(double & y)
{
	double alpha=0, xi=0, eta=0.5, Q=1;
	double W = ( process == SQUARE_ROOT ) ? 0.5 : 1;
	bool flag=false, flag_t=false;
	
	double new_y = Compute(y,alpha,xi,eta,Q,W,flag,flag_t);
	
	y = new_y;
}

void Functions::Fitted_Euler(double & y)
{	
	double alpha=0, xi=0, eta=0.5, Q=1;
	double W = ( process == SQUARE_ROOT ) ? 0.5 : 1;
	bool flag=true;
	bool flag_t = ( process == SQUARE_ROOT ) ? false : true;
	
	double new_y = Compute(y,alpha,xi,eta,Q,W,flag,flag_t);
	
	y = new_y;
}
			
void Functions::Implicit_Euler(double & y)
{	
	double alpha=1, xi=1, eta=0.5, Q=1, W=1;
	bool flag=false, flag_t=false;
	
	double new_y = Compute(y,alpha,xi,eta,Q,W,flag,flag_t);
	
	y = new_y;
}

void Functions::Crank_Nicolson(double & y)
{
	double alpha=0.5, xi=0.5, eta=0.5, Q=1, W=1;
	bool flag=false, flag_t=false;
	
	double new_y = Compute(y,alpha,xi,eta,Q,W,flag,flag_t);
	
	y = new_y;
}
	
void Functions::Fitted_Crank_Nicolson(double & y)
{
	double alpha=0.5, xi=0.5, eta=0.5, Q=1, W=1;
	bool flag=true, flag_t=true;
	
	double new_y = Compute(y,alpha,xi,eta,Q,W,flag,flag_t);
	
	y = new_y;
}

void Functions::Milstein(double & y)
{
	double alpha=0, xi=0, eta=0.5, Q=1;
	double W = ( process == SQUARE_ROOT ) ? 0.5 : 1;
	bool flag=false, flag_t=false;
	
	double new_y = Compute(y,alpha,xi,eta,Q,W,flag,flag_t);
	
	double T = time - k;
	
	new_y += 0.5*b(T)*b(T)*W*Pow(y,2*W-1)*(Normal[timestep]*Normal[timestep] - k);

	y = new_y;
}

void Functions::Fitted_Milstein(double & y)
{
	double alpha=0, xi=0, eta=0.5, Q=1;
	double W = ( process == SQUARE_ROOT ) ? 0.5 : 1;
	bool flag=true, flag_t=true;
	
	double new_y = Compute(y,alpha,xi,eta,Q,W,flag,flag_t);
	
	double T = time - k;
	
	new_y += 0.5*b(T)*b(T)*W*Pow(y,2*W-1)*(Normal[timestep]*Normal[timestep] - k);

	y = new_y;
}

void Functions::Predictor_Corrector(double & y)
{
	double alpha=0.5, xi=0.5, eta=0.5, Q=1;
	double W = (process == SQUARE_ROOT) ? 0.5 : 1;
	bool flag = false, flag_t = false;
	
	// predictor is determined with Euler
	double predictor=y;
	Euler(predictor);
	
	double factor1=Factor1(y,alpha,xi,Q,W,flag,flag_t);
	double factor3=Factor3(eta);
	
	double T = time;
	
	double part1 = Part1(alpha,T,flag)*Pow(predictor,Q);
	double part2 = - Part2(alpha,xi,W,T,flag_t)*Pow(predictor,2*W-1);
	double part3 = Part3(xi,T,flag_t)*Pow(predictor,W);
	
	y = factor1 + factor3 + part1 + part2 + part3;	
}

void Functions::Fitted_Predictor_Corrector(double & y)
{
	double alpha=0.5, xi=0.5, eta=0.5, Q=1;
	double W = (process == SQUARE_ROOT) ? 0.5 : 1;
	bool flag = true;
	bool flag_t = ( process == SQUARE_ROOT ) ? false : true;
	
	
	// predictor is determined with Euler
	double predictor=y;
	Fitted_Euler(predictor);
	
	double factor1=Factor1(y,alpha,xi,Q,W,flag,flag_t);
	double factor3=Factor3(eta);
	
	double T = time;
	
	double part1 = Part1(alpha,T,flag)*Pow(predictor,Q);
	double part2 = - Part2(alpha,xi,W,T,flag_t)*Pow(predictor,2*W-1);
	double part3 = Part3(xi,T,flag_t)*Pow(predictor,W);
	
	y = factor1 + factor3 + part1 + part2 + part3;	
}

double Functions::Compute(const double & y,
				  								const double & alpha,
                          const double & xi,
                          const double & eta,
                          const double & Q,
                          const double & W,
                          const bool & flag,
                          const bool & flag_t)
{
	double factor1, factor2, factor3;
	
	factor1 = Factor1(y,alpha,xi,Q,W,flag,flag_t);
	factor2 = Factor2(alpha,xi,W,flag,flag_t);
	factor3 = Factor3(eta);
	
	return (factor1 + factor3)/factor2;
}

double Functions::Factor1(const double & y,
                          const double & alpha,
                          const double & xi,
                          const double & Q,
                          const double & W,
                          const bool & flag,
                          const bool & flag_t)
{
	double part1, part2, part3;
	double T;
	
	// time at beginning of timestep
	T = time - k;
	
	part1 = Part1(1-alpha,T,flag)*Pow(y,Q);
	part2 = - Part2(1-alpha,xi,W,T,flag_t)*Pow(y,2*W-1);
	part3 = Part3(1-xi,T,flag_t)*Pow(y,W);
	
	return y + part1 + part2 + part3;
}

double Functions::Factor2(const double & alpha,
                          const double & xi,
                          const double & W,
                          const bool & flag,
                          const bool & flag_t)
{
	double part1, part2, part3;
	double T;
	
	// time at end of timestep
	T = time;
	
	part1 = - Part1(alpha,T,flag);
	part2 = Part2(alpha,xi,W,T,flag_t);
	part3 = - Part3(xi,T,flag_t);
	
	return 1 + part1 + part2 + part3;
}

double Functions::Factor3(const double & eta)
{
	double part1, part2;
	double T;
	
	// time at start of timestep
	T = time - k;
	
	part1 = (1 - eta)*a(T)*c(T)*k;

	// time at end of timestep
	T = time;
	
	part2 = eta*a(T)*c(T)*k;
	
	return part1 + part2;
}

double Functions::Part1(const double & alpha,
                        const double & T,
                        const bool & flag)
{
	double sigma=1;
	
	// if flag is true fitting factor is used, otherwise, it stays 1
	if(flag)sigma=Sigma(T);
	
	return k*alpha*a(T)/sigma;
}

double Functions::Part2(const double & alpha,
                        const double & xi,
                        const double & W,
                        const double & T,
                        const bool & flag_t)
{
	// sigma is always 1 for part 2
	double sigma_t=1;
	
	// if flag is true fitting factor is used, otherwise, it stays 1
	if(flag_t)sigma_t=Sigma_t(T);
	
	return k*alpha*xi*b(T)*b(T)*W/sigma_t;
}

double Functions::Part3(const double & xi,
                        const double & T,
                        const bool & flag_t)
{
	double sigma_t = 1;
	
	// if flag is true fitting factor is used, otherwise, it stays 1
	if(flag_t)sigma_t=Sigma_t(T);
	
	return Normal[timestep]*xi*b(T)/sigma_t;
}

double Functions::Sigma(const double & t)
{
	double T, exp_normal, sigma;

	// exact solution is best approximated at 1/2 of the timestep
	T = t - 0.5*k ;

	//determine the exact solution for the linear fitter
	exp_normal = exp(a(T)*k) - 1;		

	// fitting factor
	sigma = a(t)*k/exp_normal;
	
	return sigma;
}

double Functions::Sigma_t(const double & t)
{
	double T, exp_noise, sigma_t;
	
	// exact solution is best approximated at 1/2 of the timestep
	T = t - 0.5*k ;

	// determine the exact solution for the noise
	exp_noise = exp( -0.5*b(T)*b(T)*k + b(T)*Normal[timestep]) - 1;

	// noise fitting sigma
	sigma_t = b(t)*Normal[timestep]/exp_noise;
	
	return sigma_t;
}

bool Functions::CanNotPerform(void)
{
	// check if method can be combined with process=GEOMETRIC
	if(process == GEOMETRIC)
	{;}

	// check if method can be combined with process=SQUARE_ROOT
	if(process == SQUARE_ROOT)
	{
		if(method == EXACT)return DoNotRun();
		if(method == IMPLICIT_EULER)return DoNotRun();
		if(method == CRANK_NICOLSON)return DoNotRun();
		if(method == FITTED_CRANK_NICOLSON)return DoNotRun();
	}
	
	// check if method can be combined with process=MEAN_REVERTING
	if(process == MEAN_REVERTING)
	{
		if(method==EXACT)return DoNotRun();
	}
	
	// check if method is in range
	if(method < EXACT)return DoNotRun();
	if(method > PREDICTOR_CORRECTOR)return DoNotRun();
	
	//check if process is in range
	if(process < GEOMETRIC)return DoNotRun();
	if(process > MEAN_REVERTING)return DoNotRun();
	
	return false;
}

bool Functions::DoNotRun(void)
{ return true; }

double Functions::Pow(const double & y, const double & factor)
{	
	// some special cases that can be done cheaper
	if(factor == 1)return y;
	if(factor == 0) return 1;
	if(factor == 0.5) return sqrt(y);
	if(factor == -1) return 1/y;
	
	//nope, we really need to use pow() here!
	return pow(y,factor);
}






