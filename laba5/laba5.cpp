#include <iostream>
#include <glut.h>
#include <math.h>

const double tau = 0.61803399;
const double eps = 0.001;
const double A = -2.0;
const double B = 0.0;
using namespace std;

double f(double x) { return cos(x)*cos(x)*exp(-x);}

void ChangeSize1(int w, int h);
void CoordinateSystem();
void Cartoon();
double minimum(double a, double b);


int main (int argc, char **argv)
{
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

void Cartoon()
{

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem();
    glLoadIdentity();
    glLineWidth(2);
    glColor3ub(50, 100, 255);
    glBegin(GL_LINES);
    for (float i = A; i <= B; i+=eps)
    {
        glVertex3d(i, f(i), -5.0);
        glVertex3d(i + eps, f(i + eps), -5.0);
    }
    glEnd();

    double x = minimum(A, B);
    glLineWidth(1);
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
        glVertex3d(x, 0.03, -5.0);
        glVertex3d(x, -0.03, -5.0);
    glEnd();
    cout << "X = " << x << endl;
    glutSwapBuffers();
}

double minimum(double a, double b)
{
    while(abs(b - a) >= eps)
    {
        double x1 = b - tau*(b - a);
        double x2 = a + tau*(b - a);
        if (f(x1) > f(x2)) a = x1;
        else b = x2;
    }
    return (a + b)/2;
}
void ChangeSize1(int w, int h)
{
    if(h == 0)
        h = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glOrtho(-3.0, 1.0, -1.0, 1.5, -100.0, 100.0);
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
    for(int i = -3.0; i < 1.0; i++)
    {
        glVertex2d(i, 0.02);
        glVertex2d(i, -0.02);
    }
    for(int i = -1.0; i < 1.5; i++)
    {
        glVertex2d(0.03, i);
        glVertex2d(-0.03, i);
    }
    glEnd();

}
