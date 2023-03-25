

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for COMServer.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __COMServer_i_h__
#define __COMServer_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBinaryFile_FWD_DEFINED__
#define __IBinaryFile_FWD_DEFINED__
typedef interface IBinaryFile IBinaryFile;

#endif 	/* __IBinaryFile_FWD_DEFINED__ */


#ifndef __BinaryFile_FWD_DEFINED__
#define __BinaryFile_FWD_DEFINED__

#ifdef __cplusplus
typedef class BinaryFile BinaryFile;
#else
typedef struct BinaryFile BinaryFile;
#endif /* __cplusplus */

#endif 	/* __BinaryFile_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IBinaryFile_INTERFACE_DEFINED__
#define __IBinaryFile_INTERFACE_DEFINED__

/* interface IBinaryFile */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IBinaryFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ca2d3aeb-23ca-472d-b682-88bbdde615a2")
    IBinaryFile : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_sourceFilePath( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_sourceFilePath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_resultFilePath( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_resultFilePath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_orderingMode( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_orderingMode( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE sortBinaryFile( 
            /* [out] */ VARIANT_BOOL *isRun) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setResultFilesDir( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE openSourceFileAndFillDigits( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE openAndFillResultFile( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE stopSorting( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBinaryFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBinaryFile * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBinaryFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBinaryFile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBinaryFile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBinaryFile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBinaryFile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBinaryFile * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_sourceFilePath )( 
            IBinaryFile * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_sourceFilePath )( 
            IBinaryFile * This,
            /* [in] */ BSTR newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_resultFilePath )( 
            IBinaryFile * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_resultFilePath )( 
            IBinaryFile * This,
            /* [in] */ BSTR newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_orderingMode )( 
            IBinaryFile * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_orderingMode )( 
            IBinaryFile * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *sortBinaryFile )( 
            IBinaryFile * This,
            /* [out] */ VARIANT_BOOL *isRun);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setResultFilesDir )( 
            IBinaryFile * This,
            /* [in] */ BSTR newVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *openSourceFileAndFillDigits )( 
            IBinaryFile * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *openAndFillResultFile )( 
            IBinaryFile * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *stopSorting )( 
            IBinaryFile * This);
        
        END_INTERFACE
    } IBinaryFileVtbl;

    interface IBinaryFile
    {
        CONST_VTBL struct IBinaryFileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBinaryFile_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBinaryFile_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBinaryFile_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBinaryFile_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBinaryFile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBinaryFile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBinaryFile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBinaryFile_get_sourceFilePath(This,pVal)	\
    ( (This)->lpVtbl -> get_sourceFilePath(This,pVal) ) 

#define IBinaryFile_put_sourceFilePath(This,newVal)	\
    ( (This)->lpVtbl -> put_sourceFilePath(This,newVal) ) 

#define IBinaryFile_get_resultFilePath(This,pVal)	\
    ( (This)->lpVtbl -> get_resultFilePath(This,pVal) ) 

#define IBinaryFile_put_resultFilePath(This,newVal)	\
    ( (This)->lpVtbl -> put_resultFilePath(This,newVal) ) 

#define IBinaryFile_get_orderingMode(This,pVal)	\
    ( (This)->lpVtbl -> get_orderingMode(This,pVal) ) 

#define IBinaryFile_put_orderingMode(This,newVal)	\
    ( (This)->lpVtbl -> put_orderingMode(This,newVal) ) 

#define IBinaryFile_sortBinaryFile(This,isRun)	\
    ( (This)->lpVtbl -> sortBinaryFile(This,isRun) ) 

#define IBinaryFile_setResultFilesDir(This,newVal)	\
    ( (This)->lpVtbl -> setResultFilesDir(This,newVal) ) 

#define IBinaryFile_openSourceFileAndFillDigits(This)	\
    ( (This)->lpVtbl -> openSourceFileAndFillDigits(This) ) 

#define IBinaryFile_openAndFillResultFile(This)	\
    ( (This)->lpVtbl -> openAndFillResultFile(This) ) 

#define IBinaryFile_stopSorting(This)	\
    ( (This)->lpVtbl -> stopSorting(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBinaryFile_INTERFACE_DEFINED__ */



#ifndef __COMServerLib_LIBRARY_DEFINED__
#define __COMServerLib_LIBRARY_DEFINED__

/* library COMServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_COMServerLib;

EXTERN_C const CLSID CLSID_BinaryFile;

#ifdef __cplusplus

class DECLSPEC_UUID("6d7412e1-abf6-4060-9e47-bc9e059a498f")
BinaryFile;
#endif
#endif /* __COMServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


