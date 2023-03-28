#include "Characteristics.hpp"


double sigma(const pair<double,double>& state)
{ return 0.5*s*s*state.first*state.first; }


// Topper section 3.1.4 page 11: Non-constant volatility
double sigma_linear(const pair<double,double>& state)
{
	const double a=0.129;
	const double b=0.177;
	
	const double t = state.second;
	const double S = state.first;

	const double s = b+a*t;
	return 0.5*s*s*S*S;
}

double mu(const pair<double,double>& state)
{ return (r-d)*state.first; }

double forcing(const pair<double,double>& state)
{ return f; }

double b(const pair<double,double>& state)
{ return -r; }

// initial condition for call
double IC(const double& s)
{ return (s>K) ? s-K : 0; }

// initial condition for put
double IC_put(const double& s)
{ return (s<K) ? K-s : 0; }	

// Topper section 3.2.1 page 12: Power options
double IC_PO(const double& s)
{ return (pow(s,p)>K) ? pow(s,p)-K : 0; }

//Topper section 3.2.2 page 13: Capped Power options
double IC_ASCPO(const double & s)
{
	const double result = (pow(s,p)>K) ? pow(s,p)-K : 0;
	
	return (result<bcr) ? result : bcr;
	
}

//Topper section 3.2.2 page 14: Symmetric Capped Power options
double IC_SCPO(const double & s)
{
	const double result = (s-K>0) ? pow(s-K,p) : 0;
	
	return (result<bcr) ? result : bcr;
	
}

double BCR(const double& t)
{ return bcr; }

// Topper section 3.2.1 page 12: Power Options
double BCR_PO(const double& t)
{
	return pow(Xto,p)-K*exp(-(r-d)*(t - Yfrom));
}

double BCL(const double& t)
{ return bcl; }

double BCL_put(const double& t)
{
	return K*exp(-(r-d)*(t-Yfrom));
}

// Topper page 11: non-constant volatility boundary condition
double BCR_Topper_p11(const double & t)
{
	return Xto - K*exp(-(r-d)*(t - Yfrom));

}

double BCR_Topper_p10(const double & t)
{	// Topper page 10: discontinuous jumps in rebate

	double result = 1;
	int i = 1;
	while( t*12 > i ){
	 result *= 2;
	 i++;
	}
	
	return result;
}