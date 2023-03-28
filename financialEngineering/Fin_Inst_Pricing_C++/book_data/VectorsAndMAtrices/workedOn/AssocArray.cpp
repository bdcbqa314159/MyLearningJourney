// AssocArray.cpp
//
// Associative array class. In this case we access elements by 
// using non-integral indices.
// This is a proof-of-concept (POC) class.
//
// Last modification dates:
//
//	16 August 2003 DD kick off
//	12 January 2004 DD some new member functions
//
// (C) Datasim Component Technology 1999-2004

#ifndef AssocArray_cpp
#define AssocArray_cpp

#include "AssocArray.hpp"
#include <iostream>
using namespace std;

template <class V, class AI, class I, class S> 
	AssocArray<V, AI, I, S>::AssocArray()
{

	internal_array = map<AI,V>();
}

template <class V, class AI, class I, class S> 
	AssocArray<V, AI, I, S>::AssocArray(const AssocArray<V, AI, I, S>& arr2)
{

	internal_array(arr2.internal_array);
}


template <class V, class AI, class I, class S> 
	AssocArray<V, AI, I, S>::AssocArray(const list<AI>& names, const Array<V, I, S>& source)
{

	I curr = source.MinIndex();

	list<AI>::const_iterator it;
	for (it = names.begin(); it != names.end(); it++)
	{
		internal_array.insert(pair<AI,I>(*it, source[curr]));

		curr++;
	}


}



template <class V, class AI, class I, class S> 
	AssocArray<V, AI, I, S>::AssocArray(const Array<AI>& names, const Array<V, I, S>& source)
{

	// The two arrays must have the same SIZE!!!
	I curr = source.MinIndex();

	for (I j = names.MinIndex(); j <= names.MaxIndex(); j++)
	{
		internal_array.insert(pair<AI,I>(names[j], source[curr]));

		curr++;
	}


}


// Construct the map from a list of names and a REPEATED val
template <class V, class AI, class I, class S> 
	AssocArray<V, AI, I, S>::AssocArray(const list<AI>& names, const V& val)
{

	list<AI>::const_iterator it;
	for (it = names.begin(); it != names.end(); it++)
	{
		internal_array.insert(pair<AI,I>(*it, val));

	}

}

template <class V, class AI, class I, class S> 
	AssocArray<V, AI, I, S>& AssocArray<V, AI, I, S>::operator = (const AssocArray<V, AI, I, S>& ass2)
{
	(if ass2 == this)
		return *this;


	internal_array = ass2.internal_array;
	
	return *this;

}


// New overloaded indexing operator
template <class V, class AI, class I, class S> 
	V& AssocArray<V, AI, I, S>::operator [] (const AI& index)
{

	iterator it = internal_array.find(index);

	V mapIndex = (*it).second;
	return mapIndex;


}

template <class V, class AI, class I, class S> 
   const V& AssocArray<V, AI, I, S>::operator [] (const AI& index) const
{
	const_iterator it = internal_array.find(index);

	V mapIndex = (*it).second;
	return mapIndex;

}

// Iterator functions
template <class V, class AI, class I, class S> 
AssocArray<V, AI, I, S>::iterator AssocArray<V, AI, I, S>::Begin()
{ // Return iterator at begin of composite

	return internal_array.begin();
}

template <class V, class AI, class I, class S> 
AssocArray<V, AI, I, S>::const_iterator AssocArray<V, AI, I, S>::Begin() const
{ // Return const iterator at begin of composite

	return internal_array.begin();
}

template <class V, class AI, class I, class S> 
AssocArray<V, AI, I, S>::iterator AssocArray<V, AI, I, S>::End()
{ // Return iterator after end of composite

	return internal_array.end();
}

template <class V, class AI, class I, class S> 
AssocArray<V, AI, I, S>::const_iterator AssocArray<V, AI, I, S>::End() const
{ // Return const iterator after end of composite

	return internal_array.end();
}



#endif	// AssocArray_cpp