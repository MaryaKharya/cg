#include "pch.h"
#include "Lamp.h"
#include "TextureLoader.h"
#include "DirectLight.h"

constexpr size_t FACES_NUMBER = 26;


CLamp::CLamp(float size)
	: m_size(size)
{
	SetSideColor({ 134, 57, 29, 1 });
}

void CLamp::Draw()
{
	static float x = -0.13, y = 0.1, z = 0.9, y2 = 0.4;
	static float vertices3[8][3] = {
	{x, y, z}, //0
	{x, y2, z}, //1
	{x, y2, z + 0.04}, //2
	{x, y, z + 0.04}, //3

	{x - 0.04, y, z}, //4
	{x - 0.04, y2, z}, //5
	{x - 0.04, y2, z + 0.04}, //6
	{x - 0.04, y, z + 0.04}, //7
	};

	// Массив координат граней
	static constexpr unsigned char faces3[5][4] = {
		{0, 1, 2, 3},
		{7, 6, 5, 4},
		{3, 2, 6, 7},
		{4, 5, 1, 0},
		{2, 1, 5, 6},
	};

	static float translate[9][3] = {
		{-0.7 * m_size * 0.2f, 0, 0.4 * m_size * 0.2f},
		{1 * m_size * 0.2f, 0, 0.4 * m_size * 0.2f},
		{-1 * m_size * 0.2f, 0, 0.2 * m_size * 0.2f},
		{1.3 * m_size * 0.2f, 0, 0.2 * m_size * 0.2f},
	};

	static float scale[9][3] = {
		{1, 0.4, 1},
		{1, 0.4, 1},
		{1, 0.4, 1},
		{1, 0.4, 1},
	};

	static size_t const faceCount = sizeof(faces3) / sizeof(*faces3);
	for (size_t f = 0; f < 9; ++f)
	{
		glPushMatrix();
		glColor4f(1, 1, 1, 1);
		glScaled(scale[f][0], scale[f][1], scale[f][2]);
		glTranslated(translate[f][0], translate[f][1], translate[f][2]);
		for (size_t face = 0; face < faceCount; ++face)
		{
			const unsigned char* facePoints = faces3[face];
			glm::vec3 p[4];
			for (auto i = 0; i < 4; i++)
			{
				p[i] = glm::make_vec3(vertices3[facePoints[i]]) * m_size * 0.2f;

			}

			// Вычисляем нормаль
			// векторное произведение его смежных сторон
			auto v01 = p[1] - p[0];
			auto v02 = p[2] - p[0];
			auto normal = glm::normalize(glm::cross(v01, v02));

			glNormal3fv(glm::value_ptr(normal));

			glBegin(GL_QUADS);
			// устанавливаем диффузный и фоновый цвет грани
			for (auto i = 0; i < 4; i++)
			{
				glVertex3fv(glm::value_ptr(p[i]));
			}
			glEnd();
		}

		glPopMatrix();
	}
}


void CLamp::SetSideColor(const glm::vec4& color)
{
	m_sideColors = color;
}

void CLamp::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void CLamp::SetShininess(float shininess)
{
	m_shininess = shininess;
}
