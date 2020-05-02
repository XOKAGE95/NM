#include <iostream>
#include <math.h>

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


int main()
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
    double A = (4 - x - l*Fsx(x, y) + 2*(y - l*Fsy(x, y)));
    double B = (x - l*Fsx(x, y) + y - l*Fsy(x, y));
    return (A*A + B*B);
}
