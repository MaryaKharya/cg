#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <chrono>
using namespace std;

const float M_PI = 3.14159265358979323846f;
float moveFishOneLeft = 20.0f;
float moveFishOneRight = 0.0f;
float moveFishTwoX = 0.0f;
float moveFishTwoY = 0.0f;
float angleFishTwoZ = 0.0f;
float angleFishTwoY = 0.0f;
float angleFishes = 0.0f;
float angleOpenLib = 0.0f;
float phase1 = 0.9f, phase2 = 1.6f, phase3 = 0.5f;
float moveBubble = 0.0f;
std::chrono::steady_clock::time_point m_startTime;
float xButterfly = 0;
// Период вращения треугольника (за какое время треугольник делает полный оборот)

struct Color
{
    int r, g, b;
};
struct Coordinates
{
    float x, y, speedX, speedY;
    Color color;
    float angle;
};
struct Point
{
    float x, y;
    int r, g, b;
    float rx, ry;
    float speed;
};
bool isOppositeSide = false;
vector<Point> ellipseStones = {};
vector<Point> boxBubbles = {};
vector<Point> fishBubbles = {};
vector<vector<Point>> polygonStones = {};
vector<Point> points;
vector<Coordinates> coordinatesFish;


void drawCrescentLine(float step, float scale, float fullness) {
    float angle = 0.0f;
    while (angle < M_PI) {
        glVertex2f(scale * sinf(angle), scale * cosf(angle));
        angle += step;
    }
    while (angle < (2.0f * M_PI)) {
        glVertex2f(fullness * scale * sinf(angle), scale * cosf(angle));
        angle += step;
    }
    glVertex2f(0.0f, scale);
}

void FillEllipse(float xCenter, float yCenter, float rx, float ry, int points = 360)
{
    const float step = static_cast<float>(2 * M_PI / points);

    // Эллипс представлет в виде "веера" из треугольников
    glBegin(GL_TRIANGLE_FAN);
    // Начальная точка веера располагается в центре эллипса
    glVertex2d(xCenter, yCenter);
    // Остальные точки - равномерно по его границе
    for (float angle = 0; angle <= 2 * M_PI; angle += step)
    {
        float a = (fabsf(static_cast<float>(angle - 2 * M_PI)) < 1e-5) ? 0 : angle;
        const float dx = rx * cosf(a);
        const float dy = ry * sinf(a);
        glVertex2f(dx + xCenter, dy + yCenter);
    }
    glEnd();
}

void DrawEllipse(float xCenter, float yCenter, float rx, float ry, int points = 360)
{
    const float step = static_cast<float>(2 * M_PI / points);

    glBegin(GL_LINE_STRIP);
    for (float angle = 0; angle <= 2 * M_PI; angle += step)
    {
        float a = (fabsf(static_cast<float>(angle - 2 * M_PI)) < 1e-5) ? 0 : angle;
        const float dx = rx * cosf(a);
        const float dy = ry * sinf(a);
        glVertex2f(dx + xCenter, dy + yCenter);
    }
    glEnd();
}

void FillHalfEllipse(float xCenter, float yCenter, float rx, float ry, int points = 360)
{
    const float step = static_cast<float>(2 * M_PI / points);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(xCenter, yCenter);
    for (float angle = 0; angle <= M_PI + step / 2; angle += step)
    {
        float a = (fabsf(static_cast<float>(angle - 2 * M_PI)) < 1e-5) ? 0 : -angle;
        const float dx = rx * cosf(a);
        const float dy = ry * sinf(a);

        glVertex2f(dx + xCenter, dy + yCenter);
    }
    glEnd();
}



void DrawPolygon(vector<Point> points)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < points.size(); i++)
    {
        glColor3ub(points[i].r, points[i].g, points[i].b);
        glVertex2f(points[i].x, points[i].y);
    }
    glEnd();
}

void DrawButterfly()
{
    float x = 300, y = 500;
    glLineWidth(2);
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 200, 100);
    glVertex2f(x, y);
    glVertex2f(x + 20, y - 6);
    glVertex2f(x - 11, y - 36);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 200, 100);
    glVertex2f(x, y);
    glVertex2f(x + 22.5, y + 12);
    glVertex2f(x + 17, y);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(x - 11, y - 6);
    glVertex2f(x + 11, y + 12);
    glEnd();
}

