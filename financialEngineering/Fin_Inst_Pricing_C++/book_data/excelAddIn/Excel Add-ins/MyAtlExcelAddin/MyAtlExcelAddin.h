
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Dec 29 10:22:53 2003
 */
/* Compiler settings for MyAtlExcelAddin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __MyAtlExcelAddin_h__
#define __MyAtlExcelAddin_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyExcelFunctions_FWD_DEFINED__
#define __IMyExcelFunctions_FWD_DEFINED__
typedef interface IMyExcelFunctions IMyExcelFunctions;
#endif 	/* __IMyExcelFunctions_FWD_DEFINED__ */


#ifndef __MyExcelFunctions_FWD_DEFINED__
#define __MyExcelFunctions_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyExcelFunctions MyExcelFunctions;
#else
typedef struct MyExcelFunctions MyExcelFunctions;
#endif /* __cplusplus */

#endif 	/* __MyExcelFunctions_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IMyExcelFunctions_INTERFACE_DEFINED__
#define __IMyExcelFunctions_INTERFACE_DEFINED__

/* interface IMyExcelFunctions */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyExcelFunctions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DE48EB00-2907-46BD-991E-CF71ED7F2973")
    IMyExcelFunctions : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MyPI( 
            /* [retval][out] */ DOUBLE *MyPIArg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MySubtract( 
            /* [in] */ DOUBLE *arg1,
            /* [in] */ DOUBLE *arg2,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MyAdd( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielSum( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielSumReciprocals( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielSumAbsoluteValues( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMean( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielWeightedArithMean( 
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielGeometricMean( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielHarmonicMean( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielQuadraticMean( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielSumSquares( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMedian( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMode( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielDeviationFromMean( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielStandardDeviation( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielVariance( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielRthMoment( 
            /* [in] */ VARIANT *range,
            /* [in] */ LONG *r,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielRthMomentMean( 
            /* [in] */ VARIANT *range,
            /* [in] */ LONG *r,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielRthMoment2( 
            /* [in] */ VARIANT *range,
            /* [in] */ LONG *r,
            /* [in] */ DOUBLE *A,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielRthMoment3( 
            /* [in] */ VARIANT *range,
            /* [in] */ VARIANT *freq,
            /* [in] */ LONG *r,
            /* [in] */ DOUBLE *A,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielSkewness( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMomentCoeffKurtosis( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMaxValue( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMinValue( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMaxAbsValue( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMinAbsValue( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielIndexMaxValue( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielIndexMinValue( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielIndexMaxAbsValue( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielIndexMinAbsValue( 
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMaxValue2( 
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMinValue2( 
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMaxAbsValue2( 
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DanielMinAbsValue2( 
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ DOUBLE *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MyArrayFunction( 
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ VARIANT *result) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyExcelFunctionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyExcelFunctions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyExcelFunctions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyExcelFunctions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyExcelFunctions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyExcelFunctions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyExcelFunctions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyExcelFunctions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MyPI )( 
            IMyExcelFunctions * This,
            /* [retval][out] */ DOUBLE *MyPIArg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MySubtract )( 
            IMyExcelFunctions * This,
            /* [in] */ DOUBLE *arg1,
            /* [in] */ DOUBLE *arg2,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MyAdd )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielSum )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielSumReciprocals )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielSumAbsoluteValues )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMean )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielWeightedArithMean )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielGeometricMean )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielHarmonicMean )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielQuadraticMean )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielSumSquares )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMedian )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMode )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielDeviationFromMean )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielStandardDeviation )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielVariance )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielRthMoment )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [in] */ LONG *r,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielRthMomentMean )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [in] */ LONG *r,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielRthMoment2 )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [in] */ LONG *r,
            /* [in] */ DOUBLE *A,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielRthMoment3 )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [in] */ VARIANT *freq,
            /* [in] */ LONG *r,
            /* [in] */ DOUBLE *A,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielSkewness )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMomentCoeffKurtosis )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMaxValue )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMinValue )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMaxAbsValue )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMinAbsValue )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielIndexMaxValue )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielIndexMinValue )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielIndexMaxAbsValue )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielIndexMinAbsValue )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMaxValue2 )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMinValue2 )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMaxAbsValue2 )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DanielMinAbsValue2 )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ DOUBLE *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MyArrayFunction )( 
            IMyExcelFunctions * This,
            /* [in] */ VARIANT *range1,
            /* [in] */ VARIANT *range2,
            /* [retval][out] */ VARIANT *result);
        
        END_INTERFACE
    } IMyExcelFunctionsVtbl;

    interface IMyExcelFunctions
    {
        CONST_VTBL struct IMyExcelFunctionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyExcelFunctions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyExcelFunctions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyExcelFunctions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyExcelFunctions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMyExcelFunctions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMyExcelFunctions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMyExcelFunctions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMyExcelFunctions_MyPI(This,MyPIArg)	\
    (This)->lpVtbl -> MyPI(This,MyPIArg)

#define IMyExcelFunctions_MySubtract(This,arg1,arg2,result)	\
    (This)->lpVtbl -> MySubtract(This,arg1,arg2,result)

#define IMyExcelFunctions_MyAdd(This,range,result)	\
    (This)->lpVtbl -> MyAdd(This,range,result)

#define IMyExcelFunctions_DanielSum(This,range,result)	\
    (This)->lpVtbl -> DanielSum(This,range,result)

#define IMyExcelFunctions_DanielSumReciprocals(This,range,result)	\
    (This)->lpVtbl -> DanielSumReciprocals(This,range,result)

#define IMyExcelFunctions_DanielSumAbsoluteValues(This,range,result)	\
    (This)->lpVtbl -> DanielSumAbsoluteValues(This,range,result)

#define IMyExcelFunctions_DanielMean(This,range,result)	\
    (This)->lpVtbl -> DanielMean(This,range,result)

#define IMyExcelFunctions_DanielWeightedArithMean(This,range1,range2,result)	\
    (This)->lpVtbl -> DanielWeightedArithMean(This,range1,range2,result)

#define IMyExcelFunctions_DanielGeometricMean(This,range,result)	\
    (This)->lpVtbl -> DanielGeometricMean(This,range,result)

#define IMyExcelFunctions_DanielHarmonicMean(This,range,result)	\
    (This)->lpVtbl -> DanielHarmonicMean(This,range,result)

#define IMyExcelFunctions_DanielQuadraticMean(This,range,result)	\
    (This)->lpVtbl -> DanielQuadraticMean(This,range,result)

#define IMyExcelFunctions_DanielSumSquares(This,range,result)	\
    (This)->lpVtbl -> DanielSumSquares(This,range,result)

#define IMyExcelFunctions_DanielMedian(This,range,result)	\
    (This)->lpVtbl -> DanielMedian(This,range,result)

#define IMyExcelFunctions_DanielMode(This,range,result)	\
    (This)->lpVtbl -> DanielMode(This,range,result)

#define IMyExcelFunctions_DanielDeviationFromMean(This,range,result)	\
    (This)->lpVtbl -> DanielDeviationFromMean(This,range,result)

#define IMyExcelFunctions_DanielStandardDeviation(This,range,result)	\
    (This)->lpVtbl -> DanielStandardDeviation(This,range,result)

#define IMyExcelFunctions_DanielVariance(This,range,result)	\
    (This)->lpVtbl -> DanielVariance(This,range,result)

#define IMyExcelFunctions_DanielRthMoment(This,range,r,result)	\
    (This)->lpVtbl -> DanielRthMoment(This,range,r,result)

#define IMyExcelFunctions_DanielRthMomentMean(This,range,r,result)	\
    (This)->lpVtbl -> DanielRthMomentMean(This,range,r,result)

#define IMyExcelFunctions_DanielRthMoment2(This,range,r,A,result)	\
    (This)->lpVtbl -> DanielRthMoment2(This,range,r,A,result)

#define IMyExcelFunctions_DanielRthMoment3(This,range,freq,r,A,result)	\
    (This)->lpVtbl -> DanielRthMoment3(This,range,freq,r,A,result)

#define IMyExcelFunctions_DanielSkewness(This,range,result)	\
    (This)->lpVtbl -> DanielSkewness(This,range,result)

#define IMyExcelFunctions_DanielMomentCoeffKurtosis(This,range,result)	\
    (This)->lpVtbl -> DanielMomentCoeffKurtosis(This,range,result)

#define IMyExcelFunctions_DanielMaxValue(This,range,result)	\
    (This)->lpVtbl -> DanielMaxValue(This,range,result)

#define IMyExcelFunctions_DanielMinValue(This,range,result)	\
    (This)->lpVtbl -> DanielMinValue(This,range,result)

#define IMyExcelFunctions_DanielMaxAbsValue(This,range,result)	\
    (This)->lpVtbl -> DanielMaxAbsValue(This,range,result)

#define IMyExcelFunctions_DanielMinAbsValue(This,range,result)	\
    (This)->lpVtbl -> DanielMinAbsValue(This,range,result)

#define IMyExcelFunctions_DanielIndexMaxValue(This,range,result)	\
    (This)->lpVtbl -> DanielIndexMaxValue(This,range,result)

#define IMyExcelFunctions_DanielIndexMinValue(This,range,result)	\
    (This)->lpVtbl -> DanielIndexMinValue(This,range,result)

#define IMyExcelFunctions_DanielIndexMaxAbsValue(This,range,result)	\
    (This)->lpVtbl -> DanielIndexMaxAbsValue(This,range,result)

#define IMyExcelFunctions_DanielIndexMinAbsValue(This,range,result)	\
    (This)->lpVtbl -> DanielIndexMinAbsValue(This,range,result)

#define IMyExcelFunctions_DanielMaxValue2(This,range1,range2,result)	\
    (This)->lpVtbl -> DanielMaxValue2(This,range1,range2,result)

#define IMyExcelFunctions_DanielMinValue2(This,range1,range2,result)	\
    (This)->lpVtbl -> DanielMinValue2(This,range1,range2,result)

#define IMyExcelFunctions_DanielMaxAbsValue2(This,range1,range2,result)	\
    (This)->lpVtbl -> DanielMaxAbsValue2(This,range1,range2,result)

#define IMyExcelFunctions_DanielMinAbsValue2(This,range1,range2,result)	\
    (This)->lpVtbl -> DanielMinAbsValue2(This,range1,range2,result)

#define IMyExcelFunctions_MyArrayFunction(This,range1,range2,result)	\
    (This)->lpVtbl -> MyArrayFunction(This,range1,range2,result)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_MyPI_Proxy( 
    IMyExcelFunctions * This,
    /* [retval][out] */ DOUBLE *MyPIArg);


void __RPC_STUB IMyExcelFunctions_MyPI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_MySubtract_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ DOUBLE *arg1,
    /* [in] */ DOUBLE *arg2,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_MySubtract_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_MyAdd_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_MyAdd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielSum_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielSum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielSumReciprocals_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielSumReciprocals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielSumAbsoluteValues_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielSumAbsoluteValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMean_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielWeightedArithMean_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range1,
    /* [in] */ VARIANT *range2,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielWeightedArithMean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielGeometricMean_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielGeometricMean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielHarmonicMean_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielHarmonicMean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielQuadraticMean_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielQuadraticMean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielSumSquares_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielSumSquares_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMedian_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMedian_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMode_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielDeviationFromMean_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielDeviationFromMean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielStandardDeviation_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielStandardDeviation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielVariance_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielVariance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielRthMoment_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [in] */ LONG *r,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielRthMoment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielRthMomentMean_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [in] */ LONG *r,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielRthMomentMean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielRthMoment2_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [in] */ LONG *r,
    /* [in] */ DOUBLE *A,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielRthMoment2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielRthMoment3_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [in] */ VARIANT *freq,
    /* [in] */ LONG *r,
    /* [in] */ DOUBLE *A,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielRthMoment3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielSkewness_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielSkewness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMomentCoeffKurtosis_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMomentCoeffKurtosis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMaxValue_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMaxValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMinValue_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMinValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMaxAbsValue_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMaxAbsValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMinAbsValue_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMinAbsValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielIndexMaxValue_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielIndexMaxValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielIndexMinValue_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielIndexMinValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielIndexMaxAbsValue_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielIndexMaxAbsValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielIndexMinAbsValue_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielIndexMinAbsValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMaxValue2_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range1,
    /* [in] */ VARIANT *range2,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMaxValue2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMinValue2_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range1,
    /* [in] */ VARIANT *range2,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMinValue2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMaxAbsValue2_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range1,
    /* [in] */ VARIANT *range2,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMaxAbsValue2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_DanielMinAbsValue2_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range1,
    /* [in] */ VARIANT *range2,
    /* [retval][out] */ DOUBLE *result);


void __RPC_STUB IMyExcelFunctions_DanielMinAbsValue2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyExcelFunctions_MyArrayFunction_Proxy( 
    IMyExcelFunctions * This,
    /* [in] */ VARIANT *range1,
    /* [in] */ VARIANT *range2,
    /* [retval][out] */ VARIANT *result);


void __RPC_STUB IMyExcelFunctions_MyArrayFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyExcelFunctions_INTERFACE_DEFINED__ */



#ifndef __MyAtlExcelAddinLib_LIBRARY_DEFINED__
#define __MyAtlExcelAddinLib_LIBRARY_DEFINED__

/* library MyAtlExcelAddinLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MyAtlExcelAddinLib;

EXTERN_C const CLSID CLSID_MyExcelFunctions;

#ifdef __cplusplus

class DECLSPEC_UUID("7E516342-6B85-46DB-A262-CE91BF4DE8E0")
MyExcelFunctions;
#endif
#endif /* __MyAtlExcelAddinLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


