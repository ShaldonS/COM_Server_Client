
// COM_MFC_ClientDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "COM_MFC_Client.h"
#include "COM_MFC_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Диалоговое окно CCOMMFCClientDlg

CCOMMFCClientDlg::CCOMMFCClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COM_MFC_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	filesProcededCount = 0;
	threadIdx = 0;
	stop = false;
	threadsCount = 0;

	for (int i(0); i < 4; ++i) {
		m_pThread[i] = nullptr;
	}

	InitializeCriticalSection(&m_CriticalSection);
}

void CCOMMFCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCOMMFCClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CCOMMFCClientDlg::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDOK, &CCOMMFCClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_BREAK, &CCOMMFCClientDlg::OnBnClickedButtonBreak)
	ON_BN_CLICKED(IDC_RADIO_ASC, &CCOMMFCClientDlg::OnBnClickedRadioAsc)
	ON_BN_CLICKED(IDC_RADIO_DESC, &CCOMMFCClientDlg::OnBnClickedRadioDesc)
	ON_BN_CLICKED(IDCANCEL, &CCOMMFCClientDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CCOMMFCClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	//ShowWindow(SW_MAXIMIZE);

	//ShowWindow(SW_MINIMIZE);

	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::stringstream ss, ss_;
	std::tm bt, bt_;
	localtime_s(&bt, &in_time_t);
	localtime_s(&bt_, &in_time_t);
	ss << std::put_time(&bt, "%Y-%m-%d");
	ss_ << std::put_time(&bt_, "%X");

	startDateStr = ss.str();
	startTimeStr = ss_.str();



	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CCOMMFCClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CCOMMFCClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCOMMFCClientDlg::OnEnChangeMfceditbrowse1()
{
}


void CCOMMFCClientDlg::OnBnClickedOk()
{
	if (!IsDlgButtonChecked(IDC_RADIO_ASC)) {
		if (!IsDlgButtonChecked(IDC_RADIO_DESC)) {
			AfxMessageBox(_T("Please select sorting mode"));
			return;
		}
	}
	CString sourceDirPath;
	CString resultDirPath;
	GetDlgItem(IDC_MFCEDITBROWSE1)->GetWindowTextW(sourceDirPath);
	GetDlgItem(IDC_MFCEDITBROWSE2)->GetWindowTextW(resultDirPath);
	if (sourceDirPath.GetLength() == 0) {
		AfxMessageBox(_T("Please input source dir path"));
		return;
	}
	if (resultDirPath.GetLength() == 0) {
		AfxMessageBox(_T("Please input result dir path"));
		return;
	}
	GetDlgItem(IDC_RADIO_ASC)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_DESC)->EnableWindow(FALSE);

	filesProcededCount = 0;
	CString filesProcededCountStr;
	filesProcededCountStr.Format(_T("%d"), filesProcededCount);
	GetDlgItem(IDC_STATIC_FILES_COUNT)->SetWindowTextW(filesProcededCountStr);

	CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);

	CT2CA sourceDirPathAnsi(sourceDirPath), resultDirPathAnsi(resultDirPath);
	sourceDirPathStr = sourceDirPathAnsi;
	sourceDirPathStr.append("\\");
	resultDirPathStr = resultDirPathAnsi;
	resultDirPathStr.append("\\res_");

	filesProcededCount = 0;

	//int cnt = 0;

	//AfxBeginThread((AFX_THREADPROC)setfilesProcededCount, this);
	std::string sourceFilePath(sourceDirPathStr);
	IBinaryFile* binaryFile;
	HRESULT hr = CoCreateInstance(CLSID_BinaryFile, nullptr, CLSCTX_INPROC_SERVER,
		IID_IBinaryFile, (LPVOID*)&binaryFile);
	if (SUCCEEDED(hr)) {
		binaryFile->AddRef();
		if (!SUCCEEDED(binaryFile->put_orderingMode(orderingMode))) {
			AfxMessageBox(_T("Error setting ordering mode"));
		}
		for (const auto& entry : fs::directory_iterator(sourceDirPathStr)) {
			sourceFilePath.append(entry.path().filename().string());
		
			VARIANT_BOOL isRun = run;
			BSTR param1, param2;

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
			filesProcededCount++;
			CString filesProcededCountStr;
			filesProcededCountStr.Format(_T("%d"), filesProcededCount);
			this->GetDlgItem(IDC_STATIC_FILES_COUNT)->SetWindowTextW(filesProcededCountStr);
			//cnt++;
		}
		
	}

	/*for (int i(0); i < cnt; ++i) {
		while (threadsCount >= 4) {

		}
		AfxBeginThread((AFX_THREADPROC)putAndSortBinaryFile, this);
		AfxBeginThread((AFX_THREADPROC)setfilesProcededCount, this);
	}*/

	CoUninitialize();

	GetDlgItem(IDC_RADIO_ASC)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_DESC)->EnableWindow(TRUE);
}

