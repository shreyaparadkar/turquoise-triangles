#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

void display();
void reshape(int, int);
void drawCube(GLfloat[8][3]);
void translate(int, int, int);
void rotateX(float);
void rotateY(float);
void rotateZ(float);
void scale(int, int, int);
void reflectXY();
void reflectYZ();
void reflectZX();
void shearX(float, float);
void shearY(float, float);
void shearZ(float, float);
void multiplyM();

typedef float Matrix4[4][4];

Matrix4 multiplicationMatrix;

int option;
int x = 3, y = 3, z = 3;

static GLfloat cube[8][3] =
    {
        {-::x, -::y, -::z}, {::x, -::y, -::z}, {::x, ::y, -::z}, {-::x, ::y, -::z}, {-::x, -::y, ::z}, {::x, -::y, ::z}, {::x, ::y, ::z}, {-::x, ::y, ::z}};

GLfloat transformedCube[8][3];

int main(int argc, char **argv)
{
    cout << "Choose one of the below operations: " << endl;
    cout << "1 - Translation\n2 - Rotation\n3 - Scaling\n4 - Reflection\n5 - Shearing" << endl;
    cout << "Enter option: ";
    cin >> ::option;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);

    glutInitWindowPosition(450, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("3D tranformations");
    glClearColor(0.050, 0.062, 0.070, 0.1f);
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //to get the cube inside the visible frustrum
    glTranslatef(0, 0, -45);
    //to rotate get the 3d look of cube
    glRotatef(60, 1, 1, 0);

    drawCube(::cube);
    glFlush();

    float a, b, c;
    char axis;

    switch (::option)
    {
    case 1:
        cout << "Enter value to translate by in x, y and z direction: ";
        cin >> a >> b >> c;
        translate(a, b, c);
        break;
    case 2:
        cout << "Enter axis of rotation and angle of rotation: ";
        cin >> axis >> a;
        switch (char(tolower(axis)))
        {
        case 'x':
            rotateX(a);
        case 'y':
            rotateY(a);
        case 'z':
            rotateZ(a);
        default:
            break;
        }
        multiplyM();
        break;
    case 3:
        cout << "Enter value to scale in x, y and z direction: ";
        cin >> a >> b >> c;
        scale(a, b, c);
        multiplyM();
        break;
    case 4:
        cout << "Choose plane for reflection: \n1 for XY place\n2 for YZ place\n3 for ZX place\nEnter option: ";
        cin >> axis;
        switch (axis)
        {
        case '1':
            reflectXY();
        case '2':
            reflectYZ();
        case '3':
            reflectZX();
        default:
            break;
        }
        multiplyM();
        break;
    case 5:
        cout << "Enter axis for shearing: ";
        cin >> axis;
        switch (char(tolower(axis)))
        {
        case 'x':
            cout << "Enter value for shearing in y and z direction: ";
            cin >> a >> b;
            shearX(a, b);
            break;
        case 'y':
            cout << "Enter value for shearing in x and z direction: ";
            cin >> a >> b;
            shearY(a, b);
            break;
        case 'z':
            cout << "Enter value for shearing in x and y direction: ";
            cin >> a >> b;
            shearZ(a, b);
            break;
        default:
            break;
        }
        multiplyM();
        break;
    default:
        break;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawCube(::transformedCube);
    glFlush();
}

void drawCube(float a[8][3])
{
    glBegin(GL_QUADS);
    glColor3f(0, 1, 1); //behind cyan
    glVertex3fv(a[0]);
    glVertex3fv(a[1]);
    glVertex3fv(a[2]);
    glVertex3fv(a[3]);

    glColor3f(0, 1, 0); //bottom green
    glVertex3fv(a[0]);
    glVertex3fv(a[1]);
    glVertex3fv(a[5]);
    glVertex3fv(a[4]);

    glColor3f(1, 0, 0); //left red
    glVertex3fv(a[0]);
    glVertex3fv(a[4]);
    glVertex3fv(a[7]);
    glVertex3fv(a[3]);

    glColor3f(1, 0, 1); //right pink
    glVertex3fv(a[1]);
    glVertex3fv(a[2]);
    glVertex3fv(a[6]);
    glVertex3fv(a[5]);

    glColor3f(1, 1, 0); //up yellow
    glVertex3fv(a[2]);
    glVertex3fv(a[3]);
    glVertex3fv(a[7]);
    glVertex3fv(a[6]);

    glColor3f(0, 0, 1); //front blue
    glVertex3fv(a[4]);
    glVertex3fv(a[5]);
    glVertex3fv(a[6]);
    glVertex3fv(a[7]);

    glEnd();
}

void translate(int tx, int ty, int tz)
{
    for (int i = 0; i < 8; i++)
    {
        ::transformedCube[i][0] = ::cube[i][0] + tx;
        ::transformedCube[i][1] = ::cube[i][1] + ty;
        ::transformedCube[i][2] = ::cube[i][2] + tz;
    }
}

void rotateX(float angle) //Parallel to x
{
    angle = angle * 3.142 / 180;
    ::multiplicationMatrix[1][1] = cos(angle);
    ::multiplicationMatrix[1][2] = -sin(angle);
    ::multiplicationMatrix[2][1] = sin(angle);
    ::multiplicationMatrix[2][2] = cos(angle);
}

void rotateY(float angle) //parallel to y
{
    angle = angle * 3.14 / 180;
    ::multiplicationMatrix[0][0] = cos(angle);
    ::multiplicationMatrix[0][2] = -sin(angle);
    ::multiplicationMatrix[2][0] = sin(angle);
    ::multiplicationMatrix[2][2] = cos(angle);
}

void rotateZ(float angle) //parallel to z
{
    angle = angle * 3.14 / 180;
    ::multiplicationMatrix[0][0] = cos(angle);
    ::multiplicationMatrix[0][1] = sin(angle);
    ::multiplicationMatrix[1][0] = -sin(angle);
    ::multiplicationMatrix[1][1] = cos(angle);
}

void scale(int sx, int sy, int sz)
{
    ::multiplicationMatrix[0][0] = sx;
    ::multiplicationMatrix[1][1] = sy;
    ::multiplicationMatrix[2][2] = sz;
}

void reflectXY()
{
    ::multiplicationMatrix[0][0] = 1;
    ::multiplicationMatrix[1][1] = 1;
    ::multiplicationMatrix[2][2] = -1;
    ::multiplicationMatrix[3][3] = 1;
}

void reflectYZ()
{
    ::multiplicationMatrix[0][0] = -1;
    ::multiplicationMatrix[1][1] = 1;
    ::multiplicationMatrix[2][2] = 1;
    ::multiplicationMatrix[3][3] = 1;
}

void reflectZX()
{
    ::multiplicationMatrix[0][0] = 1;
    ::multiplicationMatrix[1][1] = -1;
    ::multiplicationMatrix[2][2] = 1;
    ::multiplicationMatrix[3][3] = 1;
}

void shearX(float sy, float sz)
{
    ::multiplicationMatrix[0][0] = 1;
    ::multiplicationMatrix[1][1] = 1;
    ::multiplicationMatrix[2][2] = 1;
    ::multiplicationMatrix[3][3] = 1;
    ::multiplicationMatrix[2][0] = sy;
    ::multiplicationMatrix[3][0] = sz;
}

void shearY(float sx, float sz)
{
    ::multiplicationMatrix[0][0] = 1;
    ::multiplicationMatrix[1][1] = 1;
    ::multiplicationMatrix[2][2] = 1;
    ::multiplicationMatrix[3][3] = 1;
    ::multiplicationMatrix[0][1] = sx;
    ::multiplicationMatrix[2][1] = sz;
}

void shearZ(float sx, float sy)
{
    ::multiplicationMatrix[0][0] = 1;
    ::multiplicationMatrix[1][1] = 1;
    ::multiplicationMatrix[2][2] = 1;
    ::multiplicationMatrix[3][3] = 1;
    ::multiplicationMatrix[0][2] = sx;
    ::multiplicationMatrix[1][2] = sy;
}

void multiplyM()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ::transformedCube[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                ::transformedCube[i][j] = ::transformedCube[i][j] + ::cube[i][k] * multiplicationMatrix[k][j];
            }
        }
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 10, 50);
    glMatrixMode(GL_MODELVIEW);
}
