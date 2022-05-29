#define _USE_MATH_DEFINES
#include <cmath>
//
#include <chrono>
#include <stdexcept>

#include "CMyApplication.h"

// Создаем экземпляр нашего приложения
CMyApplication app("test", 1000, 600);

int main()
{
	app.MainLoop();

	return 0;
}
