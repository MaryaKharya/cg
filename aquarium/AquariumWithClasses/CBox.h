#pragma once
#include "Point.h"
#include <math.h>
#include<gl/glut.h>

class CBox
{
public:
	CBox(float xLeft, float yBottom, float width, float height, float speed, Color colorTop, Color colorBottom);
	void DrawBox();
	void DrawBody();
	void DrawLid();
	void Animate(int value);

	~CBox();
private:
	float m_xLeft, m_yTop, m_width, m_height;
	static float m_speed, m_angle;
	Color m_colorTop, m_colorBottom;
};


