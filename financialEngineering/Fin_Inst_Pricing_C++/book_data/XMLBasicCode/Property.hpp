// property.hpp
//
// Base class for Properties. This is a concrete class.
// 
// (C) Datasim Education BV 2001
//     

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <string>

template <class Name = string, class Type = double> class Property 
{
private:

	Name nam;
	Type con;

public:
	// Constructors and destructor
	Property();
	Property(const Name& name);
	Property(const Name& name, const Type& t);
	Property(const Property<Name, Type>& source); 
		
	virtual ~Property();
 	
	
	// Accessing function operators
	virtual Type operator()() const;
	virtual void operator()(const Type& t);

	virtual Name name() const;
	virtual void name(const Name& new_name);

	Property<Name, Type>& operator = (const Property<Name, Type>& source);

	bool operator == (const Property<Name, Type>& prop2);

};

#endif // PROPERTY_HPP


