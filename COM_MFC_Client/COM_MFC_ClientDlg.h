
// COM_MFC_ClientDlg.h: файл заголовка
//

#pragma once
#include <objbase.h>

#include "../COM_Server/COMServer_i.h"
#include "../COM_Server/COMServer_i.c"

#include <fstream>
#include <iterator>
#include <vector>
#include <bitset>
#include <algorithm>

#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>

#include <queue>

#include <msxml2.h>
#import "MSXML6.dll" rename_namespace(_T("MSXML"))

namespace fs = std::filesystem;

enum orderingMode { ascending = -1, descending };
enum runingMode { run = -1, end };

// Диалоговое окно CCOMMFCClientDlg
class CCOMMFCClientDlg : public CDialogEx
{
	IBinaryFile* binaryFile[4];
	int filesProcededCount;
	int threadIdx;
	int threadsCount;

	std::string sourceDirPathStr;
	std::string resultDirPathStr;
	std::string nextSourceFile[4];

	CString resultDirPath;

	std::string startDateStr;
	std::string startTimeStr;

	CWinThread* m_pThread[4];
	std::queue<std::string> queueSourceFiles;

	bool stop;
	VARIANT_BOOL orderingMode;

	CRITICAL_SECTION m_CriticalSection;

	static UINT choosethreadIdx(CCOMMFCClientDlg* p) {
		/*bool check = true;
		while (check) {
			for (int i(0); i < 4; ++i) {
				DWORD status;
				GetExitCodeThread(p->m_pThread[i], &status);
				if (status != STILL_ACTIVE || p->m_pThread[i] == nullptr) {
					p->threadIdx = i;
					check = false;
					break;
				}
			}
		}*/
		p->doChoosethreadIdx();

		return 1;
	}

	void doChoosethreadIdx() {
		bool check = true;
		while (check) {
			for (int i(0); i < 4; ++i) {
				DWORD status;
				GetExitCodeThread(m_pThread[i], &status);
				if (status != STILL_ACTIVE || m_pThread[i] == nullptr) {
					threadIdx = i;
					check = false;
					break;
				}
			}
		}
	}

	static UINT putAndSortBinaryFile(CCOMMFCClientDlg* p) {

		p->OnPutAndSortBinaryFile();
		return 1;
	}

	void OnPutAndSortBinaryFile() {
		IBinaryFile* binaryFile;
		HRESULT hr = CoCreateInstance(CLSID_BinaryFile, nullptr, CLSCTX_INPROC_SERVER,
			IID_IBinaryFile, (LPVOID*)&binaryFile);
		if (SUCCEEDED(hr)) {
			while (threadsCount >= 4) {

			}
			threadsCount++;

			binaryFile->AddRef();
			//binaryFile->put_orderingMode(orderingMode);
			if (!SUCCEEDED(binaryFile->put_orderingMode(orderingMode))) {
				AfxMessageBox(_T("Error setting ordering mode"));
			}

			VARIANT_BOOL isRun = run;
			BSTR param1, param2;
			EnterCriticalSection(&m_CriticalSection);
			std::string sourceFilePath(queueSourceFiles.front());
			queueSourceFiles.pop();
			LeaveCriticalSection(&m_CriticalSection);
			CComBSTR temp(sourceFilePath.c_str());
			param1 = temp.Detach();

			if (!SUCCEEDED(binaryFile->put_sourceFilePath(param1))) {
				AfxMessageBox(_T("Error opening source file"));
			}

			if (!SUCCEEDED(binaryFile->sortBinaryFile(&isRun))) {
				AfxMessageBox(_T("Error sorting file"));
			}

			std::string resultDirPathStrCopy(resultDirPathStr);
			resultDirPathStrCopy.append(sourceFilePath.substr(sourceFilePath.find_last_of('\\') + 1));
			temp = resultDirPathStrCopy.c_str();
			param2 = temp.Detach();
			if (!SUCCEEDED(binaryFile->put_resultFilePath(param2))) {
				AfxMessageBox(_T("Error creating result file"));
			}
		}
		CoUninitialize();
		threadsCount--;
		filesProcededCount++;
	}

	static UINT setfilesProcededCount(CCOMMFCClientDlg* p) {
		//p->doSetfilesProcededCount();
		while (TRUE) {
			Sleep(100);
			CString filesProcededCountStr;
			filesProcededCountStr.Format(_T("%d"), p->filesProcededCount);
			::SetWindowText(::GetDlgItem(p->m_hWnd, IDC_STATIC_FILES_COUNT), filesProcededCountStr);
		}
		return 1;
	}

	void doSetfilesProcededCount() {
		CString filesProcededCountStr;
		filesProcededCountStr.Format(_T("%d"), filesProcededCount);
		this->GetDlgItem(IDC_STATIC_FILES_COUNT)->SetWindowTextW(filesProcededCountStr);
	}

public:
	CCOMMFCClientDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COM_MFC_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonBreak();
	afx_msg void OnBnClickedRadioAsc();
	afx_msg void OnBnClickedRadioDesc();

	void createXML();
	
	afx_msg void OnBnClickedCancel();
};
