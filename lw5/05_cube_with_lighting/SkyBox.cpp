#include "pch.h"
#include "SkyBox.h"

#ifndef GL_CLAMP_TO_EDGE_EXT
#define GL_CLAMP_TO_EDGE_EXT 0x812F
#endif


constexpr size_t FACES_NUMBER = 26;


SkyBox::SkyBox(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	for (size_t i = 0; i < FACES_NUMBER; i++)
	{
		SetSideColor(defaultColor);
	}
}


void SkyBox::Draw(GLfloat size)
{
	glDisable(GL_LIGHTING);
	// Отключим режим отбраковки граней, т.к. 
	// мы находимся внутри куба и видим его нелицевую сторону
	glDisable(GL_CULL_FACE);
	if (!m_tGrass)
	{
		CTextureLoader loader;
		// Устанавливаем режим "заворачиваиия" текстурных координат,
		// обеспечивающие минимальную видимость стыков на гранях куба
		loader.SetWrapMode(GL_CLAMP_TO_EDGE_EXT, GL_CLAMP_TO_EDGE_EXT);

		m_tGrass.Attach(loader.LoadTexture2D(L"grass.png"));
		m_tSky.Attach(loader.LoadTexture2D(L"sky.png"));
		m_tWest.Attach(loader.LoadTexture2D(L"west.png"));
		m_tNorth.Attach(loader.LoadTexture2D(L"north.png"));
		m_tEast.Attach(loader.LoadTexture2D(L"east.png"));
		m_tSouth.Attach(loader.LoadTexture2D(L"south.png"));
		m_material.Activate();
	}
	// Устанавливаем необходимые режимы визуализации куба
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	// сохраняем текущую матрицу
	glPushMatrix();

	// Положение камеры располаагется в 4 столбце матрицы (элементы 12-14)
	// Если занести туда 0, то матрица станет матрицей вращения.
	GLfloat modelView[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelView);
	modelView[12] = modelView[13] = modelView[14] = 0;
	glLoadMatrixf(modelView);

	// рисуем куб
	static const float vertices[12][3] =
	{
		{-0.7, -0.7, -0.7},	// 0
		{+0.7, -0.7, -0.7},	// 1
		{+0.7, +0.7, -0.7},	// 2
		{-0.7, +0.7, -0.7},	// 3
		{-0.7, -0.7, +0.7},	// 4
		{+0.7, -0.7, +0.7},	// 5
		{+0.7, +0.7, +0.7},	// 6
		{-0.7, +0.7, +0.7},	// 7
	};

	struct CubeFace
	{
		unsigned char vertex0;
		unsigned char vertex1;
		unsigned char vertex2;
		unsigned char vertex3;
		GLfloat tex0s, tex0t;
		GLfloat tex1s, tex1t;
		GLfloat tex2s, tex2t;
		GLfloat tex3s, tex3t;
		CTexture2D const& texture;
	};

	// Массив координат граней (в порядке, совпадающем с 
	// порядком объявления их в массиве цветов)
	// индексы вершин граней перечисляются в порядке их обхода
	// против часовой стрелки (если смотреть на грань снаружи)
	static const CubeFace faces[] =
	{
		{4, 7, 3, 0, 0, 1, 0, 0, 1, 0, 1, 1, m_tWest},	// грань x<0
		{5, 1, 2, 6, 1, 1, 0, 1, 0, 0, 1, 0, m_tEast},	// грань x>0
		{4, 0, 1, 5, 0, 1, 0, 0, 1, 0, 1, 1, m_tGrass},	// грань y<0
		{7, 6, 2, 3, 0, 0, 1, 0, 1, 1, 0, 1, m_tSky},	// грань y>0
		{0, 3, 2, 1, 0, 1, 0, 0, 1, 0, 1, 1, m_tNorth},	// грань z<0
		{4, 5, 6, 7, 1, 1, 0, 1, 0, 0, 1, 0, m_tSouth},	// грань z>0
	};
	static unsigned const faceCount = sizeof(faces) / sizeof(*faces);

	for (unsigned faceIndex = 0; faceIndex < faceCount; ++faceIndex)
	{
		CubeFace const& face = faces[faceIndex];

		face.texture.Bind();
		glColor4f(1, 1, 1, 1);
		// Рисуем 4 вершины квадрата
		glBegin(GL_QUADS);
		{
			glTexCoord2f(face.tex0s, face.tex0t);
			CVector3f v0(vertices[face.vertex0]);
			v0 *= size * 0.2;
			glVertex3fv(v0);

			glTexCoord2f(face.tex1s, face.tex1t);
			CVector3f v1(vertices[face.vertex1]);
			v1 *= size * 0.2;
			glVertex3fv(v1);

			glTexCoord2f(face.tex2s, face.tex2t);
			CVector3f v2(vertices[face.vertex2]);
			v2 *= size * 0.2;
			glVertex3fv(v2);

			glTexCoord2f(face.tex3s, face.tex3t);
			CVector3f v3(vertices[face.vertex3]);
			v3 *= size * 0.2;
			glVertex3fv(v3);

		}
		glEnd();
	}

	// восстанавливаем текущую матрицу
	glPopMatrix();

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

void SkyBox::SetSideColor(const glm::vec4& color)
{
	m_sideColors = color;
}

void SkyBox::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void SkyBox::SetShininess(float shininess)
{
	m_shininess = shininess;
}
