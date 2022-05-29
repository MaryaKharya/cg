#include "pch.h"
#include <iostream>
#include "Facade.h"
#include "TextureLoader.h"
constexpr size_t FACES_NUMBER = 26;


CFacade::CFacade(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	SetSideColor({ 134, 57, 29, 1 });
}


void CFacade::Draw() const
{
	// Массив координат вершин
	if (!m_texture)
	{
		// Загружаем текстуру при первом вызове метода Draw()
		CTextureLoader loader;
		m_texture.Attach(loader.LoadTexture2D(L"1.jpg"));
	}
	// Активизируем текстуру и материал
	glEnable(GL_TEXTURE_2D);
	m_texture.Bind();
	m_material.Activate();


	static float a = 0;
	static float vertices[36][3] = {
		{ -0.4, 0.1, -1 }, // 0
		{ 0.2, 0.1, -1 }, // 1
		{ 0.2, 0.1, -0.8 }, // 2
		{ 0.9, 0.1, -0.8 }, // 3
		{ 0.9, 0.1, -0.6 }, // 4
		{ 1, 0.1, -0.4 }, // 5
		{ 1, 0.1, -0.2 }, // 6
		{ 0.9, 0.1, 0 }, // 7
		{ 0.9, 0.1, 0.8 }, // 8
		{ 0.5, 0.1, 0.8 }, // 9
		{ 0.5, 0.1, 1 }, // 10
		{ 0, 0.1, 1 }, // 11
		{ 0, 0.1, 0.6 }, // 12
		{ -0.4, 0.1, 0.6 }, // 13
		{ -0.4, 0.1, 0.1 }, // 14
		{ -1, 0.1, 0.1 }, // 15

		{ -0.4, 1, -1 }, // 16
		{ 0.2, 1, -1 }, // 17
		{ 0.2, 1, -0.8 }, // 18
		{ 0.9, 1, -0.8 }, // 19
		{ 0.9, 1, -0.6 }, // 20
		{ 1, 1, -0.4 }, // 21
		{ 1, 1, -0.2 }, // 22
		{ 0.9, 1, 0 }, // 23
		{ 0.9, 1, 0.8 }, // 24
		{ 0.5, 1, 0.8 }, // 25
		{ 0.5, 1, 1 }, // 26
		{ 0, 1, 1 }, // 27
		{ 0, 1, 0.6 }, // 28
		{ -0.4, 1, 0.6 }, // 29
		{ -0.4, 1, 0.1 }, // 30

		{ -0.4, 0.4, 0.1 }, // 31
		{ -1, 0.4, 0.1 }, // 32
		{ -1, 0.4, -1 }, // 33
		{ -0.4, 0.4, -1 }, // 34
		{-1, 0.1, -1}, //35

	};	

	// Массив координат граней
	static constexpr unsigned char faces[18][4] = {
		{1, 0, 16, 17},
		{2, 1, 17, 18},
		{3, 2, 18, 19},
		{4, 3, 19, 20},
		{5, 4, 20, 21},
		{6, 5, 21, 22},
		{7, 6, 22, 23},
		{8, 7, 23, 24},
		{9, 8, 24, 25},
		{10, 9, 25, 26},
		{11, 10, 26, 27},
		{12, 11, 27, 28},
		{13, 12, 28, 29},
		{0, 13, 29, 16},
		{15, 14, 31, 32},
		{35, 15, 32, 33},
		{0, 35, 33, 34},
	};

	static size_t const faceCount = sizeof(faces) / sizeof(*faces);
	float textures[faceCount][24] = { 
		{0, 1, 0.6, 1, 0.6, 0, 0, 0},   
		{0, 1, 0.2, 1, 0.2, 0, 0, 0},   
		{0, 1, 0.8, 1, 0.8, 0, 0, 0 },
		{0, 1, 0.2, 1, 0.2, 0, 0, 0}, 
		{0, 1, 0.2, 1, 0.2, 0, 0, 0}, 
		{0, 1, 0.2, 1, 0.2, 0, 0, 0}, 
		{0, 1, 0.2, 1, 0.2, 0, 0, 0},
		{0, 1, 0.8, 1, 0.8, 0, 0, 0 },
		{0, 1, 0.4, 1, 0.4, 0, 0, 0 },
		{0, 1, 0.2, 1, 0.2, 0, 0, 0 },
		{0, 1, 0.5, 1, 0.5, 0, 0, 0 },
		{0, 1, 0.4, 1, 0.4, 0, 0, 0 },
		{0, 1, 0.4, 1, 0.4, 0, 0, 0 },
		{0, 1, 1.5, 1, 1.5, 0, 0, 0 },
		{0, 0.3, 0.7, 0.3, 0.7, 0, 0, 0 },
		{0, 0.3, 1.2, 0.3, 1.2, 0, 0, 0 },
		{0, 0.3, 0.7, 0.3, 0.7, 0, 0, 0 },
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
		// устанавливаем диффузный и фоновый цвет грани
		glColor4f(1, 0.8, 0.8, 1);
		const unsigned char* facePoints = faces[face];
		glm::vec3 p[4];
		float l[12], n[12];



		for (auto i = 0; i < 4; i++)
		{
			p[i] = glm::make_vec3(vertices[facePoints[i]]) * m_size * 0.2f;

		}

		auto v01 = p[1] - p[0];
		auto v02 = p[2] - p[0];
		auto n2 = glm::normalize(glm::cross(v01, v02));
		for (auto i = 0; i < 4; i++)
		{
			l[i * 3] = p[i][0];
			l[i * 3 + 1] = p[i][1];
			l[i * 3 + 2] = p[i][2];
			n[i * 3] = p[i][0] + n2[0];
			n[i * 3 + 1] = p[i][1] + n2[1];
			n[i * 3 + 2] = p[i][2] + n2[2];
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

void CFacade::SetSideColor(const glm::vec4& color)
{
	m_sideColors = color;
}

void CFacade::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void CFacade::SetShininess(float shininess)
{
	m_shininess = shininess;
}
