#include "CMyApplication.h"
const float M_PI = 3.14159265358979323846f;

//vector<std::shared_ptr<CSeaweed>> CMyApplication::seaweeds = {};
CMyApplication* CMyApplication::m_app = NULL;

CMyApplication::CMyApplication(const char* title, int width, int height)
	:CGLApplication(title, width, height)
	, m_width(width)
	, m_height(height)
{
	m_app = this;
}

CMyApplication::~CMyApplication(void)
{
}

void CMyApplication::OnInit()
{
	// Задаем цвет очистки буфера кадра
	glClearColor(1, 1, 1, 1);
	Color color = { 0.f, 71.f, 77.f };
	seaweeds.push_back(std::make_shared<CSeaweed>(900.f, 180.f, m_width, 10.f, 15.0f, 0.05f, 0.5f, 0.05f, color));
	color = { 0, 136, 194 };
	seaweeds.push_back(std::make_shared<CSeaweed>(110.f, 50.f, m_width, 8.f, 15.0f, 0.05f, 0.9f, 0.05f, color));
	color = { 0, 60, 77 };
	seaweeds.push_back(std::make_shared<CSeaweed>(570.f, 200.f, m_width, 12.f, 15.0f, 0.03f, 0.9f, 0.05f, color));
	color = { 0, 41, 59 };
	seaweeds.push_back(std::make_shared<CSeaweed>(700.f, 380.f, m_width, 10.f, 15.0f, 0.05f, 0.9f, 0.05f, color));
	for (auto& seaweed : seaweeds)
	{
		m_app->SetTimer(20, seaweed->Animate2, 0);
	}
	//glutPostRedisplay();
}

void CMyApplication::Animate(int value)
{
	// glutTimerFunc(20, Animate, 0);
	m_app->SetTimer(1000, Animate, 0);
	m_app->PostRedisplay();
	//glutPostRedisplay();
}

void CMyApplication::OnDisplay(void)
{
	// Очищаем буфер цвета и буфер глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Настраиваем цвет вершин
	glColor3f(0, 0, 1);

	FillPolygon({ { 0, 0, {71, 189, 255} }, { m_width, 0, {67, 0, 235} }, {m_width, m_height, {67, 0, 235} }, {0, m_height, {67, 0, 235} } });

	for (auto& seaweed : seaweeds)
	{
		glPushMatrix();
		seaweed->DrawHarmonic();
		glPopMatrix();
	}

	FillPolygon({ { 0, m_height - 40, {224, 222, 146} }, { m_width, m_height - 40, {224, 222, 146} }, {m_width, m_height, {224, 222, 146} }, {0, m_height, {224, 222, 146} } });
	//FillPolygon({ { 500, 40, {224, 242, 146} }, { m_width, m_height - 40, {224, 222, 146} }, {m_width, m_height, {224, 222, 146} }, {0, m_height, {224, 222, 146} } });
}

void CMyApplication::OnReshape(int width, int height)
{
	// Настраиваем порт просмотра
	glViewport(0, 0, width, height);

	// Делаем текущей матрицу проецирования и настраиваем ее параметры
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)width, (float)height, 0, -1, 1);

	// Делаем текущей матрицей матрицу моделирования-вида
	glMatrixMode(GL_MODELVIEW);
}

void CMyApplication::FillPolygon(vector<PointWithColor> points)
{
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < points.size(); i++)
	{
		glColor3ub(points[i].color.r, points[i].color.g, points[i].color.b);
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();
}

void CMyApplication::FillEllipse(float xCenter, float yCenter, float rx, float ry, int points)
{
	const float step = 2 * M_PI / points;

	// Эллипс представлет в виде "веера" из треугольников
	glBegin(GL_TRIANGLE_FAN);
	// Начальная точка веера располагается в центре эллипса
	glVertex2d(xCenter, yCenter);
	// Остальные точки - равномерно по его границе
	for (float angle = 0; angle <= 2 * M_PI; angle += step)
	{
		float a = (fabsf(angle - 2 * M_PI) < 1e-5) ? 0 : angle;
		const float dx = rx * cosf(a);
		const float dy = ry * sinf(a);
		glVertex2f(dx + xCenter, dy + yCenter);
	}
	glEnd();
}
