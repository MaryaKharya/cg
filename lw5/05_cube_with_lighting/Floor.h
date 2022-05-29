#pragma once
#include "BaseTexture.h"
#include "Material.h"
#include <boost/format.hpp>

class CFloor
{
public:
	explicit CFloor(float size = 1);
	void Draw() const;
	void DrawLawn() const;
	void SetSideColor(const glm::vec4& color);
	void SetSpecularColor(glm::vec4 color);
	void SetShininess(float shininess);


private:
	float m_size;
	glm::vec4 m_sideColors;
	glm::vec4 m_specularColor = { 0, 0, 0, 1 };
	float m_shininess = 1;
	mutable CTexture2D m_texture_grass, m_texture_sidewalk;
	std::wstring m_textureName;
	CMaterial m_material;
};

