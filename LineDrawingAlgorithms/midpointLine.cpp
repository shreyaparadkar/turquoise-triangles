#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

void display();
void reshape(int, int);
void drawLine();

int a1, b1, a2, b2;

int main(int argc, char **argv)
{
    cout << "Enter coordinates of start point: ";
    cin >> ::a1 >> ::b1;
    cout << "Enter coordinates of end point: ";
    cin >> ::a2 >> ::b2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(450, 450);

    glutCreateWindow("Mid-point line drawing");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawLine();

    glFlush();
}

void drawLine()
{
    glPointSize(1.5);

    if (::a1 > ::a2)
    {
        int temp_a = ::a1;
        int temp_b = ::b1;
        ::a1 = ::a2;
        ::b1 = ::b2;
        ::a2 = temp_a;
        ::b2 = temp_b;
    }

    int dx = abs(::a2 - ::a1);
    int dy = abs(::b2 - ::b1);

    int incx = 1, incy = 1;
    if (::a2 < ::a1)
        incx = -1;
    if (::b2 < ::b1)
        incy = -1;

    int x = ::a1, y = ::b1;

    glBegin(GL_POINTS);

    if (dy <= dx)
    {
        int d = dy - (dx / 2);
        glVertex2d(x, y);
        while (x < ::a2)
        {
            x += incx;
            if (d < 0)
                d += dy;
            else
            {
                d += dy - dx;
                y += incy;
            }
            glVertex2d(x, y);
        }
    }
    else
    {
        int d = dx - (dy / 2);
        glVertex2d(x, y);
        while (y < ::b2)
        {
            y += incy;
            if (d < 0)
                d += dx;
            else
            {
                d += dx - dy;
                x += incx;
            }
            glVertex2d(x, y);
        }
    }
    glEnd();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);

    glMatrixMode(GL_MODELVIEW);
}