void DrawButterfly2()
{
    float x = 100, y = 500;
    glLineWidth(3);
    glColor3ub(20, 200, 100);
    FillEllipse(x, y + 24, 11, 9);
    glColor3ub(255, 200, 100);
    FillEllipse(x + 11, y + 9, 11, 18);
    glColor3ub(255, 255, 255);
    FillEllipse(x + 11, y + 6, 5.5, 6);
    glColor3ub(255, 0, 100);
    FillEllipse(x + 11, y + 6, 4, 4.2);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(x + 3, y + 36);
    glVertex2f(x + 25, y + 18);
    glEnd();
}

void DrawButterfly3()
{
    float x = 800, y = 500;
    glLineWidth(3);
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 200, 100);
    glVertex2f(x, y);
    glVertex2f(x, y - 18);
    glVertex2f(x - 17, y - 36);
    glVertex2f(x - 17, y - 18);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 200, 100);
    glVertex2f(x, y);
    glVertex2f(x - 11, y - 3);
    glVertex2f(x - 22.5, y + 3);
    glVertex2f(x - 11, y + 12);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(x - 3, y + 13);
    glVertex2f(x + 3, y - 13);
    glEnd();
}

void DrawGrass()
{
    float x = 500, y = 500;
    glLineWidth(3);
    glColor3ub(152, 251, 152);
    glBegin(GL_LINES);
    glVertex2f(x - 17, y - 30);
    glVertex2f(x, y);
    glVertex2f(x - 5.5, y - 36);
    glVertex2f(x, y);
    glVertex2f(x, y - 42);
    glVertex2f(x, y);
    glVertex2f(x + 11, y - 36);
    glVertex2f(x, y);
    glVertex2f(x + 22.5, y - 18);
    glVertex2f(x, y);
    glVertex2f(x + 22.5, y - 18);
    glVertex2f(x + 25, y - 6);
    glEnd();
}

void DrawGrass2()
{
    float x = 300, y = 500;
    glColor3ub(30, 89, 69);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y - 60);
    glEnd();
    FillEllipse(x - 17, y - 6, 17, 6); 
    FillEllipse(x + 17, y - 6, 17, 6);
    FillEllipse(x - 14, y - 21, 14, 4.8); 
    FillEllipse(x + 14, y - 21, 14, 4.8);
    FillEllipse(x - 11, y - 33, 11, 4.8); 
    FillEllipse(x + 11, y - 33, 11, 4.8);
    FillEllipse(x - 8, y - 45, 8, 3.6); 
    FillEllipse(x + 8, y - 45, 8, 3.6);
    FillEllipse(x, y - 60, 4.5, 12);
}

void AddEllipseStone(float count, float y, float rx, float ry)
{
    float random;
    for (auto i = 0; i < count; i++)
    {
        random = static_cast<float>(rand()) / RAND_MAX + rand() % 16;
        ellipseStones.push_back({ random, y, rand() % 255, rand() % 255, rand() % 255, rx, ry});
    }
}

void AddBubbles(float count, float y)
{
    float r, rSpeed, x;
    for (auto i = 0; i < count; i++)
    {
        r = static_cast<float>(rand()) / RAND_MAX / 5;
        rSpeed = static_cast<float>(rand()) / RAND_MAX/5;
        x = 2.3f + static_cast<float>(rand()) / RAND_MAX;
        boxBubbles.push_back({ x, y, 255, 255, 255, r, r, rSpeed});
    }
}

void AddBubbles2(float count, float x, float y)
{
    float r, rSpeed;
    for (auto i = 0; i < count; i++)
    {
        r = static_cast<float>(rand()) / RAND_MAX / 7;
        rSpeed = 0.04f + static_cast<float>(rand()) / RAND_MAX / 4;
        fishBubbles.push_back({ x, y, 255, 255, 255, r, r, rSpeed});
    }
}

void AddFishes(float count)
{
    float speedFish, x, y, speedY;
    int sign;
    for (auto i = 0; i < count; i++)
    {
        sign = std::rand() % 3;
        speedFish = static_cast<float>(rand()) / RAND_MAX / 4;
        speedY = 0.01;
        if (sign > 1)
        {
            speedY *= -1;
        }
        y = 1.0 + static_cast<float>(rand()) / RAND_MAX + rand() % 4;
        x = static_cast<float>(rand()) / RAND_MAX + rand() % 4;
        coordinatesFish.push_back({ x, y, speedFish, speedY, 255, 255, 255});
    }
}

