// Decorator.cpp
//
// Base clatemplate <class Wrapper, class Contents> for  decorators
//
// 5 november 1998	RD	Started
// 2002-12-11 DD template version
// 2003-8-1 DD use of properties
//
// (C) Datasim Education BV 1998

#include "Decorator.hpp"

template <class Wrapper, class Contents>
Decorator<Wrapper,Contents>::Decorator()
{ // Default constructor

	contents = Property<string, Contents*> ();
	wrapper = Property<string, Wrapper> ();
}

template <class Wrapper, class Contents>
Decorator<Wrapper,Contents>::Decorator(const Wrapper& wrapper, const Contents& con)
{ // Normal constructor

	contents = Property<string, Contents*> ();
	wrapper = Property<string, Wrapper> ();

}

template <class Wrapper, class Contents>
Decorator<Wrapper,Contents>::Decorator(const Decorator<Wrapper,Contents>& source)
{	// Copy constructor

	contents = source.contents;
	wrapper = source.wrapper;

}

template <class Wrapper, class Contents>
Decorator<Wrapper,Contents>::~Decorator()
{ // Destructor


}



// Operators
template <class Wrapper, class Contents>
Decorator<Wrapper,Contents>& Decorator<Wrapper,Contents>::operator = (const Decorator<Wrapper,Contents>& source)
{ // Assignment operator

	if (this = &source)
		return *this;

	contents = source.contents;
	wrapper = source.wrapper;

	return *this;
}