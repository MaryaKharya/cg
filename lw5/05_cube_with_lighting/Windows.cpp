#include "pch.h"
#include "Windows.h"
#include "TextureLoader.h"

constexpr size_t FACES_NUMBER = 26;


CWindows::CWindows(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	SetSideColor({ 134, 57, 29, 1 });
}

void CWindows::DrawWideWindow()
{
	if (!m_texture)
	{
		// Загружаем текстуру при первом вызове метода Draw()
		CTextureLoader loader;
		m_texture.Attach(loader.LoadTexture2D(L"window.png"));
	}
	glEnable(GL_TEXTURE_2D);
	m_texture.Bind();
	m_material.Activate();

	// Массив координат вершин
	static float x = -0.13, y = 0.1, z = 0.9, y2 = 0.4;
	static float verticesWindow[50][3] = {
	{0.6, 0.2, 0.81}, //0
	{0.8, 0.2, 0.81}, //1
	{0.8, 0.35, 0.81}, //2
	{0.6, 0.35, 0.81}, //3

	{0.6, 0.7, 0.81}, //4
	{0.8, 0.7, 0.81}, //5
	{0.8, 0.85, 0.81}, //6
	{0.6, 0.85, 0.81}, //7

	{0, 0.7, -1.01}, //8
	{-0.2, 0.7, -1.01}, //9
	{-0.2, 0.85, -1.01}, //10
	{0, 0.85, -1.01}, //11

	{0, 0.2, -1.01}, //12
	{-0.2, 0.2, -1.01}, //13
	{-0.2, 0.35, -1.01}, //14
	{0, 0.35, -1.01}, //15

	};

	// Массив координат граней
	static constexpr unsigned char faces3[8][4] = {
		{0, 1, 2, 3},
		{4, 5, 6, 7},
		{8, 9, 10, 11},
		{12, 13, 14, 15},
	};


	static size_t const faceCount = sizeof(faces3) / sizeof(*faces3);
	glEnable(GL_COLOR_MATERIAL);
	float textures[8] = { 0, 1, 1, 1, 1, 0, 0, 0 };
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
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
		const unsigned char* facePoints = faces3[face];
		glm::vec3 p[4];
		float l[12], n[12];



		for (auto i = 0; i < 4; i++)
		{
			p[i] = glm::make_vec3(verticesWindow[facePoints[i]]) * m_size * 0.2f;

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
		glTexCoordPointer(2, GL_FLOAT, 0, textures);

		glVertexPointer(3, GL_FLOAT, 0, l);
		glDrawArrays(GL_QUADS, 0, 4);
	}
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}


void CWindows::DrawNarrowWindow()
{

	if (!m_texture2)
	{
		// Загружаем текстуру при первом вызове метода Draw()
		CTextureLoader loader;
		m_texture2.Attach(loader.LoadTexture2D(L"window2.png"));
	}
	glEnable(GL_TEXTURE_2D);
	m_texture2.Bind();
	m_material.Activate();
	static float verticesWindow2[50][3] = {

	{0.2, 0.45, 1.01}, //16
	{0.3, 0.45, 1.01}, //17
	{0.3, 0.85, 1.01}, //18
	{0.2, 0.85, 1.01}, //19

	{-0.15, 0.7, 0.61}, //20
	{-0.25, 0.7, 0.61}, //21
	{-0.25, 0.9, 0.61}, //22
	{-0.15, 0.9, 0.61}, //23
		
	{1.01, 0.7, -0.25}, //24
	{1.01, 0.7, -0.35}, //25
	{1.01, 0.9, -0.35}, //26
	{1.01, 0.9, -0.26}, //27
		
	{1.01, 0.2, -0.25}, //28
	{1.01, 0.2, -0.35}, //29
	{1.01, 0.4, -0.35}, //30
	{1.01, 0.4, -0.26}, //31

	};

	// Массив координат граней
	static constexpr unsigned char faces3[8][4] = {
		{0, 1, 2, 3},
		{7, 6, 5, 4},
		{8, 9, 10, 11},
		{12, 13, 14, 15},
	};


	static size_t const faceCount = sizeof(faces3) / sizeof(*faces3);
	float textures[8] = {0, 1, 1, 1, 1, 0, 0, 0};
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
		glColor4f(1, 1, 1, 1);
		const unsigned char* facePoints = faces3[face];
		glm::vec3 p[4];
		float l[12], n[12];



		for (auto i = 0; i < 4; i++)
		{
			p[i] = glm::make_vec3(verticesWindow2[facePoints[i]]) * m_size * 0.2f;

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

		glTexCoordPointer(2, GL_FLOAT, 0, textures);

		glVertexPointer(3, GL_FLOAT, 0, l);
		glDrawArrays(GL_QUADS, 0, 4);
	}
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

void CWindows::Draw()
{
	DrawWideWindow();
	DrawNarrowWindow();
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
}


void CWindows::SetSideColor(const glm::vec4& color)
{
	m_sideColors = color;
}

void CWindows::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void CWindows::SetShininess(float shininess)
{
	m_shininess = shininess;
}
