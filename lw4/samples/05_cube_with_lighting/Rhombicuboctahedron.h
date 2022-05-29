#pragma once

class Rhombicuboctahedron
{
public:
	explicit Rhombicuboctahedron(float size = 1);
	void Draw() const;
	void SetSideColor(size_t index, const glm::vec4& color);
	void SetSpecularColor(glm::vec4 color);
	void SetShininess(float shininess);
	

private:
	float m_size;
	glm::vec4 m_sideColors[26];
	glm::vec4 m_specularColor = { 0, 0, 0, 1 };
	float m_shininess = 1;
};
