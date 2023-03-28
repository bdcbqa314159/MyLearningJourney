// XMLWriter.hpp
//
// Visitor class for writing a SimplePropertySet to an XML file.
//
// The type of output is something like the following:
//
/*	
	<?XML version="1.0" encoding="UTF-8"?>
	<Entity>
		<StrikePrice>150</StrikePrice>
		<InterestRate>0.06</InterestRate>
		etc....
	</Entity>

*/
// (C) Datasim Education BV 2003
//

#ifndef XMLWriter_hpp
#define XMLWriter_hpp

// MUST Include/import for XML component. NOTE! this may be Windows-dependent
#import "msxml2.dll"
#include <msxml2.h>

#include "EntityVisitor.hpp"
#include "SimplePropertySet.cpp"

#include <vector>
#include <cstdlib>

template <class N, class V> class XMLWriter : public EntityVisitor<N,V>
{
private:

	// Member data.
	MSXML2::IXMLDOMDocument2Ptr m_pXMLDoc;	// XML document.
	MSXML2::IXMLDOMElementPtr pRoot;


	// No copy-constructor and assignment operator for now.
	XMLWriter( const XMLWriter<N,V> & ) {}
	XMLWriter & operator = ( const XMLWriter<N,V> & ) {}

	// Private Visit functions.
	virtual void visit(Property<N, V>& property);
	virtual void visit(SimplePropertySet<N, V>& pset);


public:
	// Constructor and destructor.
	XMLWriter();
	virtual ~XMLWriter();

	// Public Visit functions.
	virtual void visit(Entity<N,V>& entity);

	// Saves XML nodes to file.
	void Save( const string & name );

	// Write XML nodes to string.
	string ToString();


};

#endif // XMLWriter_hpp