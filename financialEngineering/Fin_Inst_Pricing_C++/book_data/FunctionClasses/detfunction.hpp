// detfunction.hpp
//
// Deterministic functions. This is the base class for all kinds of deterministic
// functions. Included are:
//
//		Atomic functions
//		Vector-valued and matrix-valued functions
//		Functions of another function
//		Lists/Vectors of functions
//
// The classes are:
//
//		ScalarFunction (maps a scalar value to a scalar value)
//		VectorFunction (maps a scalar value to a Vector)
//		ScalarVauedFunction (maps a Vector to a scalar value)
//		VectorValuedFunction (maps a Vector to a Vector)
// 
// The function classes are encaapsulations of C-functions. The class ScalarFunction is the only class
// can interface directly with C functions. This promotes information hiding but it might entail
// a bit more work on the part of the client.
// 
// (C) Datasim Component Technology BV 2000-2003
//

#ifndef DFunction_HPP
#define DFunction_HPP

template <class D, class R, class I> class FunctionVisitor;

#include "vector.cpp"


// Basic building block
template <class D, class R, class I = int> class ScalarFunction 
{ // A fundamental building-block class that is used by many other classes.


private:
	
	R (*f)(const D& x);		// Hidden classic C-type function
	

public:
	ScalarFunction();
	ScalarFunction (R (*fp)(const D& x));	// Using function objects
	ScalarFunction(const ScalarFunction<D, R,I>& f2);
	~ScalarFunction();
	ScalarFunction<D, R,I>& operator = (const ScalarFunction<D, R,I>& f2);

	R calculate(const D& x) const;

	// Choosing a new function
	void function(R (*fp)(const D& x));
	void function (const ScalarFunction<D,R,I>& NewFunc);

	void accept(FunctionVisitor<D,R,I>& v);			// Extending functionality (Visitor)

	// Useful functions
	Vector<R,I> Values(const Vector<D,I>& InputValues) const;	// Y values based on X values

};

//////////////////////////////////////////////////////////////////////////////////////////

// Functions based on vectors
template <class D, class R, class I = int> class VectorFunction
{ // Class representing vector functions. These map D into R X R (n times).
  // D == Domain, R == Range, I == Index Type

private:
		Vector<ScalarFunction<D, R,I> > vf;

		void init(const I& size);
		
public:
		VectorFunction();										// Contains 1 function
		VectorFunction(const I& size);							// Number of components
		VectorFunction(const VectorFunction<D,R,I>& f2);		// Copy constructor
		~VectorFunction();	

		VectorFunction<D, R, I>& operator = (const VectorFunction<D, R, I>& f2);

		I Dimension() const;									// Number of equations

		// Now set and get the individual functions
		void function(const I& position, const ScalarFunction<D,R,I>& func);
		ScalarFunction<D,R,I> function (const I& size) const;

		Vector<R,I> calculate(const D& x) const;

		void accept(FunctionVisitor<D,R,I>& v);		// Extending functionality (Visitor)

};

///////////////////////////////////////////////////////////////////////////////////

template <class D, class R, class I = int> class ScalarValuedFunction 
{ // Class representing scalar-valued functions. These map D X D (n times) into R.
  // D == Domain, R == Range, I == Index Type

private:

		ScalarFunction<Vector<D,I>, R, I> scf;

public:
		ScalarValuedFunction();										
		ScalarValuedFunction(const ScalarFunction<Vector<D,I>, R, I>& scalar_function);					
		ScalarValuedFunction(const ScalarValuedFunction<D,R,I>& f2);		// Copy constructor
		~ScalarValuedFunction();	

		ScalarValuedFunction<D, R, I>& operator = (const ScalarValuedFunction<D, R, I>& f2);

		void function(R (*fp)(const Vector<D, I>& x));
		void function (const ScalarValuedFunction<D, R,I>& NewFunc);
		R calculate(const Vector<D,I>& x) const;

		I Dimension() const;									// Number of equations

		void accept(FunctionVisitor<D,R,I>& v);		// Extending functionality (Visitor)


};

///////////////////////////////////////////////////////////////////////////////////////

template <class D, class R, class I = int> class VectorValuedFunction 
{ // Class of vector-valued functions
  // D == Domain, R == Range, I == Index Type

private:
		Vector<ScalarValuedFunction<D, R, I>, I > vf;
		I sz;
public:
		VectorValuedFunction();	
		VectorValuedFunction(const I& size);							// Number of Range components
		VectorValuedFunction(const VectorValuedFunction<D,R,I>& f2);
		~VectorValuedFunction();	

		VectorValuedFunction<D, R, I>& operator = (const VectorValuedFunction<D, R, I>& f2);

		I DomainDimension() const;									// Number of domain directions
		I RangeDimension() const;									// Number of equations (range)

		void function(const I& position, const ScalarValuedFunction<D,R,I>& func);

		Vector<R,I> calculate(const Vector<D,I>& x) const;

		void accept(FunctionVisitor<D,R,I>& v);		// Extending functionality (Visitor)

};


#endif