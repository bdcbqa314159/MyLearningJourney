// CDO.hpp
//
// Simple Product composite class using the STL list class.
// The composite stores Product pointers. It does it's own memory management.
//
// (C) Datasim Education BV

#ifndef CDO_hpp
#define CDO_hpp

#include "Product.hpp"



#include <list>
using namespace std;

class CDO: public Product
{
private:
	// The Productlist using the STL list
	std::list<Product*> sl;
	
	void Copy(const CDO& source);		// Copy the source composite to this Product composite



public:
	// User can use the STL iterator
	typedef std::list<Product*>::iterator iterator;
	typedef std::list<Product*>::const_iterator const_iterator;

	// Constructors and destructor
	CDO();								// Default constructor
	CDO(const CDO& source);	// Copy constructor
	virtual ~CDO();						// Destructor

	// Iterator functions
    iterator Begin();								// Return iterator at begin of composite
	const_iterator Begin() const;					// Return const iterator at begin of composite
	iterator End();									// Return iterator after end of composite
    const_iterator End() const;						// Return const iterator after end of composite

	// Selectors
	int Count() const;								// The number of Products in the list

	// Add functions
	void AddFront(Product* s);						// Add Product at the beginning of Productlist. No copy is made but composite takes care of deletion.
	void AddBack(Product* s);							// Add Product at the end of Productlist. No copy is made but composite takes care of deletion.

	// Remove functions
	void RemoveFirst();								// Remove first Product
	void RemoveLast();								// Remove last Product
	void RemoveAll();								// Remove all Products from the list

	// Special copy function to create a copy of a Product when you only have a Product pointer
	virtual Product* Clone() const;		// Create a copy of the Product

//	void Accept(CDOVisitor& v);	// Accept a visitor

	// Operators
	CDO& operator = (const CDO& source);
};

#endif	// CDO_hpp
