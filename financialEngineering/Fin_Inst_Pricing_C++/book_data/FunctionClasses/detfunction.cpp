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
//	2002-10-22 DD POC version
//	2002-12-6 DD Clone() and Visitor stuff (accept())
//	2002-12-16 DD no longer derived from a common base class
//
// (C) Datasim Component Technology BV 2000
//
//

#ifndef Function_CPP
#define Function_CPP

#include "detfunction.hpp"
#include "functionvisitor.hpp"


// Scalar Functions
template <class D, class R, class I> 
ScalarFunction<D,R,I>::ScalarFunction ()
{

		f = 0;
}

template <class D, class R, class I> 
	ScalarFunction<D,R,I>::ScalarFunction (const ScalarFunction<D,R,I>& f2)
{
		f = f2.f;
}


template <class D, class R, class I> 
	ScalarFunction<D,R,I>::ScalarFunction (R (*fp) (const D& x))
{

		f = fp;

}

template <class D, class R, class I> 
	ScalarFunction<D,R,I>::~ScalarFunction ()
{

	

}


template <class D, class R, class I> R
	ScalarFunction<D,R,I>::calculate(const D& x) const
{

		return (*f)(x);

}

template <class D, class R, class I> ScalarFunction<D,R,I>&
	ScalarFunction<D,R,I>::operator = (const ScalarFunction<D,R,I>& f2) 
{ 
		if (this == &f2)
			return *this;

		f = f2.f;

		return *this;
}

// Choosing a new function
template <class D, class R, class I> void
	ScalarFunction<D,R,I>::function (R (*fp) (const D& x))
{

		f = fp;

}

template <class D, class R, class I> void 
	ScalarFunction<D,R,I>::function (const ScalarFunction<D,R,I>& NewFunc)
{ // Choose a new function


	function(NewFunc.f);
}


template <class D, class R, class I>  
	Vector<R,I> ScalarFunction<D,R,I>::Values(const Vector<D,I>& InputValues) const
{ // Y values based on X values

	Vector result (InputValues.Size(), InputValues.MinIndex());

	for (I i=MinIndex(); i<=MaxIndex(); i++)
	{
		result[i] = calculate(InputValues[i]);
	}

	return result;
}


template <class D, class R, class I>  
 void ScalarFunction<D,R,I>::accept(FunctionVisitor<D,R,I>& v) 
{ // Make a copy of myself

	v.visit(*this);
}

 

//////////////////////////
// Vector functions
//////////////////////////
template <class D, class R, class I> 
	void VectorFunction<D,R,I>::init(const I& size)
{
	vf = Vector<ScalarFunction<D,R, I>, I > (size);

	for (int j = vf.MinIndex(); j <= vf.MaxIndex(); j++)
	{
		vf[j] = ScalarFunction<D,R, I>();
	}
}

template <class D, class R, class I> 
VectorFunction<D,R,I>::VectorFunction() 
{ // Create an array of functions of length 1

	init(1);

}

template <class D, class R, class I> 
VectorFunction<D,R,I>::VectorFunction(const I& size) 
{ // Create an array of functions of length size

	init(size);
	
}

template <class D, class R, class I> 
VectorFunction<D,R,I>::VectorFunction(const VectorFunction<D,R,I>& f2)
{ // Copy constructor

		vf = f2.vf;
}

template <class D, class R, class I> 
	VectorFunction<D,R,I>::~VectorFunction()
{ // Destructor



}

template <class D, class R, class I> 
	VectorFunction<D, R, I>& VectorFunction<D,R,I>::operator = (const VectorFunction<D, R, I>& f2)
{ // Assignment operator

		if (this == &f2)
			return *this;

		vf = f2.vf;

		return *this;
}

template <class D, class R, class I> 
		I VectorFunction<D,R,I>::Dimension() const
{ // Number of equations

		return vf.Size();
}



// Now set and get the individual functions
template <class D, class R, class I> 
	void VectorFunction<D,R,I>::function(const I& position,const ScalarFunction<D,R,I>& func)
{
	cout << "DEBUG vector function " << position << "," << endl;

	vf[position].function(func);
}

template <class D, class R, class I> 
	ScalarFunction<D,R,I> VectorFunction<D,R,I>::function (const I& size) const
{

		return vf[position];
}

template <class D, class R, class I> 
	Vector<R,I> VectorFunction<D,R,I>::calculate(const D& x) const
{
	
		Vector<R,I> result(vf.Size());

		for (I j = result.MinIndex(); j <= result.MaxIndex(); j++)
		{
			result[j] = vf[j].calculate(x);
		}

		return result;
}


template <class D, class R, class I>  
 void VectorFunction<D,R,I>::accept(FunctionVisitor<D,R,I>& v) 
{ // Make a copy of myself

	v.visit(*this);
}


//////////////////////////
// Scalar-Valued functions
//////////////////////////
template <class D, class R, class I> 
ScalarValuedFunction<D,R,I>::ScalarValuedFunction() 
//	: DFunction<Vector<D,I>, R, I>()
{ // Create a default function

	scf = ScalarFunction<Vector<D, I>, R, I>();

}

template <class D, class R, class I> 
	ScalarValuedFunction<D,R,I>::ScalarValuedFunction(const ScalarFunction<Vector<D,I>, R, I>& scalar_function)
