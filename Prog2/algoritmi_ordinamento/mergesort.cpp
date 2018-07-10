#include <iostream>
#include <cstring>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void merge(int *a, int low, int mid, int high){
    int i = low; //iteratore per la parte sinistra, deve fermarsi a mid
    int j = mid+1; //iteratore per la parte destra, deve fermarsi a high
    int *b = new int[high-low+1]; //array ausiliario che conterrà le due parti di a
    int k = 0; //iteratore per il nuovo array b
    while(i<=mid && j<=high){ //poniamo le condizioni di uscita (vedesi sopra)
        if(a[i]<a[j]) //se l'elemento più piccolo è nella parte sinistra
            b[k++] = a[i++];
        else          //se l'elemento più piccolo è nella parte destra
            b[k++] = a[j++];
    }
    while(i<=mid) //controlliamo se sono rimasti elementi nella parte sinistra
        b[k++] = a[i++];
    while(j<=high) //controlliamo se sono rimasti elementi nella parte destra
        b[k++] = a[j++];
    for(int i=low; i<=high; i++){
        a[i] = b[i-low];
    }
}

void mergesort(int *a, int low, int high){
    if(low < high){
        int mid = (low+high)/2; //dividiamo in 2 l'array
        mergesort(a, low, mid); //chiamiamo ricorsivamente sulla parte sinistra
        mergesort(a, mid+1, high); // chiamiamo ricorsivamente sulla parte destra
        merge(a, low, mid, high); //uniamo le due parti
    }
}

int main()
{
    int *a = new int[10]{22, 15, 73, 65, 36, 88, 33, 18, 24, 111};

    mergesort(a, 0, 9);
    for(int i=0; i<10; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
