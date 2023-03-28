// Entity.hpp
//
// Template classes for entities and their related classes
// (e.g. the categories to which they belong).
// 
// This is a LITE version of the full Entity pattern,
//
// The main classes are:
//
//		0. Property classes (list of attribute/value pairs)
//		0. Function classes (encapsulation of C functions) NOT HERE
//		1. EntityThing (base class fo all entities)
//		2. EntityCategory (entities grouped into a certain category) NOT HERE
//		3. Entity (building block class for all future products)
//
// An entity is a set of attribute properties than can be modified and queried.
// Furthermore, it it possible to execute 'dynamic' commands on the entities.
//
// (C) Datasim Education BV 2001-2003
//     

#ifndef Entity_HPP
#define Entity_HPP

#include "simplepropertyset.cpp"

template <class Name, class Value> class EntityThingVisitor; // Forward reference

template <class Name, class Value> class EntityThing
{
private:

public:
	EntityThing();
	EntityThing(const Name& t);
	EntityThing(const EntityThing<Name,Value>& source); 
		
	virtual ~EntityThing();
 
	// The defining structure and behaviour of entites. Notice
	// that these are public 'objects' and that we can use the 
	// member functions of the corresponding template classes.
	// Thus, there is no need to reproduce member functions.

	Property<Name, Value> name;					// The ID of the entity
	SimplePropertySet<Name, Value> properties;	// The properties in the Entity


	// Assignment operator 
	EntityThing<Name,Value>& operator = (const EntityThing<Name,Value>& source);


	////////////////////////////////////////////////////////////////////////////////////


	// Add property and property seet
	virtual void AddProperty(const Property<Name, Value>& prop);
	virtual void AddProperty(const SimplePropertySet<Name, Value>& prop_set);


	/////////////////////////////////////////////////////////////////////////////////////

	// Copy on heap (Prototype) 
	virtual EntityThing<Name,Value>* Clone() const = 0;


	// Design patterns extensions
	virtual void accept(EntityVisitor<Name,Value>& visitor) = 0;

};




template <class Name, class Value> class Entity : public EntityThing<Name,Value>
{
private:

	
public:
	// Constructors and destructor
	Entity();
	Entity(const Name& ename);
	Entity(const Entity<Name,Value>& source); 
		
	virtual ~Entity();
 

	// Copy on heap
	virtual EntityThing<Name,Value>* Clone() const;


	// Assignment operator 
	Entity<Name,Value>& operator = (const Entity<Name,Value>& source);

	// Design patterns extensions
	void accept(EntityVisitor<Name,Value>& visitor);
};






#endif // Entity_HPP


