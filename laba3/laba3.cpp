#include <iostream>
#include <fstream>
#include <iomanip>
#define double float
using namespace std;

//перечисление всех функций
bool Gauss(int n, double **a);
bool ReadFile(double **a, int n);
bool RunThrough(int n);
bool ReadFile(double *a, double *b, double *c, double *y);


int main()
{

    int n = 6;  //Колличество переменных
    double** a = new double*[n]; //Создание матрицы 
    for(int i = 0; i < n; i++)
        a[i] = new double[n+1];

    ReadFile(a, n);	//Считывание матрицы для метода Гаусса

  		//Вывод матрицы 
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << setw(4) <<a[i][j] << " ";
        cout << " | " << setw(5) << a[i][6] << endl;
    }
    cout << endl;


    Gauss(n, a); // Решение СЛАУ методом гаусса
    RunThrough(n); //Решение СЛАУ методом прогонки
    	//Удаление матрицы 

    for(int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}


							// Решение СЛАУ методом гаусса
bool Gauss(int n, double **a)
{	

    double *x = new double[n]; //Создание массива для корней

    		//Приведение матрицы к ступенчатому виду
        for(int i = 0; i < n; i ++)
        {
            for(int j = n; j >= i; j--)
                a[i][j]/=a[i][i];
            for(int j = i+1; j < n; j++)
                for(int k = n; k>=i; k--)
                    a[j][k] -= a[j][i]*a[i][k];
        }
        //Вывод ступенчатой матрицы на экран
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n + 1; j++)
        cout << setw(6) << left << setprecision(3) << a[i][j] << " ";
        cout << endl;
    }
    //Нахождение корней 
    x[n-1] = a[n-1][n];
     for (int i=n-2; i>=0; i--)
       {
           x[i] = a[i][n];
           for (int j=i+1;j<n;j++) x[i]-=a[i][j]*x[j];
       }
   //Вывод на экран корней
    cout << "Roots(Gauss): " << endl;
    for(int i = 0; i < n; i++)
        cout << "x["<< i+1 << "] = " << x[i] << endl;
    delete[] x;
}

//Считывание матрицы для метода гаусса
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

//Решение СЛАУ методом прогонки
bool RunThrough(int n)
{
	//Создание масссивов для коэффициентов а, b, с, d 
    double *a = new double[n];
    double *b = new double[n];
    double *c = new double[n];
    double *d = new double[n];

    ReadFile(a,b,c,d);  //Считывание массивов для метода прогонки
    //Вывод на экран Массивов
    cout << endl <<"[A] = ";
    for(int i = 1; i < n; i++)
        cout << a[i] << " ";
    cout << endl <<"[B] = ";
    for(int i = 0; i < n; i++)
        cout << b[i] << " ";
    cout << endl <<"[C] = ";
    for (int i = 0; i < n-1; i++)
        cout << c[i] << " ";
    //Создание массивов для прогоночных коэффициентов

    double *A = new double[n];
    double *B = new double[n];
    double *x = new double[n];
    A[0] = -c[0]/b[0];
    B[0] = d[0]/b[0];

    //Инициализация прогоночных коэффициентов:
    for (int i = 1; i < n - 1; i++)
    {
        double e = a[i]*A[i-1] + b[i];
        A[i] = -c[i]/e;
        B[i] = (d[i] - a[i]*B[i-1])/e;
    }
    //Нахождение корней
    x[n-1] = (d[n-1] - a[n-1]*B[n-2])/(b[n-1] + a[n-1]*A[n-2]);
    for (int i = n-2; i>= 0; i--)
        x[i] = A[i]*x[i+1] + B[i];
    //Вывод на экран корней
    cout << endl << "Roots: " << endl;
    for(int i = 0; i < n; i++)
        cout << "x[" << i+1 << "] = " << x[i] << endl;
    // Удаление массивов
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] d;
    delete[] A;
    delete[] B;
    delete[] x;
    return true;
}

//функция для заполнение массивов коэффициентов
bool ReadFile(double *a, double *b, double *c, double *y)
{
    ifstream file;
    file.open("enter2.txt");
    double d;
    file >> b[0];
    file.ignore();
    file >> c[0];
    file.ignore();
    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> y[0];
    file.ignore();

    file >> a[1];
    file.ignore();
    file >> b[1];
    file.ignore();
    file >> c[1];
    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> y[1];
    file.ignore();

    file >> d;
    file.ignore();
    file >> a[2];
    file.ignore();
    file >> b[2];
    file.ignore();
    file >> c[2];
    file.ignore();
    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> y[2];
    file.ignore();

    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> a[3];
    file.ignore();
    file >> b[3];
    file.ignore();
    file >> c[3];
    file.ignore();
    file >> d;
    file.ignore();
    file >> y[3];
    file.ignore();

    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> a[4];
    file.ignore();
    file >> b[4];
    file.ignore();
    file >> c[4];
    file.ignore();
    file >> y[4];
    file.ignore();
    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> d;
    file.ignore();
    file >> a[5];
    file.ignore();
    file >> b[5];
    file.ignore();
    file >> y[5];
    file.ignore();
    file.close();
}
