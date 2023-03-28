// AssocArray.hpp
//
// Associative array class. In this case we access elements by 
// using non-integral indices. This is potentially a very useful class
// and it can be used in many financial applications.
// 
// This is a proof-of-concept (POC) class.
//
// (C) Datasim Component Technology 1999-2004

#ifndef AssocArray_hpp
#define AssocArray_hpp

#include "Array.cpp"
#include <map>
#include <list>
using namespace std;

// This class is an array of values V indexed by the indexing set V.
// Default structure is FullArray with default allocator. Default integral 
// type is int.
template <class V, class AI = string, class I=int, class S=FullArray<V> >
												class AssocArray
{
private: 
		map<AI,V> internal_array;	// The list of associative values, e.g. strings


public:
	// Constructors & destructor
	AssocArray();
	AssocArray(const AssocArray<V, AI, I, S>& arr2);
	// Construct the map from a list of names and values
	AssocArray(const list<AI>& names, const Array<V, I, S>& source);
	AssocArray(const Array<AI>& names, const Array<V, I, S>& source);

	// Construct the map from a list of names and a REPEATED val
	AssocArray(const list<AI>& names, const V& val);

	AssocArray<V, AI, I, S>& operator = (const AssocArray<V, AI, I, S>& ass2);

	// New overloaded indexing operator
	virtual V& operator [] (const AI& index);	// Subscripting operator
	virtual const V& operator [] (const AI& index) const;// Subscripting operator


	typedef std::map<AI,V>::iterator iterator;
	typedef std::map<AI,V>::const_iterator const_iterator;

	// Iterator functions
    iterator Begin();				// Return iterator at begin of assoc array
	const_iterator Begin() const;	// Return const iterator at begin of assoc array
	iterator End();					// Return iterator after end of assoc array
    const_iterator End() const;		// Return const iterator after end of assoc array

};


#endif	// AssocArray_hpp