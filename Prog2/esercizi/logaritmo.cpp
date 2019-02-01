#include <iostream>

using namespace std;

int logaritmo(int base, int argomento, int esponente = 0, int x = 1)
{
    if(base <=1 || x>argomento)
        return -1;
    else if(x == argomento)
        return esponente;
    else
        return logaritmo(base, argomento, esponente+1, x*base);
}

int logaritmo2(int base, int argomento, int esponente = 0, int x = 0){
    if(base <=1 || x>argomento)
        return -1;
    else if(x == base)
        return esponente;
    else
        return logaritmo2(base, argomento, esponente+1, argomento/base);
}

int main()
{
    int base, argomento;
    cout << "inserisci base: "; cin >> base;
    cout << "inserisci argomento: "; cin >> argomento;
    int ris = logaritmo(base, argomento);
    cout << "il risultato del logaritmo intero e': " << ris << endl;
    return 0;
}
