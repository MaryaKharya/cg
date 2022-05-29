#include "pch.h"
#include "Roof.h"

#include "pch.h"
#include "Facade.h"
#include "TextureLoader.h"
constexpr size_t FACES_NUMBER = 26;


CRoof::CRoof(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	SetSideColor({ 134, 57, 29, 1 });
}
void CRoof::DrawRoofBase() const
{
	// Массив координат вершин
	if (!m_texture)
	{
		// Загружаем текстуру при первом вызове метода Draw()
		CTextureLoader loader;
		m_texture.Attach(loader.LoadTexture2D(L"wall.jpg"));
	}

	glEnable(GL_TEXTURE_2D);
	m_texture.Bind();
	//m_material.Activate();


	static float vertices[55][3] = {
		{ -0.5, 1, -1.1 }, // 0
		{ 0.3, 1, -1.1 }, // 1
		{ 0.3, 1, -0.9 }, // 2
		{ 1, 1, -0.9 }, // 3
		{ 1, 1, -0.7 }, // 4
		{ 1.1, 1, -0.7 }, // 5
		{ 1.1, 1, 0.1 }, // 6
		{ 1, 1, 0.1 }, // 7
		{ 1, 1, 0.9 }, // 8
		{ 0.6, 1, 0.9 }, // 9
		{ 0.6, 1, 1.1 }, // 10
		{ -0.1, 1, 1.1 }, // 11
		{ -0.1, 1, 0.7 }, // 12
		{ -0.5, 1, 0.7 }, // 13

		{0.3, 1, 0.7 }, //14
		{0.3, 1, 0.9}, //15
		{0.6, 1, 0.7}, //16

		{-0.5, 1.05, -1.1}, // 17
		{-0.1, 1.3, -1.1}, //18
		{ 0.3, 1.05, -1.1 }, // 19
		{ 0.3, 1.05, -0.9 }, // 20
		{ 1, 1.05, -0.9 }, // 21
		{ 1, 1.05, -0.7 }, // 22
		{ 1.1, 1.05, -0.7 }, // 23
		{ 1.1, 1.05, 0.1 }, // 24
		{ 1, 1.05, 0.1 }, // 25
		{ 1, 1.05, 0.9 }, // 26
		{ 0.6, 1.05, 0.9 }, // 27
		{ 0.6, 1.05, 1.1 }, // 28
		{ 0.25, 1.28, 1.1 }, //29
		{ -0.1, 1.05, 1.1 }, // 30
		{ -0.1, 1.05, 0.7 }, // 31
		{ -0.5, 1.05, 0.7 }, // 32

		//гараж
		{-0.4, 0.45, -1.1}, //33
		{-1.1, 0.45, -1.1}, //34
		{-1.1, 0.45, 1.1}, //35
		{-0.4, 0.45, 1.1}, //36
		{0, 0.45, 1.1}, //37
		{0, 0.45, 0.6}, //38
		{-0.4, 0.45, 0.1}, //39

		{-0.4, 0.4, -1.1}, //40
		{-1.1, 0.4, -1.1}, //41
		{-1.1, 0.4, 1.1}, //42
		{-0.4, 0.4, 1.1}, //43
		{0, 0.4, 1.1}, //44
		{0, 0.4, 0.6}, //45
		{-0.4, 0.4, 0.1}, //46

		//заднее крыльцо
		{0.1, 0.45, -1.1}, //47
		{1.0, 0.45, -1.1}, //48
		{1.0, 0.45, -0.7}, //49
		{0.1, 0.45, -0.7}, //50

		{0.1, 0.4, -1.1}, //51
		{1.0, 0.4, -1.1}, //52
		{1.0, 0.4, -0.7}, //53
		{0.1, 0.4, -0.7}, //54
	};

	// Массив координат граней
	static constexpr unsigned char faces[34][4] = {
		{0, 1, 14, 13},
		{2, 3, 8, 15},
		{4, 5, 6, 7},
		{10, 11, 12, 16},

		{1, 0, 17, 19},
		{2, 1, 19, 20},
		{3, 2, 20, 21},
		{4, 3, 21, 22},
		{5, 4, 22, 23},
		{6, 5, 23, 24},
		{7, 6, 24, 25},
		{8, 7, 25, 26},
		{9, 8, 26, 27},
		{10, 9, 27, 28},
		{11, 10, 28, 30},
		{12, 11, 30, 31},
		{13, 12, 31, 32},
		{0, 13, 32, 17},

		{17, 18, 19, 19},
		{28, 29, 30, 30},

		//гараж
		{43, 42, 41, 40},
		{46, 45, 44, 43},
		{40, 41, 34, 33},
		{41, 42, 35, 34},
		{42, 43, 36, 35},
		{43, 44, 37, 36},
		{44, 45, 38, 37},
		{45, 46, 39, 38},
		{46, 40, 33, 39},

		//заднее крыльцо
		{52, 51, 47, 48},
		{53, 52, 48, 49},
		{54, 53, 49, 50},
		{51, 54, 50, 47},
		{47, 48, 49, 50}
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);
	float textures[faceCount] = { 0, 1, 1, 1, 1, 0, 0, 0 };
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
	glDisable(GL_TEXTURE_2D);

}