void ClearBubbles()
{
    boxBubbles.clear();
}

void AddPolygonStones(float count, float countStones, float y)
{
    float randomX, randomY, random;
    Color randomColor;
    for (auto j = 0; j < countStones; j++)
    {
        vector<Point> vect;
        random = static_cast<float>(rand()) / RAND_MAX + rand() % 16;
        randomColor.r = rand() % 255;
        randomColor.g = rand() % 255;
        randomColor.b = rand() % 255;
        for (auto i = 0; i < count; i++)
        {
            randomX = static_cast<float>(rand()) / RAND_MAX/1.5;
            randomY = static_cast<float>(rand()) / RAND_MAX/1.5;
            vect.push_back({ randomX + random, randomY + y, randomColor.r, randomColor.g, randomColor.b, 0, 0 });

        }
        polygonStones.push_back(vect);
    }
}

void DrawHarmonic(float step, float a, float b, float c, float count, float x, float pos) {
    float angle = 0.0f;
    float y = 0.0f;
    while (x <= count)
    {
        y = a * sin(b * x + c) + pos;
        glVertex2f(y, x);
        x += step;
    }

}


void drawScene() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1, 0, 0);
    glLoadIdentity();
    gluOrtho2D(0, 16, 10, 0);
    glMatrixMode(GL_MODELVIEW);


    ///sky///
    points = { {0.0f, 0.0f, 71, 189, 255}, {16.0f, 0.0f, 67, 0, 235}, {16.0f, 10.0f, 67, 0, 235}, {0.0f, 10.0f, 67, 0, 235} };
    DrawPolygon(points);


    //frame
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glColor3ub(0, 0, 0);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(15.9f, 0.1f);
    glVertex2f(15.9f, 9.9f);
    glVertex2f(0.1f, 9.9f);
    glEnd();

    DrawButterfly();
    DrawButterfly2();
    DrawButterfly3();
    DrawGrass();
    DrawGrass2();

    //водоросли
    glPushMatrix();
    glLineWidth(8);
    glBegin(GL_LINE_STRIP);
    glColor3ub(0, 71, 77);
    DrawHarmonic(0.1f, 0.3f, 2.0f, phase3, 10.0f, 3.0f, 15.0f);
    glEnd();

    glLineWidth(8);
    glBegin(GL_LINE_STRIP);
    glColor3ub(0, 136, 194);
    DrawHarmonic(0.1f, 0.3f, 2.0f, phase3, 10.0f, 1.0f, 2.0f);
    glEnd();

    glLineWidth(10);
    glBegin(GL_LINE_STRIP);
    glColor3ub(0, 60, 77);
    DrawHarmonic(0.1f, 0.16f, 3.0f, phase3, 10.0f, 5.0f, 11.0f);
    glEnd();

    glLineWidth(7);
    glBegin(GL_LINE_STRIP);
    glColor3ub(0, 41, 59);
    DrawHarmonic(0.1f, 0.16f, 2.0f, phase3, 10.0f, 4.6f, 9.0f);
    glEnd();
    glPopMatrix();


    //stones
    for (auto &v : polygonStones)
    {
        DrawPolygon(v);
    }

    for (auto& v : ellipseStones)
    {
        glColor3ub(v.r, v.g, v.b);
        FillEllipse(v.x, v.y, v.rx, v.ry);
    }


    //boxBubbles
    glPushMatrix();
    glLineWidth(1);
    for (auto& bubble : boxBubbles)
    {
        glTranslatef(0.0f, bubble.y, 0.0f);
        glColor3ub(255, 255, 255);
        DrawEllipse(bubble.x, 9.0f, bubble.rx, bubble.ry);
    }
    glPopMatrix();

    //box
    //:body
    glPushMatrix();
    points = { {2.0f, 9.8f, 20, 0, 33}, {3.6f, 9.8f, 20, 0, 33}, {3.6f, 8.5f, 59, 44, 39}, {2.0f, 8.5f, 59, 44, 39} };
    DrawPolygon(points);


    //:lid
    glTranslatef(2.0, 8.5, 0.0f);
    glRotatef(angleOpenLib, 0.0f, 0.0f, 1.0f);
    glTranslatef(-2.0f, -8.5f, 0.0f);
    FillHalfEllipse(2.8f, 8.5f, 0.8f, 0.6f);
    points = { {2.0f, 8.7f, 214, 207, 0}, {3.6f, 8.7f, 214, 207, 0}, {3.6f, 8.5f, 214, 207, 0}, {2.0f, 8.5f, 214, 207, 0} };
    DrawPolygon(points);

    glPopMatrix();

    //fish (to right)
    glPushMatrix();
    glTranslatef(moveFishOneRight, 0.0f, 0.0f);

    points = { {0.6f, 3.5f, 20, 0, 33}, {0.6f, 5.5f, 20, 0, 33}, {1.6f, 4.5f, 20, 0, 33} };
    DrawPolygon(points);

    points = { {0.8f, 3.7f, 255, 255, 255}, {0.8f, 5.3f, 255, 255, 255}, {1.6f, 4.5f, 255, 255, 255} };
    DrawPolygon(points);

    points = { {1.0f, 3.9f, 20, 0, 33}, {1.0f, 5.1f, 20, 0, 33}, {1.6f, 4.5f, 20, 0, 33} };
    DrawPolygon(points);

    glColor3ub(255, 255, 255);
    FillEllipse(1.3f, 4.5f, 0.03f, 0.05f);

    DrawPolygon({ {0.0f, 4.1f, 20, 0, 33}, {0.0f, 4.9f, 20, 0, 33}, {0.6f, 4.5f, 20, 0, 33} });

    points = { {0.23f, 4.27f, 255, 255, 255}, {0.23f, 4.73f, 255, 255, 255}, {0.6f, 4.5f, 255, 255, 255} };
    DrawPolygon(points);

    glPopMatrix();

    //fish (to left)
    glPushMatrix();
    glTranslatef(moveFishOneLeft, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glColor3ub(20, 0, 33);
    glVertex2f(-0.6f, 3.5f);
    glVertex2f(-0.6f, 5.5f);
    glVertex2f(-1.6f, 4.5f);
    glEnd();

    points = { {-0.8f, 3.7f, 255, 255, 255}, {-0.8f, 5.3f, 255, 255, 255}, {-1.6f, 4.5f, 255, 255, 255} };
    DrawPolygon(points);

    points = { {-1.0f, 3.9f, 20, 0, 33}, {-1.0f, 5.1f, 20, 0, 33}, {-1.6f, 4.5f, 20, 0, 33} };
    DrawPolygon(points);

    glColor3ub(255, 255, 255);
    FillEllipse(-1.3f, 4.5f, 0.03f, 0.05f);

    glBegin(GL_POLYGON);
    glColor3ub(20, 0, 33);
    glVertex2f(0.0f, 4.1f);
    glVertex2f(0.0f, 4.9f);
    glVertex2f(-0.6f, 4.5f);
    glEnd();
    glPopMatrix();





    //2 fish
    glPushMatrix();
    glTranslatef(2.0, 0.0, 0.0f);
    glTranslatef(4.0, 2.0, 0.0f);
    glTranslatef(moveFishTwoX, moveFishTwoY, 0.0f);
    glRotatef(angleFishTwoZ, 0.0f, 0.0f, 1.0f);
    glTranslatef(-4.0f, -2.0, 0.0f);
    glTranslatef(1.1, 0.0, 0.0f);
    glRotatef(angleFishTwoY, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1.1, 0.0, 0.0f);
    glColor3ub(255, 106, 0);
    FillEllipse(1.6f, 4.0f, 0.6f, 0.4f);
    
    points = { {1.3f, 3.65f, 255, 106, 0}, {0.4f, 4.0f, 255, 106, 0}, {1.3f, 4.35f, 255, 106, 0} };
    DrawPolygon(points);

    points = { {0.2f, 3.65f, 255, 106, 0}, {0.9f, 4.0f, 255, 106, 0}, {0.2f, 4.35f, 255, 106, 0} };
    DrawPolygon(points);

    FillEllipse(0.2f, 4.0f, 0.2f, 0.32f);
    
    FillEllipse(1.6f, 3.6f, 0.25f, 0.2f);
    
    FillEllipse(1.1f, 3.7f, 0.23f, 0.18f);
    
    FillEllipse(1.3f, 4.4f, 0.3f, 0.18f);
    
    glColor3ub(18, 0, 66);

    FillEllipse(2.0f, 3.9f, 0.06f, 0.06f);

    points = { {1.5f, 3.6f, 255, 255, 255}, {1.3f, 4.0f, 255, 255, 255}, {1.5f, 4.4f, 255, 255, 255} };
    DrawPolygon(points);

    glPopMatrix();

    for (auto& bubble : fishBubbles)
    {
        glPushMatrix();
        if (angleFishTwoY != 180)
        {
            glTranslatef(4, 0.0, 0.0f);
        }
        else
        {
            glTranslatef(2, 0.0, 0.0f);
        }
        glTranslatef(0.0, 3.0, 0.0f);
        glTranslatef(bubble.x, bubble.y, 0.0);
        glColor3ub(255, 255, 255);
        DrawEllipse(0, 0, bubble.rx, bubble.ry);
        glPopMatrix();
    }

    for (auto& fish: coordinatesFish)
    {
        glPushMatrix();
        glTranslatef(fish.x, fish.y, 0.0f);
        if (fish.angle == 180.0f)
        {
            glTranslatef(0.8f, 0.0f, 0.0f);
        }
        glRotatef(fish.angle, 0.0f, 1.0f, 0.0f);
        points = { {0, 0, 255, 0, 200}, {0.3f, -0.2f, 0, 245, 216}, {0.7f, 0, 235, 255, 20}, {0.3f, 0.2f, 20, 28, 255} };
        DrawPolygon(points);
        points = { {0.7, 0, 235, 255, 20}, {0.9f, -0.2f, 235, 255, 20}, {0.8f, 0, 235, 255, 20}};
        DrawPolygon(points);
        points = { {0.7, 0, 235, 255, 20}, {0.9f, 0.2f, 235, 255, 20}, {0.8f, 0, 235, 255, 20}};
        DrawPolygon(points);
        glPopMatrix();
    }

    glLineWidth(9);
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(9.0f, 4.4f);
    glVertex2f(9.0f, 1.6f);
    glEnd;

    glutSwapBuffers();
}

