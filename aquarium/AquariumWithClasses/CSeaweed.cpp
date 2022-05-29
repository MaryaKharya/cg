#include "CSeaweed.h"

//class CMyApplication;

float CSeaweed::m_speed = 0.0f;
float CSeaweed::m_phase = 0.0f;

//float CSeaweed::m_x, CSeaweed::m_yBegin, CSeaweed::m_yEnd, CSeaweed::m_amplitude, CSeaweed::m_frequency, CSeaweed::m_thickness;
//float m_speed, m_phase;
//Color CSeaweed::m_color;
//CSeaweed* CSeaweed::m_app = NULL;

CSeaweed::CSeaweed(float x, float yBegin, float yEnd, float thickness, float amplitude, float frequency, float phase, float speed, Color color)
    : m_x(x)
	, m_yBegin(yBegin)
    , m_yEnd(yEnd)
	, m_thickness(thickness)
	, m_amplitude(amplitude)
	, m_frequency(frequency)
	//, m_speed(speed)
	, m_color(color)
{
    m_speed = speed;
    m_phase = phase;
    /*m_x = x;
    m_yBegin = yBegin;
    m_yEnd = yEnd;
    m_thickness = thickness;
    m_amplitude = amplitude;
    m_frequency = frequency;
    m_color = color;*/
}
void CSeaweed::DrawHarmonic()
{
    glLineWidth(m_thickness);
    glBegin(GL_LINE_STRIP);
    glColor3ub(m_color.r, m_color.g, m_color.b);
    float x = 0.0f;
    float y = m_yBegin, amplitude = m_amplitude;
    while (y <= m_yEnd)
    {
        x = amplitude * sin(m_frequency * y + m_phase) + m_x;
        glVertex2f(x, y);
        y += 1;
        amplitude -= 0.03;
    }
    glEnd();
}

void CSeaweed::Animate2(int value)
{
   m_phase += m_speed;
   glutTimerFunc(20, Animate2, 0);
   glutPostRedisplay();
}

CSeaweed::~CSeaweed()
{
}