#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <glut.h>
#include <locale>
#include <sstream>
#define PI 3.1415926535




//Границы отрезка
float a = -5;
float b = 10;

float N = 400;
double h;

using namespace std;

ofstream file;

void renderSpacedBitmapString(float x ,float y, void *font, string c, double dop)
{
    for (int i = 0; c[i]!= '\0'; i++)
    {
        glRasterPos2f(x,y);
        glutBitmapCharacter(font, c[i]);
        x = x + dop;
    }
}
// Функция для нахождения 1 и 2 производной
double f(double x)
{
    return ((4+3*x*x*x)/(x*pow((2 + x*x*x), 2/3)));
    //return (2 * sqrt((1 - sqrt(x)) / (1 + sqrt(x))));
}

//Функция и ее производная для нахождения корня
double f1(float x)
{
    return (x*x*x*x*x*x + 101*x*x*x*x*x + 425*x*x*x*x - 425*x*x - 101*x - 1);
}

double f2(float x)
{
    return (6*x*x*x*x*x + 505*x*x*x*x + 1700*x*x*x-850*x-101);
}

double f3(float x)
{
    double A = pow(2+x*x*x, 1/3);
    return (8*(4 + 7*x*x*x)/(x*x*x*A*A*A*A*A*A*A*A));
    //return (-8*(-5*x*x*x*x*A*A - 2*x*A*A*A*A*A)/(x*x*x*x*A*A*A*A*A*A*A*A*A*A));

}

//Отрисовка координатной системы
void CoordinateSystem()
{

    glLineWidth(1.0);       //Òîëùèíà ëèíèé
    glColor3d(0, 0, 0);     //Öâåò ëèíèé - ÷åðíûé
    glBegin(GL_LINES);
    glVertex2d(-50, 0);
    glVertex2d(13, 0);
    glVertex2d(13, 0);
    glVertex2d(12, -1);
    glVertex2d(13, 0);
    glVertex2d(12, 1);
    glEnd();
    glRasterPos2d(12.3, 5);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');
    glBegin(GL_LINES);
    glVertex2d(0, -100);
    glVertex2d(0, 50);
    glVertex2d(0, 50);
    glVertex2d(-0.5, 45);
    glVertex2d(0, 50);
    glVertex2d(0.5, 45);
    glEnd();
    glRasterPos2d(1, 48);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
    glBegin(GL_LINES);
    for(int i = -5; i < 10; i += 1)
    {
        glVertex2d(i, -1);
        glVertex2d(i, 1);
    }
        for(int i = -50; i < 45; i += 5)
    {
        glVertex2d(-0.2, i);
        glVertex2d(0.2, i);
    }
    glEnd();
    for(int i = -5; i < 10; i += 1)
    {
        if (i == 0) continue;
        std::stringstream ss;
        string str;
        ss << i;
        ss >> str;
        renderSpacedBitmapString(i, -3,  GLUT_BITMAP_HELVETICA_10, str, 0.2);
    }
    for(int i = -50; i < 45; i += 5)
    {
        if (i == 0) continue;
        std::stringstream ss;
        string str;
        ss << i;
        ss >> str;
        renderSpacedBitmapString(-1, i - 0.2,  GLUT_BITMAP_HELVETICA_10, str, 0.2);
    }
}

void CoordinateSystem2()
{

    glLineWidth(1.0);       //Òîëùèíà ëèíèé
    glColor3d(0, 0, 0);     //Öâåò ëèíèé - ÷åðíûé
    glBegin(GL_LINES);
    glVertex2d(-50, 0);
    glVertex2d(15, 0);
    glVertex2d(15, 0);
    glVertex2d(14, -10);
    glVertex2d(14, 10);
    glVertex2d(15, 0);
    glEnd();
    glRasterPos2d(14, 14);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');

    glBegin(GL_LINES);
    glVertex2d(0, -100);
    glVertex2d(0, 200);
    glVertex2d(0, 200);
    glVertex2d(-0.4, 170);
    glVertex2d(0.4, 170);
    glVertex2d(0, 200);
    glEnd();
    glRasterPos2d(-1, 190);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
    glBegin(GL_LINES);
    for(int i = -200; i < 170; i+= 10)
    {
        glVertex2d(-0.1, i);
        glVertex2d(0.1, i);

    }
    glEnd();
    for(int i = -200; i < 170; i+= 10)
    {
        if (i == 0 || i == -10) continue;
        std::stringstream ss;
        string str;
        ss << i;
        ss >> str;
        renderSpacedBitmapString(-0.9, i,  GLUT_BITMAP_HELVETICA_10, str, 0.17);
    }
    glBegin(GL_LINES);
    for(int i = -5; i <= 10; i+= 1)
    {
        glVertex2d(i, -2);
        glVertex2d(i, 2);
    }
    glEnd();
    for(int i = -5; i <= 10; i+= 1)
    {
        std::stringstream ss;
        string str;
        ss << i;
        ss >> str;
        renderSpacedBitmapString(i-0.1, -10,  GLUT_BITMAP_HELVETICA_10, str, 0.17);
    }

}

