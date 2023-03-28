// 26 September 2002 - MB - Initial code.

#ifndef XmlWriter_h
#define XmlWriter_h

#include "MSXML4.h"

#include "StandardVisitor.h"

#include <vector>
#include <cstdlib>

// Standard XML writer. Reads property set from XML document.?????
class XmlWriter
: public StandardVisitor
{
private:
	// No copy-constructor and assignment operator for now.
	XmlWriter( const XmlWriter & );
	XmlWriter & operator = ( const XmlWriter & );

public:
	// Constructor and destructor.
	XmlWriter();
	virtual ~XmlWriter();

	// Visit functions.
	void Visit( string & key, double & d );
	void Visit( string & key, int & i );
	void Visit( string & key, long & l );
	void Visit( string & key, short & s );
	void Visit( string & key, bool & b );
	void Visit( string & key, string & value );
	void Visit( string & key, TPropertySet & set );
	void Visit( string & key, TPropertySetVector & l );
	void Visit( string & key, TDoubleVector & l );
	void Visit( string & key, TIntVector & l );
	void Visit( string & key, TLongVector & l );
	void Visit( string & key, TShortVector & l );
	void Visit( string & key, TBoolVector & l );
	void Visit( string & key, TStringVector & l );
	
	// Saves XML nodes to file.
	void Save( const string & name );

	// Write XML nodes to string.
	string ToString();

private:
	// Helper method for writing vectors.
	template<class T>
	void WriteVector( const string & key, const string & type, std::vector<T> & v )
	{
		try
		{
			// Create new parent element.
			MSXML2::IXMLDOMNodePtr pOriginalParent = NewCurrentParent(key, type);
			
			// Remove last character from 'part' key.
			//string partKey = key;
			//if( partKey.length() >= 2 )
			//{
			//	partKey.erase(partKey.length() - 1);
			//}
			
			// Visit all values in the list.
			int size = v.size();
			for( int i = 0; i < size; i++ )
			{
				// Create numbered part key.
				string partKey = key;
				char buffer[20];
				partKey += _itoa(i, buffer, 10); // The stupid std::ostringstream leaks, so I do it the old-fashioned way * :( 
				
				Visit(partKey, v[i]);
			}

			// Reset current parent.
			m_pCurrentParent = pOriginalParent;
		}
		catch( _com_error & error )
		{
			bstr_t description = error.Description();
			throw string(description);
		}
	}

	// Creates new element and sets it as the current parent.
	// Returns the original parent.
	MSXML2::IXMLDOMNodePtr NewCurrentParent( string key, string type );

	// Add new element to current parent.
	void AddElement( string key, variant_t & value, string & type );

	// Member data.
	MSXML2::IXMLDOMDocument2Ptr m_pXMLDoc;	// XML document.
	MSXML2::IXMLDOMNodePtr m_pCurrentParent;	// Current parent node for adding new nodes.
};

#endif // XmlWriter_h