// MyExcelFunctions.cpp : Implementation of CMyExcelFunctions

#include "stdafx.h"
#include "MyExcelFunctions.h"
#include "Functions\ArrayMechanisms.cpp"
#include "COMUtils.hpp"

// IDTExtensibility2 function

STDMETHODIMP CMyExcelFunctions::OnConnection(LPDISPATCH Application, ext_ConnectMode ConnectMode, LPDISPATCH AddInInst, SAFEARRAY * * custom)
{
	// Store reference to the Excel host application. Exit if host application is not Excel.
	m_xl=Application;
	if (m_xl==NULL) return S_OK;

			
	// If an AddInInst object given of the type COMAddin then loaded as COM Add-in
	// If AddInInst is the same object as myself then I'm loaded as Automation Add-in
	Office::COMAddInPtr cai=AddInInst;
	if (cai!=NULL)
	{

		// Attach myself to the add-in object
		// In that way I can call functions of this object from VBA using the add-in collections
		void* id;
		this->QueryInterface(IID_IDispatch, &id);
		cai->put_Object((IDispatch*)id);

		// Now install menu item
		m_menuItem = COMUtils::AddMenuItem(m_xl, cai, CComBSTR("Tools"), CComBSTR("My ATL Add-in"), CComBSTR("MyATLAddin"));

		// And add our event sink to the menu item
		return DispEventAdvise(m_menuItem);
	}

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::OnDisconnection(ext_DisconnectMode RemoveMode, SAFEARRAY * * custom)
{
	if (m_menuItem!=NULL)
	{
		// Remove our event sink from the menu item
		DispEventUnadvise(m_menuItem);

		// Remove the menu item
		COMUtils::RemoveMenuItem(m_xl, RemoveMode, CComBSTR("Tools"), CComBSTR("My ATL Add-in"));
	}

	return S_OK;
}

// Event handlers

// Handle the Click event of the menu item
void __stdcall CMyExcelFunctions::OnButtonClick(Office::_CommandBarButtonPtr Ctrl, VARIANT_BOOL * CancelDefault)
{
	m_xl->GetRange("a1:b2")->Value2="Add-in called";
}


// CMyExcelFunctions


STDMETHODIMP CMyExcelFunctions::MyPI(DOUBLE* MyPIArg)
{
	// Return the value PI
	*MyPIArg=3.14;

	// No errors
	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::MySubtract(DOUBLE* arg1, DOUBLE* arg2, DOUBLE* result)
{
	// Subtract two values
	*result=*arg1-*arg2;

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::MyAdd(VARIANT* range, DOUBLE* result)
{
	// Check if a range object was passed
	if (range->vt!=VT_DISPATCH)
	{
		// No range passed so just return the double value
		*result=range->dblVal;
		return S_OK;
	}

	// Retrieve the Excel range object from the variant
	Excel::RangePtr pRange=range->pdispVal;	

	// Get the number of rows and columns in the range
	int columns=pRange->Columns->Count;
	int rows=pRange->Rows->Count;

	// Temporary result
	double tmp=0.0;

	// Iterate the rows and columns
	for (int r=1; r<=rows; r++)
	{
		for (int c=1; c<=columns; c++)
		{
			// Get the value of the current cell as double and add to running result
			tmp+=(((Excel::RangePtr)pRange->Item[r][c])->Value).dblVal;			
		}
	}

	// Return the result
	*result=tmp;
	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielSum(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate sum
	*result=sum(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielSumReciprocals(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate sumReciprocals
	*result=sumReciprocals(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielSumAbsoluteValues(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate sumReciprocals
	*result=sumAbsoluteValues(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMean(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate mean
	*result=mean(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielWeightedArithMean(VARIANT* range1, VARIANT* range2, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v1=COMUtils::ExcelRangeToVector(range1);
	Vector<DOUBLE> v2=COMUtils::ExcelRangeToVector(range2);
	
	// Calculate weighted arith mean
	*result=weightedArithMean(v1, v2);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielGeometricMean(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate geometric mean
	*result=geometricMean(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielHarmonicMean(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate harmonic mean
	*result=harmonicMean(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielQuadraticMean(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate quadratic mean
	*result=quadraticMean(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielSumSquares(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate sum squares
	*result=sumSquares(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMedian(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate median
	*result=median(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMode(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate mode
	*result=mode(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielDeviationFromMean(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate deviation from mean
	*result=deviationFromMean(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielStandardDeviation(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate standard deviation
	*result=standardDeviation(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielVariance(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate variance
	*result=variance(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielRthMoment(VARIANT* range, LONG* r, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=rthMoment(v, (int)*r);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielRthMomentMean(VARIANT* range, LONG* r, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);

	// Calculate
	*result=rthMomentMean(v, (int)*r);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielRthMoment2(VARIANT* range, LONG* r, DOUBLE* A, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=rthMoment(v, (int)*r, *A);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielRthMoment3(VARIANT* range, VARIANT* freq, LONG* r, DOUBLE* A, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	Vector<DOUBLE> f=COMUtils::ExcelRangeToVector(freq);
	
	// Calculate
	*result=rthMoment(v, f, (int)*r, *A);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielSkewness(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=skewness(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMomentCoeffKurtosis(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=momentCoeffKurtosis(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMaxValue(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=maxValue(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMinValue(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=minValue(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMaxAbsValue(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=maxAbsValue(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMinAbsValue(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=minAbsValue(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielIndexMaxValue(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=indexMaxValue(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielIndexMinValue(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=indexMinValue(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielIndexMaxAbsValue(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=indexMaxAbsValue(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielIndexMinAbsValue(VARIANT* range, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v=COMUtils::ExcelRangeToVector(range);
	
	// Calculate
	*result=indexMinAbsValue(v);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMaxValue2(VARIANT* range1, VARIANT* range2, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v1=COMUtils::ExcelRangeToVector(range1);
	Vector<DOUBLE> v2=COMUtils::ExcelRangeToVector(range2);
	
	// Calculate
	*result=maxValue(v1, v2);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMinValue2(VARIANT* range1, VARIANT* range2, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v1=COMUtils::ExcelRangeToVector(range1);
	Vector<DOUBLE> v2=COMUtils::ExcelRangeToVector(range2);
	
	// Calculate
	*result=minValue(v1, v2);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMaxAbsValue2(VARIANT* range1, VARIANT* range2, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v1=COMUtils::ExcelRangeToVector(range1);
	Vector<DOUBLE> v2=COMUtils::ExcelRangeToVector(range2);
	
	// Calculate
	*result=maxAbsValue(v1, v2);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::DanielMinAbsValue2(VARIANT* range1, VARIANT* range2, DOUBLE* result)
{
	// Convert input to vector
	Vector<DOUBLE> v1=COMUtils::ExcelRangeToVector(range1);
	Vector<DOUBLE> v2=COMUtils::ExcelRangeToVector(range2);
	
	// Calculate
	*result=minAbsValue(v1, v2);

	return S_OK;
}

STDMETHODIMP CMyExcelFunctions::MyArrayFunction(VARIANT* range1, VARIANT* range2, VARIANT* result)
{ // Test an array function (function that return multiple values)
  // To enter an array function in Excel you have to hold <shift>+<control> when entering a formula.
  // This still doesn't work. Some problems with returning the result as variant. Maybe it should be a range object.

	// Convert input to vector
	Vector<DOUBLE> v1=COMUtils::ExcelRangeToVector(range1);
	Vector<DOUBLE> v2=COMUtils::ExcelRangeToVector(range2);

	// Determine the minimum size of both input arrays
	size_t size;
	if (v1.Size()<v2.Size()) size=v1.Size();
	size=v2.Size();

	// Add both arrays (v1+v2 does not take different vector sizes in account)
	Vector<DOUBLE> vr(size);
	for (int i=vr.MinIndex(); i<=vr.MaxIndex(); i++)
	{
		vr[i]=v1[i]+v2[i];
	}

	// Put result in safe array
	CComSafeArray<DOUBLE> res;
	res.Create(size);

	LONG j;
	for (i=vr.MinIndex(), j=0; i<=vr.MaxIndex(); i++, j++)
	{
		res.SetAt(j, vr[i]);
	}

	// Put safe array in variant
	CComVariant v(res);

	// Put resulting variant in result
	v.Detach(result);

	return S_OK;
}
