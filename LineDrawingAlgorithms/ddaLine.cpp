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

    glutCreateWindow("DDA");

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
    float dx = ::a2 - ::a1;
    float dy = ::b2 - ::b1;

    float steps;
    if (abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    float x_increment = dx / steps;
    float y_increment = dy / steps;

    float x = ::a1;
    float y = ::b1;

    for (int i = 0; i < steps; i++)
    {
        glBegin(GL_POINTS);
        glVertex2i(round(x), round(y));
        x += x_increment;
        y += y_increment;
        glEnd();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);

    glMatrixMode(GL_MODELVIEW);
}
