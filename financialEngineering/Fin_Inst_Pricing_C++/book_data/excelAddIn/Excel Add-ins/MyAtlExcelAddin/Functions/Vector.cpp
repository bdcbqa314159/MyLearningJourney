// Vector.cpp
//
// Vector class is an array with mathematical functions
//
// 29 january 1999	RD	Started
// 2002-1-21 DD removed some specila functions; delta, gamma etc.
//
// (C) Datasim Component Technology 1999

#ifndef Vector_cpp
#define Vector_cpp

#include "Vector.hpp"


// Constructors & destructor
template <class V, class I, class S>
Vector<V, I, S>::Vector(): Array<V, I, S>()
{ // Default constructor
}

template <class V, class I, class S>
Vector<V, I, S>::Vector(size_t size): Array<V, I, S>(size)
{ // Constructor with size. Start index=1.
}

template <class V, class I, class S>
Vector<V, I, S>::Vector(size_t size, I start): Array<V, I, S>(size, start)
{ // Constructor with size & start index
}

template <class V, class I, class S>
Vector<V, I, S>::Vector(size_t size, I start, const V& val): Array<V, I, S>(size, start, val)
{ // Constructor with size & start index

	
}


template <class V, class I, class S>
Vector<V, I, S>::Vector(const Vector<V, I, S>& source): Array<V, I, S>(source)
{ // Copy constructor
}

template <class V, class I, class S>
Vector<V, I, S>::Vector(const Array<V, I, S>& source): Array<V, I, S>(source)
{ // Constructor with a Array
}

template <class V, class I, class S>
Vector<V, I, S>::~Vector()
{ // Destructor
}


// Modifiers
// Operators
template <class V, class I, class S>
Vector<V, I, S>& Vector<V, I, S>::operator = (const Vector<V, I, S>& source)
{ // Assignment operator

	// Exit if same object
	if (this==&source) return *this;

	// Call baseclass assignment
	Array<V, I, S>::operator = (source);

	return *this;
}

template <class V, class I, class S>
Vector<V, I, S> Vector<V, I, S>::operator - () const
{ // Unary minus

	// Create new vector of same size and same starting index
	Vector<V, I, S> result(Size(), MinIndex());

	// Copy all elements negative
	for (I i=MinIndex(); i<=MaxIndex(); i++) result[i] = - result[i];

	// Return result
	return result;
}

template <class V, class I, class S>
Vector<V, I, S> Vector<V, I, S>::operator + (const V& v) const
{ // Add v to every element

	// Create new vector of same size and same starting index
	Vector<V, I, S> result(Size(), MinIndex());

	// Copy all elements + v
	for (I i=MinIndex(); i<=MaxIndex(); i++) result[i] = (*this)[i] + v;

	// Return result
	return result;
}

template <class V, class I, class S>
Vector<V, I, S> Vector<V, I, S>::operator * (const V& v) const
{ // Add v to every element

	// Create new vector of same size and same starting index
	Vector<V, I, S> result(Size(), MinIndex());

	// Copy all elements + v
	for (I i=MinIndex(); i<=MaxIndex(); i++) result[i] = (*this)[i] * v;
	// Return result
	return result;
}

template <class V, class I, class S>
Vector<V, I, S> Vector<V, I, S>::operator - (const V& v) const
{ // Subtract v from every element

	// Create new vector of same size and same starting index
	Vector<V, I, S> result(Size(), MinIndex());

	// Copy all elements - v
	for (I i=MinIndex(); i<=MaxIndex(); i++) result[i] = (*this)[i] - v;

	// Return result
	return result;
}




template <class V, class I, class S>
Vector<V, I, S> Vector<V, I, S>::operator + (const Vector<V, I, S>& v) const
{ // Add the elements


	// Create new vector of same size and same starting index
	Vector<V, I, S> result(Size(), MinIndex());

	// Result[x]=Source[x]+v[x];
	for (I i=MinIndex(); i<=MaxIndex(); i++) result[i] = (*this)[i] + v[i];

	// Return result
	return result;
}

template <class V, class I, class S>
Vector<V, I, S> Vector<V, I, S>::operator - (const Vector<V, I, S>& v) const
{ // Subtract the elements


	// Create new vector of same size and same starting index
	Vector<V, I, S> result(Size(), MinIndex());

	// Result[x]=Source[x]-v[x];
	for (I i=MinIndex(); i<=MaxIndex(); i++) result[i] = (*this)[i] - v[i];

	// Return result
	return result;
}








#endif	// Vector_cpp