void AnimateBubblesOfBox(int value) {

    for (auto& bubble : boxBubbles)
    {
        bubble.y -= bubble.speed;
    }
}
int timeBubblesFish = 0;
void AnimateBubblesFish(int value) {
    if (timeBubblesFish == 200)
    {
        fishBubbles.clear();
        AddBubbles2(3, moveFishTwoX, moveFishTwoY);
        timeBubblesFish = 0;
    }
    else
    {
        for (auto i = 0; i < fishBubbles.size(); i++)
        {
            fishBubbles[i].y -= fishBubbles[i].speed;
        }
    }
    timeBubblesFish++;
    glutTimerFunc(20, AnimateBubblesFish, 0);
    glutPostRedisplay();
}

void AnimateLittleFishs(int value) {

    for (auto& fish : coordinatesFish)
    {
        fish.y += fish.speedY;
        if (fish.x - fish.speedX < 0.1f)
        {
            fish.x = 0.2f;
            fish.angle = 180.0f;
        }
        if (fish.x + fish.speedX > 15.0f)
        {
            fish.angle = 0.0f;
        }
        if (fish.angle == 0.0f)
        {
            fish.x -= fish.speedX;
        }
        else if (fish.angle == 180.0f)
        {
            fish.x += fish.speedX;
        }

        if ((fish.y > 9.6) || (fish.y < 0.3))
        {
            fish.speedY *= -1;
        }
    }
    glutTimerFunc(20, AnimateLittleFishs, 0);
}

