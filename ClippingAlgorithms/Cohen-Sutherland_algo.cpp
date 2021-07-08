#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

float a1, b1, a2, b2;
float xmin = -100;
float ymin = -100;
float xmax = 100;
float ymax = 100;

void display();
void reshape(int, int);
void clipOnKeyPress(unsigned char, int, int);
void cohenSutherlandAlgo();
int code(float, float);

int main(int argc, char **argv)
{

    cout << "Enter start coordinates: ";
    cin >> ::a1 >> ::b1;
    cout << "Enter end coordinates: ";
    cin >> ::a2 >> ::b2;
    cout << "Press enter to clip the line";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Cohen-Sutherland Algorithm");
    glClearColor(0.070, 0.070, 0.090, 0.1f);

    glutDisplayFunc(display);
    glutKeyboardFunc(clipOnKeyPress);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //window
    glColor3f(1, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(::xmin, ::ymin);
    glVertex2i(::xmin, ::ymax);
    glVertex2i(::xmax, ::ymax);
    glVertex2i(::xmax, ::ymin);
    glEnd();

    //complete line
    glColor3f(0, 1, 1);
    glBegin(GL_LINES);
    glVertex2i(::a1, ::b1);
    glVertex2i(::a2, ::b2);
    glEnd();

    glFlush();
}

void clipOnKeyPress(unsigned char key, int x, int y)
{
    if (key == 13)
    {
        cohenSutherlandAlgo();
        glFlush();
    }
}

int code(float x, float y)
{
    int c = 0;
    if (y > ymax)
        c = 8;
    if (y < ymin)
        c = 4;
    if (x > xmax)
        c = c | 2;
    if (x < xmin)
        c = c | 1;
    return c;
}

void cohenSutherlandAlgo()
{
    int c1 = code(::a1, ::b1);
    int c2 = code(::a2, ::b2);
    float m = (::b2 - ::b1) / (::a2 - ::a1);
    while ((c1 | c2) > 0)
    {
        if ((c1 & c2) > 0)
        {
            exit(0);
        }

        float xi = ::a1;
        float yi = ::b1;
        int c = c1;
        if (c == 0)
        {
            c = c2;
            xi = ::a2;
            yi = ::b2;
        }
        float x, y;
        if ((c & 8) > 0)
        {
            y = ymax;
            x = xi + 1.0 / m * (ymax - yi);
        }
        else if ((c & 4) > 0)
        {
            y = ymin;
            x = xi + 1.0 / m * (ymin - yi);
        }
        else if ((c & 2) > 0)
        {
            x = xmax;
            y = yi + m * (xmax - xi);
        }
        else if ((c & 1) > 0)
        {
            x = xmin;
            y = yi + m * (xmin - xi);
        }

        if (c == c1)
        {
            ::a1 = x;
            ::b1 = y;
            c1 = code(::a1, ::b1);
        }

        if (c == c2)
        {
            ::a2 = x;
            ::b2 = y;
            c2 = code(::a2, ::b2);
        }
    }

    display();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
    glMatrixMode(GL_MODELVIEW);
}