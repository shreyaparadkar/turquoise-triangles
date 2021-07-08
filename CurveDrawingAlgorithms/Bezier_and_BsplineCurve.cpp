#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

void display();
void reshape(int, int);
void bezierCurve();
void bsplineCurve();

int num = 4;
float xCoords[4], yCoords[4];

int main(int argc, char **argv)
{
    int t1, t2;
    cout << "Enter values of 4 vertices" << endl;
    ;
    for (int i = 0; i < ::num; i++)
    {
        cout << "Enter x and y coordinates of vertice " << i << ": ";
        cin >> t1 >> t2;
        xCoords[i] = t1;
        yCoords[i] = t2;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(450, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Curve drawing algorithms");
    glClearColor(0.050, 0.062, 0.070, 0.1f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    int option;
    cout << "Choose 1 for bezier curve and 2 for b-spline: ";
    cin >> option;
    if (option == 1)
        bezierCurve();
    else
        bsplineCurve();
    glFlush();
}

void bezierCurve()
{
    glPointSize(1.5);
    glBegin(GL_POINTS);
    for (float t = 0.0; t <= 1.0; t = t + 0.0001)
    {
        float x = pow(1 - t, 3) * xCoords[0] + 3 * t * pow(1 - t, 2) * xCoords[1] + 3 * t * t * (1 - t) * xCoords[2] + pow(t, 3) * xCoords[3];
        float y = pow(1 - t, 3) * yCoords[0] + 3 * t * pow(1 - t, 2) * yCoords[1] + 3 * t * t * (1 - t) * yCoords[2] + pow(t, 3) * yCoords[3];
        glVertex2f(x, y);
    }
    glEnd();
}

float B0(float u)
{
    return float(pow(1 - u, 3) / 6.0);
}

float B1(float u)
{
    return float((3 * pow(u, 3) - 6 * pow(u, 2) + 4) / 6.0);
}

float B2(float u)
{
    return float((-3 * pow(u, 3) + 3 * pow(u, 2) + 3 * u + 1) / 6.0);
}

float B3(float u)
{
    return float(pow(u, 3) / 6.0);
}

void bsplineCurve()
{
    glPointSize(1.5);
    int MAX_STEPS = 100;
    glBegin(GL_POINTS);
    for (int j = 0; j <= MAX_STEPS; j++)
    {

        float u = float(j) / float(MAX_STEPS);

        float Qx = B0(u) * xCoords[0] + B1(u) * xCoords[1] + B2(u) * xCoords[2] + B3(u) * xCoords[3];
        float Qy = B0(u) * yCoords[0] + B1(u) * yCoords[1] + B2(u) * yCoords[2] + B3(u) * yCoords[3];

        glVertex2f(Qx, Qy);
    }
    glEnd();
}

void reshape(int w, int h)
{
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
    glMatrixMode(GL_MODELVIEW);
}
