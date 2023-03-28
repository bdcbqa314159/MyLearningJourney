// XMLreader.cpp
//
// Last modification dates
//
//	24 July 2003 DD copy from other source and clean-up: WORKING VERSION
//  25 July 2003 DD Visit function for Entity


#ifndef XMLReader_cpp
#define XMLReader_cpp

#include "XMLReader.hpp"

// This function is here because the interface wrapper gives a
// compilation error (2* defined).
template <class N, class V> MSXML2::DOMNodeType XMLReader<N,V>::GetNodeType( MSXML2::IXMLDOMNodePtr & node )
{
	// Get node type.
	MSXML2::DOMNodeType nodeType;
	HRESULT _hr = node->get_nodeType(&nodeType);
	if( FAILED( _hr ) )
	{
		_com_issue_errorex(_hr, node, __uuidof(MSXML2::IXMLDOMNodePtr));
	}
	return nodeType;
}

// Retrieves the key and type from an element node.
template <class N, class V> void XMLReader<N,V>::GetString( MSXML2::IXMLDOMNodePtr & node, string & key, string & type )
{
	// Get key.
	_bstr_t bstrKey = node->GetnodeName();
	key = (const char *) bstrKey;


}

template <class N, class V> void XMLReader<N,V>::ThrowConversionError(const string & key, const string & type)
{
	string message;
	message += "Cannot convert property \"";
	message += key;
	message += "\" to ";
	message += type;
	throw message;
}

template <class N, class V> void XMLReader<N,V>::ThrowAsString( _com_error & error )
{
	bstr_t description = error.Description();
	if( !description )
	{
		description = error.ErrorMessage();
	}
	throw string(description);
}


// Constructor.
template <class N, class V> XMLReader<N,V>::XMLReader()
{
	// Initialize COM library.
	CoInitialize(NULL);
}

// Destructor.
template <class N, class V> XMLReader<N,V>::~XMLReader()
{
	// Release interface pointers before calling CoUnitialize().
	ReleaseInterfaces();
		
	// Unitialize COM library.
	CoUninitialize();
}



template <class N, class V> void XMLReader<N,V>::visit(Property<N,V>& propSet )
{

}


// Reads property set property from current node.
template <class N, class V> void XMLReader<N,V>::visit(SimplePropertySet<N,V>& propSet )
{


}

template <class N, class V> void XMLReader<N,V>::visit(Entity<N,V>& entity )
{
	// Create an entity with name and properties

	try
	{
		// Get first child node.
		_bstr_t bstrName = m_pCurrentNode->GetnodeName();
		string retKey = static_cast<const char*>(bstrName);
		entity.name = Property<N,V>(retKey);

	
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
				GetString(node, key, type);

		
				double value;
				Read(key, value);
				entity.AddProperty(Property<N,V>(key, value));
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


// Reads double property from current node.
template <class N, class V> void XMLReader<N,V>::Read(const string& key, double& value)
{
	try
	{
		value = m_pCurrentNode->GetnodeTypedValue();
	}
	catch( _com_error & error )
	{
		if( error.Error() == 0x80020005 )
		{
			ThrowConversionError(key, "double");
		}
		ThrowAsString(error);
	}
}




// Releases all interfaces.
template <class N, class V> void XMLReader<N,V>::ReleaseInterfaces()
{
	m_pXMLDoc = NULL;
	m_pCurrentNode = NULL;
}

// Load XML document.
template <class N, class V> void XMLReader<N,V>::Load( const string & fileName )
{
	try
	{
		ReleaseInterfaces();

		// Create COM object.
		m_pXMLDoc.CreateInstance("MsXML2.DOMDocument.4.0");

		// Load file.
		_bstr_t bstrFileName = fileName.c_str();
		VARIANT_BOOL loaded = m_pXMLDoc->load(bstrFileName);
		if( loaded )
		{
			// Set current node.
			m_pCurrentNode = m_pXMLDoc->GetdocumentElement();
		}
		else
		{
			string message = "Could not load XML document ";
			message += fileName;
			throw message;
		}
	}
	catch( _com_error & error )
	{
		ThrowAsString(error);
	}
}


#endif