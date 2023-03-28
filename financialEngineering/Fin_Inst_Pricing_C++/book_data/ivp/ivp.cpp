// ivp.cpp
//
// Generic classes that model initial value problems (IVPs). These systems
// can originate when time-dependent initial boundary value problems (IBVP) 
// are discretised in the space variable (which can be multi-dimensional). 
// The resulting system of ODEs is sometimes called the semi-discrete scheme.
//	
// Last modification dates:
//
//	2002-11-8 DD Kick-off
//	2003-4-18 DD LinearIVP set up
//	2003-7-13 DD all functions are now properties (NO, don't work)
//
// (C) Datasim Component Technology BV 2002
//

#ifndef IVP_cpp
#define IVP_cpp

#include "ivp.hpp"


template <class V> ScalarIVP<V>::ScalarIVP()
{

	ic = 0;
	ran = Range<V>();

	rhs = 0;
	a = 0;


}

template <class V> ScalarIVP<V>::ScalarIVP(const Range<V> range, const V& initial_condition)
{

	ran = range;
	ic = initial_condition;

	rhs = 0;
	a = 0;


}


template <class V> ScalarIVP<V>::ScalarIVP(const ScalarIVP<V>& source)
{	

	ran = source.ran;
	ic = source.ic;

	rhs = source.rhs;
	a = source.a;

	

}


template <class V> ScalarIVP<V>::~ScalarIVP()
{

}


 	
template <class V>  ScalarIVP<V>& ScalarIVP<V>::operator = (const ScalarIVP<V>& source)
{

	if (this == &source)
		return *this;

	ran = source.ran;
	ic = source.ic;

	rhs = source.rhs;
	a = source.a;

	
	return *this;
}

template <class V> void ScalarIVP<V>::Rhs(V (*fp)(const V& x))
{ // Choose the function f(t)

	rhs = fp;

}

template <class V> void ScalarIVP<V>::Coeff(V (*fp)(const V& x))
{ // Choose the function a(t)

	a = fp;
}


// Selector functions
template <class V> Range<V> ScalarIVP<V>::range() const
{ // Interval of interest

	return ran;
}


template <class V> V ScalarIVP<V>::startValue() const
{ // Give the initial value

	return ic;
}

template <class V> V ScalarIVP<V>::RhsCalc(const V& t) const
{ // Calculate the function f(t)

	return (*rhs)(t);
}

template <class V>	V ScalarIVP<V>::CoeffCalc(const V& t) const
{ // Calculate the value of the coefficient

	return (*a)(t);
}



/*
/////////// NL Scalar IVP ///////////////////////////////////////////////////////////////////////

template <class V> NLScalarIVP<V>::NLScalarIVP()
{

	ic = 0;
	ran = Range<V>();

	f = 0;



}

template <class V> NLScalarIVP<V>::NLScalarIVP(const Range<V> range, const V& initial_condition)
{

	ran = range;
	ic = initial_condition;

	f = 0;


}


template <class V> NLScalarIVP<V>::NLScalarIVP(const NLScalarIVP<V>& source)
{	

	ran = source.ran;
	ic = source.ic;

	f = source.f;

}


template <class V> NLScalarIVP<V>::~NLScalarIVP()
{

}

	
template <class V>  NLScalarIVP<V>& NLScalarIVP<V>::operator = (const NLScalarIVP<V>& source)
{
	if (this == &source)
		return *this;

	ran = source.ran;
	ic = source.ic;

	f = source.fs;


	return *this;
}


// Choosing functions in equation
template <class V> void NLScalarIVP<V>::Rhs(V (*func) (const V& t, const V& u ) )
{ // Choose the function f(t, u(t)))

	f = func;
}


// Selector functions
template <class V> Range<V> NLScalarIVP<V>::range() const
{ // Interval of interest

	return ran;
}

template <class V> V NLScalarIVP<V>::startValue() const
{ // Give the initial value

	return ic;
}


template <class V> V NLScalarIVP<V>::RhsCalc(const V& t,  const V& u) const
{ // Calculate the function f(t)

	return (*f)(t, u);
}


/// Systems of ODEs dU/dt + AU = F ////////////////////////////////////////
	

template <class V, class I>	LinearIVP<V,I>::LinearIVP()
{

	ran = Range<V>();
	ic	= Vector<V,I>();
//	A	= NumericMatrix<ScalarFunction<V,V,I> > ();
	F	= VectorFunction <V,V,I> ();
	dim	= 1;

}

template <class V, class I>	LinearIVP<V,I>::LinearIVP(const Range<V>& range, const Vector<V,I>& initial_condition)
{

	ran = range;
	ic	= initial_condition;

//	A	= NumericMatrix<ScalarFunction<V,V,I> > ();
	F	= VectorFunction <V,V,I> ();
	dim	= ic.Size();

}

template <class V, class I>	LinearIVP<V,I>::LinearIVP(const LinearIVP<V,I>& source)
{
	ran = source.ran;
	ic	= source.ic;;

//	A	= source.A;
	F	= source.F;
	dim	= source.dim;
}

template <class V, class I> LinearIVP<V,I>& LinearIVP<V,I>::operator = (const LinearIVP<V,I>& source)
{
	if (this == &source)
		return *this;

	ran = source.ran;
	ic	= source.ic;;

//	A	= source.A;
	F	= source.F;
	dim	= source.dim;


	return *this;
}
		
// Modifier functions


template <class V, class I>	void LinearIVP<V,I>::matrixCoefficient (const NumericMatrix<ScalarFunction<V,V,I>, I>& Anew)
{

	//	A = Anew;
}

template <class V, class I>	void LinearIVP<V,I>::Rhs(const VectorFunction <V,V,I>& RHS)
{
		F = RHS;
}


// Is this a wel-defined IVP? Dimension correct?
template <class V, class I> bool LinearIVP<V,I>::ConsistentIVP() const
{

	//cout << "Size IVP: " << ic.Size() << "," << F() << endl;

	if (ic.Size() != F.Dimension())
		return false;

	// Check A stuff

	return true;
}

*/
#endif