//	: DFunction<Vector<D,I>, R, I>(scf)
{ // Create a function based on a vector domain

	scf = scalar_function;
}

template <class D, class R, class I> 
ScalarValuedFunction<D,R,I>::ScalarValuedFunction(const ScalarValuedFunction<D,R,I>& f2)
//	: DFunction<Vector<D,I>, R, I>(f2)
{ // Copy constructor


		scf = f2.scf;
}


template <class D, class R, class I> 
	ScalarValuedFunction<D,R,I>::~ScalarValuedFunction()
{ // Destructor



}

template <class D, class R, class I> 
	ScalarValuedFunction<D, R, I>& ScalarValuedFunction<D,R,I>::operator = (const ScalarValuedFunction<D, R, I>& f2)
{ // Assignment operator

		if (this == &f2)
			return *this;

		scf = f2.scf;

		return *this;
}

template <class D, class R, class I>
	void ScalarValuedFunction<D, R, I>::function (R (*fp)(const Vector<D, I>& x))
{

		scf = ScalarFunction<Vector<D,I>,R,I> (fp) ;
}

template <class D, class R, class I>
	void ScalarValuedFunction<D, R, I>::function (const ScalarValuedFunction<D,R,I>& NewFunc)
{

	scf = NewFunc.scf;
}


template <class D, class R, class I> R
	ScalarValuedFunction<D, R, I>::calculate(const Vector<D,I>& x) const
{

		return scf.calculate(x);
}




template <class D, class R, class I>  
 void ScalarValuedFunction<D,R,I>::accept(FunctionVisitor<D,R,I>& v) 
{ // Make a copy of myself

	v.visit(*this);
}


//////////////////////////
// Vector-valued functions
//////////////////////////
template <class D, class R, class I> 
VectorValuedFunction<D,R,I>::VectorValuedFunction()
{ // Create an array of functions of length 1 an array of length 1


	vf = Vector<ScalarValuedFunction<D,R,I>, I > (1);

	for (int j = vf.MinIndex(); j <= vf.MaxIndex(); j++)
	{
		vf[j] = ScalarValuedFunction<D,R,I>();
	}

	sz = 1;
}

template <class D, class R, class I> 
VectorValuedFunction<D,R,I>::VectorValuedFunction(const I& size) //: DFunction<Vector<D, I>, Vector<R, I>, I> () 
{
	vf = Vector<ScalarValuedFunction<D,R, I>, I> (size);

	for (int j = vf.MinIndex(); j <= vf.MaxIndex(); j++)
	{
		vf[j] = ScalarValuedFunction<D,R, I>();
	}

	sz = size;
}


template <class D, class R, class I> 
	VectorValuedFunction<D,R,I>::VectorValuedFunction(const VectorValuedFunction<D,R,I>& f2)
//	: DFunction<Vector<D, I>, Vector<R, I>,I> (f2)
{ // Copy constructor

	vf = Vector<ScalarValuedFunction<D,R, I > >(f2.vf.Size());

	for (int j = vf.MinIndex(); j <= vf.MaxIndex(); j++)
	{
		vf[j] = f2.vf[j];
	}

	sz = f2.sz;
}

template <class D, class R, class I> 
	VectorValuedFunction<D,R,I>::~VectorValuedFunction()
{ // Destructor

}

template <class D, class R, class I> 
	VectorValuedFunction<D, R, I>& VectorValuedFunction<D,R,I>::operator = (const VectorValuedFunction<D, R, I>& f2)
{ // Assignment operator

		if (this == &f2)
			return *this;

		sz = f2.sz;
		vf = Vector<ScalarValuedFunction<D, R, I>, I> (sz);

		cout << "Size vf " << vf.Size() << endl;

		cout << "Indexes " << vf.MinIndex() << ","  << vf.MaxIndex();

		for (int j = vf.MinIndex(); j <= vf.MaxIndex(); j++)
		{
			vf[j] = f2.vf[j];
		}

		cout << "range this " << (*this).RangeDimension() << endl;
		return *this;

		cout << "range this " << (*this).RangeDimension() << endl;

}

template <class D, class R, class I> 
I VectorValuedFunction<D,R,I>::DomainDimension() const
{ // Number of domain directions

	return 1;
}

template <class D, class R, class I> 
		I VectorValuedFunction<D,R,I>::RangeDimension() const
{ // Number of equations (range)

	cout << "In range dime " << sz << endl;

	return sz;
}

template <class D, class R, class I> 
	void VectorValuedFunction<D,R,I>::function(const I& position, const ScalarValuedFunction<D,R,I>& func)
{

	vf[position].function(func);
}

template <class D, class R, class I> 
Vector<R,I> VectorValuedFunction<D,R,I>::calculate(const Vector<D,I>& x) const
{

		Vector<R,I> result(vf.Size());

		for (I j = result.MinIndex(); j <= result.MaxIndex(); j++)
		{
			result[j] = vf[j].calculate(x);
		}

		return result;

}


template <class D, class R, class I>  
 void VectorValuedFunction<D,R,I>::accept(FunctionVisitor<D,R,I>& v) 
{ // Make a copy of myself

	v.visit(*this);
}



#endif