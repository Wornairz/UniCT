#include <math.h>
#include <iostream>
using namespace std;

double logaritmo(double base, double argomento)
{
    double esponente = 1, logaritmo = 0;
    while(argomento > 1)
    {
        if(argomento >= base)
        {
            logaritmo += esponente;
            argomento /= base;
        }
        else
        {
            esponente /= 2;
            base = sqrt(base);
        }
    }
    return logaritmo;

}

int main()
{
   cout << logaritmo(3, 57) << endl;
}
