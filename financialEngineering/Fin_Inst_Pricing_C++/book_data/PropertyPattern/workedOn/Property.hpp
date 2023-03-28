// property.hpp
//
// Base class for Properties. This is a concrete class.
// A property is a name-value pair and it can be used in 
// many kinds of applications.
//
// The default Value for the name is 'string' and the default
// value Value is 'double'. You use it in the following way:
//
//		Property<> myDefaultProperty
//
// (C) Datasim Education BV 2001-2004
//     

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <string>

template <class Name = string, class Value = double> class Property 
{
private:

	Name nam;
	Value con;

public:
	// Constructors and destructor
	Property();
	Property(const Value& t);
	Property(const Name& name);
	Property(const Name& name, const Value& t);
	Property(const Property<Name, Value>& source); 
		
	virtual ~Property();
 	
	
	// Accessing function operators
	// Get and set the value of the Property
	virtual Value operator()() const;
	virtual void operator()(const Value& t);

	// Get the name of the property
	virtual Name name() const;

	Property<Name, Value>& operator = (const Property<Name, Value>& source);

	// True if name and value are the same
	bool operator == (const Property<Name, Value>& prop2);

};

#endif // PROPERTY_HPP


