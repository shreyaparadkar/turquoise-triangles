#include <iostream>
#include <GL/glut.h>
using namespace std;

void init();
void display();
void colorOnClick(int, int, int, int);
void floodFill(int, int, float *, float *);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(450, 450);
    glutCreateWindow("Flood Fill");
    glutDisplayFunc(display);
    glutMouseFunc(colorOnClick);
    init();
    glutMainLoop();
    return 0;
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 450, 0, 450);
}

void floodFill(int x, int y, float *fillColor, float *defaultColor)
{
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    if (color[0] == defaultColor[0] && color[1] == defaultColor[1] && color[2] == defaultColor[2])
    {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        floodFill(x + 1, y, fillColor, defaultColor);
        floodFill(x - 1, y, fillColor, defaultColor);
        floodFill(x, y + 1, fillColor, defaultColor);
        floodFill(x, y - 1, fillColor, defaultColor);
    }
}

void colorOnClick(int btn, int state, int x, int y)
{
    y = 450 - y;
    if (btn == GLUT_LEFT_BUTTON)
    {
        float defaultColor[] = {1, 1, 1};
        float fillColor[] = {0, 1, 1};
        floodFill(x, y, fillColor, defaultColor);
    }
}

void display()
{
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(250, 300);
    glVertex2i(400, 100);
    glEnd();
    glFlush();
}
