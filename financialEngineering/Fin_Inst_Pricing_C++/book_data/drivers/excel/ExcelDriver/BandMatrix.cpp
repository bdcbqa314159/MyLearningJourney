// BandMatrix.cpp
//
// Template class for normal matrices.
// A size_t is used for indexing. Indexing starts at 1.
//
// N/A 2002-4-8 DD Another possibility FArray<FArray <TValue> >; Use or redundant values nr, nc
// 2003-4-12 DD Initial code (copied from BandMatrix class)
//
// (C) Datasim Component Technology 2003

#ifndef BandMatrix_cpp
#define BandMatrix_cpp

#include "BandMatrix.hpp"

// Constructors & destructor
template <class V, class TA>
BandMatrix<V, TA>::BandMatrix(): MatrixStructure<V>()
{ // Default constructor

	m_structure=BandArray<BandArray<V, TA>, std::allocator<BandArray<V, TA> > >();

	nr = nc = 1;
}

template <class V, class TA>
BandMatrix<V, TA>::BandMatrix(size_t rows, size_t columns, size_t bandWidth): MatrixStructure<V>()
{ // Constructor with size

	// Create the rows
	m_structure=BandArray<BandArray<V, TA>, std::allocator<BandArray<V, TA> > >(rows);

	// Build up the matrix structure

	// 'Top' extremity
	m_structure[1] = BandArray<V, TA>(columns, 1, K+1);

	size_t startIndex = 1;
	for (size_t i= 2; i< m_structure.Size(); i++)	// N.B. limits!
	{
		m_structure[i]=BandArray<V, TA>(columns, startIndex, 2*K + 1);
		startIndex++;
	}

	// 'Bottom' extremity
	m_structure[m_structure.Size()] = BandArray<V, TA>(columns, 1, K+1);
	nr = rows; nc = columns;

	K = bandWidth;
}

template <class V, class TA>
BandMatrix<V, TA>::BandMatrix(const BandMatrix<V, TA>& source): MatrixStructure<V>(source)
{ // Copy constructor

	m_structure=source.m_structure;

	nr = sopurce.nr; nc = source.nc;

	K = source.K;
}

template <class V, class TA>
BandMatrix<V, TA>::~BandMatrix()
{ // Destructor
}

// Selectors
template <class V, class TA>
size_t BandMatrix<V, TA>::Rows() const
{ // Number of rows

	return nr;
}

template <class V, class TA>
size_t BandMatrix<V, TA>::Columns() const
{ // Number of columns

	return nc;
}

template <class V, class TA>
size_t BandMatrix<V, TA>::bandSize() const
{ // Number of arrays above/below main diagonal

	return K;
}



// Modifiers
// Operators
template <class V, class TA>
ArrayStructure<V>& BandMatrix<V, TA>::operator[] (size_t row)
{ // Subscripting operator

	return m_structure[row];
}

template <class V, class TA>
const ArrayStructure<V>& BandMatrix<V, TA>::operator[] (size_t row) const
{ // Subscripting operator

	return m_structure[row];
}

template <class V, class TA>
BandMatrix<V, TA>& BandMatrix<V, TA>::operator = (const BandMatrix<V, TA>& source)
{ // Assignment operator

	// Exit if same object
	if (this==&source) return *this;

	// Call base class assignment
	MatrixStructure<V>::operator = (source);

	m_structure=source.m_structure;

	nr = source.nr; nc = source.nc;

	K = source.K;

	return *this;
}



#endif	// BandMatrix_cpp
