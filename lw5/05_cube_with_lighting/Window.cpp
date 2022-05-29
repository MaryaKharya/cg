#include "pch.h"
#include "Window.h"
#include "DirectLight.h"
#include <iostream>

namespace
{
// Угол обзора по вертикали
constexpr double FIELD_OF_VIEW = 19 * M_PI / 180.0;
// Размер стороны куба
constexpr double CUBE_SIZE = 1;
constexpr size_t FACES_NUMBER = 26;

constexpr double Z_NEAR = 0.1;
constexpr double Z_FAR = 10;

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
	, m_skyBox(CUBE_SIZE)
	, m_foundation(CUBE_SIZE)
{
	m_cameraMatrix = glm::translate(m_cameraMatrix, glm::dvec3(0.0f, -0.2f, 0.0f));
#if 1
	float r = 1, g = 0, b = 0;
	size_t count = 0;
	glm::vec4 sideColors[26];
	for (size_t i = 0; i < FACES_NUMBER; i++)
	{
		m_foundation.SetSideColor(i, sideColors[count]);
		//m_facade.SetSideColor({ 1, 1, 1, 1});
		m_roof.SetSideColor({ 1, 0.98, 0.91, 1});
		m_skyBox.SetSideColor({ 1, 1, 1, 1 });
		m_lamp.SetSideColor({ 1, 1, 1, 1 });
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
	//m_rhombicuboctahedron.SetSpecularColor({ 1, 1, 1, 1 });
	//m_rhombicuboctahedron.SetShininess(4.0f);
	m_foundation.SetSpecularColor({ 1, 1, 1, 1 });
	m_foundation.SetShininess(4.0f);
	m_facade.SetSpecularColor({ 0, 0, 0, 1 });
	m_facade.SetShininess(4.0f);
	m_roof.SetSpecularColor({ 1, 1, 1, 1 });
	m_roof.SetShininess(4.0f);
	m_door.SetSpecularColor({ 1, 1, 1, 1 });
	m_door.SetShininess(4.0f);
	m_window.SetSpecularColor({ 1, 1, 1, 1 });
	m_window.SetShininess(4.0f);
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
		std::cout << xAngle << " " << yAngle << "\n";
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
	m_angleX += xAngleRadians;
	m_angleY += yAngleRadians;

	m_cameraMatrix = glm::rotate(m_cameraMatrix, yAngleRadians, yAxis);
	std::cout << m_cameraMatrix[0][0] << " " << m_cameraMatrix[1][0] << " " << m_cameraMatrix[2][0] << "\n";
	std::cout << m_cameraMatrix[0][1] << " " << m_cameraMatrix[1][1] << " " << m_cameraMatrix[2][1] << "\n";

	if (m_angleX <= 0)
	{
		m_angleX = 0;
	}
	else if (m_angleX >= M_PI/2)
	{
		m_angleX = M_PI/2;
	}
	m_cameraMatrix = glm::rotate(m_cameraMatrix, xAngleRadians, xAxis);


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
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);

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

}

void Window::Draw(int width, int height)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraMatrix();
	m_skyBox.Draw();
	m_lamp.Draw();
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	// Направление на источник света (совпадает с позицией наблюдателя)
	DirectLight light{ { 0.1, 0.7f, -0.3f }};
	//light.SetDirection({ 0.0f, 1.0f, 1.0f })
	light.SetDiffuseIntensity({ 0.52, 0.34, 0.14, 1 });
	light.SetAmbientIntensity({ 0.0f, 0.1f, 0.0f, 1.0f });
	light.SetSpecularIntensity({ 0.0f, 0.0f, 0.0f, 1.0f });
	light.Apply(GL_LIGHT0);

	DirectLight light2{ { 0.8, 0, 1.4 } };
	light2.SetDiffuseIntensity({ 0.65, 0.75, 1, 1.0f });
	light2.SetAmbientIntensity({ 0.0f, 0.0f, 0.0f, 1.0f });
	light2.SetSpecularIntensity({ 0, 0, 0, 1.0f });
	light2.Apply(GL_LIGHT1);

	DirectLight light3{ { 0.5, 0, 1.2 } };
	light3.SetDiffuseIntensity({ 0.65, 0.75, 1, 1.0f });
	light3.SetAmbientIntensity({ 0.0f, 0.0f, 0.0f, 1.0f });
	light3.SetSpecularIntensity({ 0, 0, 0, 1.0f });
	light3.Apply(GL_LIGHT2);

	DirectLight light4{ { -0.3, 0, 1.2 } };
	light4.SetDiffuseIntensity({ 0.65, 0.75, 1, 1.0f });
	light4.SetAmbientIntensity({ 0.0f, 0.0f, 0.0f, 1.0f });
	light4.SetSpecularIntensity({ 0, 0, 0, 1.0f });
	light4.Apply(GL_LIGHT3);

	DirectLight light5{ { -0.5, 0, 1.2 } };
	light5.SetDiffuseIntensity({ 0.65, 0.75, 1, 1.0f });
	light5.SetAmbientIntensity({ 0.0f, 0.0f, 0.0f, 1.0f });
	light5.SetSpecularIntensity({ 0, 0, 0, 1.0f });
	light5.Apply(GL_LIGHT4);

	glDisable(GL_CULL_FACE);
	m_foundation.Draw();
	m_roof.Draw();
	m_door.Draw();
	m_window.Draw();
	m_facade.Draw();
	m_fence.Draw();
	m_floor.Draw();
}

void Window::SetupCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}
