
// function.hpp
//
// Abstract base class for all possible types of functions that are needed in
// business and industry. For example, it is a base class for all:
//
//		Deterministic functions in numerical analysis in general
//		'Stochastic' functions in Stochastic mathematics (e.g. SDE)
//		Fuzzy functions
//		Functions in genetic algorithms (GAs)
//
// In general terms a function (mapping) f is defined by
//
//		f: A --> B
//
//	where A is the Domain of f and B is the co-Domain of f.
//
//	It is sometimes useful to think of a function as a 
//	Cartesian product in the form (s,t) where s is in A
//	and t is in B.
//
// (C) Datasim Component Technology BV 2000
//

#ifndef Function_HPP
#define Function_HPP

template <class D, class R, class I> class FunctionVisitor;		// Forward reference

template <class D, class R, class I> class Function
{ // D == Domain, R == Range
private:

	
public:
	//	virtual Function<D, R, I>* Clone() const = 0; // A heap-copy of myself
		virtual void accept(FunctionVisitor<D,R,I>& v) = 0;   // Extending functionality

	//	virtual R calculate(const D& x) const = 0; // Derived classes must do it!

		// We try to have as little functionality as possible here
};

/*
template <class D, class R> class StochasticFunction: public Function <D, R>
{ // Abstract base class for all stochastic functions
};

*/

#endif