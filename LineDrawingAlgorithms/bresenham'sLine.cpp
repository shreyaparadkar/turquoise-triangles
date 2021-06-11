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

    glutCreateWindow("Bresenham's");

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

    int dx, dy, p;
    int incx = 1, incy = 1;
    int x, y;

    dx = abs(::a2 - ::a1);
    dy = abs(::b2 - ::b1);

    //set is slope is negative
    if (::a2 < ::a1)
        incx = -1;
    if (::b2 < ::b1)
        incy = -1;

    x = ::a1;
    y = ::b1;

    glBegin(GL_POINTS);
    //less than 45deg
    if (dx > dy)
    {
        glVertex2d(x, y);
        p = 2 * dy - dx;
        for (int i = 0; i < dx; i++)
        {
            if (p >= 0)
            {
                y += incy;
                p += 2 * (dy - dx);
            }
            else
                p += 2 * dy;
            x += incx;
            glVertex2d(x, y);
        }
    }
    //slope greater than 45deg
    else
    {
        glVertex2d(x, y);
        p = 2 * dx - dy;
        for (int i = 0; i < dy; i++)
        {
            if (p >= 0)
            {
                x += incx;
                p += 2 * (dx - dy);
            }
            else
                p += 2 * dx;
            y += incy;
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
