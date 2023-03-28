// XMLReader.hpp
//
// Visitor class for reading XML documents for SimplePropertySets
// that have already been written by XMLWriter.
//
// (C) Datasim Education BV 2003
//

#ifndef XMLReader_hpp
#define XMLReader_hpp


// MUST Include/import for XML component. NOTE! this may be Windows-dependent
#import "msxml2.dll"
#include <msxml2.h>


#include "SimplePropertySet.cpp"
#include "entityvisitor.hpp"

#include <string>
using namespace std; 

// Standard XML reader. Reads property set from XML document.
template <class N, class V> class XMLReader : public EntityVisitor <N, V>
{
private:

	// No copy-constructor and assignment operator for now.
	XMLReader( const XMLReader & ) {}
	XMLReader & operator = ( const XMLReader & ) {}

	// Private Visit functions.
	virtual void visit(Property<N, V>& property);
	virtual void visit(SimplePropertySet<N, V>& pset);

public:

	// Constructor and destructor.
	XMLReader();
	virtual ~XMLReader();

	// Public Visit functions.
	virtual void visit(Entity<N,V>& entity);


	// Loads XML file.
	void Load( const string & fileName );



private:
	// Member data.
	MSXML2::IXMLDOMDocument2Ptr m_pXMLDoc;	// XML document object.
	MSXML2::IXMLDOMNodePtr m_pCurrentNode;	// Current node for reading nodes.

	// Releases all interfaces.
	void ReleaseInterfaces();

	// Static helpers.
	static MSXML2::DOMNodeType GetNodeType( MSXML2::IXMLDOMNodePtr & node );
	static void GetString( MSXML2::IXMLDOMNodePtr & node, string & key, string & type );
	static void ThrowConversionError(const string & key, const string & type);
	static void ThrowAsString( _com_error & error );

	void Read(const string& key,double& value );	// Read Value at current node
};

#endif // XMLReader_hpp