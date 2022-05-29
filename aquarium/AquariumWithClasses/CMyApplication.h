#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include "CGLApplication.h"
#include "Point.h"
#include "CSeaweed.h"

using namespace std;

class CMyApplication : public CGLApplication
{
public:
	CMyApplication(const char* title, int width, int height);
	~CMyApplication(void);
protected:
	// Перегружаем необходимые виртуальные методы родительского класса
	virtual void OnInit();
	virtual void OnDisplay(void);
	virtual void OnReshape(int width, int height);
public:
	static void FillEllipse(float xCenter, float yCenter, float rx, float ry, int points = 360);
	static void FillPolygon(vector<PointWithColor> points);
	static void Animate(int value);
private:
	float m_width, m_height;
	vector<std::shared_ptr<CSeaweed>> seaweeds;
	static CMyApplication* m_app;

};

