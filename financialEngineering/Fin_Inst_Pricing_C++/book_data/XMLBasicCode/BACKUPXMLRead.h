// 26 September 2002 - MB - Initial code.

#ifndef XmlReader_h
#define XmlReader_h

#include "MSXML4.h"

#include "StandardVisitor.h"

#include <string>
using namespace std; 

// Standard XML reader. Reads property set from XML document.
class XmlReader
{
private:
	// No copy-constructor and assignment operator for now.
	XmlReader( const XmlReader & );
	XmlReader & operator = ( const XmlReader & );

public:

	typedef PropertySet<string, StandardVisitor> TPropertySet;

	// Constructor and destructor.
	XmlReader();
	virtual ~XmlReader();

	// Visit functions.
	void Read( const string & key, double & d );
	void Read( const string & key, int & i );
	void Read( const string & key, long & l );
	void Read( const string & key, short & s );
	void Read( const string & key, bool & b );
	void Read( const string & key, string & value );
	void Read( string & key, TPropertySet & set );
	
	template <class T>
	void Read( const string & key, vector<T> & v )
	{
		try
		{
			// Get first child node.
			MSXML2::IXMLDOMNodePtr node = m_pCurrentNode->GetfirstChild();
			while( node )
			{
				MSXML2::DOMNodeType nodeType = GetNodeType(node);

				// If node is an element.
				if( nodeType == MSXML2::NODE_ELEMENT )
				{
					// Set current node.
					m_pCurrentNode = node;

					// Get key and type.
					string key;
					string type;
					GetStringAndType(node, key, type);

					// Check type.
					T value;
					Read(key, value);
					v.push_back(value);
				}

				// Go to next sibling.
				node = node->GetnextSibling();
			}
		}
		catch( _com_error & error )
		{
			ThrowAsString(error);
		}
	}
		
	// Loads XML file.
	void Load( const string & fileName );

	// Load from string.
	void LoadXml( BSTR xmlString );

private:
	// Member data.
	MSXML2::IXMLDOMDocument2Ptr m_pXMLDoc;	// XML document object.
	MSXML2::IXMLDOMNodePtr m_pCurrentNode;	// Current node for reading nodes.

	// Releases all interfaces.
	void ReleaseInterfaces();

	// Static helpers.
	static MSXML2::DOMNodeType GetNodeType( MSXML2::IXMLDOMNodePtr & node );
	static void GetStringAndType( MSXML2::IXMLDOMNodePtr & node, string & key, string & type );
	static void ThrowConversionError(const string & key, const string & type);
	static void ThrowAsString( _com_error & error );
};

#endif // XmlReader_h