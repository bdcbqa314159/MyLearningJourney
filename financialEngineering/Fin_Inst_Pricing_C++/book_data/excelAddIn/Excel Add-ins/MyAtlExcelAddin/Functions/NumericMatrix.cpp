// NumericMatrix.hpp
//
// Numeric matrix class.
// This is a matrix class for numerical data. Derived from Matrix and 
// it adds mathematical functions.
//
// 2 february 1999	RD	Started
// 2002-4-9 DD removed functions that belong elsewhere
//
// (C) Datasim Component Technology 1999

#ifndef NumericMatrix_cpp
#define NumericMatrix_cpp

#include "NumericMatrix.hpp"


// Constructors & destructor
template <class V, class I, class S>
NumericMatrix<V, I, S>::NumericMatrix(): Matrix<V, I, S>()
{ // Default constructor
}

template <class V, class I, class S>
NumericMatrix<V, I, S>::NumericMatrix(size_t rows, size_t columns): Matrix<V, I, S>(rows, columns)
{ // Constructor with size. Start index=0.
}

template <class V, class I, class S>
NumericMatrix<V, I, S>::NumericMatrix(size_t rows, size_t columns, I rowStart, I columnStart): Matrix<V, I, S>(rows, columns, rowStart, columnStart)
{ // Constructor with size & start index
}

template <class V, class I, class S>
NumericMatrix<V, I, S>::NumericMatrix(const Matrix<V, I, S>& source): Matrix<V, I, S>(source)
{ // Constructor with matrix
}

template <class V, class I, class S>
NumericMatrix<V, I, S>::NumericMatrix(const NumericMatrix<V, I, S>& source): Matrix<V, I, S>(source)
{ // Copy constructor
}

template <class V, class I, class S>
NumericMatrix<V, I, S>::~NumericMatrix()
{ // Destructor
}

// Selectors
template <class V, class I, class S>
Vector<V, I> NumericMatrix<V, I, S>::Row(I row) const
{ // Return row. Overloads Matrix::Row() to return Vector instead of Array

	return Vector<V, I>(Matrix<V, I, S>::Row(row));
}

template <class V, class I, class S>
Vector<V, I> NumericMatrix<V, I, S>::Column(I column) const
{ // Return Column. Overloads Matrix::Row() to return Vector instead of Array

	return Vector<V, I>(Matrix<V, I, S>::Column(column));
}


// Modifiers
template <class V, class I, class S>
void NumericMatrix<V, I, S>::Row(I row, const Array<V, I> val)
{ // Replace row. Overloaded because Row() selector is overloaded thus hiding Matrix::Row() modifier.

	Matrix<V, I, S>::Row(row, val);
}

template <class V, class I, class S>
void NumericMatrix<V, I, S>::Column(I column, const Array<V, I> val)
{ // Replace column. Overloaded because Column() selector is overloaded thus hiding Matrix::Column() modifier.

	Matrix<V, I, S>::Column(column, val);
}

// Operators
template <class V, class I, class S>
NumericMatrix<V, I, S>& NumericMatrix<V, I, S>::operator = (const NumericMatrix<V, I, S>& source)
{ // Assignment operator

	// Exit if same object
	if (this==&source) return *this;

	// Call base class assignment
	Matrix<V, I, S>::operator = (source);

	return *this;
}

template <class V, class I, class S>
NumericMatrix<V, I, S> NumericMatrix<V, I, S>::operator - () const
{ // Unary minus

	// Create new matrix with same size and same starting index
	NumericMatrix<V, I, S> result(Rows(), Columns(), MinRowIndex(), MinColumnIndex());
	I r, c;

	// Copy all elements negative
	for (r=MinRowIndex(); r<=MaxRowIndex(); r++)
	{
		for (c=MinColumnIndex(); c<=MaxColumnIndex(); c++) result.Element(r, c, -Element(r, c));
	}

	// Return the result
	return result;
}

