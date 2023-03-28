// BandArray.cpp
//
// Template class for a normal arrays.
//
// 12 April 2003 DD Code created (as a copy of FullArray)
//
//
// (C) Datasim Component Technology 2003

#ifndef BandArray_cpp
#define BandArray_cpp

#include "BandArray.hpp"

// Constructors & destructor
template <class V, class TA>
BandArray<V, TA>::BandArray(): ArrayStructure<V>()
{ // Default constructor

	m_vector=std::vector<V, TA>(1);	// vector object with 1 element
	low = upp = 1;
}

template <class V, class TA>
BandArray<V, TA>::BandArray(size_t size, size_t lower, size_t upper): ArrayStructure<V>()
{ // Constructor with size

	m_vector=std::vector<V, TA>(size);
	low = lower;
	upp = upper;
}

template <class V, class TA>
BandArray<V, TA>::BandArray(const BandArray<V, TA>& source): ArrayStructure<V>(source)
{ // Copy constructor

	m_vector=source.m_vector;
	low = source.low;
	upp = source.upp;
}

template <class V, class TA>
BandArray<V, TA>::~BandArray()
{ // Destructor
}

// Selectors
template <class V, class TA>
size_t BandArray<V, TA>::Size() const
{ // Size of the array

	return m_vector.size();
}

template <class V, class TA>
	size_t BandArray<V, TA>::lowerIndex() const
{
	return low;
}


template <class V, class TA>
	size_t BandArray<V, TA>::upperIndex() const
{

	return upp;
}



// Modifiers

// Operators
template <class V, class TA>
V& BandArray<V, TA>::operator[] (size_t index)
{ // Subscripting operator

	if (index < low || index > upp)
		return 0.0;

	return m_vector[index - 1];
}

template <class V, class TA>
const V& BandArray<V, TA>::operator[] (size_t index) const
{ // Subscripting operator

	if (index < low || index > upp)
		return 0.0;

	return m_vector[index - 1];
}

template <class V, class TA>
BandArray<V, TA>& BandArray<V, TA>::operator = (const BandArray<V, TA>& source)
{ // Assignment operator

	// Exit if same object
	if (this==&source) return *this;

	// Call base class constructor
	ArrayStructure<V>::operator = (source);

	// Copy the embedded vector
	m_vector=source.m_vector;
	low = source.low;
	upp = source.upp;

	return *this;
}


#endif // BandArray_cpp
