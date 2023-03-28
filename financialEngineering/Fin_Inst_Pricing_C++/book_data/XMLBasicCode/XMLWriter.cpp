//XMLWriter.cpp
//
// Last modification dates:
//
// July 22 2003 DD Changes to template form
// July 25 2003 DD Visit function for Entity
//
// (C) Copyright Datasim Education BV 2003

#ifndef XMLWriter_cpp
#define XMLWriter_cpp

#include "XMLWriter.hpp"
#include <algorithm>
#include <iostream>


// Helper functions in 'local' namespace. Useful function from STL (algorithm)
namespace
{
	// Removes illegal characters for element name.
	void RemoveIllegalChars( string & s )
	{
		string::iterator newEnd = remove(s.begin(), s.end(), ' ');
		newEnd = remove(s.begin(), newEnd, ')');
		newEnd = remove(s.begin(), newEnd, '(');
		newEnd = remove(s.begin(), newEnd, '&');
		newEnd = remove(s.begin(), newEnd, '\"');
		newEnd = remove(s.begin(), newEnd, '\'');
		newEnd = remove(s.begin(), newEnd, ';');
		s.erase(newEnd, s.end());
	}
}



// Constructor.
template <class N, class V> XMLWriter<N,V>::XMLWriter()
{
	// Initialize COM library.
	CoInitialize(NULL);

	try
	{
		// Create document.
		m_pXMLDoc.CreateInstance("Msxml2.DOMDocument.4.0");

		//	Create the Processing Instruction
		MSXML2::IXMLDOMProcessingInstructionPtr pPI = NULL;
		pPI = m_pXMLDoc->createProcessingInstruction
			("xml", "version='1.0' encoding='UTF-8'");

		_variant_t vNullVal;
		vNullVal.vt = VT_NULL;
		m_pXMLDoc->insertBefore(pPI, vNullVal);
	
	}
	catch( _com_error & error )
	{
		bstr_t description = error.Description();
		throw string(description);
	}

}

// Destructor.
template <class N, class V> XMLWriter<N,V>::~XMLWriter()
{
	try
	{		
		// Release interface pointers before calling CoUnitialize().
		m_pXMLDoc = NULL;
		pRoot = NULL;
		
		// Unitialize COM library.
		CoUninitialize();
	}
	catch( _com_error & error )
	{
		bstr_t description = error.Description();
		throw string(description);
	}
}




template <class N, class V> void XMLWriter<N,V>::visit(Property<N,V>& prop)
{

	try{
		// Create new child (simple property)
		string s = prop.name();
		_bstr_t key = s.c_str();
		MSXML2::IXMLDOMElementPtr entry = m_pXMLDoc->createElement( key );

		// Set value.
		_variant_t value = prop();
		value.ChangeType(VT_BSTR);
		entry ->nodeTypedValue = value;


		// Add child to root element.
		pRoot->appendChild( entry );

	}
	catch( _com_error & error )
	{
		// Get pointer to error description.
		bstr_t description = error.Description();
		
		// If no error description, try error message.
		if( !description )
		{
			description = error.ErrorMessage();
		}

		// Display error.
		cout << (const char*) description << endl;
	}
}

template <class N, class V> void XMLWriter<N,V>::visit(SimplePropertySet<N, V>& pset)
{
	
	pset.accept(*this);
}

template <class N, class V> void XMLWriter<N,V>::visit(Entity<N,V>& entity)
{ // Write an entity to XML document

		// 1. Write name as the root of the XML document
		// 2. Write property set

	
		// Create root element, This is the name of the Entity
		
	try
	{
		// Create root.
		string N = entity.name.name();
		_bstr_t root = N.c_str();
		pRoot = m_pXMLDoc->createElement( root );

		// Add root to document element.
		m_pXMLDoc->appendChild( pRoot );

	}
	catch( _com_error & error )
	{
		bstr_t description = error.Description();
		throw string(description);
	}

	visit(entity.properties);

}


// Saves XML nodes to file.
template <class N, class V> void XMLWriter<N,V>::Save( const string & name )
{
	try
	{
		// Save XML document.
		m_pXMLDoc->save(name.c_str());

		// Show XML in console.
		_bstr_t bstrXML = m_pXMLDoc->Getxml();
		string XML = bstrXML;
		cout << XML << endl;
	}
	catch( _com_error & error )
	{
		bstr_t description = error.Description();
		throw string(description);
	}
}

// Write XML nodes to string.
template <class N, class V> string XMLWriter<N,V>::ToString()
{
	return (const char *) m_pXMLDoc->GetXML();
}

#endif