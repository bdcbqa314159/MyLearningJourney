// property.cpp
//
// Base class for Properties
//
// Last modification dates:
//
//	2001-6-18 DD Modifications to previously defined classes
//	2001-7-2 DD Compiler directives
//	2002-12-7 DD bug fix
//
// (C) Datasim Education BV 2001


#ifndef PROPERTY_CPP
#define PROPERTY_CPP

#include "property.hpp"

// Constructors and destructor
template <class Name, class Type> 
Property< Name,  Type>::Property()
{// Default constructor

	nam = Name();
	con = Type();
}

template <class Name, class Type> 
Property< Name,  Type>::Property(const Name& name)
{// Constructor  

	nam = name;
	con = Type();
}


template <class Name, class Type> 
Property< Name,  Type>::Property(const Name& name, const Type& t)
{// Constructor  

	nam = name;
	con = t;
}

template <class Name, class Type> 
Property< Name,  Type>::Property(const Property<Name, Type>& source) 
{// Copy-constructor

	nam = source.nam;
	con = source.con;
}

template <class Name, class Type> 
Property< Name,  Type>::~Property()
{// Destructor

}

template <class Name, class Type>  
Property< Name,  Type>& Property<Name, Type>::operator =(const Property<Name, Type>& source)
{// Assignment operator 

	if (this == &source)
		return *this;

	nam = source.nam;
	con = source.con;

	return *this;
}

		
// Accessing function operators
template <class Name, class Type> Type Property<Name, Type>::operator()() const
{

		return con;

}

template <class Name, class Type> void Property<Name, Type>::operator()(const Type& t)
{

		con = t;

}

template <class Name, class Type> Name Property<Name, Type>::name() const
{

	return nam;
}


template <class Name, class Type> void Property<Name, Type>::name(const Name& new_name)
{

	nam = new_name;
}

template <class Name, class Type> bool Property<Name, Type>:: operator == (const Property<Name, Type>& prop2)
{

		if (nam != prop2.name())
			return false;

		if (con != prop2.con)
			return false;

		return true;

}

#endif // PROPERTY_CPP