void AnimateFishOneLeft(int value) 
{
    if (moveFishOneLeft <= 1.0f + 1.6f / 2)
    {
        moveFishOneLeft = 19.1f;
        isOppositeSide = false;
        moveFishOneRight = 0.0f;
    }
    if (isOppositeSide)
    {
        moveFishOneLeft -= 0.05f;
    }

    glutTimerFunc(20, AnimateFishOneLeft, 0);
}
void AnimateFishOneRight(int value) {


    if (moveFishOneRight >= 15.0f - 1.6f/2)
    {
        moveFishOneRight = -16.0f;
        isOppositeSide = true;
        moveFishOneLeft = 15.0f;
    }
    if (!isOppositeSide)
    {
        moveFishOneRight += 0.05f;
    }
    glutTimerFunc(20, AnimateFishOneRight, 0);
}


void AnimateFishTwo(int value) 
{
    if (angleFishTwoY == 0.0f)
    {
        moveFishTwoX += 0.02f;
        moveFishTwoY += 0.02f;
    }
    else
    {
        moveFishTwoX -= 0.02f;
        moveFishTwoY -= 0.02f;
    }

    if (moveFishTwoX < 0.0f - 1.9f)
    {
        moveFishTwoY += 0.04f;
        moveFishTwoX += 0.02f;
        if (moveFishTwoY > 3.0f)
        {
            angleFishTwoY = 0;
        }
    }
    else if (moveFishTwoX < 15.0f - 3.3f)
    {
        if ((angleFishTwoZ < 20) && (angleFishTwoY == 0))
        {
            angleFishTwoZ += 0.1f;
        }
    }
    else
    {
        moveFishTwoY -= 0.04f;
        moveFishTwoX -= 0.02f;
        if (angleFishTwoZ > 0)
        {
            angleFishTwoZ -= 0.2f;
        }
        if (moveFishTwoY < 3.0f)
        {
            angleFishTwoY = 180;
        }
    }

    if (moveFishTwoY < 0.0f - 2.0f)
    {
        moveFishTwoY += 0.02f;
        //moveFishTwoX += 0.0f;
    }
    else if (moveFishTwoY >= 9.6f/ 2 + 1.2)
    {
        moveFishTwoY -= 0.02f;
        moveFishTwoX -= 0.01f;
    }

    //AddBubbles2(1, moveFishTwoX, 0);
    glutTimerFunc(20, AnimateFishTwo, 0);
    //glutPostRedisplay();
}

