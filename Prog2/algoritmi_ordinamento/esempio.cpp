#include "Sorting.h"


int main()
{
    const int n = 20000;
    Sorting s;
    int * a;

    a = s.randomArray(n);
    s.test(a, n, s, Sorting::bubbleSort);

    a = s.sortedArray(n);
    s.test(a, n, s, Sorting::quickSort);

    a = s.revSortedArray(n);
    s.test(a, n, s, Sorting::insertionSort);

    return 0;
}


