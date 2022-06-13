#include "pch.h"
#include "MyApplication.h"
#include "ShaderLoader.h"
#include "ShaderCompiler.h"
#include "ProgramLinker.h"
#include "Vector3.h"

CMyApplication::CMyApplication(const char* title, int width, int height)
	:CGLApplication(title, width, height)
{
}

CMyApplication::~CMyApplication(void)
{
}

void CMyApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
	glColor3f(1, 1, 1);

	// Задаем параметры камеры
	glLoadIdentity();
	gluLookAt(
		5, 4, 5,
		0, 0.5, 0,
		0, 1, 0);

	InitShaders();
}

void CMyApplication::InitShaders()
{
	// Создаем загрузчик шейдеров
	CShaderLoader loader;
	// И загружаем с его помощью вершинный и фрагментный шейдеры
	CShader vertexShader =
		loader.LoadShader(GL_VERTEX_SHADER, "checker.vert");
	CShader fragmentShader =
		loader.LoadShader(GL_FRAGMENT_SHADER, "checker.fsh");

	Sleep(1);
	LARGE_INTEGER tick0;
	QueryPerformanceCounter(&tick0);

	// Создаем компилятор
	CShaderCompiler compiler;
	// и запускаем компиляцию шейдеров
	compiler.CompileShader(vertexShader);
	compiler.CompileShader(fragmentShader);

	LARGE_INTEGER tick1;
	QueryPerformanceCounter(&tick1);

	std::cout << "Compilation duration: " << tick1.QuadPart - tick0.QuadPart << "\n";

	// Создаем программу и присоединяем к ней шейдеры
	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);

	LARGE_INTEGER tick2;
	QueryPerformanceCounter(&tick2);
	std::cout << "Attach shaders duration: " << tick2.QuadPart - tick1.QuadPart << "\n";

	// Проверяем состояние скомпилированности шейдеров.
	// Если хотя бы один из шейдеров скомпилировался с ошибкой
	// будет выброшено исключение
	compiler.CheckStatus();
	// Все нормально, шейдеры скомпилировались без проблем

	LARGE_INTEGER tick3;
	QueryPerformanceCounter(&tick3);
	std::cout << "Compilation checking status duration: " << tick3.QuadPart - tick2.QuadPart << "\n";

	// Создаем компоновщик,
	CProgramLinker linker;
	// компонуем программу с его помощью
	linker.LinkProgram(m_program);

	LARGE_INTEGER tick4;
	QueryPerformanceCounter(&tick4);
	std::cout << "Link duration: " << tick4.QuadPart - tick3.QuadPart << "\n";

	// Проверяем состояние скомпонованности программ
	// Если при компоновке возникла ошибка, то
	// будет выброшено исключение
	linker.CheckStatus();
	// Все нормально

	LARGE_INTEGER tick5;
	QueryPerformanceCounter(&tick5);
	std::cout << "Link checking status duration: " << tick5.QuadPart - tick4.QuadPart << "\n";
}

void CMyApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);

	int timeLocation = glGetUniformLocation(m_program, "u_time");
	glUniform1f(timeLocation, m_time);

	// Рисуем квадрат

	CVector3f startPos = { -1, 0, -1 };
	glColor4d(0, 0, 0, 1);
	for (int i = 0; i < 20; ++i)
	{
		CVector3f currPos = startPos;
		currPos.x += 0.1f * i;

		for (int j = 0; j < 20; ++j)
		{
			glLineWidth(3);
			glBegin(GL_LINE_LOOP);
			{
				glTexCoord3f(0, 0, 0);
				glVertex3f(currPos.x, currPos.y, currPos.z);

				glTexCoord3f(1, 0, 0);
				glVertex3f(currPos.x + 0.1, currPos.y, currPos.z);

				glTexCoord3f(1, 0, 1);
				glVertex3f(currPos.x + 0.1, currPos.y, currPos.z + 0.1);

				glTexCoord3f(0, 0, 1);
				glVertex3f(currPos.x, currPos.y, currPos.z + 0.1);
			}
			glEnd();

			currPos.z += 0.1f;
		}

	}

	glUseProgram(0);
	UpdateTime();
}


void CMyApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-aspect, +aspect, -1, 1, 0, 10);
	glMatrixMode(GL_MODELVIEW);
}

void CMyApplication::UpdateTime()
{
	m_time += 0.01;
	glutPostRedisplay();
}