void CRoof::DrawRoof() const
{
	if (!m_texture_roof)
	{
		CTextureLoader loader;
		m_texture_roof.Attach(loader.LoadTexture2D(L"roof.jpg"));
	}
	glEnable(GL_TEXTURE_2D);
	m_texture_roof.Bind();


	static float a2 = 0;
	static float vertices2[46][3] = {
		{-0.5, 1.05, -1.1}, // 0
		{-0.1, 1.3, -1.1}, //1
		{ 0.3, 1.05, -1.1 }, // 2
		{ 0.3, 1.05, -0.9 }, // 3
		{ 1, 1.05, -0.9 }, // 4
		{ 1, 1.05, -0.7 }, // 5
		{ 1.1, 1.05, -0.7 }, // 6
		{ 1.1, 1.05, 0.1 }, // 7
		{ 1, 1.05, 0.1 }, // 8
		{ 1, 1.05, 0.9 }, // 9
		{ 0.6, 1.05, 0.9 }, // 10
		{ 0.6, 1.05, 1.1 }, // 11
		{0.25, 1.28, 1.1}, //12
		{ -0.1, 1.05, 1.1 }, // 13
		{ -0.1, 1.05, 0.7 }, // 14
		{ -0.5, 1.05, 0.7 }, // 15

		{-0.5, 1.05, -0.9}, //16
		{1, 1.05, 0.7}, //17
		
		{0.2, 1.5, -0.1},//18
		{0.3, 1.5, -0.1}, //19

		{-0.1, 1.3, -0.4}, //20
		{0.3, 1.05, -0.5}, //21
		{-0.5, 1.05, -0.5}, //22

		{0.7, 1.3, -0.3}, //23
		{0.6, 1.3, -0.3}, //24

		{0.45, 1.40, 0 }, //25
		{0.45, 1.40, 0.25}, //26
		{-0.1, 1.05, 0.9}, //27

		{0.25, 1.28, 0.3}, //28

		//гараж
		{-0.4, 0.45, -1.1}, //29
		{-1.1, 0.45, -1.1}, //30
		{-1.1, 0.45, 1.1}, //31
		{-0.4, 0.45, 1.1}, //32
		{0, 0.45, 1.1}, //33
		{0, 0.45, 0.6}, //34
		{-0.4, 0.45, 0.1}, //35
		{0, 0.8, 0.1}, //36
		{-0.4, 0.8, 0.1}, //37
		{-0.4, 0.8, -0.2}, //38

		//заднее крыльцо
		{0.1, 0.45, -1.1}, //39
		{1.0, 0.45, -1.1}, //40
		{1.0, 0.45, -0.7}, //41
		{0.1, 0.45, -0.7}, //42
		{0.1, 0.7, -0.8}, //43
		{0.7, 0.7, -0.8}, //44
		{0.7, 0.7, -0.7}, //45
	};

	// Массив координат граней
	static constexpr unsigned char faces2[27][4] = {
		{21, 2, 1, 20},
		{0, 22, 20, 1},

		{6, 5, 24, 23},
		{8, 7, 23, 24},
		{7, 6, 23, 23},

		{9, 17, 25, 26},
		{14, 27, 26, 25},
		{27, 9, 26, 26},

		{27, 13, 12, 28},
		{11, 10, 28, 12},

		{4, 16, 18, 19},
		{15, 17, 19, 18},
		{17, 4, 19, 19},
		{16, 15, 18, 18},

		//гараж
		{29, 30, 38, 38},
		{30, 31, 37, 38},
		{31, 33, 36, 37},
		{29, 38, 37, 32},
		{33, 34, 36, 36},

		//заднее крыльцо
		{40, 39, 43, 44},
		{41, 40, 44, 45},
		{41, 45, 42, 42},
		{39, 42, 43, 43},
	};

	static size_t const faceCount = sizeof(faces2) / sizeof(*faces2);
	float textures[faceCount][24] = {
		{0, 1, 1, 1, 1, 0, 0, 0},
		{0, 1, 1, 1, 1, 0, 0, 0},
		{0, 1, 0.2, 1, 0.2, 0, 0, 0 },
		{0, 1, 0.2, 1, 0.2, 0, 0, 0},
		{0, 1, 0.8, 1, 0.4, 0, 0.5, 0},
		{ 0, 0, 0, 0.2, 1.2, 0.2, 1.2, 0},
		{ 0, 0, 0, 0.2, 1.2, 0.2, 1.2, 0},
		{0, 1, 1.6, 1, 0.8, 0, 0.8, 0},
		{0.7, 0.7, 1, 0.7, 1, 0, 0, 0},
		{0, 0.7, 0.3, 0.7, 1, 0, 0, 0},
		{0, 1.4, 1.7, 1.4, 0.9, 0, 0.8, 0},
		{0, 1.4, 1.7, 1.4, 0.9, 0, 0.8, 0},
		{0, 1.4, 1.7, 1.4, 0.85, 0, 0.85, 0},
		{0, 1.4, 1.7, 1.4, 0.85, 0, 0.85, 0},
		
		{0, 1.4, 1, 1.4, 0, 0, 0, 0},
		{0, 1.4, 2.1, 1.4, 1.2, 0, 0.9, 0},
		{0, 1.4, 1.7, 1.4, 1.7, 0, 1.1, 0},
		{1, 1, 1, 0, 1, 0, 0, 1},
		{1, 1, 1, 0, 1, 0, 0, 1},
		
		{0, 0.6, 1, 0.6, 1, 0, 0.3, 0},
		{0, 0.6, 0.5, 0.6, 0.2, 0, 0, 0},
		{0, 0.6, 1, 0.6, 1, 0, 0.3, 0},
		{0, 0.6, 0.5, 0.6, 0.2, 0, 0, 0},
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

		glTexCoordPointer(2, GL_FLOAT, 0, textures[face]);

		glVertexPointer(3, GL_FLOAT, 0, l);
		glDrawArrays(GL_QUADS, 0, 4);
	}
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

void CRoof::Draw() const
{
	DrawRoofBase();
	DrawRoof();
}

void CRoof::SetSideColor(const glm::vec4& color)
{
	m_sideColors = color;
}

void CRoof::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void CRoof::SetShininess(float shininess)
{
	m_shininess = shininess;
}
