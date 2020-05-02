#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <glut.h>

const int p = 3;
const int n = 20;
const double w = 1;
const double eps = 0.001;
double x[n] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
double y[n] = {-2.28, -2.83, -1.45, -1.4, -2.33, 0.09, -1.96, -2.28, -0.36, 0.71, -0.8, 0.26, -0.06, -0.29, 1.26, 0.68, 0.19, 1.04, 0.6, 1.94};
double *fss = new double[n];

using namespace std;

double fs(double x, double *a);
double f(int i, double x);
double Fun(double *a);
double Func(double *a, double x);
bool MATC(double **C);
bool MATF(double *F);
bool WriteFile(double **A, double *F);
bool Gauss(int n, double **a, double *x);
bool ReadFile(double **a, int n);
void Cartoon();
void CoordinateSystem();
void ChangeSize1(int w, int h);



int main(int argc, char **argv)
{
    double **C = new double*[p];
    for (int i = 0; i < p; i++)
        C[i] = new double[p];

    double *F = new double[p];

    for(int i = 0; i < n; i++)
        x[i] = i+1;

    MATF(F);
    MATC(C);
    WriteFile(C, F);
    for(int i = 0; i < p; i++)
        delete[] C[i];
    delete[] C;
    delete[] F;

    double **a = new double*[p];
    for(int i = 0; i < p; i++)
        a[i] = new double[p+1];

    double *A = new double[p];

    ReadFile(a, p);
    cout << setw(12) << right << "C";
    cout << setw(19) << right << "F" << endl;
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < p; j++)
            cout << left <<setw(7) <<a[i][j] << " ";
        cout << " | " << setw(5) << a[i][p] << endl;
    }
    cout << endl;
    Gauss(p, a, A);
    for(int i = 0; i < p; i++)
        delete[] a[i];
    delete[] a;

    double MIN = Fun(A);

    double Cs[p][p] = {{0.289, -0.0303, -0.251}, {-0.302, 0.0088, -0.00238}, {-0.251, -0.00235, 0.374}};
    cout << endl <<"C-1 = " << endl;
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < p; j++)
        cout << left << setw(9) <<Cs[i][j];
        cout << endl;
    }

    cout << endl << "Rmin = " << MIN << endl;
    cout << "eps = " << sqrt(MIN/(n-p)) << endl;
    for(int i = 0; i < p; i++)
        cout << "D'[" << i+1 << "] = " << sqrt(MIN/(n-p) * Cs[i][i]) << endl;

    for(int i = 0; i < n; i++)
        fss[i] = Func(A, i);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860, 620);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("heh");
    glutDisplayFunc(Cartoon);
    glutReshapeFunc(ChangeSize1);
    glutMainLoop();
    delete[] A;
    return 0;

}

double f(int i, double x)
{
    switch(i)
    {
        case 0: return sqrt(x);
        case 1: return x;
        case 2: return log(x);
    }
}

bool MATC(double **C)
{

    for(int k = 0; k < p; k++)
        for (int j = 0; j < p; j++)
        {
            double sum = 0;
            for(int i = 0; i < n; i ++)
                sum+= w*f(k, x[i])*f(j, x[i]);
            C[k][j] = sum;
        }
    return true;
}

bool MATF(double *F)
{
    for(int m = 0; m < p; m++)
    {
        double sum = 0;
        for(int i = 0; i < n; i++)
            sum+= w*f(m, x[i])*y[i];
        F[m] = sum;
    }
    return true;
}

bool WriteFile(double **A, double *F)
{
    ofstream file;
    file.open("Enter.txt");
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < p; j++)
            file << A[i][j] << " ";
        file << F[i] << endl;
    }
    file.close();
    return true;
}

bool Gauss(int n, double **a, double *x)
{
        for(int i = 0; i < n; i ++)
        {
            for(int j = n; j >= i; j--)
                a[i][j]/=a[i][i];
            for(int j = i+1; j < n; j++)
                for(int k = n; k>=i; k--)
                    a[j][k] -= a[j][i]*a[i][k];
        }
    x[n-1] = a[n-1][n];
     for (int i=n-2; i>=0; i--)
       {
           x[i] = a[i][n];
           for (int j=i+1;j<n;j++) x[i]-=a[i][j]*x[j];
       }
    for(int i = 0; i < n; i++)
        cout << "a'["<< i+1 << "] = " << x[i] << endl;
    return true;
}

bool ReadFile(double **a, int n)
{
    ifstream file;
    file.open("Enter.txt");
    if(!file) return false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n + 1; j++)
        {
            file>> a[i][j];
            file.ignore();
        }
    file.close();
    return true;
}

double Fun(double *a)
{
    double SUM = 0;
    for(int i = 0; i < n; i++)
    {
        double sum = 0;
        for(int j = 0; j < p; j++)
            sum += a[j]*f(j, x[i]);
        SUM += (y[i] - sum)*(y[i] - sum);
    }
    return SUM;
}

void Cartoon()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CoordinateSystem();
    glLoadIdentity();

    glBegin(GL_LINES);
    for(int i = 1; i < n; i++)
    {
        glColor3ub(0,0,255);
        glVertex3d(x[i-1], y[i-1], -5.0);
        glVertex3d(x[i], y[i], -5.0);

        glColor3ub(255,0,100);
        glVertex3d(x[i-1], fss[i-1], -5.0);
        glVertex3d(x[i], fss[i], -5.0);
    }
    glEnd();
    glutSwapBuffers();
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
    for(int i = 0; i < 21; i++)
    {
        glVertex2d(i, 0.05);
        glVertex2d(i, -0.05);
    }
    for(int i = -5; i < 5; i++)
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
    glOrtho(-1.0, 21.0, -5.0, 5.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

double Func(double *a, double x)
{
    double sum = 0;
    for(int i = 0; i < p; i++)
        sum+= a[i]*f(i, x);
    return sum;
}
