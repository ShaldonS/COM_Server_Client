// BinaryFile.h: объявление CBinaryFile

#pragma once
#include "resource.h"       // основные символы
#include <fstream>
#include <iterator>
#include <vector>
#include <bitset>
#include <algorithm>
#include <comdef.h>

#include "COMServer_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;

enum orderingMode { ascending = -1, descending };
enum runingMode { run = -1, end };
const int BIT_DEPTH = 32;

// CBinaryFile

class ATL_NO_VTABLE CBinaryFile :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBinaryFile, &CLSID_BinaryFile>,
	public IDispatchImpl<IBinaryFile, &IID_IBinaryFile, &LIBID_COMServerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CBinaryFile()
	{
		sourceFilePath = _T("");
		resultFilePath = _T("");
		orderingMode = -1;
		stop = false;
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CBinaryFile)
	COM_INTERFACE_ENTRY(IBinaryFile)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
private: 
	//BSTR filePath;
	BSTR sourceFilePath;
	BSTR sourceFilePathCopy;
	CComBSTR resultFilePath;
	BSTR resultFilesDir;
	CComBSTR  resPrefix;
	CComBSTR  resPostfix;
	
	VARIANT_BOOL orderingMode;
	std::vector<uint32_t> digits;
	bool stop;

public:

	//STDMETHOD(get_filePath)(BSTR* pVal);
	//STDMETHOD(put_filePath)(BSTR newVal);
	//STDMETHOD_(void, PrintPath)();

//public:
	//STDMETHOD(printFilePath)(BSTR* filePath);
	STDMETHOD(get_sourceFilePath)(BSTR* pVal);
	STDMETHOD(put_sourceFilePath)(BSTR newVal);
	STDMETHOD(get_resultFilePath)(BSTR* pVal);
	STDMETHOD(put_resultFilePath)(BSTR newVal);
	STDMETHOD(get_orderingMode)(VARIANT_BOOL* pVal);
	STDMETHOD(put_orderingMode)(VARIANT_BOOL newVal);
	STDMETHOD(sortBinaryFile)(VARIANT_BOOL* isRun);
	STDMETHOD(setResultFilesDir)(BSTR newVal);
	STDMETHOD(openSourceFileAndFillDigits)();
	STDMETHOD(openAndFillResultFile)();
	STDMETHOD(stopSorting)();

	int partition(std::vector<uint32_t> &a, int start, int end);
	bool quickSort(std::vector<uint32_t> &a, int start, int end);

};

OBJECT_ENTRY_AUTO(__uuidof(BinaryFile), CBinaryFile)
