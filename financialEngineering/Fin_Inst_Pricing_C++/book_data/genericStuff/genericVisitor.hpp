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
template <class T>
	class Visitor
{
public:
		virtual void visit (T& type) = 0;
};

// The base class for Visitable

class BaseVisitable
{
protected:
		template <class T>	// Template function
		static void acceptImp(T& visited, BaseVisitor& guest)
		{
				// Apply Acyclic Visitor
				if (Visitor<T>* p = dynamic_cast<Visitor<T>* > (&guest))
				{
						p -> visit(visited);
				}
		}

public:
		virtual ~BaseVisitable() {}	// Inline
		virtual void accept(BaseVisitor& bv) = 0;
};

// A macro, oh no
#define DEFINE_VISITABLE() \
	virtual void accept(BaseVisitor& guest) \
{acceptImp(*this, guest); }


// Now for some real stuff
class Instrument : public BaseVisitable
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
		public Visitor<Instrument>,
		public Visitor<Option>

{
public:

	void visit(Instrument& i) { cout << "Instrument\n";}
	void visit(Option& o) { cout << "Option\n";}

};


#endif



