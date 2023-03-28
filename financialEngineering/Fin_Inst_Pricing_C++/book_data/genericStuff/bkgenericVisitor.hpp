// genericVisitor.hpp
//
// Generic Visitor and Visitable Classes. Based on
// Modern C++ Design chapter 10.
//
// (C) Datasim Education BV 2004

#ifndef genericVisitor_hpp
#define genericVistor_hpp

#include <iostream>
using namespace std;

// Strawman class for Acyclic Visitor pattern

class BaseVisitor
{
public:
	virtual ~BaseVisitor() {}	// Inline
};


// Abstract template class for visiting an object of type T
template <class T, typename R = void>	// R == return type
	class Visitor
{
public:
		typeder R ReturnType;
		virtual ReturnType visit (T& type) = 0;
};

// The base class for Visitable

template <typename R = void>
		class BaseVisitable
{
protected:
		static ReturnType acceptImp(T& visited, BaseVisitor& guest)
		{
				// Apply Acyclic Visitor
				if (Visitor<T>* p = dynamic_cast<Visitor<T>* > (&guest)
				{
						return p -> visit(visited);
				}

				return ReturnType();
		}

public:
		typedef R ReturnType;
		virtual ~BaseVisitable() {}	// Inline
		virtual ReturnType accept(BaseVisitor& bv) = 0;
};

// A macro, oh no
#define DEFINE_VISITABLE() \
	virtual ReturnType accept(BaseVisitor& guest) \
{return acceptImp(*this, guest); }


// Now for some real stuff
class Instrument : public BaseVisitable<>
{
public:
	DEFINE_VISITABLE();

};

class Option: public Instrument
{
public:
	DEFINE_VISITABLE();

};

class MyInstrumentVisitor : 
		public BaseVisitor,
		public Visitor(Instrument),
		public Visitor(Option)

public:

	void visit(Instrument& i) { cout << "Instrument\n";}
	void visit(Option& o) { cout << "Option\n";}

};


#endif



