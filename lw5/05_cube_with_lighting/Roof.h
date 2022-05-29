#pragma once
#include "BaseTexture.h"
#include <boost/format.hpp>
class CRoof
{
public:
	explicit CRoof(float size = 1);
	void DrawRoofBase() const;
	void DrawRoof() const;
	void Draw() const;
	void SetSideColor(const glm::vec4& color);
	void SetSpecularColor(glm::vec4 color);
	void SetShininess(float shininess);


private:
	float m_size;
	glm::vec4 m_sideColors;
	glm::vec4 m_specularColor = { 0, 0, 0, 1 };
	float m_shininess = 1;
	mutable CTexture2D m_texture, m_texture_roof;
	std::wstring m_textureName;

};

