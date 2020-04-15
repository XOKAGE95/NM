#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

#define PI 3.1415926535

const double a = 0, b = PI/2;
double h;

using namespace std;
double f(double x)
{
    return(sqrt(1+cos(x)*cos(x)));
}

double Rectangles(double N)
{
    h = (b - a)/N;
    double sum = 0;
    double x = a;
    for (x = a; x <= b; x+= h)
        sum+= f(x);
    sum *= h;
    return sum;
}

double Trapezes(double N)
{
    h = (b - a)/N;
    double sum;
    double x = a;
    sum = f(a) + f(b);
    for (x = a + h; x <= b-h; x+= h)
        sum += 2*f(x);
    sum *= h/2;
    return sum;
}

double Simpson(double N)
{
    h = (b - a)/N;
    double sum;
    double A = 0;
    double B = 0;
    for (double x = a + 2*h; x <= b - 2*h; x+= 2*h)
        A += f(x);
    for (double x = a + h; x <= b - h; x+= 2*h)
        B += f(x);
    sum = h/3*(f(a) + f(b) + 2*A + 4*B);
    return sum;
}

int main()
{
    cout << "Enter N: ";
    double N;
    cin >> N;
    cout << "Method Rectangles: " << setprecision(10) << Rectangles(N) << " (N) " << setprecision(10) << Rectangles(2*N) << " (2N) "<< endl;
    cout << "Method Trapezes: " << setprecision(10) << Trapezes(N) << " (N) " << setprecision(10) << Trapezes(2*N) << " (2N) "<< endl;
    cout << "Method Simpson: " << setprecision(10) << Simpson(N) << " (N) " << setprecision(10) << Simpson(2*N) << " (2N) "<< endl;
    return 0;
}