template <class V, class I, class S>
NumericMatrix<V, I, S> NumericMatrix<V, I, S>::operator + (const V& v) const
{ // Add v to every element

	// Create new matrix with same size and same starting index
	NumericMatrix<V, I, S> result(Rows(), Columns(), MinRowIndex(), MinColumnIndex());
	I r, c;

	// Copy all elements+v
	for (r=MinRowIndex(); r<=MaxRowIndex(); r++)
	{
		for (c=MinColumnIndex(); c<=MaxColumnIndex(); c++) result.Element(r, c, Element(r, c)+v);
	}

	// Return the result
	return result;
}

template <class V, class I, class S>
NumericMatrix<V, I, S> NumericMatrix<V, I, S>::operator - (const V& v) const
{ // Subtract v from every element

	// Create new matrix with same size and same starting index
	NumericMatrix<V, I, S> result(Rows(), Columns(), MinRowIndex(), MinColumnIndex());
	I r, c;

	// Copy all elements-v
	for (r=MinRowIndex(); r<=MaxRowIndex(); r++)
	{
		for (c=MinColumnIndex(); c<=MaxColumnIndex(); c++) result.Element(r, c, Element(r, c)-v);
	}

	// Return the result
	return result;
}

template <class V, class I, class S>
NumericMatrix<V, I, S> NumericMatrix<V, I, S>::operator * (const V& v) const
{ // Multiply every element by v

	// Create new matrix with same size and same starting index
	NumericMatrix<V, I, S> result(Rows(), Columns(), MinRowIndex(), MinColumnIndex());
	I r, c;

	// Copy all elements*v
	for (r=MinRowIndex(); r<=MaxRowIndex(); r++)
	{
		for (c=MinColumnIndex(); c<=MaxColumnIndex(); c++) result.Element(r, c, Element(r, c)*v);
	}

	// Return the result
	return result;
}

template <class V, class I, class S>
NumericMatrix<V, I, S> NumericMatrix<V, I, S>::operator / (const V& v) const
{ // Divide every element by v

	// Create new matrix with same size and same starting index
	NumericMatrix<V, I, S> result(Rows(), Columns(), MinRowIndex(), MinColumnIndex());
	I r, c;

	// Copy all elements/v
	for (r=MinRowIndex(); r<=MaxRowIndex(); r++)
	{
		for (c=MinColumnIndex(); c<=MaxColumnIndex(); c++) result.Element(r, c, Element(r, c)/v);
	}

	// Return the result
	return result;
}

template <class V, class I, class S>
NumericMatrix<V, I, S> NumericMatrix<V, I, S>::operator + (const NumericMatrix<V, I, S>& m) const
{ // Add the elements

	
	// Create new matrix with same size and same starting index
	NumericMatrix<V, I, S> result(Rows(), Columns(), MinRowIndex(), MinColumnIndex());
	I r1, c1, r2, c2;

	// Add all elements
	for (r1=MinRowIndex(), r2=m.MinRowIndex(); r1<=MaxRowIndex(); r1++, r2++)
	{
		for (c1=MinColumnIndex(), c2=m.MinColumnIndex(); c1<=MaxColumnIndex(); c1++, c2++) result.Element(r1, c1, Element(r1, c1)+m.Element(r2, c2));
	}

	// Return the result
	return result;
}

template <class V, class I, class S>
NumericMatrix<V, I, S> NumericMatrix<V, I, S>::operator - (const NumericMatrix<V, I, S>& m) const
{ // Subtract the elements

	// Create new matrix with same size and same starting index
	NumericMatrix<V, I, S> result(Rows(), Columns(), MinRowIndex(), MinColumnIndex());
	I r1, c1, r2, c2;

	// Add all elements
	for (r1=MinRowIndex(), r2=m.MinRowIndex(); r1<=MaxRowIndex(); r1++, r2++)
	{
		for (c1=MinColumnIndex(), c2=m.MinColumnIndex(); c1<=MaxColumnIndex(); c1++, c2++) result.Element(r1, c1, Element(r1, c1)-m.Element(r2, c2));
	}

	// Return the result
	return result;
}

