/////   Metody Numeryczne i Optymalizacja
/////   Zadanie 4
/////   Obliczanie calkek za pomoca kwadratury Gaussa-Legendre'a oraz metoda Simpsona
/////   Autorzy - Justyna Hubert 210200, Karol Podlewski 210294

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

// >> funkcja zwracajaca wartosc Y dla podanego X, w zaleznosci od tego jaka funkcjie wybral uzytkownik
double funkcja(double x, int wybor)
{   switch(wybor)
    {
        case 1: return x+8;
        case 2: return fabs(x);
        case 3: //3x^3-3x^2-2x+11
        {
            int wsp[4]={3,-3,-2,11};    //wspolczynniki
            int N=3;                    //stopien wielomianu
            double wynik=wsp[0];

            for (int i=1; i<=N; i++)    //schemat hornera iteracyjnie
                wynik=wynik*x+wsp[i];

            return wynik;
        }
        case 4: return cos(x);
        case 5: return ((x+8)*cos(x));
        case 6: return fabs(2*cos(2*x)+1);
        case 7: return x*x+2*x;
        case 8: return (x/(1+x));  //przedzial 0-1
    }
}

//metoda Simpsona
double simpson(double const a, double const b, int wybor, int N)
{
    double s;  //wartosc naszej calki
    double st; //suma wartosc funkcji w punktach srodkowych
    double dx; //odleglosci miedzy dwoma sasiednimi punktami podzialowymi
    double x;  //pozycja punktu podzialowego
    int i;     //licznik punktow podzialowych

    s=0; //wartosc calki na zero
    st=0; //suma wartosci funkcji w punktach srodkowych
    dx = (b-a)/N; //obliczamy odleglosc miedzy dwoma punktami podzialowymi

    for(i=1; i<=N; i++)
    {
        x=a+i*dx; // wartosc punktu podzialowego
        st+=funkcja(x-dx/2, wybor); //wyznaczamy wartosc w punkcie srodkowym
                                    //i dodajemy do siebie

        if(i < N) //zakres do n-1
            s+=funkcja(x, wybor);
    }
    s=dx/6*(funkcja(a, wybor)+funkcja(b, wybor)+2*s+4*st); //wzor simpsona

    return s;
}


//kwadratura Gaussa-Legendre'a
double gauss_p(double m, bool b, double xk);

double gauss(int N, double const a, double const b, int wybor)
{
    double wynik=0;

    double w_x[4][5]={  -0.577350269189626,  0.577350269189626,  0,                  0,                  0,
                        -0.774596669241483,  0.0,                0.774596669241483,  0,                  0,
                        -0.861136311594053, -0.339981043584856,  0.339981043584856,  0.861136311594053,  0,
                        -0.906179845938664, -0.538469310105683,  0.0,                0.538469310105683,  0.906179845938664 };

    for (int k=0; k<N; k++)
    {
        double n=N;
        double x_pom = ( ((a+b)/2) + (((b-a)/2) * w_x[N-2][k]) );
        double Ak = ( (-2)/((n+1)*gauss_p(n+1,0,w_x[N-2][k])*gauss_p(n,1,w_x[N-2][k])) );

        wynik += Ak * funkcja( x_pom , wybor );
    }

    wynik *= ((b-a)/2);

    return wynik;
}

double gauss_p(double m, bool b, double xk)
{
    if (m==0 && b==0)
        return 1;

    else if (m==1 && b==0)
        return xk;

    else if (b==0)
    {
        double wynik = ((2*(m-1)+1)/m)*xk*gauss_p(m-1,0,xk) - (((m-1)/m)*gauss_p(m-2,0,xk));
        if (fabs(wynik)<0.001)      wynik=0;
        return wynik;
    }

    else
    {
        double wynik = (((m/(xk*xk-1))*xk*gauss_p(m,0,xk)) - ((m/(xk*xk-1))*gauss_p(m-1,0,xk)));;
        if (fabs(wynik)<0.001)      wynik=0;
        return wynik;
    }
}



int main()
{
    int wybor;      // zmienna, ktora odpowiada za wywolanie prawidlowej funkcji do obliczenia
    int warunek;    // warunek stopu w programie

    double a,b;     // zakres funkcji
    int z=1;        // zageszczenie
    double e;       // epsilon

    // nazwy zmiennych w stringu, by latwiej bylo je wprowadzac do pliku wynikowego oraz do legendy na wykresie
    string nazwa[8]={"x+8","|x|","x^3-2x^2+7x-3","cos(x)","cos(x)*(x+8)","|2cos(2x)+1|","x^2+2x","x/(1+x)"};

    char t='n';         // zmienna pomocnicza
    ofstream plik;      // plik, do ktorego zapisujemy wyniku programu - na potrzeby wlasne, bez podanych etykiet
    plik.open("wyniki.txt");        //otwieranie owego pliku

    while(t=='n')
    {
        system( "cls" );

        cout<<"Wybierz funkcje:";
        cout<<"\n[1] Liniowa: x+8";
        cout<<"\n[2] Modul: |x|";
        cout<<"\n[3] Wielomian: x^3-2x^2+7x-3";
        cout<<"\n[4] Trygonometryczna: cos(x)";
        cout<<"\n[5] Zlozenie: cos(x)*(x+8)";
        cout<<"\n[6] Zlozenie: |2cos(2x)+1|";
        cout<<"\n[7] x^2+2x";
        cout<<"\n[8] x/(1+x)";
        cout<<"\n\nWybieram: ";
        cin>>wybor;

        while (wybor>8 || wybor<1)
        {
            cout<<"Bledny wybor! Wybieram: ";
            cin>>wybor;
        }

        cout<<"\nWprowadz zakres: ";
        cin>>a>>b;

        if (a>b)
        {
            int c=b;
            b=a;
            a=c;
        }

        cout<<"\nWpisz epsilon: ";
        cin>>e;

////    >>>>> Wypisywanie info do pliku i na ekran

        system( "cls" );

        cout << "Funkcja:\t" << nazwa[wybor-1];
        cout << "\nPrzedzial:\ta=" << a << ", b=" << b;
        cout << "\nEpsilon:\t" << e;

        plik << "Funkcja: " << nazwa[wybor-1];
        plik << "\nPrzedzial: a=" << a << ", b=" << b;
        plik << "\nEpsilon: " << e;

////    >>>>> Metoda Simpsona

        int i=1;

        double calka_old=0, calka=simpson(a,b,wybor,i);
        while( fabs(calka_old-calka)>e )
        {
            i++;
            calka_old=calka;
            calka=simpson(a,b,wybor,i);
        }

        cout << "\n\nMetoda Simpsona: " << calka;
        cout << "\nLiczba przebiegow: " << i;

        plik << "\n\nMetoda Simpsona: " << calka;
        plik << "\nLiczba przebiegow: " << i;

////    >>>>> Kwadratura Gaussa-Legendre'a

        cout << "\n\nKwadratura Gaussa-Legendre'a dla:";
        plik << "\n\nKwadratura Gaussa-Legendre'a dla:";

        for (int j=2; j<6; j++)
        {
            cout << "\n - " << j << " wezlow: " << gauss(j,a,b,wybor);
            plik << "\n - " << j << " wezlow: " << gauss(j,a,b,wybor);
        }

////    >>>>> Koniec programu

        plik << "\n\n\n";

        cout << "\n\nKonczymy dzialanie programu? ";
        cout << "\n[t] - zakoncz program";
        cout << "\n[n] - rozpocznij program od nowa ";
        cout << "\n\nWybieram: ";
        cin>>t;
    }

    plik.close();

    return 0;
}
