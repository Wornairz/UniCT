# Sorting

 La libreria "Sorting" è stata creata con lo scopo di studiare l'implementazione di vari algoritmi di ordinamento e compararne il tempo di esecuzione
 su tipologie di input differenti.

```cpp

#include "Sorting.h"

int main()
{
    
    const int n = 9999;
    int * a;
    
    a = randomArray(n); 
    test(a, n, bubbleSort); // Testa il tempo di esecuzione del bubbleSort su un array generato casualmente

    a = sortedArray(n);
    test(a, n, quickSort); // Testa il tempo di esecuzione del quickSort su un array ordinato

    a = revSortedArray(n);
    test(a, n, insertionSort); // Testa il tempo di esecuzione dell'insertionSort su un array ordinato all'inverso

}
