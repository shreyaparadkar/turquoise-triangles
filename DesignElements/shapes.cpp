#include <GL/glut.h>
#include <corecrt_math.h>

void display();
void reshape(int, int);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(600, 600);

    glutCreateWindow("Shapes");
    glClearColor(0.098, 0.086, 0.113, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //dashed line
    glColor3f(0.917, 0.8, 0.960);
    glPushAttrib(GL_ENABLE_BIT);
    glLineStipple(1, 0xEEEE);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex2d(-7, 7);
    glVertex2d(0, 7);
    glEnd();
    glPopAttrib();

    //arc
    glColor3f(0.745, 0.976, 0.960);
    glBegin(GL_LINE_STRIP);
    int num_segments = 100;
    int r = 3;
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 3.0f * 3.1415926f / 4.0f * float(ii) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + 4, y + 5);
    }
    glEnd();

    //square
    glColor3f(0.752, 0.423, 0.517);
    glBegin(GL_QUADS);
    glVertex2d(-8.0, 4.0);
    glVertex2d(-3.0, 4.0);
    glVertex2d(-3.0, 0.0);
    glVertex2d(-8.0, 0.0);
    glEnd();

    //polygon
    glColor3f(0.878, 0.760, 0.937);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 4);
    glVertex2f(2, 3);
    glVertex2f(2, 0);
    glVertex2f(-2, 0);
    glVertex2f(-2, 3);
    glEnd();

    //triangle
    glColor3f(0.509, 0.760, 0.890);
    glBegin(GL_TRIANGLES);
    glVertex2d(6, 4);
    glVertex2d(3, 0);
    glVertex2d(9, 0);
    glEnd();

    //circle
    glColor3f(0.623, 0.215, 0.901);
    int x = -4;
    int y = -4;
    int radius = 3;
    double twicePi = 2.0 * 3.142;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 50; i++)
    {
        glVertex2f(
            (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20))));
    }
    glEnd();

    //ellipse
    glColor3f(0.960, 0.678, 0.847);
    float theta = 2 * 3.1415926 / float(num_segments);
    float x1 = -4;
    float y1 = -4;
    float rx = 0.5;
    float ry = 0.25;
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f((x1 + 8) * rx, (y1 - 15) * ry);
        //apply the rotation matrix
        float t = x1;
        x1 = cosf(theta) * x1 - sinf(theta) * y1;
        y1 = sinf(theta) * t + cosf(theta) * y1;
    }
    glEnd();

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);

    glMatrixMode(GL_MODELVIEW);
}