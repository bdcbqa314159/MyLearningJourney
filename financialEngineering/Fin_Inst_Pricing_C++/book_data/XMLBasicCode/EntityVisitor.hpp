// entityvisitor.hpp
// 
// Base class for visitor functionality for Properties and Entities
//
// (C) Datasim Education BV 2003
//

#ifndef EntityVisitor_hpp
#define EntityVisitor_hpp


#include <vector>
#include <string>
using namespace std;

#include "entity.cpp"

// Property set visitor base class for standard types.
template <class N, class V> class EntityVisitor
{
public:


	// Visit functions.
	virtual void visit(Property<N, V>& property) = 0;
	virtual void visit(SimplePropertySet<N, V>& pset) = 0;
	virtual void visit(Entity<N,V>& entity) = 0;
	
};

#endif // EntityVisitor_hpp