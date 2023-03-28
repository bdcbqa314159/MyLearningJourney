// Lattice.cpp
//
// Class respresenting a special kind of triangular matrix that is
// needed in specific applications, for example binomial and trinomial 
// methods in options pricing.
//
// The matrix is 'expanding' in the form of a lattice; the user must define a function
// that states how many elements to create in moving from step 'j' to step 'j+1'.
//
// Last modification dates:
//
//	2001-4-23 DD kick-off date
//
// (C) Datasim Component Technology 2001


#ifndef Lattice_cpp
#define Lattice_cpp


#include "Lattice.hpp"

template <class V, class I>
	I Lattice< V, I>::next_index(const I& iprev)
{ // Calculate branching factor

	I result = iprev + 1;	// Default

	if (typ == TrinomialLatticeType)
		result = (2*iprev) - 1;


	return result;
}


// Constructors & destructor
template <class V, class I> Lattice< V, I>::Lattice()
{ // Default constructor

		tree = Array<Vector<V, I> > (1, 1); // A flat matrix with 1 row in array
											// Start index == 1
		tree[1] = Vector<V, I> (1,1);

		typ = BinomialLatticeType;
}


template <class V, class I> Lattice< V, I>::Lattice(const I& Nrows, LatticeType lattice)
{ // Number of rows and branch factor


	nrows = Nrows;

	tree = Array<Vector<V, I>, I> (nrows + 1, 1); // Start index == 1

	I currentBranch = 1;	// There is always one single root

	// Initialise tree vectors (give sizes of vectors)
	for(int j = tree.MinIndex(); j <= tree.MaxIndex(); j++)
	{
		tree[j] = 	Vector<double, int>(currentBranch,1);	

		// Calculate the next number of columns

		currentBranch = next_index(currentBranch);
	}

	typ = lattice;
}

template <class V, class I> Lattice< V, I>::Lattice(const I& Nrows, LatticeType lattice, const V& val)
{ // Number of rows and branch factor


	nrows = Nrows;

	tree = Array<Vector<V, I>, I> (nrows + 1, 1); // Start index == 1

	I currentBranch = 1;	// There is always one single root

	// Initialise tree vectors (give sizes of vectors)
	for(int j = tree.MinIndex(); j <= tree.MaxIndex(); j++)
	{
		tree[j] = 	Vector<double, int>(currentBranch, 1, val);	

		// Calculate the next number of columns

		currentBranch = next_index(currentBranch);
	}

	typ = lattice;
}


template <class V, class I> Lattice<V, I>::Lattice(const Lattice<V, I>& source)
{ // Copy constructor

	tree = source.tree;
	typ = source.typ;
}

template <class V, class I> Lattice<V, I>::~Lattice()
{ // Destructor

}


// Operators
template <class V, class I> Lattice<V, I>& Lattice< V, I>::operator = (const Lattice<V, I>& source)
{

	if (this == &source)
		return *this;

	tree = source.tree;
	typ = source.typ;


	return *this;
}


// Iterating in a Lattice; we need forward and backward versions
template <class V, class I>	I Lattice< V, I>::MinIndex() const
{ // Return the minimum row index

	return tree.MinIndex();
}

template <class V, class I>	I Lattice< V, I>::MaxIndex() const
{ // Return the maximum row index

	return tree.MaxIndex();

}

// Selectors
template <class V, class I>	LatticeType Lattice<V, I>::type() const
{
	return typ;
}

template <class V, class I>	I Lattice<V, I>::Depth() const
{ // The (depth) number of rows in the lattice

	return tree.Size();
}



template <class V, class I>
Vector<V, I>& Lattice<V, I>::operator [] (const I& index)
{ // Subscripting operator

	return tree[index];
}


template <class V, class I>
const Vector<V, I>& Lattice<V, I>::operator [] (const I& index) const
{ // Subscripting operator

	return tree[index];
}
 
#endif
