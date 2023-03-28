// detfunction.cpp
//
//	Last modification dates:
//	2000-7-27 DD classes for functions with 1 and 2 parameters
//	(oh ya, almost forget special thanks to Adriaan)
//	2000-7-28 DD No base class, just 2 template classes to represent 2
//	parameters and one parameter.
//	2000-11-12 DD more generic approach (less classes needed)
//	2001-1-9 DD mathematical functions
//	2001-1-20 DD New interpretation of MatrixDFunction (as a vector function of a 
//	vector variable).
//	2001-2-1 DD Decorator (composite) functions
//  2002-17-5 RM Constructor TwoVarDFunction now recieves pair
//  2002-17-5 RM operator = must return *this
//  2002-17-5 RM .hpp file contains function XX which is never declared. Removed it
//	2003-8-13 DD Pruning number of classes (pedagogical reasons)
//
// (C) Datasim Component Technology BV 2000-2004
//
//

#ifndef DFunction_cpp
#define DFunction_cpp

#include "detfunction.hpp"

template <class D, class R> 
	AtomicDFunction<D, R>::AtomicDFunction ()
{

		f = 0;

}


template <class D, class R> 
	AtomicDFunction<D, R>::AtomicDFunction (const AtomicDFunction<D, R>& f2)
{
		f = f2.f;
}


template <class D, class R> 
	AtomicDFunction<D, R>::AtomicDFunction (R (*fp) (const D& x))
{

		f = fp;

}

template <class D, class R> 
	AtomicDFunction<D, R>::~AtomicDFunction ()
{

	

}


template <class D, class R> R
	AtomicDFunction<D,R>::calculate(const D& x) const
{

		return (*f)(x);

}

template <class D, class R> AtomicDFunction<D, R>&
	AtomicDFunction<D, R>::operator = (const AtomicDFunction<D,R>& f2) 
{ 
		if (this == &f2)
			return *this;

		f = f2.f;

		return *this;
}

// Choosing a new function
template <class D, class R> void
	AtomicDFunction<D, R>::function (R (*fp) (const D& x))
{

		f = fp;

}

template <class D, class R>	
	R AtomicDFunction<D,R>::add(const AtomicDFunction<D,R>& f2, const D& x) const
{

		return calculate(x) + f2.calculate(x);
}


template <class D1, class D2, class R> 
	TwoVarDFunction<D1,D2,R>::TwoVarDFunction() : AtomicDFunction<pair<D1,D2>, R>()
{

}


template <class D1, class D2, class R>
	TwoVarDFunction<D1,D2,R>::TwoVarDFunction (R (*fp)(const pair<D1,D2>&)) : AtomicDFunction<pair<D1,D2>,R> (fp)
{ // 'Normal' C functions as input
}

template <class D1, class D2, class R> 
	TwoVarDFunction<D1,D2,R>::TwoVarDFunction(const TwoVarDFunction<D1,D2,R>& f2) : AtomicDFunction<pair<D1,D2>,R> (f2)
{

}

template <class D1, class D2, class R>
 	TwoVarDFunction<D1,D2,R>::~TwoVarDFunction()
{

}

template <class D1, class D2, class R> 	
	TwoVarDFunction<D1,D2,R>& TwoVarDFunction<D1,D2,R>::operator = (const TwoVarDFunction<D1,D2,R>& f2)
{
		if (this == &f2)
			return *this;

		AtomicDFunction<pair<D1,D2>,R>::operator = (f2);
		
		return *this;
}

template <class D1, class D2, class R> 	
	R TwoVarDFunction<D1,D2,R>::calculate(const D1& d1, const D2& d2) const
{
	return AtomicDFunction<pair<D1, D2>, R>::calculate(pair<D1, D2> (d1, d2));
}




#endif