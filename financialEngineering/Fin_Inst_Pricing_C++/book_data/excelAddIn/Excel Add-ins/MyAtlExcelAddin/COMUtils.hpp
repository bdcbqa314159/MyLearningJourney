#ifndef COMUtils_hpp
#define COMUtils_hpp


#include "stdafx.h"
#include "atlsafe.h"
#include "Functions\Vector.hpp"

class COMUtils
{
public:
	// Register a COM add-in
	static HRESULT RegisterCOMAddin(LPCSTR pszOfficeApp, LPCSTR pszProgID, LPCSTR pszFriendlyName, DWORD dwStartupContext);

	// Unregister a COM add-in
	static HRESULT UnRegisterCOMAddin(LPCSTR pszOfficeApp, LPCSTR pszProgID);

	// Set a key in the registry
	static BOOL SetKeyAndValue(HKEY hKeyRoot, LPCSTR pszPath, LPCSTR pszSubkey, LPCSTR pszValue);

	// Recursively delete a key in the registry
	static LONG RecursiveDeleteKey(HKEY hKeyParent, LPCSTR pszKeyChild);

	// Convert variant to vector with doubles
	static Vector<DOUBLE> ExcelRangeToVector(VARIANT* range);

	// Convert Excel range to vector with doubles
	static Vector<DOUBLE> ExcelRangeToVector(Excel::RangePtr pRange);

	// Add menu item to Excel
	static Office::_CommandBarButtonPtr AddMenuItem(Excel::_ApplicationPtr xl, Office::COMAddInPtr addin, CComBSTR menuName, CComBSTR menuItemCaption, CComBSTR menuItemKey);

	// Remove menu item from Excel
	static void COMUtils::RemoveMenuItem(Excel::_ApplicationPtr xl, ext_DisconnectMode removeMode, CComBSTR menuName, CComBSTR menuItemCaption);

};


#endif COMUtils_hpp
