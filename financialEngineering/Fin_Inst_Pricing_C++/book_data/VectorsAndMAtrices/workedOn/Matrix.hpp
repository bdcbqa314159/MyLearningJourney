// Matrix.hpp
//
// Matrix class. It uses an MatrixStructure for the actual storage.
// This class acts like a kind of adapter class since it defines a common interface
// for different matrix structures like normal matrices and sparse matrices.
// The matrix structure to use is given as template argument.
//
// (C) Datasim Component Technology 1999

#ifndef Matrix_hpp
#define Matrix_hpp

#include "FullMatrix.cpp"
#include "Array.hpp"

// Default structure is FullArray with default allocator. Default integral type is int.
template <class V, class I=int, class S=FullMatrix<V> >
class Matrix
{
private:
	S m_structure;				// The array structure
	I m_rowstart;				// The row start index
	I m_columnstart;			// The column start index

	// Redundant data 
	size_t nr, nc;

public:
	// Constructors & destructor
	Matrix();																			// Default constructor
	Matrix(size_t rows, size_t columns);												// Constructor with size. Start index=0.
	Matrix(size_t rows, size_t columns, I rowStart, I columnStart);		// Constructor with size & start index
	Matrix(const Matrix<V, I, S>& source);						// Copy constructor
	virtual ~Matrix();																	// Destructor

	// Selectors
	I MinRowIndex() const;				// Return the minimum row index
	I MaxRowIndex() const;				// Return the maximum row index
	I MinColumnIndex() const;			// Return the minimum column index
	I MaxColumnIndex() const;			// Return the maximum column index

	size_t Rows() const;				// The number of rows
	size_t Columns() const;				// The number of columns


	// Operators
	const V& operator () (I row, I column) const;	// Get the element at position
	V& operator () (I row, I column);				// Get the element at position

	Matrix<V, I, S>& operator = (const Matrix<V, I, S>& source);
};

#endif	// Matrix_hpp

