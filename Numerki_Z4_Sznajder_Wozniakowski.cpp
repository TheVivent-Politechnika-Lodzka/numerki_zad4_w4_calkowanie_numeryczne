#include <iostream>
#include <cmath>
using namespace std;
double (*fun)(double);
double a(double x)
{
    return -x*x+4*x+12;
}
double b(double x)
{
    return 2*sin(x);
}
double c(double x)
{
    return 3*x+5;
}
double d(double x)
{
    return log(x+2)+x*x-6;
}
double silnia(int x)
{
    double wynik=1;
    for(int i=0;i<x;i++)
    {
        wynik=wynik*(x-i);
    }
    return wynik;
}
double powe(int a, int b)
{
    double wynik=1;
    for(int i=0;i<b;i++)
    {
        wynik=wynik*a;
    }
    return wynik;
}
sum(double d, double p, double k, int n)
{
    double result;
    int coe;
    double *tab=new double [n-1];
    for(int i=1;i<n;i++)
    {
        tab[i-1]=fun(p+i*d);
    }
    result=fun(p)+fun(k);
    for(int i=0;i<n-1;i++)
    {
        if(i%2==0) coe=4;
        else coe=2;
        result=result+coe*tab[i];
    }
    return result;
}

double gauss(int n, double p, double k)
{
    double Ak[4][5]={
    1,1,0,0,0,
    0.55556, 0.88889, 0.55556,0,0,
    0.347855,0.652145,0.652145, 0.347855, 0,
    0.236927,0.478629,0.568889,0.478629,0.236927
    };
    double Xk[4][5]={
    -0.57735, 0.57735, 0, 0, 0,
    -0.774597, 0, 0.774597, 0, 0,
    -0.861136, -0.339981, 0.339981, 0.861136, 0,
    -0.906180, -0.538469, 0, 0.538469, 0.906180
    };
    double fac;
    double result=0;
    double factor=(k-p)/2;

    for(int i=0;i<n;i++)
    {
        fac=((p+k)/2)+(((k-p)/2)*Xk[n-2][i]);
        result=result+Ak[n-2][i]*fun(fac);
    }
    result=factor*result;
    return result;

}

int main()
{
    double p,k;
    double approx;
    char choice;
    cout<<"-------------------------Pierwsza czesc----------------------------"<<endl;
    cout<<"Wybierz funkcje: "<<endl;
    cout<<"a) -x^2 + 4x + 12"<<endl;
    cout<<"b) 2sinx"<<endl;
    cout<<"c) 3*x+5"<<endl;
    cout<<"d) log(x+2) + x^2 - 6";
    cin>>choice;
    switch (choice)
    {
        case 'a':
            {
                fun=a;
                break;
            }
        case 'b':
            {
                fun=b;
                break;
            }
        case 'c':
            {
                fun=c;
                break;
            }
        case 'd':
            {
                fun=d;
                break;
            }
        default:
            {
                return 0;
            }
    }
    cout<<"Podaj poczatek przedzialu: ";
    cin>>p;
    cout<<"Podaj koniec przedzialu: ";
    cin>>k;
    cout<<"Podaj przyblizenie: ";
    cin>>approx;
    double delta;
    double prev=1000;
    double current=0;
    int n=2;
    while(abs(prev-current)>approx)
    {
        delta=(k-p)/n;
        prev=current;
        for(int i=0;i<n;i++)
        {
            current=(delta/3)*sum(delta,p,k,n);
        }
        n=n+2;
    }
    cout<<"Wynik to: "<<current;
    cout<<endl<<"--------------------Druga czesc-------------------------"<<endl;

    for(int j=2;j<6;j++)
    {
        double wynik = gauss(j,p,k);
    cout<<"Wynik dla "<<j<<" wezlow, to: "<<wynik<<endl;
    }


    return 0;
}
