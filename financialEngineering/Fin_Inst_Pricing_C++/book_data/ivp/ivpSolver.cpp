// ivpSolver.cpp
//
//	Last modification dates:
//
//	DD 2003-4-5 Kick off
//	DD 2003-7-25 Predictor-corrector added
//
// (C) Datasim Component Technology BV 2003
//


#ifndef IVPSolver_cpp
#define IVPSolver_cpp

#include "ivpsolver.hpp"
#include <math.h>



template <class V, class I>  ScalarIVPSolver<V,I>:: ScalarIVPSolver()
{

	ivp = 0;
	typ = EEuler;
	N = 10;

	k = ivp -> range().spread()/N;
	res = Vector<V, I> (N+1, 1);	// Size = N + 1, start index = 1

}

template <class V, class I>  ScalarIVPSolver<V,I>:: ScalarIVPSolver(ScalarIVP<V>& source, FDMType type)
{

	ivp = &source;
	typ = type;
	N = 10;

	k = ivp -> range().spread()/N;
	res = Vector<V, I> (N+1, 1);	// Size = N + 1, start index = 1
}



template <class V, class I>  ScalarIVPSolver<V,I>:: ScalarIVPSolver(const  ScalarIVPSolver<V,I>& source)
{	

	ivp = source.ivp;
	typ = source.type;
	N = source.N;

	k = ivp -> range().spread()/N;
	res = source.res;

}


template <class V, class I>  ScalarIVPSolver<V,I>::~ ScalarIVPSolver()
{

}


 	
template <class V, class I>   ScalarIVPSolver<V,I>&  ScalarIVPSolver<V,I>::operator = (const  ScalarIVPSolver<V,I>& source)
{

	if (this == &source)
		return *this;

	ivp = source.ivp;
	typ = source.typ;
	N = source.N;

	k = souurce.k;
	res = source.res;

	return *this;
}

// Modifier functions
template <class V, class I> void ScalarIVPSolver<V,I>::steps(const I& Nsteps)
{
	
	N = Nsteps;

	// Don't forget to update rdundant attributes!
	k = ivp -> range().spread()/N;
	res = Vector<V, I> (N+1, 1);	// Size = N + 1, start index = 1
	
}

template <class V, class I>	void ScalarIVPSolver<V,I>::setType(FDMType type)
{
	typ = type;
}

// Output
template <class V, class I>	V ScalarIVPSolver<V,I>::stepSize() const
{
	
	return k;
}


template <class V, class I> Vector<V, I> ScalarIVPSolver<V,I>::result()
{ // The result of the calculation

	
		res[res.MinIndex()] = (ivp -> startValue());

		 // Types are {EEuler, IEuler, Box, Trap, Fitted, ExtrapEuler};

		if (typ == EEuler)
		{
		
			eeuler();
		
		}

		if (typ == IEuler)
		{
			ieuler();
		}

		if (typ == Box)
		{
			
			box();

		}

		if (typ == Fitted)
		{ // Duffy's fitting factor

			fitted();
		}

		if (typ == Trap)
		{
			
			trap();
		}

		if (typ == FittedBox)
		{
			fittedbox();

		}

		if (typ == ExtrapEuler)
		{	
		
			extrapeuler();
		
				
		}

		if (typ == PC)
		{	
		
		
			predictorCorrector();
				
		}
		return res;

}

