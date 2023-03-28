// BandArray.hpp
//
// Template class for 'banded' arrays. These arrays contain a contiguous
// set of values within a larger container. Note that all indices are based
// on the assumption that the first index is 1.
//
// (C) Datasim Component Technology 2003

#ifndef BandArray_hpp
#define BandArray_hpp

// Use the STL vector class
#include <vector>
#include "ArrayStructure.cpp"


template <class V, class TA=std::allocator<V> >
							class BandArray: public ArrayStructure<V>
{
private:
	std::vector<V, TA> m_vector;	// Use STL vector class for storage of contiguous memory
	size_t low, upp;				// Lower and uppers indices of contiguous memory							

public:
	// Constructors & destructor
	BandArray();											
	BandArray(size_t size, size_t lower, size_t upper);									
	BandArray(const BandArray<V, TA>& source);				
	virtual ~BandArray();									

	// Selectors
	virtual size_t Size() const;
	size_t lowerIndex() const;
	size_t upperIndex() const;

	// Modifiers

	// Operators
	V& operator[] (size_t index);							
	const V& operator[] (size_t index) const;				

	BandArray<V, TA>& operator = (const BandArray<V, TA>& source);
};


#endif	// BandArray_hpp
