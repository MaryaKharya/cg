#pragma once
#include "BaseTexture.h"
#include "Material.h"
#include "TextureLoader.h"

class CFoundation
{
public:
	explicit CFoundation(float size = 1);
	void Draw();
	void DrawFoundation() const;
	void DrawFloor() const;
	void DrawPillar();
	//float* AddCoordinatePillar(float x, float y, float z, float z2);
	void SetSideColor(size_t index, const glm::vec4& color);
	void SetSpecularColor(glm::vec4 color);
	void SetShininess(float shininess);


private:
	float m_size;
	glm::vec4 m_sideColors[26];
	glm::vec4 m_specularColor = { 0, 0, 0, 1 };
	mutable CTexture2D m_texture, m_texture2;
	std::wstring m_textureName;
	CMaterial m_material;
	float m_shininess = 1;
};