// Decorator.hpp
//
//	A class that wraps another class with some extra information. 
// This can be seen as a template Decorator class.
//
// (C) Datasim Education BV 1998-2003

#ifndef Decorator_hpp
#define Decorator_hpp

#include "property.cpp"
#include <string>
using namespace std;


template <class Wrapper, class Contents> class Decorator
{
private:

	Decorator();
	Decorator(const Decorator<Wrapper, Contents>& source);		// Copy constructor
	// Operators
	Decorator<Wrapper,Contents>& operator = (const Decorator<Wrapper, Contents>& source);

public:
	// Constructors and destructors
	Decorator(const Wrapper& wrapper, const Contents& con);	
	virtual ~Decorator();										// Destructor

	// The parts of the decorator
	Property<string, Contents*> contents;	
	Property <string, Wrapper> wrappe;

};

#endif // Decorator_hpp