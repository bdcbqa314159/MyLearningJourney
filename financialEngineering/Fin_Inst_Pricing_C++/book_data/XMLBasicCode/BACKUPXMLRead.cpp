// 26 September 2002 - MB - Initial code.

//#include "..//DPS2//DisableWarning4786.h"

#include "XmlReader.h"

// This function is here because the interface wrapper gives a
// compilation error (2* defined).
MSXML2::DOMNodeType XmlReader::GetNodeType( MSXML2::IXMLDOMNodePtr & node )
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
void XmlReader::GetStringAndType( MSXML2::IXMLDOMNodePtr & node, string & key, string & type )
{
	// Get key.
	_bstr_t bstrKey = node->GetnodeName();
	key = (const char *) bstrKey;

	// Get type.
	MSXML2::IXMLDOMElementPtr element = node;
	MSXML2::IXMLDOMAttributePtr typeAttribute = element->getAttributeNode("type");
	if( typeAttribute )
	{
		_bstr_t bstrType = typeAttribute->GetnodeValue();
		type = (const char *) bstrType;
	}
	else
	{
		string message;
		message += "No type attribute for property \"";
		message += key;
		message += "\".";
		throw message;
	}
}

void XmlReader::ThrowConversionError(const string & key, const string & type)
{
	string message;
	message += "Cannot convert property \"";
	message += key;
	message += "\" to ";
	message += type;
	throw message;
}

void XmlReader::ThrowAsString( _com_error & error )
{
	bstr_t description = error.Description();
	if( !description )
	{
		description = error.ErrorMessage();
	}
	throw string(description);
}


// Constructor.
XmlReader::XmlReader()
{
	// Initialize COM library.
	CoInitialize(NULL);
}

// Destructor.
XmlReader::~XmlReader()
{
	// Release interface pointers before calling CoUnitialize().
	ReleaseInterfaces();
		
	// Unitialize COM library.
	CoUninitialize();
}

// Reads string property from current node.
void XmlReader::Read( const string & key, string & value )
{
	try
	{
		_variant_t varValue = m_pCurrentNode->GetnodeTypedValue();
		_bstr_t bstrValue = varValue;
		value = (const char *) bstrValue;
	}
	catch( _com_error & error )
	{
		ThrowAsString(error);
	}
}

// Reads property set property from current node.
void XmlReader::Read( string & retKey, TPropertySet & propSet )
{
	try
	{
		// Get first child node.
		_bstr_t bstrName = m_pCurrentNode->GetnodeName();
		retKey = static_cast<const char*>(bstrName);

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

				// Switch on different types.
				if( type == "string" )
				{
					string value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "int" )
				{
					int value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "long" )
				{
					long value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "short" )
				{
					short value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "bool" )
				{
					bool value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "double" )
				{
					double value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "propertySet" )
				{
					TPropertySet value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "vector:string" )
				{
					vector<string> value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "vector:double" )
				{
					vector<double> value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "vector:int" )
				{
					vector<int> value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "vector:long" )
				{
					vector<long> value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "vector:short" )
				{
					vector<short> value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "vector:bool" )
				{
					vector<bool> value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
				else if( type == "vector:propertySet" )
				{
					vector<TPropertySet> value;
					Read(key, value);
					propSet.AddProperty(key, value);
				}
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
/*
// Reads list of property sets from current node.
void XmlReader::Visit( string & key, TPropertySetList & setList )
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
				if( type == "propertySet" )
				{
					TPropertySet value;
					Visit(key, value);
					setList.push_back(value);
				}
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

// Reads string list property from current node.
void XmlReader::Visit( string & key, TStringList & stringList )
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
				if( type == "string" )
				{
					string value;
					Visit(key, value);
					stringList.push_back(value);
				}
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
*/
// Reads double property from current node.
void XmlReader::Read( const string & key, double & value )
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

// Reads int property from current node.
void XmlReader::Read( const string & key, int & value )
{
	try
	{
		value = (int)(long) m_pCurrentNode->GetnodeTypedValue();
	}
	catch( _com_error & error )
	{
		if( error.Error() == 0x80020005 )
		{
			ThrowConversionError(key, "int");
		}
		ThrowAsString(error);
	}
}

// Reads long property from current node.
void XmlReader::Read( const string & key, long & value )
{
	try
	{
		value = m_pCurrentNode->GetnodeTypedValue();
	}
	catch( _com_error & error )
	{
		if( error.Error() == 0x80020005 )
		{
			ThrowConversionError(key, "long");
		}
		ThrowAsString(error);
	}
}

// Reads short property from current node.
void XmlReader::Read( const string & key, short & value )
{
	try
	{
		value = m_pCurrentNode->GetnodeTypedValue();
	}
	catch( _com_error & error )
	{
		if( error.Error() == 0x80020005 )
		{
			ThrowConversionError(key, "short");
		}
		ThrowAsString(error);
	}
}

// Reads bool property from current node.
void XmlReader::Read( const string & key, bool & value )
{
	try
	{
		_bstr_t bstrValue = m_pCurrentNode->GetnodeTypedValue();
		if( bstrValue == _bstr_t("true") )
		{
			value = true;
		}
		else if( bstrValue == _bstr_t("false") )
		{
			value = false;
		}
		else
		{
			ThrowConversionError(key, "bool");
		}
	}
	catch( _com_error & error )
	{
		if( error.Error() == 0x80020005 )
		{
			ThrowConversionError(key, "bool");
		}
		ThrowAsString(error);
	}
}

// Releases all interfaces.
void XmlReader::ReleaseInterfaces()
{
	m_pXMLDoc = NULL;
	m_pCurrentNode = NULL;
}

// Load XML document.
void XmlReader::Load( const string & fileName )
{
	try
	{
		ReleaseInterfaces();

		// Create COM object.
		m_pXMLDoc.CreateInstance("Msxml2.DOMDocument.4.0");

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

// Load from string.
void XmlReader::LoadXml( BSTR xmlString )
{
	try
	{
		ReleaseInterfaces();

		// Create COM object.
		m_pXMLDoc.CreateInstance("Msxml2.DOMDocument.4.0");

		// Load file.
		VARIANT_BOOL loaded = m_pXMLDoc->loadXML(xmlString);
		if( loaded )
		{
			// Set current node.
			m_pCurrentNode = m_pXMLDoc->GetdocumentElement();
		}
		else
		{
			string message = "Could not load XML string.";
			throw message;
		}
	}
	catch( _com_error & error )
	{
		ThrowAsString(error);
	}
}