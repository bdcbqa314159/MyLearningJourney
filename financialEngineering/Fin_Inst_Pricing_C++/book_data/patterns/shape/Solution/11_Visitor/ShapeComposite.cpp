// CDO.cpp
//
// Simple Product composite class using the STL list class.
// The composite stores Product pointers. It does it's own memory management.
//
// 15 september 1998	RD	Started
// 2004-1-28 DD CDO

// (C) Datasim Education BV

#include "CDO.hpp"
#include "CDOVisitor.hpp"

void CDO::Copy(const CDO& source)
{ // Copy the source composite to this Product composite

	// Create STL list iterator
	std::list<Product*>::const_iterator it;

	for (it=source.sl.begin(); it!=source.sl.end(); it++)
	{ // Copy the whole list

		// Add a copy of the Product to our list
		sl.push_back((*it)->Clone());
	}
}

CDO::CDO(): Product()
{ // Default constructor

	sl=std::list<Product*>();
}

CDO::CDO(const CDO& source): Product(source)
{ // Copy constructor

	sl=std::list<Product*>();
	Copy(source);
}

CDO::~CDO()
{ // Destructor

	RemoveAll();
}

// Iterator functions
CDO::iterator CDO::Begin()
{ // Return iterator at begin of composite

	return sl.begin();
}

CDO::const_iterator CDO::Begin() const
{ // Return const iterator at begin of composite

	return sl.begin();
}

CDO::iterator CDO::End()
{ // Return iterator after end of composite

	return sl.end();
}

CDO::const_iterator CDO::End() const
{ // Return const iterator after end of composite

	return sl.end();
}

// Selectors
int CDO::Count() const
{ // Return the number of Products in the composite

	return sl.size();
}

// Add functions
void CDO::AddFront(Product* s)
{ // Add Product at the beginning of Productlist. No copy is made.

	sl.push_front(s);
}

void CDO::AddBack(Product* s)
{ // Add Product at the end of Productlist. No copy is made.

	sl.push_back(s);
}

// Remove functions
void CDO::RemoveLast()
{ // Remove last Product

	delete sl.back();		// Delete the Product
	sl.pop_back();			// Remove Product pointer from list
}

void CDO::RemoveFirst()
{ // Remove first Product

	delete sl.front();		// Delete the Product
	sl.pop_front();			// Remove Product pointer from list
}

void CDO::RemoveAll()
{ // Remove all Products from the list

	// Create STL list iterator
	std::list<Product*>::iterator it;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ // Delete every Product in the list

		delete (*it);	// Delete Product
	}

	// Remove the Product pointers from the list
	sl.clear();
}

// Special copy function to create a copy of a Product when you only have a Product pointer
Product* CDO::Clone() const
{// Create a copy of the Product
	return new CDO(*this);
}

void CDO::Accept(ProductVisitor& v)
{// Accept a visitor
	v.Visit(*this);
}

// Operators
CDO& CDO::operator = (const CDO& source)
{ // Assignment

	// Exit if same object
	if (this==&source) return *this;

	// First clear our list
	RemoveAll();

	// Base class assignment
	Product::operator = (source);

	// Copy other list
	Copy(source);

	return *this;
}