void AnimateF(int value)
{
    fishBubbles.clear();
    AddBubbles2(2, moveFishTwoX, moveFishTwoY);
    glutTimerFunc(60, AnimateBubblesFish, 0);
}

void AnimateSeaweed(int value) 
{
    phase1 += 0.1f;
    phase2 += 0.4f;
    phase3 += 0.2f;
    glutTimerFunc(20, AnimateSeaweed, 0); //Notify GLUT to call update again in 25 milliseconds
    //glutPostRedisplay();
}

float timer = 0.0f;
bool b = false;
void update3(int value) {

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    const auto currentTime = std::chrono::steady_clock::now();
    const auto timeSinceStart = currentTime - m_startTime;
    if (b)
    {
        angleOpenLib += 1.0f;
    }
    else
    {
        angleOpenLib -= 1.0f;
    }
    if (angleOpenLib < -90.0)
    {
        angleOpenLib = -90.0;
        AddBubbles(1, 9.0f);
        timer += 0.1f;
    }
    if (angleOpenLib > 0.0)
    {
        angleOpenLib = 0.0;
        ClearBubbles();
        timer += 0.1f;
    }
    if (timer > 20)
    {
        timer = 0;
        b = !b;
    }
    glutTimerFunc(20, AnimateBubblesOfBox, 0);
    glutTimerFunc(10, update3, 0);
}


void update8(int value) 
{

    glutTimerFunc(20, update8, 0); //Notify GLUT to call update again in 25 milliseconds
}

void Init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(drawScene);
    AddPolygonStones(8, 50, 9.7f);
    AddPolygonStones(9, 50, 9.6f);
    AddEllipseStone(100, 9.8f, 0.1f, 0.05f);
    AddEllipseStone(100, 9.9f, 0.1f, 0.08f);
    AddEllipseStone(70, 9.8f, 0.2f, 0.11f);
    AddEllipseStone(100, 9.5f, 0.1f, 0.06f);
    AddEllipseStone(100, 9.6f, 0.15f, 0.08f);
    AddEllipseStone(50, 9.4f, 0.1f, 0.09f);
    AddFishes(10);

    glutTimerFunc(20, AnimateFishOneRight, 0);
    glutTimerFunc(20, AnimateFishOneLeft, 0); //Add a timer
    glutTimerFunc(20, AnimateSeaweed, 0);
    glutTimerFunc(10, AnimateBubblesOfBox, 0);
    glutTimerFunc(10, AnimateFishTwo, 0);
    glutTimerFunc(20, AnimateLittleFishs, 0);
    glutTimerFunc(20, AnimateBubblesFish, 0);
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    m_startTime = std::chrono::steady_clock::now();






    glutInitWindowSize(1000, 600);
    glutCreateWindow("Transformation");


    Init();


    //Timer();


    glutTimerFunc(10, update3, 0);
    //glutKeyboardFunc(handleKeypress);

    //glutMouseFunc(handleMouse);
    glutMainLoop();
    return 0;
}