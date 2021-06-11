#include <GL/glut.h>
#include <string.h>

void display();
void reshape(int, int);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 250);

    glutCreateWindow("Banner");
    glClearColor(0.18, 0.15, 0.25, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //outer box
    glPushAttrib(GL_ENABLE_BIT);
    glColor3f(0.752, 0.635, 0.925);
    glLineStipple(1, 0xCCCC);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_STRIP);
    glVertex2f(6.5, 3.5);
    glVertex2f(-6.3, 3.5);
    glVertex2f(-6.3, -6.5);
    glVertex2f(6.5, -6.5);
    glEnd();
    glPopAttrib();

    //inner box
    glPushAttrib(GL_ENABLE_BIT);
    glColor3f(0.635, 0.913, 0.925);
    glLineStipple(1, 0xEEEE);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-6, 3);
    glVertex2f(6.5, 3);
    glVertex2f(6.5, -6);
    glVertex2f(-6, -6);
    glEnd();
    glPopAttrib();

    //text
    const char text[] = "CONVERSE";
    glColor3f(1, 1, 1);
    glRasterPos2f(-2.6, -1);
    int len;
    len = (int)strlen(text);
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    //line
    glColor3f(0.752, 0.635, 0.925);
    glBegin(GL_LINES);
    glVertex2d(-3.5, -2.1);
    glVertex2d(3.5, -2.1);
    glEnd();

    //secondary text
    const char text2[] = "Shoes are boring. Wear Sneakers.";
    glColor3f(0.874, 0.980, 0.988);
    glRasterPos2f(-5, -4);
    int len1;
    len1 = (int)strlen(text2);
    for (int i = 0; i < len1; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text2[i]);
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
