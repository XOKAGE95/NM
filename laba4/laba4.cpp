#include <iostream>
#include <math.h>
#include <glut.h>

const double a = 0;
const double b = 0.3;

double lengthX;
double lengthY;
double xx0, xx1;
double yy0, yy1;
double zz0, zz1;

using namespace std;

double f1(double x, double y, double z) { return -2*x*y + z - x -1;}
double f2(double x, double y, double z) { return -1/2 - y - x/z;}
bool FourthOrderAccuracy(void);
bool SecondOrderAccuracy(void);
void Cartoon();
void ChangeSize1(int w, int h);
void CoordinateSystem();

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("task1");
    glutDisplayFunc(Cartoon);
    glutReshapeFunc(ChangeSize1);
    glutMainLoop();
    return 0;
}

void Cartoon()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem();
    glLoadIdentity();

    glLineWidth(3);
    SecondOrderAccuracy();
    glLineWidth(1);
    FourthOrderAccuracy();
    glutSwapBuffers();

}

void ChangeSize1(int w, int h)
{
    xx0 = -0.5;
    xx1 = 0.5;
    yy0 = -0.1;
    yy1 = 1.5;
    zz0= -100.0;
    zz1 = 100.0;
    if(h == 0)
        h = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glOrtho(xx0, xx1, yy0, yy1, zz0, zz1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CoordinateSystem()
{
    lengthX = abs((xx1 - xx0)/150);
    lengthY = abs((yy1 - yy0)/150);
    glLineWidth(1.0);
    glColor3d(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2d(xx0, 0);
    glVertex2d(xx1, 0);
    glVertex2d(0, yy0);
    glVertex2d(0, yy1);
    for(int i = xx0; i < xx1; i++)
    {
        glVertex2d(i, lengthY);
        glVertex2d(i, -lengthY);
    }
    for(int i = yy0; i < yy1; i++)
    {
        glVertex2d(lengthX, i);
        glVertex2d(-lengthX, i);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2d(xx1, 0);
    glVertex2d(xx1 - lengthX*4, lengthY*2);
    glVertex2d(xx1 - lengthX*4, -lengthY*2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2d(0, yy1);
    glVertex2d(lengthX*2, yy1 - lengthY*4);
    glVertex2d(-lengthX*2, yy1 - lengthY*4);
    glEnd();

    glRasterPos3f(xx1 - lengthX * 4, 0 + lengthY * 4, 0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');

    glRasterPos3f(0 + lengthX * 4, yy1 - lengthY * 4, 0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
}

bool FourthOrderAccuracy(void)
{
    double h = 0.001;
    double UY = 1;
    double UZ = 1;

    glBegin(GL_LINES);
    for (double i = a + h; i <= b; i+= h)
    {
        double k = h*f1(i, UY, UZ);
        double m = h*f2(i, UY, UZ);

        double k2 = h*f1(i + h/2, UY + k/2,UZ + m/2);
        double m2 = h*f2(i + h/2, UY + k/2, UZ + m/2);

        double k3 = h*f1(i + h/2, UY + k2/2, UZ + m2/2);
        double m3 = h*f2(i + h/2, UY + k2/2, UZ + m2/2);

        double k4 = h*f1(i + h, UY + k3, UZ + m3);
        double m4 = h*f2(i + h, UY + k3, UZ + m3);

        double UYk = UY + (k + 2*k2 + 2*k3 + k4)/6;
        double UZk = UZ + (m + 2*m2 + 2*m3 + m4)/6;

        glColor3ub(255, 0, 0);
        glVertex3d(i, UY, 0.0);
        glVertex3d(i, UYk, 0.0);

        glColor3ub(0, 0, 255);
        glVertex3d(i, UZ, 0.0);
        glVertex3d(i, UZk, 0.0);

        UY = UYk;
        UZ = UZk;
    }
    glEnd();
    return true;
}

bool SecondOrderAccuracy(void)
{
    double h = 0.001;
    double UY = 1;
    double UZ = 1;
    glBegin(GL_LINES);
    for (double i = a + h; i <= b; i+= h)
    {

        double UYk = UY + h*f1(i + h/2, UY + h*f1(i, UY, UZ)/2, UZ + h*f1(i, UY, UZ)/2);
        double UZk = UZ + h*f2(i + h/2, UY + h*f1(i, UY, UZ)/2, UZ + h*f1(i, UY, UZ)/2);

        glColor3ub(255, 255, 0); // Yellow
        glVertex3d(i, UY, 0.0);
        glVertex3d(i, UYk, 0.0);

        glColor3ub(0, 255, 100); //Green
        glVertex3d(i, UZ, 0.0);
        glVertex3d(i, UZk, 0.0);

        UY = UYk;
        UZ = UZk;
    }
    glEnd();

}