//Функция для обработки изменения окна
void ChangeSize1(int w, int h)
{
    if(h == 0)
        h = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glOrtho(-10.0, 15.0, -50.0, 50.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ChangeSize2(int w, int h)
{
    if(h == 0)
        h = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glOrtho(-10.0, 15.0, -200.0, 200.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//1 задание. Выводит 1 производную 1 порядка точности и 1 производную 2 порядка точности для сравнения
void task1()
{
    file.open("Task1.txt");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem();
    glLoadIdentity();
    glColor3ub(0,0,255);
    double x = a;
    double y, y1;
    y1 = (f(x+h) - f(x))/h;
    glLineWidth(2);
    // 1 производная 1 порядка точности
    glBegin(GL_LINES);
    while (x <= b)
    {
        if ((x > -0.2) & (x < 0.2)) x = 0.2;
        y = y1;
        glVertex3d(x, y, 0.0);
        y1 = (f(x+h) - f(x))/h;
        glVertex3d(x,y1, 0.0);
        file << x << "\t" << y1 << endl;
        x+= h;
    }
    glEnd();
    file.close();
    //1 производная 2 порядка точности
    file.open("Task2.txt");
    glColor3ub(255,0,0);
    x = a;
    y1 = (f(x+h) - f(x-h))/2/h;
    glLineWidth(1);
    glBegin(GL_LINES);
    while (x <= b)
    {
        if ((x > -0.2) & (x < 0.2)) x = 0.2;
        if (x == pow(-2, 1/3)) continue;
        y = y1;
        glVertex2d(x, y);
        y1 = (f(x+h) - f(x-h))/2/h;
        glVertex2d(x, y1);
        file << x << "\t" << y1 << endl;
        x+= h;
    }
    glEnd();

    glutSwapBuffers();
}

void task2()	// Отрисовка 1 производной 2 порядка точности
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem();
    glLoadIdentity();
    glColor3ub(255,0,0);
    double x = a;
    double y, y1;
    y1 = (f(x+h) - f(x-h))/2/h;
    glBegin(GL_LINES);
    while (x <= b)
    {
        if ((x > -0.2) & (x < 0.2)) x = 0.2;
        if (x == pow(-2, 1/3)) continue;
        y = y1;
        glVertex2d(x, y);
        y1 = (f(x+h) - f(x-h))/2/h;
        glVertex2d(x, y1);
        x+= h;
    }
    glEnd();
    glutSwapBuffers();
}

void task3() // Отрисовка 2 произовдной 2 порядка точности
{
    file.open("Task3.txt");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem2();
    glLoadIdentity();
    glColor3ub(0, 255, 0);
    double x = a;
    double y, y1;
    y1 = (f(x+h) - 2*f(x)+f(x-h))/(h*h);
    glBegin(GL_LINES);
    while (x <= b)
    {
        if ((x > -0.2) & (x < 0.2)) x = 0.2;
        if (x == pow(-2, 1/3)) continue;
        y = y1;
        glVertex2d(x, y);
        y1 = (f(x+h) - 2*f(x) + f(x-h))/h/h;
        glVertex2d(x, y1);
        file << x << "\t" << y1 << endl;
        x+= h;
    }
    glEnd();
    file.close();
    glColor3ub(200, 100, 20);
    glBegin(GL_LINES);
    for (double x = a; x <= b; x+= h)
    {
        glVertex2d(x, f3(x));
        glVertex2d(x+h, f3(x+h));
    }
    glEnd();
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

bool Nuton()	//Метод Ньютона
{
    cout << "Enter Xn: ";
    double Xn;
    cin >> Xn;
    cout << "Enter eps: ";
    double eps;
    cin >> eps;
    int count;
    double y;
    do
    {
        if (count > 10000000) return false;
        y = f1(Xn)/f2(Xn);
        Xn = Xn - y;
        count ++;
    }
    while((abs(y) >= eps) && (count < 1000000000));
    cout << "X = " << Xn << endl;
    return true;
}

int main (int argc, char **argv)
{
    h = (b-a)/N;
    //if(!Dihotomia()) cout << "Error" << endl;
    if (!Nuton()) cout << "Error" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("task1");
    glutDisplayFunc(task1);
    glutReshapeFunc(ChangeSize1);
    // задание 2
    glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("task2");
    glutDisplayFunc(task2);
    glutReshapeFunc(ChangeSize1);
    //3 задание
    glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("task3");
    glutDisplayFunc(task3);
    glutReshapeFunc(ChangeSize2);
    glutMainLoop();
    return 0;
}
