#include "pch.h"
#include "Rhombicuboctahedron.h"


constexpr size_t FACES_NUMBER = 26;


Rhombicuboctahedron::Rhombicuboctahedron(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	for (size_t i = 0; i < FACES_NUMBER; i++)
	{
		SetSideColor(i, defaultColor);
	}
}


void Rhombicuboctahedron::Draw() const
{
	// Массив координат вершин
	static float a = 1 + (float)sqrt(2);
	static float vertices[26][3] = {
		{ -1, a, -1 }, // 0
		{ +1, a, -1 }, // 1
		{ +1, a, +1 }, // 2
		{ -1, a, +1 }, // 3

		{ -a, +1, -1 }, // 4
		{ -a, +1, +1 }, // 5
		{ -1, +1, -a }, // 6
		{ +1, +1, -a }, // 7
		{ +a, +1, -1 }, // 8
		{ +a, +1, +1 }, // 9
		{ -1, +1, +a }, // 10
		{ +1, +1, +a }, // 11

		{ -a, -1, -1 }, // 12
		{ -a, -1, +1 }, // 13
		{ -1, -1, -a }, // 14
		{ +1, -1, -a }, // 15
		{ +a, -1, -1 }, // 16
		{ +a, -1, +1 }, // 17
		{ -1, -1, +a }, // 18
		{ +1, -1, +a }, // 19

		{ -1, -a, -1 }, // 20
		{ +1, -a, -1 }, // 21
		{ +1, -a, +1 }, // 22
		{ -1, -a, +1 }, // 23
	};

	// Массив координат граней
	static constexpr unsigned char faces[26][4] = {
		{ 3, 2, 1, 0},
		{ 4, 5, 3, 0},
		{ 6, 0, 1, 7},
		{ 1, 2, 9, 8},
		{ 2, 3, 10, 11},

		{ 5, 4, 12, 13},
		{ 6, 7, 15, 14},
		{ 17, 16, 8, 9},
		{ 18, 19, 11, 10},

		{ 4, 6, 14, 12},
		{ 7, 8, 16, 15},
		{ 9, 11, 19, 17},
		{ 10, 5, 13, 18},

		{ 13, 12, 20, 23},
		{ 14, 15, 21, 20},
		{ 16, 17, 22, 21},
		{ 19, 18, 23, 22},
		{ 20, 21, 22, 23},

		{ 0, 6, 4},
		{ 1, 8, 7},
		{ 2, 11, 9},
		{ 3, 5, 10},
		{ 20, 12, 14},
		{ 21, 15, 16},
		{ 22, 17, 19},
		{ 23, 18, 13},
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glEnable(GL_COLOR_MATERIAL);
	// Цвет вершины будет управлять диффузным и фоновым цветом материала
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specularColor));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
	for (size_t face = 0; face < faceCount - 8; ++face)
	{
		glBegin(GL_QUADS);
		// устанавливаем диффузный и фоновый цвет грани
		glColor4fv(glm::value_ptr(m_sideColors[face]));
		const unsigned char* facePoints = faces[face];
		glm::vec3 p[4];
		for (auto i = 0; i < 4; i++)
		{
			p[i] = glm::make_vec3(vertices[facePoints[i]]) * m_size;
		}

		// векторное произведение его смежных сторон
		auto v01 = p[1] - p[0];
		auto v02 = p[2] - p[0];
		auto normal = glm::normalize(glm::cross(v01, v02));

		glNormal3fv(glm::value_ptr(normal));
		for (auto i = 0; i < 4; i++)
		{
			glVertex3fv(glm::value_ptr(p[i]));
		}
		glEnd();
	}
	for (size_t face = faceCount - 8; face < faceCount; ++face)
	{
		glBegin(GL_TRIANGLES);
		// устанавливаем диффузный и фоновый цвет грани
		glColor4fv(glm::value_ptr(m_sideColors[face]));
		const unsigned char* facePoints = faces[face];
		glm::vec3 p[3];
		for (auto i = 0; i < 3; i++)
		{
			p[i] = glm::make_vec3(vertices[facePoints[i]]) * m_size;
		}

		// Вычисляем нормаль к грани куба через
		// векторное произведение его смежных сторон
		auto v01 = p[1] - p[0];
		auto v02 = p[2] - p[0];
		auto normal = glm::normalize(glm::cross(v01, v02));

		glNormal3fv(glm::value_ptr(normal));
		for (auto i = 0; i < 3; i++)
		{
			glVertex3fv(glm::value_ptr(p[i]));
		}
		glEnd();
	}
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glColor4f(0, 0, 0, 1);
	glLineWidth(3);
	for (size_t face = 0; face < faceCount - 8; ++face)
	{
		glBegin(GL_LINE_LOOP);
		const unsigned char* facePoints = faces[face];
		glm::vec3 p[4];
		for (auto i = 0; i < 4; i++)
		{
			p[i] = glm::make_vec3(vertices[facePoints[i]]) * m_size;
		}
		auto v01 = p[1] - p[0];
		auto v02 = p[2] - p[0];
		auto normal = glm::normalize(glm::cross(v01, v02));

		glNormal3fv(glm::value_ptr(normal));
		for (auto i = 0; i < 4; i++)
		{
			glVertex3fv(glm::value_ptr(p[i]));
		}
		glEnd();
	}
}

void Rhombicuboctahedron::SetSideColor(size_t index, const glm::vec4& color)
{
	//unsigned index = static_cast<unsigned>(side);
	m_sideColors[index] = color;
}

void Rhombicuboctahedron::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void Rhombicuboctahedron::SetShininess(float shininess)
{
	m_shininess = shininess;
}
