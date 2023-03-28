#include "stdafx.h"
#include "COMUtils.hpp"
#include "Functions\Vector.cpp"

// Performs registration of Addin for Office 2000 and some other applications. The start context is
// determined by a combination of the following values:
// 
//    Disconnect        - 0   Is not loaded.
//    Connected         - 1   Is loaded.
//    Bootload          - 2   Load on application Startup.
//    DemandLoad        - 8   Load only when requested by user.
//    ConnectFirstTime   - 16  Load only once (on next startup). 
//
//
// Normal value passed is 3.
// Some of the possible applications: Word, Excel, FrontPage, PowerPoint
HRESULT COMUtils::RegisterCOMAddin(LPCSTR pszOfficeApp, LPCSTR pszProgID, LPCSTR pszFriendlyName, DWORD dwStartupContext)
{  
	HKEY hKey;
	CHAR szKeyBuf[1024];

	// Copy keyname into buffer.
	lstrcpy(szKeyBuf, "Software\\Microsoft\\Office\\");
    lstrcat(szKeyBuf, pszOfficeApp);
    lstrcat(szKeyBuf, "\\Addins\\");
	lstrcat(szKeyBuf, pszProgID);

	// Create and open key and subkey.
	long lResult = RegCreateKeyEx(HKEY_CURRENT_USER, szKeyBuf, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (lResult != ERROR_SUCCESS) return E_ACCESSDENIED;
   
    DWORD dwTemp = 0;

	// Write startup context and commandline safe options to registry.
    RegSetValueEx(hKey, "LoadBehavior", 0, REG_DWORD, (BYTE*)&dwStartupContext, 4);
    RegSetValueEx(hKey, "CommandLineSafe", 0, REG_DWORD, (BYTE*)&dwTemp, 4);

	// Write friendly name of the add-in to the registry.
    if (NULL != pszFriendlyName) 
	{
        dwTemp = lstrlen(pszFriendlyName) + 1;
        RegSetValueEx(hKey, "FriendlyName", 0, REG_SZ, (BYTE*)pszFriendlyName, dwTemp);
        RegSetValueEx(hKey, "Description", 0, REG_SZ, (BYTE*)pszFriendlyName, dwTemp);
    }

	// Close the registry.
    RegCloseKey(hKey);
    return S_OK;
}

// Removes the COM Addin for the given (Office) Application.
// Some of the possible applications: Word, Excel, FrontPage, PowerPoint.
HRESULT COMUtils::UnRegisterCOMAddin(LPCSTR pszOfficeApp, LPCSTR pszProgID)
{  
	CHAR szKeyBuf[1024];

	// Copy keyname into buffer.
	lstrcpy(szKeyBuf, "Software\\Microsoft\\Office\\");
    lstrcat(szKeyBuf, pszOfficeApp);
    lstrcat(szKeyBuf, "\\Addins\\");
	lstrcat(szKeyBuf, pszProgID);

	// Recursively delete the add-in from the registry.
	RecursiveDeleteKey(HKEY_CURRENT_USER, szKeyBuf);

    return S_OK;
}


// Set a key value in the registry.
BOOL COMUtils::SetKeyAndValue(HKEY hKeyRoot, LPCSTR pszPath, LPCSTR pszSubkey, LPCSTR pszValue)
{
	HKEY hKey;
	CHAR szKeyBuf[1024];

	// Copy keyname into buffer.
	lstrcpy(szKeyBuf, pszPath);

	// Add subkey name to buffer.
	if (pszSubkey != NULL)
	{
		lstrcat(szKeyBuf, "\\");
		lstrcat(szKeyBuf, pszSubkey);
	}

	// Create and open key and subkey.
	long lResult = RegCreateKeyEx(hKeyRoot, szKeyBuf, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (lResult != ERROR_SUCCESS) return FALSE;

	// Set the key value.
	if (pszValue != NULL) RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE*)pszValue, lstrlen(pszValue)+1);

	// Close the registry key
	RegCloseKey(hKey);
	return TRUE;
}

