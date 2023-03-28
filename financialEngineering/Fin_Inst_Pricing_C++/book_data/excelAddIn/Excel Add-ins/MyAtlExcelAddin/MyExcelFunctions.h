// MyExcelFunctions.h : Declaration of the CMyExcelFunctions

#pragma once
#include "resource.h"       // main symbols

#include "MyAtlExcelAddin.h"


// CMyExcelFunctions

class ATL_NO_VTABLE CMyExcelFunctions : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyExcelFunctions, &CLSID_MyExcelFunctions>,
	public IDispatchImpl<IMyExcelFunctions, &IID_IMyExcelFunctions, &LIBID_MyAtlExcelAddinLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<_IDTExtensibility2, &__uuidof(_IDTExtensibility2), &LIBID_AddInDesignerObjects, /* wMajor = */ 1, /* wMinor = */ 0>,
	public IDispEventImpl</*nID*/ 1, CMyExcelFunctions, &__uuidof(Office::_CommandBarButtonEvents), &__uuidof(Office::__Office), /*wMajor*/ 2, /*wMinor*/ 2>
{

private:
	Excel::_ApplicationPtr m_xl;				// The Excel instance the add-in communicates with
	Office::_CommandBarButtonPtr m_menuItem;	// The menu item added by the add-in

public:
	CMyExcelFunctions()
	{
		m_menuItem=NULL;
		m_xl;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MYEXCELFUNCTIONS)


	BEGIN_COM_MAP(CMyExcelFunctions)
		COM_INTERFACE_ENTRY(IMyExcelFunctions)
		COM_INTERFACE_ENTRY2(IDispatch, IMyExcelFunctions)
		COM_INTERFACE_ENTRY(_IDTExtensibility2)
	END_COM_MAP()

	BEGIN_SINK_MAP(CMyExcelFunctions)
		SINK_ENTRY_EX(/*nID =*/ 1, __uuidof(Office::_CommandBarButtonEvents), /*dispid =*/ 1, OnButtonClick)
	END_SINK_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease() 
	{
	}

public:

	// _IDTExtensibility2 Methods
	STDMETHOD(OnConnection)(LPDISPATCH Application, ext_ConnectMode ConnectMode, LPDISPATCH AddInInst, SAFEARRAY * * custom);
	STDMETHOD(OnDisconnection)(ext_DisconnectMode RemoveMode, SAFEARRAY * * custom);

	STDMETHOD(OnAddInsUpdate)(SAFEARRAY * * custom)
	{
		return S_OK;
	}

	STDMETHOD(OnStartupComplete)(SAFEARRAY * * custom)
	{
		return S_OK;
	}

	STDMETHOD(OnBeginShutdown)(SAFEARRAY * * custom)
	{
		return E_NOTIMPL;
	}

	// Event handlers
	void __stdcall OnButtonClick(Office::_CommandBarButtonPtr Ctrl, VARIANT_BOOL * CancelDefault);

	// My Excel worksheet functions
	STDMETHOD(MyPI)(DOUBLE* MyPIArg);
	STDMETHOD(MySubtract)(DOUBLE* arg1, DOUBLE* arg2, DOUBLE* result);
	STDMETHOD(MyAdd)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielSum)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielSumReciprocals)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielSumAbsoluteValues)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielMean)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielWeightedArithMean)(VARIANT* range1, VARIANT* range2, DOUBLE* result);
	STDMETHOD(DanielGeometricMean)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielHarmonicMean)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielQuadraticMean)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielSumSquares)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielMedian)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielMode)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielDeviationFromMean)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielStandardDeviation)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielVariance)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielRthMoment)(VARIANT* range, LONG* r, DOUBLE* result);
	STDMETHOD(DanielRthMomentMean)(VARIANT* range, LONG* r, DOUBLE* result);
	STDMETHOD(DanielRthMoment2)(VARIANT* range, LONG* r, DOUBLE* A, DOUBLE* result);
	STDMETHOD(DanielRthMoment3)(VARIANT* range, VARIANT* freq, LONG* r, DOUBLE* A, DOUBLE* result);
	STDMETHOD(DanielSkewness)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielMomentCoeffKurtosis)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielMaxValue)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielMinValue)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielMaxAbsValue)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielMinAbsValue)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielIndexMaxValue)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielIndexMinValue)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielIndexMaxAbsValue)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielIndexMinAbsValue)(VARIANT* range, DOUBLE* result);
	STDMETHOD(DanielMaxValue2)(VARIANT* range1, VARIANT* range2, DOUBLE* result);
	STDMETHOD(DanielMinValue2)(VARIANT* range1, VARIANT* range2, DOUBLE* result);
	STDMETHOD(DanielMaxAbsValue2)(VARIANT* range1, VARIANT* range2, DOUBLE* result);
	STDMETHOD(DanielMinAbsValue2)(VARIANT* range1, VARIANT* range2, DOUBLE* result);
	STDMETHOD(MyArrayFunction)(VARIANT* range1, VARIANT* range2, VARIANT* result);
};

OBJECT_ENTRY_AUTO(__uuidof(MyExcelFunctions), CMyExcelFunctions)
