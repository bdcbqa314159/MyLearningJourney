// MyAtlExcelAddin.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "MyAtlExcelAddin.h"
#include "COMUtils.hpp"

// Strings for registering my COM add-in
LPSTR pszProgID = "MyAtlExcelAddin.MyExcelFunctions";
LPSTR pszFriendlyName = "My First Excel Add-in!";

class CMyAtlExcelAddinModule : public CAtlDllModuleT< CMyAtlExcelAddinModule >
{
public :
	DECLARE_LIBID(LIBID_MyAtlExcelAddinLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MYATLEXCELADDIN, "{2F599BCE-55FE-4219-B5C4-7CADC33E0258}")
};

CMyAtlExcelAddinModule _AtlModule;


// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}


// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	// Register this COM add-in for Excel
	COMUtils::RegisterCOMAddin("Excel", pszProgID, pszFriendlyName, 16);

    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	// Unregister this COM add-in
	COMUtils::UnRegisterCOMAddin("Excel", pszProgID);

	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}
