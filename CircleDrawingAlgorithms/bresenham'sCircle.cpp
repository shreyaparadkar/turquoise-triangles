#include <GL/glut.h>
#include <iostream>

float px, py, r;

void display();
void reshape(int, int);
void plot(int, int);

int main(int argc, char **argv)
{

    std::cout << "Enter center coordinates: ";
    std::cin >> ::px >> ::py;
    std::cout << "Enter radius: ";
    std::cin >> ::r;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Bresenham’s circle drawing algorithm");
    glClearColor(0.070, 0.070, 0.090, 0.1f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(::px + x, ::py + y);
    glVertex2i(::px + x, ::py - y);
    glVertex2i(::px + y, ::py + x);
    glVertex2i(::px + y, ::py - x);
    glVertex2i(::px - x, ::py - y);
    glVertex2i(::px - y, ::py - x);
    glVertex2i(::px - x, ::py + y);
    glVertex2i(::px - y, ::py + x);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    int x = 0, y = r, k;
    float pk = (5.0 / 4.0) - r;
    plot(x, y);
    while (x < y)
    {
        x = x + 1;
        if (pk < 0)
            pk = pk + 2 * x + 1;
        else
        {
            y = y - 1;
            pk = pk + 2 * (x - y) + 1;
        }
        plot(x, y);
    }
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
    glMatrixMode(GL_MODELVIEW);
}