// Private functions
template <class V, class I> void ScalarIVPSolver<V,I>::eeuler()
{

		for (I i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
		{
			res[i] = res[i-1]*( 1.0 - (k* ivp->CoeffCalc((i-1)*k)) ) + (k* ivp->RhsCalc((i-1)*k));
		}

}


template <class V, class I> void ScalarIVPSolver<V,I>::ieuler()
{


	for (I i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
	{
			res[i] = ( res[i-1] + (k* ivp->RhsCalc(i*k)) ) / ( 1.0 + (k* ivp->CoeffCalc(i*k)) );
	}



}

template <class V, class I> void ScalarIVPSolver<V,I>::box()
{

	for (I i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
	{
			V mu = ivp->CoeffCalc( (i-0.5)*k ) * k * 0.5;
			res[i] = ( (1.0 - mu)* res[i-1] + (k* ivp->RhsCalc( (i-0.5)*k)  ) ) / (1.0 + mu);
	}


}

template <class V, class I> void ScalarIVPSolver<V,I>::trap()
{

	for (I i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
	{
			V vup = 1.0 - ( k * 0.5 *ivp->CoeffCalc((i-1)*k) );
			V vlow = 1.0 + ( k * 0.5 * ivp->CoeffCalc(i*k) );
			V favg = k * 0.5 * ( ivp->RhsCalc(i*k) + ivp->RhsCalc((i-1)*k) );
		
			res[i] = (res[i-1] * vup + favg) / vlow;
	}


}

template <class V, class I> void ScalarIVPSolver<V,I>::fitted()
{
	V fit, coeff;
	for (I i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
	{

			if (ivp->CoeffCalc(i*k) == 0.0)
				fit = 1.0;
			else
			{
				coeff = (ivp->CoeffCalc(i*k)) * k;
				fit = coeff / (::exp(coeff) - 1.0);
			}
	
			res[i] = ( fit*res[i-1] + (k* ivp->RhsCalc(i*k)) ) / ( fit + (k* ivp->CoeffCalc(i*k)) );
	}


}

template <class V, class I> void ScalarIVPSolver<V,I>::fittedbox()
{

	V fit, coeff;
	for (I i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
	{
	
			V coeff = (ivp->CoeffCalc((i-0.5)*k)) * k;
			if (ivp->CoeffCalc((i-0.5)*k) == 0.0)
				fit = 2.0;
			else
			{
				V tmp = ::exp(coeff);
				fit = (0.5 * coeff * (tmp + 1.0) ) / (tmp - 1.0);
			}

			res[i] = ( (fit - coeff*0.5)* res[i-1] + k* ivp->RhsCalc((i-0.5)*k)   ) / (fit + coeff*0.5);
	}


}

template <class V, class I> void ScalarIVPSolver<V,I>::extrapeuler()
{

	
	// Extrapolated implicit Euler; we create two solution based on k/2 and k called
	// v(k/2) and v(k), respectively.  Then form the new array 2*v(k/2) - v(k)

	// Code can be optimised (later)
	
	// Refined mesh and solution
	Vector<V, I> res2 (2*N + 1);
	V k2 = k * 0.5;


	res2[res2.MinIndex()] = (ivp -> startValue());
	for (I i = res2.MinIndex() + 1; i <= res2.MaxIndex(); i++)
	{
		res2[i] = ( res2[i-1] + (k2 * ivp->RhsCalc(i*k2)) ) / ( 1.0 + (k2 * ivp->CoeffCalc(i*k2)) );
	}


	// Rougher mesh
	Vector<V, I> res1 (N + 1);
	res1[res1.MinIndex()] = (ivp -> startValue());
	for (I ii = res1.MinIndex() + 1; ii <= res1.MaxIndex(); ii++)
	{
		res1[ii] = ( res1[ii-1] + (k* ivp->RhsCalc(ii*k)) ) / ( 1.0 + (k* ivp->CoeffCalc(ii*k)) );
	}

	// Extrapolated solution
	for (I iii = res1.MinIndex(); iii <= res1.MaxIndex(); iii++)
	{
		res[iii] = (2.0 * res2[(2*iii) - 1]) - res1[iii];
	}
	

}

template <class V, class I>	void ScalarIVPSolver<V,I>::predictorCorrector()
{ // Predictor-corrector method

	for (I i = res.MinIndex() + 1; i <= res.MaxIndex(); i++)
	{

			// First get the predictor (Explicit Euler)
			V predictor = res[i-1]*( 1.0 - (k* ivp->CoeffCalc((i-1)*k)) ) + (k* ivp->RhsCalc((i-1)*k));
		
			// Corrector (this IS the solution)
			V vup = 1.0 - ( k * 0.5 *ivp->CoeffCalc((i-1)*k) );
			V pTerm = (k * 0.5 * ivp->CoeffCalc(i*k) ) * predictor;
	
			V favg = k * 0.5 * ( ivp->RhsCalc(i*k) + ivp->RhsCalc((i-1)*k) );
		
			res[i] = (res[i-1] * vup - pTerm + favg) ;

		

	}

}



#endif

		