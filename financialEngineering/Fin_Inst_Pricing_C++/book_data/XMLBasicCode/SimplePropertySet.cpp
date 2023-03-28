// SimplePropertySet.cpp
//
// Composite function class
//
//	7 November 2002 DD Kick-of
//	8 December New class
//	10 December 2002 remove() and other list-based functions
//	2002-12-26 DD Set has a name
//
// (C) Datasim Education BV

#ifndef SimplePropertySet_CPP
#define SimplePropertySet_CPP

#include "SimplePropertySet.hpp"

template <class N, class V>
SimplePropertySet<N,V>::SimplePropertySet()
{ // Default constructor

	nam = N();
	sl=list<Property<N,V> >();
}

template <class N, class V>
SimplePropertySet<N,V>::SimplePropertySet(const N& name)
{ // Named property set

	nam = name;
	sl=list<Property<N,V> >();
}

template <class N, class V>
SimplePropertySet<N,V>::SimplePropertySet(const SimplePropertySet<N,V>& source)
{ // Copy constructor
	
	nam = source.nam;

	sl = source.sl;
}


template <class N, class V>
SimplePropertySet<N,V>::~SimplePropertySet()
{ // Destructor


}

// Iterator functions
template <class N, class V>
SimplePropertySet<N,V>::iterator SimplePropertySet<N,V>::Begin()
{ // Return iterator at begin of composite

	return sl.begin();
}

template <class N, class V>
SimplePropertySet<N,V>::const_iterator SimplePropertySet<N,V>::Begin() const
{ // Return const iterator at begin of composite

	return sl.begin();
}

template <class N, class V>
SimplePropertySet<N,V>::iterator SimplePropertySet<N,V>::End()
{ // Return iterator after end of composite

	return sl.end();
}

template <class N, class V>
SimplePropertySet<N,V>::const_iterator SimplePropertySet<N,V>::End() const
{ // Return const iterator after end of composite

	return sl.end();
}

// Selectors
template <class N, class V>
int SimplePropertySet<N,V>::Count() const
{ // Return the number of functions in the composite

	return sl.size();
}

template <class N, class V>
	N SimplePropertySet<N,V>::operator ()() const
{ // The name of the property set

		return nam;
}

template <class N, class V>
	bool SimplePropertySet<N,V>::hasPropery(const N& search_name) const
{ // Is the property in the list?

	// We iterate over the list until we find the value
	const_iterator it;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ 

		if ((*it).name() == search_name)
		{
			return true;
		}
	}

	return false;
}


// Modifiers
template <class N, class V>
	void SimplePropertySet<N,V>::operator () (const N& name)
{

		nam = name;
}


template <class N, class V>
	Property<N,V> SimplePropertySet<N,V>::value(const N& name) const
{


	// We iterate over the list until we find the value
	const_iterator it;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ 

		if ((*it).name() == name)
		{
			return (*it);
		}
	}

	
	cout << "???? Property not found in list ?????\n";
	return Property<N,V> ("BLA AT END", 99999);

}

// Add functions
template <class N, class V>
void SimplePropertySet<N,V>::add(const Property<N,V>& scf)
{ // Add a property to the list


	sl.push_back(scf);
}

template <class N, class V>
void SimplePropertySet<N,V>::add(const SimplePropertySet<N,V>& scf)
{ // Add a property set to the list


	//	sl.merge(scf.sl); This function does not work because scf is emptied 
	// by merge() and thus cannot be const.

	// We iterate over the SECOND list until we find the value
	const_iterator it;

	for (it=scf.sl.begin(); it!=scf.sl.end(); it++)
	{ 

		add((*it));
	}

}

template <class N, class V>
	void SimplePropertySet<N,V>::remove(const N& value)
{ // Remove all elements with 'value' O(N)

	// We iterate over the list until we find the value
	iterator it;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ 

		if ((*it)() == value)
		{
			erase(it);
		}
	}

}



// Operators
template <class N, class V>
	SimplePropertySet<N,V>& SimplePropertySet<N,V>::operator = (const SimplePropertySet<N,V>& source)
{ // Assignment

	// Exit if same object
	if (this==&source) return *this;


	nam = source.nam;

	sl = source.sl;

	return *this;
}

template <class N, class V>
	void SimplePropertySet<N,V>::accept (EntityVisitor<N,V>& v)
{

	// We iterate over the list and visit each element
	iterator it;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ 

		v.visit(*it);
	}
}


#endif