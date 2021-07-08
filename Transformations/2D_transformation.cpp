#include <GL/glut.h>
#include <iostream>

using namespace std;

void display();
void reshape(int, int);
void translate(float, float);
void rotate(float);
void scale(float, float);
void reflection(char);
void shearing(char, float);

int option;
int x = 150, y = 150;
int xCoords[] = { -::x,::x,::x,-::x };
int yCoords[] = { ::y, ::y, -::y, -::y };

int main(int argc, char** argv) {
    cout << "Choose one of the below operations: " << endl;
    cout << "1 - Translation\n2 - Rotation\n3 - Scaling\n4 - Reflection\n5 - Shearing" << endl;
    cout << "Enter option: ";
    cin >> ::option;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("2D tranformations");
    glClearColor(0.050, 0.062, 0.070, 0.1f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3ub(170, 217, 238);
    glPointSize(2);

    glPushAttrib(GL_ENABLE_BIT);
    glLineStipple(1, 0xEEEE);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
    {
        glVertex2i(::xCoords[i], ::yCoords[i]);
    }
    glEnd();
    glPopAttrib();

    glFlush();

    glColor3ub(199, 247, 171);

    float a, b;
    char axis;

    switch (::option)
    {
    case 1:
        cout << "Enter value to translate by in x and y direction: ";
        cin >> a >> b;
        translate(a, b);
        break;
    case 2:
        cout << "Enter angle of rotation ";
        cin >> a;
        rotate(a);
        break;
    case 3:
        cout << "Enter value to scale in x and y direction: ";
        cin >> a >> b;
        scale(a, b);
        break;
    case 4:
        cout << "Enter axis for reflection: ";
        cin >> axis;
        reflection(axis);
        break;
    case 5:
        cout << "Enter axis for shearing and its value: ";
        cin >> axis >> a;
        shearing(axis, a);
        break;
    default:
        break;
    }

}

void translate(float a, float b) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
    {
        glVertex2i(round(::xCoords[i] + a), round(::yCoords[i] + b));
    }
    glEnd();
    glFlush();
}

void rotate(float theta) {
    theta = theta * (3.14 / 180);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
    {
        glVertex2i(
            round((::xCoords[i] * cos(theta)) - (::yCoords[i] * sin(theta))),
            round((::xCoords[i] * sin(theta)) + (::yCoords[i] * cos(theta))));
    }
    glEnd();
    glFlush();
}

void scale(float a, float b) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
    {
        glVertex2i(round(::xCoords[i] * a), round(::yCoords[i] * b));
    }
    glEnd();
    glFlush();
}

void reflection(char axis) {
    glBegin(GL_LINE_LOOP);
    if (axis == 'x' || axis == 'X') {
        for (int i = 0; i < 4; i++) {
            glVertex2i(xCoords[i] - ::x * 2, yCoords[i] * (-1));
        }
    }
    else {
        for (int i = 0; i < 4; i++) {
            glVertex2i(xCoords[i] * -1, yCoords[i] - ::y * 2);
        }
    }
    glEnd();
    glFlush();
}

void shearing(char axis, float a) {
    glBegin(GL_LINE_LOOP);
    if (axis == 'x' || axis == 'X') {
        glVertex2i(xCoords[0] + a, yCoords[0]);

        glVertex2i(xCoords[1] + a, yCoords[1]);
        glVertex2i(xCoords[2], yCoords[2]);

        glVertex2i(xCoords[3], yCoords[3]);
    }
    else {
        glVertex2i(xCoords[0], yCoords[0]);
        glVertex2i(xCoords[1], yCoords[1] + a);

        glVertex2i(xCoords[2], yCoords[2] + a);
        glVertex2i(xCoords[3], yCoords[3]);
    }
    glEnd();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
    glMatrixMode(GL_MODELVIEW);
}
