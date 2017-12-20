#include <iostream>


uintmax_t fibo_r(int n);
uintmax_t fibo_i(int n);
/*
    Il programma ha lo scopo di mostrare la differenza nel tempo di esecuzione tra la successione di Fibonacci definita in modo ricorsivo ed iterativo
*/

int main()
{
    using namespace std;

    unsigned int posizione=1;
    bool scelta=true;

    cout << "0)Fibonacci iterativo\n1)Fibonacci ricorsivo\n";
    cin >> scelta;
    cout << "Inserisci la posizione del numero da restituire(MAX=93)\n";
    cin >> posizione;
    cout << "Il numero di Fibonacci alla posizione " << posizione << " e' " << (scelta ? fibo_r(posizione) : fibo_i(posizione));
}

uintmax_t fibo_r(int n)
{
    if(n==1 || n==2) return 1; //Oppure if(n<3)
    else return fibo_r(n-1)+fibo_r(n-2);
}


uintmax_t fibo_i(int n)
{
    uintmax_t num=1, num_prec=1;
    for(unsigned int i=2; i<n; i++)
    {
        num+=num_prec;
        num_prec=num-num_prec;
    }
    return num;
}









