// LatticeMechanisms.hpp
//
// Generic functions that have to do with lattice classes.
//
// (C) Datasim Education BV 2004
//

#ifndef LatticeMechanisms_hpp
#define LatticeMechanisms_hpp

#include "lattice.cpp"


// We assume that the lattice object has been created and we
// now give values to the knot points. The lattice objects will
// be modified.

// Forward build up of the tree from the initial root point
template <class V, class I> void modify	(Lattice<V, I>& source,
						const V& rootValue, const V& up, const V& down);

// Traverse the binomial tree from the terminal position and work backwards. The vector RHS
// must hav size 2N - 1, where N is the number of intervals.

enum ExerciseType {EuropeanExerciseType, AmericanExerciseType};
enum OptionType {PutOptionType, CallOptionType};

template <class V, class I> V traverse	(const Lattice<V, I>& source, const Vector<V,I>& RHS,
						const V& probValue, const V& discounting, ExerciseType type,
						Lattice<V, I>& treevalues);

// Derivatives (Greeks)
template <class V, class I> Lattice<V, I> dividedDifference (const Lattice<V, I>& Y, const Lattice<V, I>& X);

// Discrete payoff functions
template <class V, class I> Vector<V,I> CallPayOff(const V& K, const Vector<V,I>& StockArr);
template <class V, class I> Vector<V,I> PutPayOff(const V& K, const Vector<V,I>& StockArr);

// Adjust a lattice for American options; we must tell the strike K and whether it is call or put
template <class V, class I> void modify	(Lattice<V, I>& source,
						const V& K, const V& prob, OptionType otype);

#endif
