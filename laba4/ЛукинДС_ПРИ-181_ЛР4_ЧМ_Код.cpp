#include <iostream>
#include <math.h>
#include <glut.h>

const double a = 0;
const double b = 0.3;

using namespace std;

double f1(double x, double y, double z) { return -2*x*y + z - x -1;}
double f2(double x, double y, double z) { return -1/2 - y - x/z;}
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
    glLineWidth(2);
    double h = 0.001;
    double UY = 1;
    double UZ = 1;
    glBegin(GL_LINES);
    for (double i = a + h; i <= b; i+= h)
    {
        /*double UYk = UY + (1 - alfa)*f1(i, UY, UZ) + alfa*f1(i + h/2/alfa, UY + h/(2*alfa*f1(i, UY, UZ)), UZ + h/(2*alfa*f1(i, UY, UZ)));
        double UZk = UZ + (1 - alfa)*f2(i, UY, UZ) + alfa*f2(i + h/2/alfa, UY + h/(2*alfa*f2(i, UY, UZ)), UZ + h/(2*alfa*f2(i, UY, UZ)));
        */
        double k = h*f1(i, UY, UZ);
        double m = h*f2(i, UY, UZ);
        //cout << "k1 = " << k << "\tm1 = " << m << endl;
        double k2 = h*f1(i + h/2, UY + k/2,UZ + m/2);
        double m2 = h*f2(i + h/2, UY + k/2, UZ + m/2);
        //cout << "k2 = " << k2 << "\tm2 = " << m2 << endl;
        double k3 = h*f1(i + h/2, UY + k2/2, UZ + m2/2);
        double m3 = h*f2(i + h/2, UY + k2/2, UZ + m2/2);
        //cout << "k3 = " << k3 << "\tm3 = " << m3 << endl;
        double k4 = h*f1(i + h, UY + k3, UZ + m3);
        double m4 = h*f2(i + h, UY + k3, UZ + m3);
        //cout << "k4 = " << k4 << "\tm4 = " << m4 << endl << endl;

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
        cout << "Uy = " << UY << "\tUz = " << UZ << endl;
    }
    glEnd();
    glutSwapBuffers();
}

void ChangeSize1(int w, int h)
{
    if(h == 0)
        h = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glOrtho(-1.0, 1.0, -0.1, 1.5, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CoordinateSystem()
{

    glLineWidth(1.0);       //Òîëùèíà ëèíèé
    glColor3d(0, 0, 0);     //Öâåò ëèíèé - ÷åðíûé
    glBegin(GL_LINES);
    glVertex2d(-100, 0);
    glVertex2d(100, 0);
    glVertex2d(0, -100);
    glVertex2d(0, 100);
    glEnd();

}
