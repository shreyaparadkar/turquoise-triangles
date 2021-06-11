#include <GL/glut.h>
#include <string.h>

void display();
void reshape(int, int);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 290);

    glutCreateWindow("Visual Studio Logo");
    glClearColor(0.129, 0.105, 0.152, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //creating logo of Visual Studio

    //right polygon
    glColor3f(0.694, 0.470, 0.937);
    glBegin(GL_POLYGON);
    glVertex2d(2, 6.5);
    glVertex2d(3.8, 4.8);
    glVertex2d(3.8, -4.8);
    glVertex2d(2, -6.5);
    glEnd();

    //diagonal polygon
    glColor3f(0.415, 0.2, 0.682);
    glBegin(GL_POLYGON);
    glVertex2d(2, 6.5);
    glVertex2d(2, 3);
    glVertex2d(-3, -4);
    glVertex2d(-3.5, -3);
    glEnd();

    //diagonal polygon 2
    glColor3f(0.517, 0.298, 0.776);
    glBegin(GL_POLYGON);
    glVertex2d(2, -3);
    glVertex2d(2, -6.5);
    glVertex2d(-3.5, 3);
    glVertex2d(-3, 4);
    glEnd();

    //left ploygon
    glColor3f(0.317, 0.125, 0.533);
    glBegin(GL_POLYGON);
    glVertex2d(-3.5, 3);
    glVertex2d(-2.8, 1.85);
    glVertex2d(-2.8, -1.85);
    glVertex2d(-3.5, -3);
    glEnd();

    //text
    const char text[] = "Visual Studio";
    glColor3f(0.768, 0.631, 0.909);
    glRasterPos2f(-2, -8.6);
    int len;
    len = (int)strlen(text);
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    }

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
