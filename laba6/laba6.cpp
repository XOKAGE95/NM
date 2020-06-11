#include <iostream>
#include <math.h>
#include "glut.h"

using namespace std;

const double tau = 0.61803399;
const double eps = 0.001;
const double A = -5.0;
const double B = 5.0;
using namespace std;


struct vectoR
{
    double x;
    double y;
    vectoR operator+(vectoR A) {A.x += x; A.y += y; return A;};
    vectoR operator-(vectoR A) {A.x -= x; A.y -= y; return A;};
    bool operator*(double k) {x *= k; y *= k; return true;};
};

double grad(vectoR V);
double gradx(vectoR V);
double grady(vectoR V);
double minimum(double a, double b, double x, double y);
double Fsx(double x, double y);
double Fsy(double x, double y);
double Fl(double x, double y, double l);
double Fun(double x, double y);
void Cartoon();
void CoordinateSystem();
void ChangeSize1(int w, int h);


int main(int argc, char **argv)
{
    vectoR now, next;
    int k = 0;
    cout << "Enter point:\n";
    cout << "x0 = ";
    cin >> now.x;
    cout << "y0 = ";
    cin >> now.y;
    next.x = gradx(now);
    next.y = grady(now);
    do
    {
        double l = minimum(A, B, now.x, now.y);
        next.operator*(l);
        now.x -= next.x;
        now.y -= next.y;
        next.x = gradx(now);
        next.y = grady(now);
        k++;
    }while(grad(now) > eps);
    cout << "point = (" << next.x << ", " << next.y << ")\n";
    cout << "F = " << (4 - next.x + 2*next.y*next.y)*(4 - next.x + 2*next.y*next.y) + (next.x + next.y)*(next.x + next.y) << endl;
    cout << "iterations = " << k << endl;
    glutInit(&argc, argv); // Инициализация библиотеки GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Подключение режимов отображения
    glutInitWindowSize(860, 620); // Задание размеров окна
    glutInitWindowPosition(20, 20); // Позиция окна
    glutCreateWindow("LW 5"); // Создание окна
    glutDisplayFunc(Cartoon); // Рендер функции
    glutReshapeFunc(ChangeSize1);
    glutMainLoop();
    return 0;

}

double gradx(vectoR V)
{
    double y = V.y;
    double t = V.x;
    return (8*t*(3-y+1+2*t*t) + 2*(t + y));
}

double grady(vectoR V)
{
    double y = V.y;
    double x = V.x;
    return (-2*(3-y+1+2*x*x) + 2*(x+y));
}

double grad(vectoR V)
{
    return sqrt(gradx(V)*gradx(V) + grady(V)*grady(V));
}

double minimum(double a, double b, double x, double y)
{
    while(abs(b - a) >= eps)
    {
        double L1 = b - tau*(b - a);
        double L2 = a + tau*(b - a);
        if (Fl(x, y, L1) > Fl(x, y, L2)) a = L1;
        else b = L2;
    }
    return (a + b)/2;
}

double Fsx(double x, double y)
{
    return ((-6 + 2*x - 2 - 6*y*y) + 2*x + 2*y);
}

double Fsy(double x, double y)
{
    return ((6 - 2*x + 3 + 6*y*y)*(4*y) + 2*y + 2*x);
}

double Fl(double x, double y, double l)
{
    double a = (4 - x - l*Fsx(x, y) + 2*(y - l*Fsy(x, y)));
    double b = (x - l*Fsx(x, y) + y - l*Fsy(x, y));
    return (a*a + b*b);
}

double Fun(double x, double y)
{
    double a = (3 - y + 1 + 2*x*x);
    double b = (x + y);
    return (a*a + b*b);
}

void Cartoon()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem();
    glLoadIdentity();
    glLineWidth(2);
    glColor3ub(50, 100, 255);
    glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
    glBegin(GL_LINES);
    for(double i = A; i < B; i+= 0.01)
        for(double j = A; j < B; j+= 0.01)
    {
        glVertex3d(i,j,Fun(i, j));
    }
    glEnd();
    glutSwapBuffers();
}

void CoordinateSystem()
{

    glLineWidth(1.0);       //Òîëùèíà ëèíèé
    glColor3d(0, 0, 0);     //Öâåò ëèíèé - ÷åðíûé
    glBegin(GL_LINES);
    glVertex3d(-10000, 0, 0);
    glVertex3d(10000, 0, 0);
    glVertex3d(0, -10000, 0);
    glVertex3d(0, 10000, 0);
    glVertex3d(0, 0, -10000);
    glVertex3d(0, 0, 10000);

    for(double i = 100; i < 100; i++)
    {
        glVertex2d(i, 5.0);
        glVertex2d(i, -5.0);
    }
    for(double i = -100; i < 100; i++)
    {
        glVertex2d(0.5, i);
        glVertex2d(-0.5, i);
    }
    for(double i = 100; i < 100; i++)
    {
        glVertex3d(1.0, 0.0, i);
        glVertex3d(-1.0, 0.0, i);
    }
    glEnd();

}

void ChangeSize1(int w, int h)
{
    if(h == 0)
        h = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glOrtho(-30, 30, -30, 30, -10.0, 10.0);
    gluLookAt(0.0, 0.0, 0.0, -4.0,-4.0,-2.5, 1.0,1.0,0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