void CCOMMFCClientDlg::createXML() {
	//CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
	MSXML::IXMLDOMDocument2Ptr pXMLDoc;
	HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument30));
	if (FAILED(hr))
	{
		AfxMessageBox(_T("Failed to create the XML class instance"));
		return;
	}
	if (pXMLDoc->loadXML(_T("<Parent></Parent>")) == VARIANT_FALSE)
	{
		return;
	}
	MSXML::IXMLDOMElementPtr pXMLRootElem = pXMLDoc->GetdocumentElement();

	MSXML::IXMLDOMProcessingInstructionPtr pXMLProcessingNode =
		pXMLDoc->createProcessingInstruction("xml", " version='1.0' encoding='UTF-8'");

	_variant_t vtObject;
	vtObject.vt = VT_DISPATCH;
	vtObject.pdispVal = pXMLRootElem;
	vtObject.pdispVal->AddRef();

	pXMLDoc->insertBefore(pXMLProcessingNode, vtObject);

	CString startDateCStr(startDateStr.c_str());
	CString startTimeCStr(startTimeStr.c_str());

	MSXML::IXMLDOMElementPtr pXMLChild1 = pXMLDoc->createElement(_T("Launch"));
	pXMLChild1 = pXMLRootElem->appendChild(pXMLChild1);

	MSXML::IXMLDOMElementPtr pXMLChild2 = pXMLDoc->createElement(_T("Date"));
	pXMLChild2->Puttext((_bstr_t)(startDateCStr));
	pXMLChild2 = pXMLChild1->appendChild(pXMLChild2);

	MSXML::IXMLDOMElementPtr pXMLChild3 = pXMLDoc->createElement(_T("Time"));
	pXMLChild3->Puttext((_bstr_t)(startTimeCStr));
	pXMLChild3 = pXMLChild1->appendChild(pXMLChild3);

	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::stringstream ss, ss_;
	std::tm bt, bt_;
	localtime_s(&bt, &in_time_t);
	localtime_s(&bt_, &in_time_t);
	ss << std::put_time(&bt, "%Y-%m-%d");
	ss_ << std::put_time(&bt_, "%X");

	std::string dateStr = ss.str();
	std::string timeStr = ss_.str();
	CString dateCStr(dateStr.c_str());
	CString timeCStr(timeStr.c_str());

	MSXML::IXMLDOMElementPtr pXMLChild4 = pXMLDoc->createElement(_T("Exit"));
	pXMLChild4 = pXMLRootElem->appendChild(pXMLChild4);

	MSXML::IXMLDOMElementPtr pXMLChild5 = pXMLDoc->createElement(_T("Date"));
	pXMLChild5->Puttext((_bstr_t)(dateCStr));
	pXMLChild5 = pXMLChild4->appendChild(pXMLChild5);

	MSXML::IXMLDOMElementPtr pXMLChild6 = pXMLDoc->createElement(_T("Time"));
	pXMLChild6->Puttext((_bstr_t)(timeCStr));
	pXMLChild6 = pXMLChild4->appendChild(pXMLChild6);

	_bstr_t PID = GetCurrentProcessId();
	MSXML::IXMLDOMElementPtr pXMLChild7 = pXMLDoc->createElement(_T("PID"));
	pXMLChild7->Puttext(PID);
	pXMLChild7 = pXMLRootElem->appendChild(pXMLChild7);

	MSXML::IXMLDOMDocument2Ptr loadXML;
	hr = loadXML.CreateInstance(__uuidof(DOMDocument30));
	if (FAILED(hr))
	{
		return;
	}

	if (loadXML->load(variant_t(_T("StyleSheet.xsl"))) == VARIANT_FALSE)
	{
		return;
	}

	MSXML::IXMLDOMDocument2Ptr pXMLFormattedDoc;
	hr = pXMLFormattedDoc.CreateInstance(__uuidof(DOMDocument30));

	CComPtr<IDispatch> pDispatch;
	hr = pXMLFormattedDoc->QueryInterface(IID_IDispatch, (void**)&pDispatch);
	if (FAILED(hr))
	{
		return;
	}

	_variant_t    vtOutObject;
	vtOutObject.vt = VT_DISPATCH;
	vtOutObject.pdispVal = pDispatch;
	vtOutObject.pdispVal->AddRef();

	hr = pXMLDoc->transformNodeToObject(loadXML, vtOutObject);

	MSXML::IXMLDOMNodePtr pXMLFirstChild = pXMLFormattedDoc->GetfirstChild();
	MSXML::IXMLDOMNamedNodeMapPtr pXMLAttributeMap = pXMLFirstChild->Getattributes();
	MSXML::IXMLDOMNodePtr pXMLEncodNode = pXMLAttributeMap->getNamedItem(_T("encoding"));
	pXMLEncodNode->PutnodeValue(_T("UTF-8"));

	UpdateData();
	CString sLocation = _T("Log.xml");
	hr = pXMLFormattedDoc->save(sLocation.AllocSysString());
	if (FAILED(hr))
	{
		return;
	}
}

void CCOMMFCClientDlg::OnBnClickedButtonBreak()
{
	stop = true;
	for(int i(0); i < 4; ++i)
		if(binaryFile[i] != nullptr)
			binaryFile[i]->stopSorting();
}


void CCOMMFCClientDlg::OnBnClickedRadioAsc()
{
	orderingMode = ascending;
}


void CCOMMFCClientDlg::OnBnClickedRadioDesc()
{
	orderingMode = descending;
}


void CCOMMFCClientDlg::OnBnClickedCancel()
{
	CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
	createXML();
	CoUninitialize();
	CDialogEx::OnCancel();
}
