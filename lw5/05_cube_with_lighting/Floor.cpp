#include "pch.h"
#include "Floor.h"
#include <iostream>
#include "TextureLoader.h"
constexpr size_t FACES_NUMBER = 26;


CFloor::CFloor(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	SetSideColor({ 134, 57, 29, 1 });
}


void CFloor::DrawLawn() const
{
	// Массив координат вершин
	if (!m_texture_grass)
	{
		// Загружаем текстуру при первом вызове метода Draw()
		CTextureLoader loader;
		m_texture_grass.Attach(loader.LoadTexture2D(L"sidewalk.jpg"));
	}
	// Активизируем текстуру и материал
	glEnable(GL_TEXTURE_2D);
	m_texture_grass.Bind();

	static float a = 0;
	static float vertices[36][3] = {

		{ -0.3, 0.0001, -0.3 }, // 4
		{ -0.3, 0.0001, 0.3 }, // 5
		{ 0.3, 0.0001, 0.3 }, // 6
		{ 0.3, 0.0001, -0.3 }, // 7

	};

	// Массив координат граней
	static constexpr unsigned char faces[27][4] = {
		{0, 1, 2, 3},
	};

	static size_t const faceCount = sizeof(faces) / sizeof(*faces);
	float textures[faceCount][8] = {
		{0, 5, 5, 5, 5, 0, 0, 0},
	};
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
		const unsigned char* facePoints = faces[face];
		glm::vec3 p[4];
		float l[12], n[12];



		for (auto i = 0; i < 4; i++)
		{
			p[i] = glm::make_vec3(vertices[facePoints[i]]) * m_size;

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



void CFloor::Draw() const
{

	if (!m_texture_sidewalk)
	{
		CTextureLoader loader;
		m_texture_sidewalk.Attach(loader.LoadTexture2D(L"Grass.jpg"));
	}

	glEnable(GL_TEXTURE_2D);
	m_texture_sidewalk.Bind();

	m_material.Activate();


	static float a = 0;
	static float vertices[36][3] = {
		{-6.0, 0.0, -6.0}, // 0
		{ -6.0, 0.0, 6.0 }, // 1
		{ 6.0, 0.0, 6.0 }, // 2
		{ 6.0, 0.0, -6.0 }, // 3

	};

	// Массив координат граней
	static constexpr unsigned char faces[27][4] = {
		{0, 1, 2, 3},
	};

	static size_t const faceCount = sizeof(faces) / sizeof(*faces);
	float textures[faceCount][24] = {
		{0, 1, 1, 1, 1, 0, 0, 0},
	};
	glDisable(GL_LIGHTING);
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
		glColor4f(1, 1, 1, 1);
		const unsigned char* facePoints = faces[face];
		glm::vec3 p[4];
		float l[12], n[12];



		for (auto i = 0; i < 4; i++)
		{
			p[i] = glm::make_vec3(vertices[facePoints[i]]) * m_size;

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

	glEnable(GL_LIGHTING);
	DrawLawn();

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}


void CFloor::SetSideColor(const glm::vec4& color)
{
	m_sideColors = color;
}

void CFloor::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void CFloor::SetShininess(float shininess)
{
	m_shininess = shininess;
}
