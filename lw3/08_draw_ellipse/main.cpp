#define _USE_MATH_DEFINES
#include <cmath>
//
#include <GLFW/glfw3.h>
#include <chrono>
#include <stdexcept>

float _moveA = -3.0f;
float _moveB = 4.0f;
float _moveC = 0.0f;
float _angle1 = 0.0f;
float speed = 0.03f;
float pos = -1.0f;
bool f = false;

class GLFWInitializer final
{
public:
	GLFWInitializer()
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
	}

	GLFWInitializer(const GLFWInitializer&) = delete;
	GLFWInitializer& operator=(const GLFWInitializer&) = delete;

	~GLFWInitializer()
	{
		glfwTerminate();
	}
};

class BaseWindow
{
public:
	BaseWindow(int w, int h, const char* title)
		: m_window{ CreateWindow(w, h, title) }
	{
		if (!m_window)
		{
			throw std::runtime_error("Failed to create window");
		}
	}
	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void Run()
	{
		glfwMakeContextCurrent(m_window);
		OnRunStart();
		while (!glfwWindowShouldClose(m_window))
		{
			int w, h;
			glfwGetFramebufferSize(m_window, &w, &h);
			Draw(w, h);
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
		OnRunEnd();
	}

private:
	virtual void Draw(int width, int height) = 0;

	virtual void OnRunStart() {}
	virtual void OnRunEnd() {}

	static GLFWwindow* CreateWindow(int w, int h, const char* title)
	{
		return glfwCreateWindow(w, h, title, nullptr, nullptr);
	}
	GLFWwindow* m_window;
};

class Window : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void OnRunStart() override
	{
		// Задаем цвет очистки буфера кадра
		m_startTime = std::chrono::steady_clock::now();
	}

	void Draw(int width, int height) override
	{
		using namespace std::chrono;
		const auto currentTime = steady_clock::now();
		const auto timeSinceStart = currentTime - m_startTime;
		const auto phase = 0.2f;

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, width, height);
		SetupProjectionMatrix(width, height);
		//glVertex2f(-2.0f, 3.0f);
		SetupModelViewMatrix();
		//glEnd();
		glPushMatrix();
		glTranslatef(_moveA, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-0.85f, -0.1f);
		glVertex2f(-0.85f, 0.1f);
		glVertex2f(-0.5f, 0.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-0.5f, -0.25f);
		glVertex2f(-0.5f, 0.25f);
		glVertex2f(0.1f, 0.0f);
		//glVertex2f(0.3f, 0.8f);
		glEnd();

		glPopMatrix();

		glPushMatrix();
		glTranslatef(_moveB, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-0.85f, -0.1f);
		glVertex2f(-0.85f, 0.1f);
		glVertex2f(-1.2f, 0.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-1.2f, -0.25f);
		glVertex2f(-1.2f, 0.25f);
		glVertex2f(-1.8f, 0.0f);
		//glVertex2f(0.3f, 0.8f);
		glEnd();

		glPopMatrix();
	}

	static void FillEllipse(float xCenter, float yCenter, float rx, float ry, int points = 360)
	{
		const float step = static_cast<float>(2 * M_PI / points);

		// Эллипс представлет в виде "веера" из треугольников
		glBegin(GL_TRIANGLE_FAN);
		// Начальная точка веера располагается в центре эллипса
		glVertex2d(xCenter, yCenter);
		// Остальные точки - равномерно по его границе
		for (float angle = 0; angle <= 2 * M_PI; angle += step)
		{
			float a = (fabsf(static_cast<float>(angle - 2 * M_PI)) < 1e-5) ? 0 : angle;
			const float dx = rx * cosf(a);
			const float dy = ry * sinf(a);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();
	}

	static void SetupProjectionMatrix(int width, int height)
	{
		// Вычисляет матрицу ортографического преобразования такую, чтобы вписать квадратную область
		// [-1;+1] по обеим осям внутрь видового порта размером width*height пикселей
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		const double aspectRatio = double(width) / double(height);
		double viewWidth = 1.0;
		double viewHeight = viewWidth;
		if (aspectRatio > 1.0)
		{
			viewWidth = viewHeight * aspectRatio;
		}
		else
		{
			viewHeight = viewWidth / aspectRatio;
		}
		glOrtho(-viewWidth, viewWidth, -viewHeight, viewHeight, -1.0, 1.0);
	}

	static void SetupModelViewMatrix()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glRotated(phase * 360, 0.0, 0.0, 1.0);
		if (_moveA > 3.0f)
		{
			f = true;
			_moveA = -3.0;
		}
		if (_moveB < -3.0f)
		{
			f = false;
			_moveB = 4.0f;
		}
		if (!f)
		{
			_moveA += 0.0003f;
		}
		else
		{
			_moveB -= 0.0003f;
		}
	}
	std::chrono::steady_clock::time_point m_startTime;
	// Период вращения треугольника (за какое время треугольник делает полный оборот)
	const std::chrono::milliseconds ANIMATION_PERIOD = std::chrono::milliseconds{ 10000 };
};

int main()
{
	GLFWInitializer initGLFW;
	Window window{ 1500, 800, "Hello, ellipse" };
	window.Run();
}
