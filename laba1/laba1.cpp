#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <glut.h>
#define PI 3.1415926535

float a = -5;
float b = 10;
float N = 200;
double h;

using namespace std;

ofstream file;

float f(float x)
{
    return ((4+3*x*x*x)/(x*pow((2 + x*x*x), 2/3)));

}

float f1(float x)
{
    return (x*x*x*x*x*x + 101*x*x*x*x*x + 425*x*x*x*x - 425*x*x - 101*x - 1);
}

void CoordinateSystem()
{

    glLineWidth(1.0);       //Òîëùèíà ëèíèé
    glColor3d(0, 0, 0);     //Öâåò ëèíèé - ÷åðíûé
    glBegin(GL_LINES);
    glVertex3d(-1.4, 0.0, -5.0);
    glVertex3d(1.4, 0.0, -5.0);
    glVertex3d(1.4, 0.0, -5.0);
    glVertex3d(1.2, -0.1, -5.0);
    glVertex3d(1.2, 0.1, -5.0);
    glVertex3d(1.4, 0.0, -5.0);
    glVertex3d(0.0, -1.4, -5.0);
    glVertex3d(0.0, 1.4, -5.0);
    glVertex3d(0.0, 1.4, -5.0);
    glVertex3d(0.1, 1.2, -5.0);
    glVertex3d(-0.1, 1.2, -5.0);
    glVertex3d(0.0, 1.4, -5.0);
    glEnd();

}

void ChangeSize1(int w, int h)
{
    if(h == 0)
        h = 1;
    float ratio = 1.0* w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(35,ratio,3,1000);
    gluOrtho2D(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ChangeSize2(int w, int h)
{
    if(h == 0)
        h = 1;
    float ratio = 1.0* w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(35,ratio,3,1000);
    gluOrtho2D(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void task1()
{
    file.open("Task1.txt");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem();
    glLoadIdentity();
    glColor3d(0.3, 0.5, 1.0);
    float x = a;
    float y, y1;
    y1 = (f(x+h) - f(x))/h;
    glBegin(GL_LINES);
    while (x <= b)
    {
        if ((x > -0.2) & (x < 0.2)) x = 0.2;
        if (x == pow(-2, 1/3)) continue;
        y = y1;
        glVertex3d(x/9.75002, y/19.91, -5.0);
        y1 = (f(x+h) - f(x))/h;
        glVertex3d(x/9.75002, y1/19.91, -5.0);
        file << x << "\t" << y1 << endl;
        x+= h;
    }
    glEnd();
    file.close();
    glutSwapBuffers();
}

void task2()
{
    file.open("Task2.txt");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem();
    glLoadIdentity();
    glColor3d(0.3, 0.5, 1.0);
    float x = a;
    float y, y1;
    y1 = (f(x+h) - f(x-h))/2/h;
    glBegin(GL_LINES);
    while (x <= b)
    while (x <= b)
    {
        if ((x > -0.2) & (x < 0.2)) x = 0.2;
        if (x == pow(-2, 1/3)) continue;
        y = y1;
        glVertex3d(x/9.75002, y/19.91, -5.0);
        y1 = (f(x+h) - f(x-h))/2/h;
        glVertex3d(x/9.75002, y1/19.91, -5.0);
        file << x << "\t" << y1 << endl;
        x+= h;
    }
    glEnd();
    file.close();
    glutSwapBuffers();
}

void task3()
{
    file.open("Task3.txt");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem();
    glLoadIdentity();
    glColor3d(0.3, 0.5, 1.0);
    float x = a;
    float y, y1;
    y1 = (f(x+h) - 2*f(x)+f(x-h))/(h*h);
    glBegin(GL_LINES);
    while (x <= b)
    {
        if ((x > -0.2) & (x < 0.2)) x = 0.2;
        if (x == pow(-2, 1/3)) continue;
        y = y1;
        glVertex3d(x/10, y/20, -5.0);
        y1 = (f(x+h) - 2*f(x) + f(x-h))/(h*h);
        //cout << x << "\tF1 = " << f(x+h) << "\tF2 = " << f(x) << "\tF3 = " << f(x-h) << endl;
        glVertex3d(x/10, y1/20, -5.0);
        file << x << "\t" << y1 << endl;
        x+= h;
    }
    glEnd();
    file.close();
    glutSwapBuffers();
}

bool Dihotomia()
{
    float eps;
    cout << "Enter eps: ";
    cin >> eps;
    float A, B;
    cout << "Enter A: ";
    cin >> A;
    cout << "Enter B: ";
    cin >> B;
    float x1, x2, x0;
    //cout << f1(A) << "\t" << f1(B) << endl;
    if (f1(A)*f(B) > 0)
        return false;
    x0 = A;
    x1 = B;
    while (abs(x1 - x0) > eps)
    {
        x2 = (x0 + x1)/2;
        if (f1(x1)*f1(x2) <= 0)
            x0 = x2;
        else x1 = x2;
    }
    cout << "X = " << (x0 + x1)/2 << endl;

    return true;
}

bool Nuton()
{
    cout << "Enter Xn: ";
    float Xn;
    cin >> Xn;
    float Xn1 = Xn;
    cout << "Enter eps: ";
    float eps;
    cin >> eps;
    do
    {
        Xn1 = Xn - f1(Xn)/((f1(Xn+h) - f(Xn-h))/2/h);
    }
    while(abs(Xn1 - Xn) < eps);
    cout << "X = " << Xn1 << endl;
}
int main (int argc, char **argv)
{
    h = (b-a)/N;
    if(!Dihotomia()) cout << "Error" << endl;
    Nuton();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("task1");
    glutDisplayFunc(task1);
    glutReshapeFunc(ChangeSize1);
    //glutIdleFunc(task1);
    // задание 2
    glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("task2");
    glutDisplayFunc(task2);
    glutReshapeFunc(ChangeSize1);
    //glutIdleFunc(task2);
        glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("task3");
    glutDisplayFunc(task3);
    glutReshapeFunc(ChangeSize2);
    //glutIdleFunc(task2);
    glutMainLoop();
    return 0;
}
