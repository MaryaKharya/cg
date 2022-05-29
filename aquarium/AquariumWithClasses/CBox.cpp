#include "CBox.h"
const float M_PI = 3.14159265358979323846f;

float CBox::m_angle = 0;

CBox::CBox(float xLeft, float yTop, float width, float height, float speed, Color colorTop, Color colorBottom)
	: m_xLeft(xLeft)
	, m_yTop(yTop)
	, m_width(width)
	, m_height(height)
	//, m_speed(speed)
	, m_colorTop(colorTop)
	, m_colorBottom(colorBottom)
{}
void CBox::DrawBox()
{

}
void CBox::DrawBody()
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(20, 0, 33);
	glVertex2f(20, 98);
	glVertex2f(36, 98);
	glColor3ub(59, 44, 39);
	glVertex2f(36, 85);
	glVertex2f(20, 85);
	glEnd();
}

void CBox::DrawLid()
{
	glTranslatef(2.0, 8.5, 0.0f);
	glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-2.0f, -8.5f, 0.0f);

	const float step = static_cast<float>(2 * M_PI / 360);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(m_xLeft + m_width/2, m_yTop + m_height/3);
	for (float angle = 0; angle <= M_PI + step / 2; angle += step)
	{
		float a = (fabsf(static_cast<float>(angle - 2 * M_PI)) < 1e-5) ? 0 : -angle;
		const float dx = m_width / 2 * cosf(a);
		const float dy = m_height / 3 * sinf(a);

		glVertex2f(dx + m_xLeft + m_width / 2, dy + m_yTop + m_height / 3);
	}
	glEnd();

	//points = { {2.0f, 8.7f, 214, 207, 0}, {3.6f, 8.7f, 214, 207, 0}, {3.6f, 8.5f, 214, 207, 0}, {2.0f, 8.5f, 214, 207, 0} };
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(214, 207, 0);
	glVertex2f(20, 98);
	glVertex2f(36, 98);
	glVertex2f(36, 85);
	glVertex2f(20, 85);
	glEnd();
}

void CBox::Animate(int value)
{}

CBox::~CBox()
{
}