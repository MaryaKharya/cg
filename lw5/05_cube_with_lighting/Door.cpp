#include "pch.h"
#include "Door.h"
#include "TextureLoader.h"
#include "DirectLight.h"
constexpr size_t FACES_NUMBER = 26;


CDoor::CDoor(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	SetSideColor({ 134, 57, 29, 1 });
}


void CDoor::Draw() const
{
	// Массив координат вершин
	if (!m_texture)
	{
		// Загружаем текстуру при первом вызове метода Draw()
		CTextureLoader loader;
		m_texture.Attach(loader.LoadTexture2D(L"door.jpg"));
	}
	// Активизируем текстуру и материал планеты
	glEnable(GL_TEXTURE_2D);
	m_texture.Bind();
	m_material.Activate();


	static float a = 0;
	static float vertices[16][3] = {
		{ -0.2, 0.1, 0.61 }, // 0
		{ -0.2, 0.3, 0.61 }, // 1
		{ -0.3, 0.3, 0.61 }, // 2
		{ -0.3, 0.1, 0.61 }, // 3

		{ 0.4, 0.1, -0.81 }, // 4
		{ 0.4, 0.3, -0.81 }, // 5
		{ 0.5, 0.3, -0.81 }, // 6
		{ 0.5, 0.1, -0.81 }, // 7

		{ -0.8, 0, -1.01 }, // 8
		{ -0.8, 0.2, -1.01 }, // 9
		{ -0.9, 0.2, -1.01 }, // 10
		{ -0.9, 0, -1.01 }, // 11

		{ -0.5, 0, 0.11 }, // 12
		{ -0.5, 0.27, 0.11 }, // 13
		{ -0.9, 0.27, 0.11 }, // 14
		{ -0.9, 0, 0.11 }, // 15



	};

	// Массив координат граней
	static constexpr unsigned char faces[4][4] = {
		{0, 1, 2, 3},
		{4, 5, 6, 7},
		{11, 10, 9, 8},
		{12, 13, 14, 15},
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);
	float textures[faceCount][8] = {
		{ -0.6, 1, 1, 1, 1, 0, -0.6, 0 },
		{ -0.6, 1, 1, 1, 1, 0, -0.6, 0 },
		{ -0.6, 1, 1, 1, 1, 0, -0.6, 0 },
		{ 0, 2, 1, 2, 1, 0, 0, 0 }
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
		glColor4f(1, 1, 1, 1);
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

void CDoor::SetSideColor(const glm::vec4& color)
{
	m_sideColors = color;
}

void CDoor::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void CDoor::SetShininess(float shininess)
{
	m_shininess = shininess;
}
