#include <iostream> //Подключение библиотек
#include <math.h>
#include <glut.h>

const double PI = 3.1415926535; //константа пи

const double eps = 0.001; //некоторые константы
const double a = 0; //Интервал
const double b = 1;
const double y0y = 0; //Граничные условия
const double y1y = -1;
const double h = 0.0001; 

double lengthX;//Переменные для размеров окна
double lengthY;
double xx0, xx1;
double yy0, yy1;
double zz0, zz1;


using namespace std;

double f(double, double, double);
double g(double, double, double);
double z(double a);
double RungeKutt(double z0);
double Shooting();
void CoordinateSystem(void);
void ChangeSize1(int, int);
void Cartoon();


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("heh");
    glutDisplayFunc(Cartoon);
    glutReshapeFunc(ChangeSize1);
    glutMainLoop();
    return 0;
}

double f1(double x, double y, double z) //1 уравнение системы
{
	return 2*x + y; //Dz/dy = 2x + y
}

double f2(double x, double y, double z) //2 уравнение системы
{
	return z; //Dy/dx = z;
}

double z(double a) //Функция F(a) = Y(x,a) - B
{
    return(RungeKutt(a) - y1y);
}

double RungeKutt(double z0)//Решение системы методом Рунге-Кутты
{
    double UY = y0y; //Начальные условия
    double UZ = z0;
    glBegin(GL_LINES);
    for (double x = a + h; x < b; x += h) //На выходе имеем значения этих функций на границе интервала.
    {
        glVertex2d(x - h, UY + UZ); 

        double k = h*f1(x, UY, UZ);
        double m = h*f2(x, UY, UZ);

        double k2 = h*f1(x + h/2, UY + k/2,UZ + m/2);
        double m2 = h*f2(x + h/2, UY + k/2, UZ + m/2);

        double k3 = h*f1(x + h/2, UY + k2/2, UZ + m2/2);
        double m3 = h*f2(x + h/2, UY + k2/2, UZ + m2/2);

        double k4 = h*f1(x + h, UY + k3, UZ + m3);
        double m4 = h*f2(x + h, UY + k3, UZ + m3);

        double UYk = UY + (k + 2*k2 + 2*k3 + k4)/6;
        double UZk = UZ + (m + 2*m2 + 2*m3 + m4)/6;


        UY = UYk;
        UZ = UZk;

        glVertex2d(x, UY + UZ);

    }
    glEnd();
    return UY + UZ; 
    /*
		Возвращаемое значение равно сумме, т.к. мы заменили y'' на z, а изначальная функция равна z + y' - y = 2x 
    */
}

double Shooting() //Метод стрельбы
{
    double a0, a1, a2 = 100000, a = 100;
    //Задаем отрезок с искомым альфа
    cout << "enter a0: ";
    cin >> a0;
    cout << "enter a1: ";
    cin >> a1;

    glColor3ub(255, 0, 0); //Цвет - красный

    if(z(a0)*z(a1) < 0) //Если искомый альфа находится в этом отрезке
    {


        while (abs(a2 - a) >= eps) //Пока разница между a[i] и a[i+1] больше чем точность мы находим корень уравнения F(a) методом дихотомии
        {
            a = a2;
            a2 = 0.5*(a0 + a1);

            if (z(a0)*z(a2) < 0)
                a1 = a2;
            else if (z(a2)*z(a1) < 0)
                a0 = a2;
        }
        return a2;
    }
    return -1000; //Если корней нет.
}

void Cartoon()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem();
    glLoadIdentity();
    double a = Shooting();
    if(a != -1000) //Если возвращаемое значение не равно возвращаемому значению при отсутствии корней, то выводим найденые значения на экран
    {
        cout << "alfa = " << a << endl;
        glLineWidth(3);
        glColor3ub(0, 0, 255);
        cout << "F = " << z(a);
    }
    else
    {
        cout << "NO roots";
        return;
    }



    glutSwapBuffers();
}

void CoordinateSystem() //Отрисовка координатной системы
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

void ChangeSize1(int w, int h)
{
    xx0 = a - 0.5;
    xx1 = b + 0.5;
    yy0 = -10.0;
    yy1 = 10.0;
    zz0 = -100.0;
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
