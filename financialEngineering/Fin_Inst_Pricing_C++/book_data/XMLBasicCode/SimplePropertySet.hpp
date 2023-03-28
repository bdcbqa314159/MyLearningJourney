// SimplePropertySet.hpp
//
// Class that represents a list of named properties. This is simply a list of
// Property objects. Each property is a name/value pair.
// This kind of structure occurs in many applications, for example relational
// database theory.
//
// (C) Datasim Education BV 2002

#ifndef SimplePropertySet_hpp
#define SimplePropertySet_hpp

#include "property.cpp"
#include <list>
#include <set>

using namespace std;

template <class N, class V> class EntityVisitor;

template <class N, class V> class SimplePropertySet
{
private:

	N nam;		// The name of the set

	// The SimplePropertySet list using the STL list
	list<Property<N,V> > sl;


public:
	// User can use the STL iterator
	typedef list<Property<N,V> >::iterator iterator;
	typedef list<Property<N,V> >::const_iterator const_iterator;

	// Constructors and destructor
	SimplePropertySet();		// Default constructor
	SimplePropertySet(const N& name);		// Named property set
	SimplePropertySet(const SimplePropertySet<N,V>& source);	// Copy constructor

	virtual ~SimplePropertySet();	// Destructor

	// Iterator functions
    iterator Begin();			// Return iterator at begin of composite
	const_iterator Begin() const;// Return const iterator at begin of composite
	iterator End();				// Return iterator after end of composite
    const_iterator End() const;	// Return const iterator after end of composite

	// Selectors
	int Count() const;				// The number of properties in the list
	N operator ()() const;			// The name of the property set
	bool hasPropery(const N& search_name) const;	// Is the property in the list?

	// Modifiers
	void operator () (const N& name);			// Change the name of the property set
	Property<N,V> value(const N& name) const;	// Get the Property based on a name

	// Add and remove functions (sort of mixin or embedded inheritance)
	void add(const Property<N,V>& p); 
	void add(const SimplePropertySet<N,V>& p); 
	void remove(const N& value);		// Remove all elements with 'value' O(N)

	
	// Operators
	SimplePropertySet<N,V>& operator = (const SimplePropertySet<N,V>& source);


	// Visitor
	void accept (EntityVisitor<N,V>& vis);

};

#endif	// SimplePropertySet_hpp
