
// lw22.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы
#include <gdiplus.h>


// Clw22App:
// Сведения о реализации этого класса: lw22.cpp
//

class Clw22App : public CWinApp
{
public:
	Clw22App();

// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
protected:
	ULONG_PTR m_tokenGdiplus;
};

extern Clw22App theApp;
