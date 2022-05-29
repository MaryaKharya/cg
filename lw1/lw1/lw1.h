
// lw1.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// Clw1App:
// Сведения о реализации этого класса: lw1.cpp
//

class Clw1App : public CWinApp
{
public:
	Clw1App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern Clw1App theApp;
