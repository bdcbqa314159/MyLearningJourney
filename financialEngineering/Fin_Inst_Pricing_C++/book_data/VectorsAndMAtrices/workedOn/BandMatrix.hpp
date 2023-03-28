// BandMatrix.hpp
//
// Template class for banded matrices, for example tridiagonal
// matrices. A size_t value is used for indexing. Indexing starts at 1.
// We need a new member data that tells us what the band width (size) K is.
// This means that we have 1 main diagonal array, K arrays above the main 
// diagonal and K arrays below the main diagonal. Thus, in the 'interior' 
// of the array we have 2K + 1 array; at the extermities we have 1 + K and 
// K + 1 arrays, respectively.
//
// (C) Datasim Component Technology 2003

#ifndef BandMatrix_hpp
#define BandMatrix_hpp

#include "MatrixStructure.cpp"
#include "BandArray.hpp"


template <class TValue, class TA=std::allocator<TValue> >
class BandMatrix: public MatrixStructure<TValue>
{
	BandArray<BandArray<TValue, TA>, std::allocator<BandArray<TValue, TA> > > m_structure;

	// Redundant data 
	size_t nr, nc;
	size_t K;		// The band size

public:
	// Constructors & destructor
	BandMatrix();													// Tridiagonal matrix K == 1
	BandMatrix(size_t rows, size_t columns, size_t bandWidth);						// Constructor with size and K
	BandMatrix(const BandMatrix<TValue, TA>& source);				// Copy constructor
	virtual ~BandMatrix();											// Destructor

	// Selectors
	virtual size_t Rows() const;									// Number of rows
	virtual size_t Columns() const;									// Number of columns
	virtual size_t bandSize() const;								// Number above/below main diagonal

	// Modifiers

	// Operators
	virtual ArrayStructure<TValue>& operator[] (size_t index);					// Subscripting operator
	virtual const ArrayStructure<TValue>& operator[] (size_t index) const;		// Subscripting operator

	BandMatrix<TValue, TA>& operator = (const BandMatrix<TValue, TA>& source);
};



#endif	// BandMatrix_hpp