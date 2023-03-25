// BinaryFile.cpp: реализация CBinaryFile

#include "pch.h"
#include "BinaryFile.h"


// CBinaryFile


/*
STDMETHODIMP CBinaryFile::get_filePath(BSTR* pVal)
{
    *pVal = filePath;

    return S_OK;
}


STDMETHODIMP CBinaryFile::put_filePath(BSTR newVal)
{
    filePath = newVal;

    return S_OK;
}*/


/*STDMETHODIMP_(void) CBinaryFile::PrintPath()
{
    
}*/


/*STDMETHODIMP CBinaryFile::printFilePath(BSTR* filePath)
{
    *filePath = this->filePath;

    return S_OK;
}*/


STDMETHODIMP CBinaryFile::get_sourceFilePath(BSTR* pVal)
{
    *pVal = _bstr_t(sourceFilePath).copy();

    return S_OK;
}


STDMETHODIMP CBinaryFile::put_sourceFilePath(BSTR newVal)
{
	sourceFilePath = _bstr_t(newVal).copy();

	if (!SUCCEEDED(openSourceFileAndFillDigits())) {
		return S_FALSE;
	}
	/*std::ifstream sourceFile;
	sourceFile.open(sourceFilePath, std::ios::in | std::ios::binary);
	if (!sourceFile) {
		// callback error opening file

		return S_FALSE;
	}
	std::vector<char> contents((std::istreambuf_iterator<char>(sourceFile)),
		std::istreambuf_iterator<char>());
	int idx = -1;

	std::bitset<BIT_DEPTH> bits;
	char i = 0;
	std::string sourceFileStr;

	for (const char& i : contents) {
		bits[++idx] = (uint32_t)(i - '0');
		if (idx == BIT_DEPTH - 1) {
			digits.push_back(bits.to_ulong());
			idx = -1;
			bits.reset();
		}
	}
	sourceFile.close();*/

	/*resPrefix = SysAllocString(L"\\res_");
	std::wstring ws(sourceFilePath, SysStringLen(sourceFilePath));
	ws = ws.substr(ws.find_last_of('\\')+1);
	resPostfix = SysAllocStringLen(ws.data(), ws.size());*/

    return S_OK;
}


STDMETHODIMP CBinaryFile::get_resultFilePath(BSTR* pVal)
{
    *pVal = _bstr_t(resultFilePath).copy();

    return S_OK;
}


STDMETHODIMP CBinaryFile::put_resultFilePath(BSTR newVal)
{
	resultFilePath = _bstr_t(newVal).copy();

	if (!SUCCEEDED(openAndFillResultFile())) {
		return S_FALSE;
	}
	
    return S_OK;
}


STDMETHODIMP CBinaryFile::get_orderingMode(VARIANT_BOOL* pVal)
{
    *pVal = orderingMode;

    return S_OK;
}


STDMETHODIMP CBinaryFile::put_orderingMode(VARIANT_BOOL newVal)
{
	orderingMode = newVal;

    return S_OK;
}

STDMETHODIMP CBinaryFile::setResultFilesDir(BSTR newVal)
{
	/*while (olechar != _T('/')) {
		olechar = sourceFilePath[len - idxIter];
		tmpChar[idxIter] = olechar;
		idxIter++;
		if (idxIter == len - 1) {
			break;
		}
	}*/
	//resultFilesDir = newVal;
	//resultFilePath = newVal;

	//if (!SUCCEEDED(openAndFillResultFile())) {
		//return S_FALSE;
	//}

	/*resultFilePath.AppendBSTR(resultFilesDir);
	resultFilePath.AppendBSTR(resPrefix);
	resultFilePath.AppendBSTR(resPostfix);*/

	/*if (orderingMode == ascending) {
		std::sort(digits.begin(), digits.end());
	}
	else {
		std::sort(digits.begin(), digits.end(), std::greater<>());
	}*/

	/*std::ofstream resultFile;
	resultFile.open(resultFilePath, std::ios::out | std::ios::binary);
	if (!resultFile) {
		// callback error opening file

		return S_FALSE;
	}
	for (uint32_t num : digits) {
		std::bitset<BIT_DEPTH> bits(num);
		std::string str = bits.to_string();
		std::reverse(str.begin(), str.end());
		//bits = std::bitset<BIT_DEPTH>(str);
		resultFile.write(str.c_str(), BIT_DEPTH);
	}
	resultFile.close();*/
	//resultFilePath.Empty();
	//digits.clear();

	return S_OK;
}

