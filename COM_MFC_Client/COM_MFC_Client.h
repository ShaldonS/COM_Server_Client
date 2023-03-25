
// COM_MFC_Client.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CCOMMFCClientApp:
// Сведения о реализации этого класса: COM_MFC_Client.cpp
//

class CCOMMFCClientApp : public CWinApp
{
public:
	CCOMMFCClientApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnUpdateMfceditbrowse1();
};

extern CCOMMFCClientApp theApp;