template <class V, class I, class S>
NumericMatrix<V, I, S> NumericMatrix<V, I, S>::operator * (const NumericMatrix<V, I, S>& m) const
{ // Multiply the matrix.
  // This function can be optimized by calculating the inner product ourselfs instead of 
  // using the InnerProduct function of Vector. This saves a couple of row and column copies.


	// Create new matrix with same row size of first matrix and column size of second matrix and same starting index as first matrix
	NumericMatrix<V, I, S> result(Rows(), m.Columns(), MinRowIndex(), MinColumnIndex());
	I r1, c2, rr, cr;

	// Element of resulting array is dot/inner product of corresponding row m1 and corresponding column m2
	for (rr=result.MinRowIndex(), r1=MinRowIndex(); rr<=result.MaxRowIndex(); rr++, r1++)
	{
		for (cr=result.MinColumnIndex(), c2=m.MinColumnIndex(); cr<=result.MaxColumnIndex(); cr++, c2++) result.Element(rr, cr, Row(r1).InnerProduct(m.Column(c2)));
	}

	// Return the result
	return result;
}

template <class V, class I, class S>
NumericMatrix<V, I, S>& NumericMatrix<V, I, S>::operator += (const V& v)
{ // Add v to every element

	I r, c;

	// Add v to every element of the matrix
	for (r=MinRowIndex(); r<=MaxRowIndex(); r++)
	{
		for (c=MinColumnIndex(); c<=MaxColumnIndex(); c++) Element(r, c, Element(r, c)+v);
	}

	return *this;
}

template <class V, class I, class S>
NumericMatrix<V, I, S>& NumericMatrix<V, I, S>::operator -= (const V& v)
{ // Subtract v from every element

	I r, c;

	// Subtract v from every element of the matrix
	for (r=MinRowIndex(); r<=MaxRowIndex(); r++)
	{
		for (c=MinColumnIndex(); c<=MaxColumnIndex(); c++) Element(r, c, Element(r, c)-v);
	}

	return *this;
}

template <class V, class I, class S>
NumericMatrix<V, I, S>& NumericMatrix<V, I, S>::operator *= (const V& v)
{ // Multiply every element by v

	I r, c;

	// Multiply every element of the matrix by v
	for (r=MinRowIndex(); r<=MaxRowIndex(); r++)
	{
		for (c=MinColumnIndex(); c<=MaxColumnIndex(); c++) Element(r, c, Element(r, c)*v);
	}

	return *this;
}

template <class V, class I, class S>
NumericMatrix<V, I, S>& NumericMatrix<V, I, S>::operator /= (const V& v)
{ // Divide every element by v

	I r, c;

	// Divide every element of the matrix by v
	for (r=MinRowIndex(); r<=MaxRowIndex(); r++)
	{
		for (c=MinColumnIndex(); c<=MaxColumnIndex(); c++) Element(r, c, Element(r, c)/v);
	}

	return *this;
}

template <class V, class I, class S>
NumericMatrix<V, I, S>& NumericMatrix<V, I, S>::operator += (const NumericMatrix<V, I, S>& m)
{ // Add the elements

	
	I r1, c1, r2, c2;

	// Add all elements
	for (r1=MinRowIndex(), r2=m.MinRowIndex(); r1<=MaxRowIndex(); r1++, r2++)
	{
		for (c1=MinColumnIndex(), c2=m.MinColumnIndex(); c1<=MaxColumnIndex(); c1++, c2++) Element(r1, c1, Element(r1, c1)+m.Element(r2, c2));
	}

	// Return the result
	return *this;
}

template <class V, class I, class S>
NumericMatrix<V, I, S>& NumericMatrix<V, I, S>::operator -= (const NumericMatrix<V, I, S>& m)
{ // Subtract the elements

	I r1, c1, r2, c2;

	// Subtract all elements
	for (r1=MinRowIndex(), r2=m.MinRowIndex(); r1<=MaxRowIndex(); r1++, r2++)
	{
		for (c1=MinColumnIndex(), c2=m.MinColumnIndex(); c1<=MaxColumnIndex(); c1++, c2++) Element(r1, c1, Element(r1, c1)-m.Element(r2, c2));
	}

	// Return the result
	return *this;
}

template <class V, class I, class S>
NumericMatrix<V, I, S>& NumericMatrix<V, I, S>::operator *= (const NumericMatrix<V, I, S>& m)
{ // Multiply the matrices

	*this=(*this)*m;

	return *this;
}


#endif	// NumericMatrix_cpp