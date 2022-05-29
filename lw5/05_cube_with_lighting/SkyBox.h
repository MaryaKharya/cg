#pragma once
#include "Material.h"
#include "TextureLoader.h"
#include "Vector3.h"
#include <vector>
#include <memory>

class SkyBox
{
public:
	explicit SkyBox(float size = 1);
	void Draw(GLfloat size = 1);
	void SetSideColor(const glm::vec4& color);
	void SetSpecularColor(glm::vec4 color);
	void SetShininess(float shininess);
	

private:
	float m_size;
	glm::vec4 m_sideColors;
	glm::vec4 m_specularColor = { 0, 0, 0, 1 };
	float m_shininess = 1;
	CTexture2D m_tGrass;
	CTexture2D m_tSky;
	CTexture2D m_tWest;
	CTexture2D m_tNorth;
	CTexture2D m_tEast;
	CTexture2D m_tSouth;
	std::wstring m_textureName;
	CMaterial m_material;
};
