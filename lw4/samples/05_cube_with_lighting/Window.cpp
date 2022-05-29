#include "pch.h"
#include "Window.h"
#include "DirectLight.h"

namespace
{
// Угол обзора по вертикали
constexpr double FIELD_OF_VIEW = 80*M_PI / 180.0;
// Размер стороны куба
constexpr double CUBE_SIZE = 0.3;
constexpr double CUBE_SIZE_2 = 0.1;
constexpr size_t FACES_NUMBER = 26;

constexpr double Z_NEAR = 0.4;
constexpr double Z_FAR = 50;

// Ортонормируем матрицу 4*4 (это должна быть аффинная матрица)
glm::dmat4x4 Orthonormalize(const glm::dmat4x4& m)
{
	// Извлекаем подматрицу 3*3 из матрицы m и ортонормируем её
	const auto normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
	// Заменяем 3 столбца исходной матрицы
	return {
		glm::dvec4{ normalizedMatrix[0], 0.0 },
		glm::dvec4{ normalizedMatrix[1], 0.0 },
		glm::dvec4{ normalizedMatrix[2], 0.0 },
		m[3]
	};
}

} // namespace

Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_rhombicuboctahedron(CUBE_SIZE)
	, m_rhombicuboctahedron2(CUBE_SIZE_2)
{
#if 1
	float r = 1, g = 0, b = 0;
	size_t count = 0;
	glm::vec4 sideColors[26];
	for (size_t i = 0; i < FACES_NUMBER; i++)
	{
		r = (g >= 1.0f) && (b <= 0.0f) ? r - 0.2 : r;
		r = (g <= 0.0f) && (b >= 1.0f) ? r + 0.2 : r;
		g = (r <= 0.0f) && (b >= 1.0f) ? g - 0.2 : g;
		g = (r >= 1.0f) && (b <= 0.0f) ? g + 0.2 : g;
		b = (r >= 1.0f) && (g <= 0.0f) ? b - 0.2 : b;
		b = (r <= 0.0f) && (g >= 1.0f) ? b + 0.2 : b;
		sideColors[i] = {r, g, b, 1};
	}
	for (size_t i = 0; i < FACES_NUMBER; i++)
	{
		m_rhombicuboctahedron.SetSideColor(i, sideColors[count]);
		count += 7;
		if (count >= FACES_NUMBER)
		{
			count = count - FACES_NUMBER;
		}
	}
#else
	for (size_t i = 0; i < FACES_NUMBER; i++)
	{
		m_cube.SetSideColor(i, { 1, 1, 1, 1 });
}
#endif
	m_rhombicuboctahedron.SetSpecularColor({ 1, 1, 1, 1 });
	m_rhombicuboctahedron.SetShininess(4.0f);
}

void Window::OnMouseButton(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		m_leftButtonPressed = (action & GLFW_PRESS) != 0;
	}
}

void Window::OnMouseMove(double x, double y)
{
	const glm::dvec2 mousePos{ x, y };
	if (m_leftButtonPressed)
	{
		const auto windowSize = GetFramebufferSize();

		const auto mouseDelta = mousePos - m_mousePos;
		const double xAngle = mouseDelta.y * M_PI / windowSize.y;
		const double yAngle = mouseDelta.x * M_PI / windowSize.x;
		RotateCamera(xAngle, yAngle);
	}
	m_mousePos = mousePos;
}

// Вращаем камеру вокруг начала координат
void Window::RotateCamera(double xAngleRadians, double yAngleRadians)
{
	const glm::dvec3 xAxis{
		m_cameraMatrix[0][0], m_cameraMatrix[1][0], m_cameraMatrix[2][0]
	};
	const glm::dvec3 yAxis{
		m_cameraMatrix[0][1], m_cameraMatrix[1][1], m_cameraMatrix[2][1]
	};
	m_cameraMatrix = glm::rotate(m_cameraMatrix, xAngleRadians, xAxis);
	m_cameraMatrix = glm::rotate(m_cameraMatrix, yAngleRadians, yAxis);

	m_cameraMatrix = Orthonormalize(m_cameraMatrix);
}

void Window::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	const auto proj = glm::perspective(FIELD_OF_VIEW, aspect, Z_NEAR, Z_FAR);
	glLoadMatrixd(&proj[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

void Window::OnRunStart()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Включаем режим отбраковки граней
	glEnable(GL_CULL_FACE);
	// Отбраковываться будут нелицевые стороны граней
	//glCullFace(GL_FRONT);


	glCullFace(GL_BACK);
	// Сторона примитива считается лицевой, если при ее рисовании
	// обход верших осуществляется против часовой стрелки
	glFrontFace(GL_CCW);

	// Включаем тест глубины для удаления невидимых линий и поверхностей
	glEnable(GL_DEPTH_TEST);

	// Направление на источник света (совпадает с позицией наблюдателя)
	DirectLight light{ { 0.0f, 0.0f, 1.0f } };
	light.SetDiffuseIntensity({ 0.5f, 0.5f, 0.5f, 1.0f });
	light.SetAmbientIntensity({ 0.0f, 0.0f, 0.0f, 1.0f });
	light.SetSpecularIntensity({ 0.3f, 0.3f, 0.3f, 1.0f });
	light.Apply(GL_LIGHT0);

}

void Window::Draw(int width, int height)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	SetupCameraMatrix();

	m_rhombicuboctahedron.Draw();
	glPushMatrix();
	glTranslatef(0.6, 0.6, 0.6);
	m_rhombicuboctahedron2.Draw();
	glPushMatrix();

}

void Window::SetupCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}