// Recursively delete a key from the registry.
LONG COMUtils::RecursiveDeleteKey(HKEY hKeyParent, LPCSTR pszKeyChild)
{
	// Open the child.
	HKEY hKeyChild ;
	LONG lRes = RegOpenKeyEx(hKeyParent, pszKeyChild, 0, KEY_ALL_ACCESS, &hKeyChild);
	if (lRes != ERROR_SUCCESS)	return lRes;

	// Enumerate all of the decendents of this child.
	FILETIME time;
	CHAR szBuffer[256];
	DWORD dwSize = 256;
	while (RegEnumKeyEx(hKeyChild, 0, szBuffer, &dwSize, NULL, NULL, NULL, &time) == S_OK)
	{
		// Delete the decendents of this child.
		lRes = RecursiveDeleteKey(hKeyChild, szBuffer);
		if (lRes != ERROR_SUCCESS)
		{
		
			// Cleanup before exiting.
			RegCloseKey(hKeyChild);
			return lRes;
		}
		dwSize = 256;
	}

	// Close the child.
	RegCloseKey(hKeyChild);

	// Delete this child.
	return RegDeleteKey(hKeyParent, pszKeyChild);
}

// Convert a variant to our vector template class
Vector<DOUBLE> COMUtils::ExcelRangeToVector(VARIANT* range)
{
	// Check if a range object was passed
	if (range->vt!=VT_DISPATCH)
	{
		// No range passed so just return the double value in a vector
		Vector<DOUBLE> v(1);
		v[v.MinIndex()]=range->dblVal;
		return v;
	}

	// Retrieve the Excel range object from the variant and convert it to a Vector<DOUBLE>
	Excel::RangePtr pRange=range->pdispVal;
	return COMUtils::ExcelRangeToVector(pRange);
}

// Convert an Excel range to our vector template class
Vector<DOUBLE> COMUtils::ExcelRangeToVector(Excel::RangePtr pRange)
{
	// Get the number of rows and columns in the range
	int columns=pRange->Columns->Count;
	int rows=pRange->Rows->Count;

	// Create the vector with the correct size
	Vector<DOUBLE> v(columns*rows);

	// Iterate the rows and columns
	int index=v.MinIndex();
	for (int r=1; r<=rows; r++)
	{
		for (int c=1; c<=columns; c++)
		{
			// Add each element in the range to our vector
			v[index++]=(((Excel::RangePtr)pRange->Item[r][c])->Value).dblVal;
		}
	}

	// Return the vector
	return v;
}

// Add a menu item to Excel
Office::_CommandBarButtonPtr COMUtils::AddMenuItem(Excel::_ApplicationPtr xl, Office::COMAddInPtr addin, CComBSTR menuName, CComBSTR menuItemCaption, CComBSTR menuItemKey)
{
	
	Office::CommandBarPtr cmdBar;
	Office::_CommandBarButtonPtr button;
    
	// Get the "menuName" dropdown menu
	cmdBar=xl->GetCommandBars()->GetItem(CComVariant(menuName));
    
	// If not found then end of exercition
	if (cmdBar==NULL) return NULL;
    
	// Try to get the "menuItemCaption" menu item
	button=cmdBar->FindControl(vtMissing, vtMissing, CComVariant(menuItemKey), vtMissing, vtMissing);
    
	// If not found, add it
	if (button==NULL)
	{
        
		// Add new button
		Office::CommandBarControlsPtr controls;
		cmdBar->get_Controls(&controls);
		button=controls->Add(Office::msoControlButton, vtMissing, CComVariant(menuItemKey), vtMissing, vtMissing);
        
		// Set button's Caption, Tag, Style, and OnAction properties.
		button->put_Caption(menuItemCaption);
		button->put_Tag(menuItemKey);
		button->put_Style(Office::msoButtonCaption);
            
		BSTR progId;
		addin->get_ProgId(&progId);

		// Use addin argument to return reference to this add-in.
		CComBSTR str("!<");
		str.AppendBSTR(progId);
		str.Append(">");
		button->put_OnAction(str);
	}
    
	// Return the created button
	return button;
}


// Remove the installed menu item
void COMUtils::RemoveMenuItem(Excel::_ApplicationPtr xl, ext_DisconnectMode removeMode, CComBSTR menuName, CComBSTR menuItemCaption)
{
	Office::CommandBarPtr cmdBar;

	// If user unloaded add-in, remove button. Otherwise, add-in is
	// being unloaded because application is closing; in that case,
	// leave button as is.
	if (removeMode == ext_dm_UserClosed)
	{
		// Get the "menuName" dropdown menu
		cmdBar=xl->GetCommandBars()->GetItem(CComVariant(menuName));
		
		// Delete the "menuItemCaption" menu item
		cmdBar->Controls->GetItem(CComVariant(menuItemCaption))->Delete();
	}
}