int CBinaryFile::partition(std::vector<uint32_t> &a, int start, int end)
{
	int pivot = a[end];

	int P_index = start;
	int i, t; //t is temporary variable

	for (i = start; i < end; i++)
	{
		if (orderingMode == ascending) {
			if (a[i] <= pivot)
			{
				t = a[i];
				a[i] = a[P_index];
				a[P_index] = t;
				P_index++;
			}
		}
		else {
			if (a[i] >= pivot)
			{
				t = a[i];
				a[i] = a[P_index];
				a[P_index] = t;
				P_index++;
			}
		}
	}
	t = a[end];
	a[end] = a[P_index];
	a[P_index] = t;

	return P_index;
}
bool CBinaryFile::quickSort(std::vector<uint32_t> &a, int start, int end)
{
	if (stop) {
		return S_FALSE;
	}
	if (start < end)
	{
		int P_index = partition(a, start, end);
		quickSort(a, start, P_index - 1);
		quickSort(a, P_index + 1, end);
	}
}

STDMETHODIMP CBinaryFile::sortBinaryFile(VARIANT_BOOL* isRun)
{
	//sourceFilePath = L"C:/Users/eemee/source/repos/COM_Server/source.txt";

	/*std::ifstream sourceFile;
	sourceFile.open(sourceFilePath, std::ios::in | std::ios::binary);
	if (!sourceFile) {
		// callback error opening file
	}
	std::vector<char> contents((std::istreambuf_iterator<char>(sourceFile)),
		std::istreambuf_iterator<char>());
	int idx = -1;
	std::vector<uint32_t> digits;
	std::bitset<BIT_DEPTH> bits;
	char i = 0;
	std::string sourceFileStr;

	for(const char &i : contents) {
		bits[++idx] = (uint32_t)(i - '0');
		if (idx == BIT_DEPTH - 1) {
			digits.push_back(bits.to_ulong());
			idx = -1;
			bits.reset();
		}
	}
	sourceFile.close();*/

	
	/*if (orderingMode == ascending) {
		std::sort(digits.begin(), digits.end());
	}
	else {
		std::sort(digits.begin(), digits.end(), std::greater<>());
	}

	std::ofstream resultFile;
	resultFile.open(resultFilePath, std::ios::out | std::ios::binary);
	if (!resultFile) {
		// callback error opening file
	}
	for (uint32_t num : digits) {
		std::bitset<BIT_DEPTH> bits(num);
		std::string str = bits.to_string();
		std::reverse(str.begin(), str.end());
		//bits = std::bitset<BIT_DEPTH>(str);
		resultFile.write(str.c_str(), BIT_DEPTH);
	}
	resultFile.close();
    isRun = 0;
	resultFilePath.Empty();
	digits.clear();*/

	/*if (orderingMode == ascending) {
		std::sort(digits.begin(), digits.end(), [](int32_t a, int32_t b) {
			return a <= b;
		});
	}
	else {
		std::sort(digits.begin(), digits.end(), std::greater<>());
	}*/

	if (!quickSort(digits, 0, digits.size() - 1)) {
		return S_FALSE;
	}

	//digits.clear();

	isRun = 0;

    return S_OK;
}

STDMETHODIMP CBinaryFile::openSourceFileAndFillDigits()
{
	std::ifstream sourceFile;
	sourceFile.open(sourceFilePath, std::ios::in | std::ios::binary);
	if (!sourceFile) {
		return S_FALSE;
	}
	std::vector<char> contents((std::istreambuf_iterator<char>(sourceFile)),
		std::istreambuf_iterator<char>());
	int idx = -1;

	std::bitset<BIT_DEPTH> bits;
	char i = 0;
	std::string sourceFileStr;

	for (const char& i : contents) {
		bits[++idx] = (uint32_t)(i - '0');
		if (idx == BIT_DEPTH - 1) {
			unsigned long ln = bits.to_ulong();
			digits.push_back(bits.to_ulong());
			idx = -1;
			bits.reset();
		}
	}
	sourceFile.close();

	return S_OK;
}


STDMETHODIMP CBinaryFile::openAndFillResultFile()
{
	std::ofstream resultFile;
	resultFile.open(resultFilePath, std::ios::out | std::ios::binary | std::ofstream::trunc);
	if (!resultFile) {
		return S_FALSE;
	}
	for (uint32_t num : digits) {
		std::bitset<BIT_DEPTH> bits(num);
		std::string str = bits.to_string();
		std::reverse(str.begin(), str.end());
		//bits = std::bitset<BIT_DEPTH>(str);
		resultFile.write(str.c_str(), BIT_DEPTH);
	}
	resultFile.close();

	digits.clear();

	return S_OK;
}


STDMETHODIMP CBinaryFile::stopSorting()
{
	stop = true;
	this->InternalRelease();
	stop = false;

	return S_OK;
}
