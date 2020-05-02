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
    cout << setw(5) << "A" << setw(10) << "B" << setw(10) << "C" << setw(10) << "D" << endl;
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
    glColor3ub(100, 100, 255);
    glBegin(GL_LINES);
    for(int i = 1; i < N; i++)
        DrawF(x[i-1], x[i], y[i], b[i], c[i], d[i]);
    glEnd();

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
    glLineWidth(1.0);

    for(double i = X0 + eps; i <= XN; i+= eps)
    {
        glVertex2d(i - eps, yy);
        yy = A + B*(i - X0) + C*(i - X0)*(i - X0) + D*(i - X0)*(i - X0)*(i - X0);
        glVertex2d(i, yy);
    }
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
    for(int i = -2; i < 2; i++)
    {
        glVertex2d(i, 0.05);
        glVertex2d(i, -0.05);
    }
    for(int i = -2; i < 2; i++)
    {
        glVertex2d(0.07, i);
        glVertex2d(-0.07, i);
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
    glOrtho(-2.0, 2.0, -2.0, 2.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
