#include "pch.h"
#include "Foundation.h"

constexpr size_t FACES_NUMBER = 26;


CFoundation::CFoundation(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	for (size_t i = 0; i < FACES_NUMBER; i++)
	{
		SetSideColor(i, defaultColor);
	}
}

void CFoundation::DrawFoundation() const
{

	// Массив координат вершин
	static float a = 0;
	static float vertices[32][3] = {
		{ -1, 0, -1 }, // 0
		{ 0.2, 0, -1 }, // 1
		{ 0.9, 0, -1 }, // 2
		{ 0.9, 0, -0.8 }, // 3
		{ 0.9, 0, -0.6 }, // 4
		{ 1, 0, -0.4 }, // 5
		{ 1, 0, -0.2 }, // 6
		{ 0.9, 0, 0 }, // 7
		{ 0.9, 0, 0.8 }, // 8
		{ 0.5, 0, 0.8 }, // 9
		{ 0.5, 0, 1 }, // 10
		{ 0, 0, 1 }, // 11
		{ -0.4, 0, 1 }, // 12
		{ -0.4, 0, 0.6 }, // 13
		{ -0.4, 0, 0.1 }, // 14
		{ -1, 0, 0.1 }, // 15

		{ -1, 0.1, -1 }, // 16
		{ 0.2, 0.1, -1 }, // 17
		{ 0.9, 0.1, -1 }, // 18
		{ 0.9, 0.1, -0.8 }, // 19
		{ 0.9, 0.1, -0.6 }, // 20
		{ 1, 0.1, -0.4 }, // 21
		{ 1, 0.1, -0.2 }, // 22
		{ 0.9, 0.1, 0 }, // 23
		{ 0.9, 0.1, 0.8 }, // 24
		{ 0.5, 0.1, 0.8 }, // 25
		{ 0.5, 0.1, 1 }, // 26
		{ 0, 0.1, 1 }, // 27
		{ -0.4, 0.1, 1 }, // 28
		{ -0.4, 0.1, 0.6 }, // 29
		{ -0.4, 0.1, 0.1 }, // 30
		{ -1, 0.1, 0.1 }, // 31

	};

	// Массив координат граней
	static constexpr unsigned char faces[17][4] = {
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
		{14, 13, 29, 30},
		{15, 14, 30, 31},
		{0, 15, 31, 16},
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);
	float textures[faceCount][8] = {
		{ -0.6, 1, 1, 1, 1, 0, -0.6, 0 },
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
		glColor4f(0.3, 0.3, 0.3, 1);
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
			p[i] = glm::make_vec3(vertices[facePoints[i]]) * m_size * 0.2f;
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
	//glDisable(GL_TEXTURE_2D);
}

void CFoundation::DrawFloor() const
{
	// Массив координат вершин



	static float vertices2[32][3] = {
		{ 0, 0.1, 1 }, // 0
		{ 0, 0.1, 0.6}, //1
		{ -0.4, 0.1, 0.6 }, // 2
		{ -0.4, 0.1, 1 }, // 3

		//гараж
		{-0.4, 0, 1}, //4
		{-0.4, 0, 0.1}, //5
		{-1, 0, 0.1}, //6
		{-1, 0, 1}, //7
		{-0.4, 0.01, 1}, //8
		{-0.4, 0.01, 0.1}, //9
		{-1, 0.01, 0.1}, //10
		{-1, 0.01, 1}, //11

		//крыльцо2
		{0.2, 0.1, -1}, //12
		{0.2, 0.1, -0.8}, //13
		{0.9, 0.1, -0.8}, //14
		{0.9, 0.1, -1}, //15

		//порог
		{-0.75, 0.01, -1}, //16
		{-0.95, 0.01, -1}, //17
		{-0.95, 0.01, -1.1}, //18
		{-0.75, 0.01, -1.1}, //19
	};

	// Массив координат граней
	static constexpr unsigned char faces2[7][4] = {
		{0, 1, 2, 3},

		//гараж
		{4, 5, 9, 8 },
		{6, 7, 11, 10},
		{7, 4, 8, 11},
		{8, 9, 10, 11},

		//крыльцо2
		{12, 13, 14, 15},

		//порог
		{19, 18, 17, 16},
	};
	static size_t const faceCount = sizeof(faces2) / sizeof(*faces2);
	float textures[faceCount][8] = {
		{ 0, 1, 1, 1, 1, 0, 0, 0 },
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
		const unsigned char* facePoints = faces2[face];
		glm::vec3 p[4];
		float l[12], n[12];



		for (auto i = 0; i < 4; i++)
		{
			p[i] = glm::make_vec3(vertices2[facePoints[i]]) * m_size * 0.2f;

		}

		auto v01 = p[1] - p[0];
		auto v02 = p[2] - p[0];
		auto n2 = glm::normalize(glm::cross(v01, v02));
		for (auto i = 0; i < 4; i++)
		{
			p[i] = glm::make_vec3(vertices2[facePoints[i]]) * m_size * 0.2f;
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
}


void CFoundation::DrawPillar()
{
	// Массив координат вершин
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
	static constexpr unsigned char faces3[4][4] = {
		{0, 1, 2, 3},
		{7, 6, 5, 4},
		{3, 2, 6, 7},
		{4, 5, 1, 0},
	};

	static float translate[9][3] = {
		{0, 0, 0},
		{-0.2 * m_size * 0.2f, 0, 0},
		{-0.8 * m_size * 0.2f, -0.1 * m_size * 0.2f, 0},
		{-0.8 * m_size * 0.2f, -0.1 * m_size * 0.2f, -0.4 * m_size * 0.2f},
		{-0.8 * m_size * 0.2f, -0.1 * m_size * 0.2f, -0.8 * m_size * 0.2f},
		{0.36 * m_size * 0.2f, 0, -1.9 * m_size * 0.2f},
		{0.66 * m_size * 0.2f, 0, -1.9 * m_size * 0.2f},
		{0.96 * m_size * 0.2f, 0, -1.9 * m_size * 0.2f},
	};

	static float scale[9][3] = {
		{1, 1, 1},
		{1, 1, 1},
		{1, 1.4, 1},
		{1, 1.4, 1},
		{1, 1.4, 1},
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1},
	};

	static size_t const faceCount = sizeof(faces3) / sizeof(*faces3);
	float textures[faceCount][8] = {
	{ 0, 1, 1, 1, 1, 0, 0, 0 },
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
	for (size_t f = 0; f < 9; ++f)
	{
		glPushMatrix();
		glScaled(scale[f][0], scale[f][1], scale[f][2]);
		glTranslated(translate[f][0], translate[f][1], translate[f][2]);
		for (size_t face = 0; face < faceCount; ++face)
		{
			// устанавливаем диффузный и фоновый цвет грани
			glColor4f(0.3, 0.3, 0.3, 1);
			const unsigned char* facePoints = faces3[face];
			glm::vec3 p[4];
			float l[12], n[12];



			for (auto i = 0; i < 4; i++)
			{
				p[i] = glm::make_vec3(vertices3[facePoints[i]]) * m_size * 0.2f;

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
		glPopMatrix();
	}
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

void CFoundation::Draw()
{
	if (!m_texture)
	{
		// Загружаем текстуру при первом вызове метода Draw()
		CTextureLoader loader;
		m_texture.Attach(loader.LoadTexture2D(L"stones.jpg"));
	}
	// Активизируем текстуру и материал планеты
	glEnable(GL_TEXTURE_2D);
	m_texture.Bind();
	m_material.Activate();
	DrawFoundation();
	DrawPillar();

	if (!m_texture2)
	{
		// Загружаем текстуру при первом вызове метода Draw()
		CTextureLoader loader;
		m_texture2.Attach(loader.LoadTexture2D(L"wall.jpg"));
	}
	// Активизируем текстуру и материал планеты
	glEnable(GL_TEXTURE_2D);
	m_texture2.Bind();
	m_material.Activate();
	DrawFloor();
	glDisable(GL_TEXTURE_2D);
}

void CFoundation::SetSideColor(size_t index, const glm::vec4& color)
{
	//unsigned index = static_cast<unsigned>(side);
	m_sideColors[index] = color;
}

void CFoundation::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void CFoundation::SetShininess(float shininess)
{
	m_shininess = shininess;
}
