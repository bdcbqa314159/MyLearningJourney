// Lattice.hpp
//
// Class respresenting a special kind of tree-like matrix that is
// needed in specific applications, for example binomial and trinomial 
// methods in options pricing.
//
// The matrix is 'expanding' in the form of a lattice; the user must define a 
// function that states how many elements to create in moving from step 'j' 
// to step 'j+1'. The lattice is recombining or reconnecting as is usual in 
// some applications.
//
//
// (C) Datasim Component Technology 2001-2004


#ifndef Lattice_hpp
#define Lattice_hpp

#include "Array.cpp"
#include "Vector.cpp"

// This class is a special kind of matrix with a given number of rows
// and where the number of columns is row-dependent. For example, in a
// binomial matrix the number of columns increases by 1 (i + 1) wrt the previous
// row while in a trinomial matrix the number increases by a factor of
// 2*i - 1, where is the number of columns in the previous row. However, this
// factor is variable and you can choose it.
//

enum LatticeType {BinomialLatticeType, TrinomialLatticeType};

template <class V, class I> class Lattice
{
private:

	// Implement as a full nested Vector class
	Array<Vector<V, I>, I >  tree;

	// Redundant data
	I nrows;			// Number of rows
	LatticeType typ;	// What kind of lattice

	// Private functions
	I next_index(const I& iprev);	// Calculate branching factor

	Lattice();									// Default constructor

public:
	// Constructors & destructor
	Lattice(const I& Nrows, LatticeType lattice); 	// Number of rows and branch factor
	Lattice(const I& Nrows, LatticeType lattice, const V& val); // + value at nodes
	Lattice(const Lattice<V, I>& source);		// Copy constructor
	virtual ~Lattice();							// Destructor

	// Selectors
	LatticeType type() const;

	// Iterating in a Lattice; we need forward and backward versions
	I MinIndex() const;								// Return the minimum row index
	I MaxIndex() const;								// Return the maximum row index
	I Depth() const;								// The (depth) number of rows in the lattice


	// Operators
	Lattice<V, I>& operator = (const Lattice<V, I>& source);
	Vector<V, I>& operator [] (const I& index);				// Subscripting operator
	const Vector<V, I>& operator [] (const I& index) const;	// Subscripting operator

};

#endif	