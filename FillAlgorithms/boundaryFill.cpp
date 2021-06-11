#include <iostream>
#include <GL/glut.h>

using namespace std;

void init();
void display();
void colorOnClick(int, int, int, int);
void boundaryFill(int, int, float *, float *);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(450, 450);
    glutCreateWindow("Boundary Fill");
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

void boundaryFill(int x, int y, float *fillColor, float *bc)
{
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) && (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2]))
    {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        boundaryFill(x + 1, y, fillColor, bc);
        boundaryFill(x - 1, y, fillColor, bc);
        boundaryFill(x, y + 1, fillColor, bc);
        boundaryFill(x, y - 1, fillColor, bc);
    }
}

void colorOnClick(int btn, int state, int x, int y)
{
    y = 450 - y;
    if (btn == GLUT_LEFT_BUTTON)
    {
        float bCol[] = {1, 0, 0};
        float color[] = {1, 1, 0};
        boundaryFill(x, y, color, bCol);
    }
}

void display()
{
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 100);
    glVertex2i(150, 200);
    glVertex2i(250, 200);
    glVertex2i(250, 100);
    glEnd();
    glFlush();
}
