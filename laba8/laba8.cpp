#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <glut.h>

const int N = 10;
int k = 0;
float *x;
float *y;
float *h;
float *l;
float*delta;
float *lambda;
float *c;
float *d;
float *b;

double lengthX;
double lengthY;
double xx0, xx1;
double yy0, yy1;
double zz0, zz1;

using namespace std;

double ch(double);
bool allocmatrix(void);
bool freematrix(void);
bool EnterDisplay(void);
void Cartoon(void);
void DrawF(double, double, double, double, double, double);
void CoordinateSystem(void);
void ChangeSize1(int w, int h);

int main(int argc, char **argv)
{
    k=0;
    cout << "N = " << N << endl;
    allocmatrix();
    double xx = -1;
    for(int i = 0; i <= N; i++)
    {
        x[i] = xx;
        y[i] = ch(x[i]);
        xx += (2.0/N);
    }
    x[5] = 0;
    for(int i = 0; i < N; i++)
        cout << "x[" << i+1 << "] = " << x[i] << endl;

    for(k=1; k<=N; k++)
    {
        h[k] = x[k] - x[k-1];
        l[k] = (y[k] - y[k-1])/h[k];
    }
    delta[1] = - h[2]/(2*(h[1]+h[2]));
    lambda[1] = 1.5*(l[2] - l[1])/(h[1]+h[2]);
    for(k=3; k<=N; k++)
    {
        delta[k-1] = - h[k]/(2*h[k-1] + 2*h[k] + h[k-1]*delta[k-2]);
        lambda[k-1] = (3*l[k] - 3*l[k-1] - h[k-1]*lambda[k-2]) /
                      (2*h[k-1] + 2*h[k] + h[k-1]*delta[k-2]);
    }
    c[0] = 0;
    c[N] = 0;
    for(k=N; k>=2; k--)
    {
        c[k-1] = delta[k-1]*c[k] + lambda[k-1];
    }
    for(k=1; k<=N; k++)
    {
        d[k] = (c[k] - c[k-1])/(3*h[k]);
        b[k] = l[k] + (2*c[k]*h[k] + h[k]*c[k-1])/3;
    }
    EnterDisplay();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("heh");
    glutDisplayFunc(Cartoon);
    glutReshapeFunc(ChangeSize1);
    glutMainLoop();

    freematrix();
    return 0;
}

double ch(double x)
{
    return (exp(x) + exp(-x))/2;
}

bool allocmatrix()
{
    x = new float[N+1];
    y = new float[N+1];
    h = new float[N+1];
    l = new float[N+1];
    delta = new float[N+1];
    lambda = new float[N+1];
    c = new float[N+1];
    d = new float[N+1];
    b = new float[N+1];
    return true;
}

bool freematrix()
{
    delete [] x;
    delete [] y;
    delete [] h;
    delete [] l;
    delete [] delta;
    delete [] lambda;
    delete [] c;
    delete [] d;
    delete [] b;
    return true;
}

bool EnterDisplay()
{
    cout << setw(5) << "y" << setw(10) << "B" << setw(10) << "C" << setw(10) << "D" << endl;
    for(int i = 1; i <= N; i++)
        cout << setw(10) << left << y[i] << setw(10) << left << b[i] << setw(10) << left << c[i] << setw(10) << left << d[i] << endl;
    return true;
}

void Cartoon()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem();
    glLoadIdentity();

    glLineWidth(2.0);
    glColor3ub(100, 100, 255);


    glBegin(GL_LINES);
    for(int j = 1; j < N; j++)
    {
        double eps =0.001;
        double yy = y[j - 1];
        for(double i = x[j-1] + eps; i <= x[j]; i+= eps)
        {
            double X = (i - x[j]);
        glVertex2d(i - eps, yy);
        yy = (y[j] + b[j]*X + c[j]*X*X + d[j]*X*X*X);
        glVertex2d(i, yy);
        }
    }
        //DrawF(x[i - 1], x[i], y[N - i], b[i], c[i], d[i]);
    glEnd();

    glLineWidth(1.0);
    glColor3ub(255, 100, 100);
    glBegin(GL_LINES);
    for(int i = 1; i < N; i++)
    {
        glVertex2d(x[i-1], y[i-1]);
        glVertex2d(x[i], y[i]);
    }

    glEnd();
    glutSwapBuffers();
}

void DrawF(double X0, double XN, double A, double B, double C, double D)
{
    double eps =0.001;
    double yy = A;

    for(double i = X0 + eps; i <= XN; i+= eps)
    {
        double X = (i - X0);
        glVertex2d(i - eps, yy);
        yy = (A + B*X + C*X*X + D*X*X*X);
        glVertex2d(i, yy);
    }
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

void ChangeSize1(int w, int h)
{
    xx0 = -2.0;
    xx1 = 2.0;
    yy0 = -2.0;
    yy1 = 2.0;
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
