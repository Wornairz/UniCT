#include <iostream>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(int *a, int low, int high)
{
    // a[high] è il pivot
    int i = low-1; //i punta all'ultimo elemento minore del pivot (dopo i sono tutti maggiori del pivot)
    for(int j=low; j<high; j++) //j scorre l'array che va da low fino ad high
    {
        if(a[j]<a[high]) //se troviamo un elemento minore del pivot
            swap(a[j], a[++i]); //lo scambiamo con il successivo di i che sarà o sè stesso o maggiore del pivot
    }
    swap(a[high], a[i+1]); //mettiamo il pivot al posto giusto dell'intero array (a sinistra avrà tutti i minori e a destra tutti i maggiori)
    return i+1; //ritorniamo la posizione del pivot
}

void quicksort(int *a, int low, int high)
{
    if(low < high) //caso base, evita loop
    {
        int pivot = partition(a, low, high); //dopo partition, pivot sarà alla posizione corretta (vedesi ultimo swap della partition)
        quicksort(a, low, pivot-1); //chiamiamo ricorsivamente sulla parte di array inferiore al pivot
        quicksort(a, pivot+1, high); //chiamiamo ricorsivamente sulla parte di array superiore a pivot
    }
}

int main()
{
    //int *a = new int[10]{22, 15, 73, 65, 36, 88, 33, 18, 24, 111};
    int *a = new int[10] {22, 15, 73, 65, 36, 88, 33, 18, 24, 111};

    quicksort(a, 0, 9);
    for(int i=0; i<10; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
