// parabolicFDM.cpp
//
// Finite difference method for Parabolic PDE.
//
// Last modification dates:
//
//	2000-7-30 DD kick-off code. The member 'theta' is for a future version
//	2000-8-1 DD more improvements, specific use of Array code
//	2000-8-2 DD getting ready for Robert and Jasmin
//	2001-1-30 DD debugging and checking (heavy overhaul)
//	2001-2-10 DD 'improvements'
//	2002-1-8 DD Cleaning up mostly
//  2002-4-9 DD Later on the discrete A, B, C and F can be replaced by one generic function
//  2002-17-5 RM coth added to ParabolicFDM class (RM = R. Mirani)
//  2002-17-5 RM functions ::A, ::B and ::C changed to internal note 1 format
//  2002-17-5 RM some small errors in ::init()
//  2002-21-5 RM current now initialized (to 0) in constructor
//	2002-21-5 RM Completely new advance() function
//  2002-21-5 RM initial condition IC() added
//  2002-21-5 RM function start() now computes the complete result
//  2002-22-5 RM pde is not a pointer! All calls pde->function() changed to pde.function()
//  2002-23-5 RM factor 0.5*k added in finished to prevent roundof errors screwing up stopping condition
//  2002-16-6 RM bug in advance: stock price domain assumed to start at 0
//
// (C) Datasim Component Technology BV 2000
//


#ifndef FDM_CPP
#define FDM_CPP

// 1/5/2002 - changed by R. Mirani
//#include "parabolicfdm.hpp"
#include "ParabolicFDM.hpp"

#include <math.h>

//altered by R. Mirani
//double coth(const double& x)
template <class X, class T, class V> V ParabolicFDM<X,T,V>::coth(const V& x) const
{ // Hyperbolic cotangent function
	V tmp=::exp(-2*x);
	return (1.0 + tmp)/(1.0 - tmp);
}

// 2002-17-5 RM ::A already like in internal note 1
// Special functions for setting up tridiagonal matrices
template <class X, class T, class V> V ParabolicFDM<X,T,V>::A(const X& x, const T& t) const
{ // Sub-diagonal term in matrix in semi-discrete scheme

	// alpha - beta
	
	// 2/5/2002 - altered by R. Mirani. One bracket too many!
	//return (fitting_factor(x,t)/(h*h)) - (0.5 * pde->convection(x,t))/(h));
	//
	// 2002-22-5 RM
	//return (fitting_factor(x,t)/(h*h) - (0.5 * pde->convection(x,t))/(h));
	return (fitting_factor(x,t)/(h*h) - (0.5 * pde.convection(x,t))/(h));
}

// 2002-17-5 RM ::B altered to be like in internal note 1
//template <class X, class T, class V> V ParabolicFDM<X,T,V>::B(const X& x, const T& t, const T& Delta_t) const
template <class X, class T, class V> V ParabolicFDM<X,T,V>::B(const X& x, const T& t) const
{ // Main diagonal term in matrix in semi-discrete scheme

	// - 2 * alpha + b

	
	//return - 2.0 * (fitting_factor(x,t)/(h*h)) + pde -> zeroterm(x,t) - Delta_t;
	// 2002-22-5 RM
	//return - 2.0 * (fitting_factor(x,t)/(h*h)) + pde -> zeroterm(x,t);
	return - 2.0 * (fitting_factor(x,t)/(h*h)) + pde.zeroterm(x,t);
}

// 2002-17-5 RM ::C already like in internal note 1
template <class X, class T, class V>V ParabolicFDM<X,T,V>::C(const X& x, const T& t) const
{ // Super-diagonal term in matrix in semi-discrete scheme

	// alpha + beta
	// 2002-22-5 RM
	//return (fitting_factor(x,t)/(h*h)) + (0.5 * pde->convection(x,t))/(h);
	return (fitting_factor(x,t)/(h*h)) + (0.5 * pde.convection(x,t))/(h);
	
	
}

template <class X, class T, class V>V ParabolicFDM<X,T,V>::F(const X& x, const T& t) const
{ // Right-hand side of matrix equation in semi-discrete scheme

	// 2002-22-5 RM
	//return (pde->RHS(x,t));
	return (pde.RHS(x,t));
	
}

// 2002-21-5 RM the initial condition
template <class X, class T, class V>V ParabolicFDM<X,T,V>::IC(const X& x) const
{ // Initial condition

	// 2002-2-5 RM
	//return pde->IC(x);
	return pde.IC(x);
	
}



template <class X, class T, class V> V ParabolicFDM<X,T,V>::fitting_factor(const X& x, const T& t) const
{ // Il'in fitting function

	// 2002-22-5 RM
	//V tmp = pde->convection(x,t) * h * 0.5;
	//return tmp * coth(tmp/(pde->diffusion(x,t))); // Uses hyperbolic cotangent
	V tmp = pde.convection(x,t) * h * 0.5;
	return tmp * coth(tmp/(pde.diffusion(x,t))); // Uses hyperbolic cotangent
}

