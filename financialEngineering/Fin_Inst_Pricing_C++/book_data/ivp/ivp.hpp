// ivp.hpp
//
// Generic clasdses that model initial value problems (IVPs). These systems
// can originate when time-dependent initial boundary value problems (IBVP) 
// are discretised in the space variable (which can be multi-dimensional). 
// The resulting system of ODEs is sometimes called the semi-discrete scheme.
//	
// The assumption is that the domain and range spaces are the same, for example 
// double-precision numbers.
//
// The kinds of IVPs in this module are:
//
//		1. Scalar linear IVP du/dt + a(t)u = f(t), u(0) = A
//		2. Scalar NONlinear IVP du/dt = f(t, u), u(0) = A
//		3. Linear IVP system dU/dt + A(t)U = F(t), U(0) = A. In this case U and F
//		are vector-valued function, A is a matrix of scalar-valued functions and A
//		is a vector.
//
// (C) Datasim Component Technology BV 2003
//

#ifndef IVP_hpp
#define IVP_hpp

#include "detfunction.cpp"
#include "vector.cpp"
#include "range.cpp"


template <class V> class ScalarIVP			// du/dt + a(t)u = f(t), u(0) = A
{ // Scalar initial value problem (first order). Mainly for test cases 
  // and illustration of theory and models.

private:
		
		V ic;					// Initial condition
		Range<V> ran;			// The interval that we are interested in

		V (*rhs)(const V& t);	// Forcing term f(t), the right-hand side
		V (*a)(const V& t);		// The coefficient of the zero order term

public:
		ScalarIVP();
		ScalarIVP(const Range<V> range, const V& initial_condition);
		ScalarIVP(const ScalarIVP<V>& source); 
		
		virtual ~ScalarIVP();
 	
		ScalarIVP<V>& operator = (const ScalarIVP<V>& source);

		// Choosing functions in equation
		void Rhs(V (*fp)(const V& x));		// Choose the function f(t)
		void Coeff(V (*fp)(const V& x));	// Choose the function a(t)

		// Selector functions
		Range<V> range() const;				// Interval of interest
		V startValue() const;				// Give the initial value
		V RhsCalc(const V& t) const;		// Calculate the function f(t)
		V CoeffCalc(const V& t) const;		// Calculate the value of the coefficient
};

/*

template <class V> class NLScalarIVP		// du/dt = f(t, u(t)), u(0) = A
{ // Nonlinear scalar initial value problem (first order). Mainly for test cases 
  // and illustration of theory and models.

private:
		
		V ic;					// Initial condition
		Range<V> ran;			// The interval that we are interested in

		V (*f) (const V& t, const V& u);

public:
		NLScalarIVP();
		NLScalarIVP(const Range<V> range, const V& initial_condition);
		NLScalarIVP(const NLScalarIVP<V>& source); 
		
		virtual ~NLScalarIVP();
 	
		NLScalarIVP<V>& operator = (const NLScalarIVP<V>& source);

		// Choosing functions in equation
		void Rhs(V (*func) (const V& t, const V& u) );
		// Choose the function f(t)
	
		// Selector functions
		Range<V> range() const;				// Interval of interest
		V startValue() const;				// Give the initial value
		V RhsCalc(const V& t, const V& u) const;// Calculate the function f(t, u)

};


template <class V, class I> class LinearIVP
{ // General Linear IVP dU/dt + AU = F, U(0) = A
  // V == Numeric type, I == Indexing type

private:

		Range<V> ran;						// Interval where integration takes place
		Vector<V,I> ic;						// Initial condition
	//	NumericMatrix<ScalarFunction<V,V,I>, I > A;// Matrix function
		int A;
		VectorFunction <V,V,I> F;			// Right-hand side of equation
		I dim;								// Number of dimensions in ODE

public:
		LinearIVP();
		LinearIVP(const Range<V>& range, const Vector<V,I>& initial_condition);
		LinearIVP(const LinearIVP<V,I>& source); 

		LinearIVP<V,I>& operator = (const LinearIVP<V,I>& source);
	
		// Modifier functions
		void matrixCoefficient (const NumericMatrix<ScalarFunction<V,V,I>, I>& Anew );
		void Rhs(const VectorFunction <V,V,I>& RHS);

		// Is this a well-defined IVP? Dimension correct?
		bool ConsistentIVP() const;

};
*/

#endif
