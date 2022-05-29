#include "pch.h"
#include "Fence.h"
#include <iostream>
#include "TextureLoader.h"
constexpr size_t FACES_NUMBER = 26;


CFence::CFence(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	SetSideColor({ 134, 57, 29, 1 });
}


void CFence::Draw() const
{
	// Массив координат вершин
	if (!m_texture)
	{
		// Загружаем текстуру при первом вызове метода Draw()
		CTextureLoader loader;
		m_texture.Attach(loader.LoadTexture2D(L"flower.jpg"));
	}
	// Активизируем текстуру и материал
	glEnable(GL_TEXTURE_2D);
	m_texture.Bind();
	m_material.Activate();


	static float a = 0;
	static float vertices[36][3] = {
		{ 1.5, 0.0, -1.5 }, // 0
		{ 1.5, 0.0, 1.5 }, // 1
		{ 1.5, 0.3, 1.5 }, // 2
		{ 1.5, 0.3, -1.5 }, // 3
		{ 1.7, 0.0, 1.5 }, // 4
		{ 1.7, 0.0, -1.5 }, // 5
		{ 1.7, 0.3, -1.5 }, // 6
		{ 1.7, 0.3, 1.5 }, // 7
		{ 1.55, 0.33, -1.5}, // 8
		{ 1.55, 0.33, 1.5 }, // 9
		{ 1.65, 0.33, 1.5 }, // 10
		{ 1.65, 0.33, -1.5 }, // 11

		{ -1.5, 0.0, -1.5 }, // 12
		{ -1.5, 0.0, 1.5 }, // 13
		{ -1.5, 0.3, 1.5 }, // 14
		{ -1.5, 0.3, -1.5 }, // 15
		{ -1.7, 0.0, 1.5 }, // 16
		{ -1.7, 0.0, -1.5 }, // 17
		{ -1.7, 0.3, -1.5 }, // 18
		{ -1.7, 0.3, 1.5 }, // 19
		{ -1.55, 0.33, -1.5}, // 20
		{ -1.55, 0.33, 1.5 }, // 21
		{ -1.65, 0.33, 1.5 }, // 22
		{ -1.65, 0.33, -1.5 }, // 23

		{ -1.5, 0.0, -1.5 }, // 24
		{ 1.5, 0.0, -1.5 }, // 25
		{ 1.5, 0.3, -1.5 }, // 26
		{ -1.5, 0.3, -1.5 }, // 27
		{ 1.5, 0.0, -1.7 }, // 28
		{ -1.5, 0.0, -1.7 }, // 29
		{ -1.5, 0.3, -1.7 }, // 30
		{ 1.5, 0.3, -1.7 }, // 31
		{ -1.5, 0.33, -1.55}, // 32
		{ 1.5, 0.33, -1.55 }, // 33
		{ 1.5, 0.33, -1.65 }, // 34
		{ -1.5, 0.33, -1.65 }, // 35

	};

	// Массив координат граней
	static constexpr unsigned char faces[27][4] = {
		{0, 1, 2, 3},
		{4, 5, 6, 7},
		{8, 9, 10, 11},
		{3, 2, 9, 8},
		{7, 6, 11, 10},

		{13, 12, 15, 14},
		{17, 16, 19, 18},
		{21, 20, 23, 22},
		{14, 15, 20, 21},
		{18, 19, 22, 23},

		{24, 25, 26, 27},
		{28, 29, 30, 31},
		{32, 33, 34, 35},
		{27, 26, 33, 32},
		{31, 30, 35, 34},

		{5, 28, 31, 6},
		{6, 31, 34, 11},
		{11, 34, 33, 8},
		{8, 33, 3, 3},

		{29, 17, 18, 30},
		{30, 18, 23, 35},
		{35, 23, 20, 32},
		{32, 20, 27, 27},

		{1, 4, 7, 2},
		{2, 7, 10, 9},

		{16, 13, 14, 19},
		{19, 14, 21, 22},
	};

	static size_t const faceCount = sizeof(faces) / sizeof(*faces);
	float textures[faceCount][24] = {
		{0, 1, 10, 1, 10, 0, 0, 0},
		{0, 1, 10, 1, 10, 0, 0, 0},
		{0, 0.5, 10, 0.5, 10, 0, 0, 0},
		{0, 0.2, 10, 0.2, 10, 0, 0, 0},
		{0, 0.2, 10, 0.2, 10, 0, 0, 0},

		{0, 1, 10, 1, 10, 0, 0, 0},
		{0, 1, 10, 1, 10, 0, 0, 0},
		{0, 0.5, 10, 0.5, 10, 0, 0, 0},
		{0, 0.2, 10, 0.2, 10, 0, 0, 0},
		{0, 0.2, 10, 0.2, 10, 0, 0, 0},

		{0, 1, 10, 1, 10, 0, 0, 0},
		{0, 1, 10, 1, 10, 0, 0, 0},
		{0, 0.5, 10, 0.5, 10, 0, 0, 0},
		{0, 0.2, 10, 0.2, 10, 0, 0, 0},
		{0, 0.2, 10, 0.2, 10, 0, 0, 0},

		{0, 0.8, 1, 0.8, 1, 0, 0, 0 },
		{0, 0.3, 1, 0.3, 1, 0, 0, 0 },
		{0, 0.3, 1, 0.3, 1, 0, 0, 0 },
		{0, 0.3, 1, 0.3, 1, 0, 0, 0 },

		{0, 0.8, 1, 0.8, 1, 0, 0, 0 },
		{0, 0.3, 1, 0.3, 1, 0, 0, 0 },
		{0, 0.3, 1, 0.3, 1, 0, 0, 0 },
		{0, 0.3, 1, 0.3, 1, 0, 0, 0 },

		{0, 1.2, 1, 1.2, 1, 0, 0, 0 },
		{0, 0.1, 1, 0.1, 0.6, 0, 0.4, 0 },

		{0, 1.2, 1, 1.2, 1, 0, 0, 0 },
		{0, 0.1, 1, 0.1, 0.6, 0, 0.4, 0 },
	};
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	// Цвет вершины будет управлять диффузным и фоновым цветом материала
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specularColor));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	for (size_t face = 0; face < faceCount; ++face)
	{
		glColor4f(1, 0.5, 0.3, 1);
		const unsigned char* facePoints = faces[face];
		glm::vec3 p[4];
		float l[12], n[12];



		for (auto i = 0; i < 4; i++)
		{
			p[i] = glm::make_vec3(vertices[facePoints[i]]) * m_size * 0.2f;

		}

		auto v01 = p[1] - p[0];
		auto v02 = p[2] - p[0];
		auto normal2 = glm::normalize(glm::cross(v01, v02));
		for (auto i = 0; i < 4; i++)
		{
			l[i * 3] = p[i][0];
			l[i * 3 + 1] = p[i][1];
			l[i * 3 + 2] = p[i][2];
			n[i * 3] = p[i][0] + normal2[0];
			n[i * 3 + 1] = p[i][1] + normal2[1];
			n[i * 3 + 2] = p[i][2] + normal2[2];
			glNormalPointer(GL_FLOAT, 0, n);

		}

		glTexCoordPointer(2, GL_FLOAT, 0, textures[face]);

		glVertexPointer(3, GL_FLOAT, 0, l);
		glDrawArrays(GL_QUADS, 0, 4);
	}
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

void CFence::SetSideColor(const glm::vec4& color)
{
	m_sideColors = color;
}

void CFence::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void CFence::SetShininess(float shininess)
{
	m_shininess = shininess;
}
