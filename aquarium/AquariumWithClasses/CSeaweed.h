#pragma once
#include "Point.h"
#include <math.h>
#include<gl/glut.h>
//#include "CGLApplication.h"

//class CMyApplication;

class CSeaweed
{
public:
	CSeaweed(float x, float yBegin, float yEnd, float thickness, float amplitude, float frequency, float phase, float speed, Color olor);
	void DrawHarmonic();
	static void Animate2(int value);
	
	~CSeaweed();
private:
	float m_x, m_yBegin, m_yEnd, m_amplitude, m_frequency, m_thickness;
	static float m_speed, m_phase;
	Color m_color;

	//static CSeaweed* m_app;
};