// Fully-discrete coefficients
template <class X, class T, class V> Vector<V,long> ParabolicFDM<X,T,V>::Adiscrete(const T& t) const
{ // Array of A's in semi-discrete scheme

	// Create an array a[1..J-1]

	Vector<V,long> result(J-1, 1);
	for (long j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		result[j] = A(XARR[j], t);		
	}

	return result;
		
}

template <class X, class T, class V> Vector<V,long > ParabolicFDM<X,T,V>::Bdiscrete(const T& t) const
{ // Array of B's in semi-discrete scheme

	// Create an array b[1..J-1]
		
	Vector<V,long > result(J-1, 1);
	for (long j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		result[j] = B(XARR[j], t);		//?
	}

	return result;
}



template <class X, class T, class V> Vector<V,long > ParabolicFDM<X,T,V>::Cdiscrete(const T& t) const
{ // Array of C's in semi-discrete scheme

	// Create an array c[1..J-1]
	Vector<V,long > result(J-1, 1);
	for (long j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		result[j] = C(XARR[j], t);	
	}

	return result;
}

template <class X, class T, class V> Vector<V,long > ParabolicFDM<X,T,V>::Fdiscrete(const T& t) const
{ // Right-hand side in semi-discrete scheme


	// Create an array f[1..J-1]
	Vector<V,long > result (J-1, 1);

	
	for (long j = result.MinIndex(); j <= result.MaxIndex(); j++)
	{
		result[j] = F(XARR[j], t);
	}

	return result;

}

template <class X, class T, class V> void ParabolicFDM<X,T,V>::init()
{ // Initialise all variables, arrays and matrices

	// 1. Mesh stuff
	h = X(pde.first().spread()) /  V(J);
	k = T(pde.second().spread())/  V(N);
	
	// Make 2 arrays of in range [0..J] and [0..N]
	
	// 2002-17-5 RM initialized locally and thrown away... UNACCEPTABLE
	//Vector<X,long> XARR(J+1, 0);	// X0 ... XJ
	//Vector<T,long> TARR(N+1, 0);	// T0 ... TN
	XARR = Vector<X,long>(J+1, 0);	// X0 ... XJ
	TARR = Vector<T,long>(N+1, 0);	// T0 ... TN

	// fill the two arrays at their lower boundaries	
	XARR[XARR.MinIndex()] = (pde.first().low());
	TARR[TARR.MinIndex()] = (pde.second().low());

	// fill the body of the spatial array
	for (long j = XARR.MinIndex() + 1; j <= XARR.MaxIndex(); j++)
	{
		XARR[j] = h + XARR[j-1];
	}

	// fill the body of the temporal array
	for (long n = TARR.MinIndex() + 1; n <= TARR.MaxIndex(); n++)
	{
		//2002-17-5 RM TARR[J-1] should be TARR[n-1]
		//TARR[n] =  k + TARR[J-1];
		TARR[n] = k + TARR[n-1];
	}

	// Initialise results arrays and matrices ?? suspect
	
	// 2002-22-5 RM "next is not needed
	//next = tmp = Vector<V,long> (J-1, 1);	// Level n (tmp), n+1(next)
	tmp = Vector<V,long> (J-1, 1);	// Level n (tmp), n+1(next)
	
	
	// 2002-17-5 RM time-index starts at 0, not 1
	//mresult	= NumericMatrix<V,long> (J-1, N+1, 1, 1);
	
	// 2002-17-5 RM should be the other way round
	//mresult = NumericMatrix<V,long> (J-1, N+1, 1, 0);
	// WARNING: this matrix is never used!
//	mresult = NumericMatrix<V,long> (N+1, J-1, 0, 1);
}

template <class X, class T, class V> ParabolicFDM<X,T,V>::ParabolicFDM(const ParabolicPDE<X,T,V>& context, long Xintervals, long Tintervals, const V& time_discrete)
{
	pde = context;

	// 2002-21-5 RM - current initialized (to 0)
	current = pde.second().low();
	
	// number of intervals in spatial axis
	J = Xintervals;
	
	// number of intervals in temporal axis
	N = Tintervals;

	// ratio between explicit and implicit
	theta = time_discrete;
	
	// initialize the run
	init();

}

// The computational scenario
template <class X, class T, class V> void ParabolicFDM<X,T,V>::start()
{ // Fill in initial data

	// set initial condition
	for (long j = tmp.MinIndex(); j <= tmp.MaxIndex(); j++)
	{
		tmp[j] = IC(XARR[j]);
	}

	// 2002-21-5 RM
	// compute the results
	while(!finished())
		advance();
	
}

