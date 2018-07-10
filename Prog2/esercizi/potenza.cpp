#include <iostream>

using namespace std;

int potenza(int base, int esp)
{
    if(esp == 0)
        return 1;
    if(esp == 1) //caso base
        return base;
    else if(esp%2==0)
    {
        int y = potenza(base, esp/2);
        return y*y;
    }
    else
    {
        int y = potenza(base, (esp-1)/2);
        return base*y*y;
    }
}

int main()
{
    int base, esponente;
    cout << "inserisci base: "; cin >> base;
    cout << "inserisci esponente: "; cin >> esponente;
    cout << "il risultato e': " << potenza(base, esponente);
    return 0;
}
