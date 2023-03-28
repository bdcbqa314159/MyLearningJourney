// Simple demo of creating an XML document with MS' XML parser using
// the DOM interface.

// Required parser: MSXML 2.0
//
// (C) Datasim Education BV 2003

// Include/import for XML component.
#import "msxml2.dll"
#include <msxml2.h>

// Standard stuff.
#include <string>
#include <iostream>

using namespace std;

void Demo()
{
	// Initialize COM library (don't forget :)).
	CoInitialize(NULL);

	try
	{
		///////////////////////////////////////////////////////
		// 1. Create instance of XML COM class. 
		
		// COM smart pointers.
		MSXML2::IXMLDOMDocument2Ptr doc;	// XML document.

		// Create document object.
		doc.CreateInstance("Msxml2.DOMDocument.4.0");

		///////////////////////////////////////////////////////
		// 2. Create processing instruction.
		
		// Create the Processing Instruction
		MSXML2::IXMLDOMProcessingInstructionPtr header = NULL;
		header = doc->createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");

		// Add processing instruction.
		_variant_t vNullVal;
		vNullVal.vt = VT_NULL;
		doc->insertBefore(header, vNullVal);

		///////////////////////////////////////////////////////
		// 3. Create root element.
		
		// Create root.
		_bstr_t root = "Point";
		MSXML2::IXMLDOMElementPtr pRoot = doc->createElement( root );

		// Add root to document element.
		doc->appendChild( pRoot );

		///////////////////////////////////////////////////////
		// 4. Create child element.
		
		// Create new child (The X coordinate of the point)
		_bstr_t Xcoord = "X";
		MSXML2::IXMLDOMElementPtr pXcoord = doc->createElement( Xcoord );

		// Set value.
		_variant_t value = 2.71;			// Any compatible type, see _variant_t documentation.
		value.ChangeType(VT_BSTR);
		pXcoord->nodeTypedValue = value;

		// Create first attribute.
		pXcoord->setAttribute( "Name", "X coordinate" );

		// Add child to root element.
		pRoot->appendChild( pXcoord );

	
	
		// Create another new child (The Y coordinate of the point)
		_bstr_t Ycoord = "Y";
		MSXML2::IXMLDOMElementPtr pYcoord = doc->createElement( Ycoord );

		// Set value.
		_variant_t value2 = 2.71;			// Any compatible type, see _variant_t documentation.
		value2.ChangeType(VT_BSTR);
		pYcoord->nodeTypedValue = value2;

		// Create first attribute.
		pYcoord->setAttribute( "Name", "Y coordinate" );

		// Add child to root element.
		pRoot->appendChild( pYcoord );

	
		///////////////////////////////////////////////////////
		// 5. Create output.
				
		// Save XML document.
		doc->save( "Chapter27.xml" );

		// Show XML in console.
		_bstr_t bstrXml = doc->Getxml();
		string xml = bstrXml;
		cout << xml << endl;
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

	// Uninitialize COM library.
	CoUninitialize();
}

int main()
{
	Demo();

	return 0;
}