template <class X, class T, class V> void ParabolicFDM<X,T,V>::advance()
{ // Go to the next time stage and calculate. This is where all the action
  // takes place.


	// Calculate the coefficients
	
	// set the time
	T t = current;

	// Build up Matrix vectors
	Vector<V, long> A_now(J-1, 1);		// Start index 1, size J-1
	Vector<V, long> B_now(J-1, 1);
	Vector<V, long> C_now(J-1, 1);
	Vector<V, long> F_now(J-1, 1);    // forcing term at time current
	Vector<V, long> G_now(J-1, 1, 0);	//boundary condition Gamma at time current
	
	Vector<V, long> A_next(J-1, 1);		// Start index 1, size J-1
	Vector<V, long> B_next(J-1, 1);
	Vector<V, long> C_next(J-1, 1);
	Vector<V, long> F_next(J-1, 1);   // forcing term at time current + k
	Vector<V, long> G_next(J-1, 1, 0);// boundary condition Gamma at time current + k
	
	Vector<V, long> unit(J-1, 1, 1.0);		// All elements == 1.0

	// determine matrix- and vector-values at time current
	V coeff_now = k * (1 - theta);
	A_now = Adiscrete(t)*coeff_now;
	B_now = unit + (Bdiscrete(t) * coeff_now);
	C_now = Cdiscrete(t) * coeff_now;
	F_now = - Fdiscrete(t) * coeff_now;

	// 2002-16-6 RM domain of stock price doesn't necessarily start at 0
  //G_now[1] = coeff_now * pde.BCL(t) * A(h,t);
	//G_now[J-1] = coeff_now * pde.BCR(t) * C((J-1)*h,t);
	
	// compute the boundary conditions at time current
	G_now[1] = coeff_now * pde.BCL(t) * A(XARR[1],t);
	G_now[J-1] = coeff_now * pde.BCR(t) * C(XARR[J-1],t);
	
	// determine matrix- and vector-values at time current + k
	V coeff_next = k * theta;
	A_next = - Adiscrete(t+k) * coeff_next;
	B_next = unit - Bdiscrete(t+k) * coeff_next;
	C_next = - Cdiscrete(t+k) * coeff_next;
	F_next = - Fdiscrete(t+k) * coeff_next;
	
	// 2002-16-6 RM domain of stock price doesn't necessarily start at 0
	//G_next[1] = coeff_next * pde.BCL(t+k) * A(h,t+k);
	//G_next[J-1] = coeff_next * pde.BCR(t+k) * C((J-1)*h,t+k);
	
	// compute the boundary conditions at time current + k
	G_next[1] = coeff_next * pde.BCL(t+k) * A(XARR[1],t+k);
	G_next[J-1] = coeff_next * pde.BCR(t+k) * C(XARR[J-1],t+k);
		
	// determine result of matrix multiplication ( see formula 8 in Internal Note 1 )
	Vector<V,long> outcome(J-1, 1);		// matrix * next = outcome
	
	for(long q=outcome.MinIndex()+1; q<= outcome.MaxIndex()-1; q++)	// determine outcome in range 2...J-2
		outcome[q] = A_now[q]*tmp[q-1]+B_now[q]*tmp[q]+C_now[q]*tmp[q+1];
	outcome[1]=B_now[1]*tmp[1]+C_now[1]*tmp[2]; 						// determine outcome at 1
	outcome[J-1]=A_now[J-1]*tmp[J-2]+B_now[J-1]*tmp[J-1];   // determine outcome at J-1	
//	outcome += G_now + G_next + F_now + F_next;  						// determine rest of outcome
	outcome = outcome + G_now + G_next + F_now + F_next;  						// determine rest of outcome
	
	// The objective is to calculate the 'next' vector (BALAYAGE)
	DoubleSweep<V, long> ss( A_next, B_next, C_next, outcome, 0, 0 );
	
	// 2002-22-5 RM "next is not needed"
	//next = ss.result(); // [1,J-1] ==> length J - 1
	
	// store the result of the current timestep
	tmp = ss.result(); // [1,J-1] ==> length J - 1
	
	// why do we have a separate tmp and next?
	// 2002-22-5 RM "next is not needed"
	//tmp = next;
	
	current += k;					// Next floor (I mean time level)

}


template <class X, class T, class V> bool ParabolicFDM<X,T,V>::finished() const
{ // Have we calculated the last vector?

	// 2002-21-5 RM
		//if (current == M)
			//return true;
		// 2002-23-5 RM factor 0.5*k needed because of roundof errors
		//if(current > pde.second().high())
		
		// determine if time t = T
		if(current > pde.second().high() - 0.5*k)
			return true;
			
		return false;
}



// Results
template <class X, class T, class V> Vector<V,long > ParabolicFDM<X,T,V>::line() const
{ // Current vector output

	// 2002-22-5 RM better to use tmp instead of next
	//return next;
	
	// return the result of the run
	return tmp;
}

/*

template <class X, class T, class V> NumericMatrix<V,long> ParabolicFDM<X,T,V>::result() const
{ // Solution so far

	// This is a [1..J-1] X [1,N] matrix
	// WARNING: mresult is never filled
	return mresult;
}

*/
#endif