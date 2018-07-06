#include "Sorting.h"

void Sorting::insertionSort(int * v, int n)
{
    // STABILE , IN-PLACE
    // CASO MIGLIORE: Ω(n), CASO MEDIO: Θ(n^2), CASO PEGGIORE: O(n^2)
    int key, i, j;
    for(i = 1; i < n; i++)
    {
        key = v[i];
        j = i;

        while(--j >= 0 && key < v[j])
            v[j+1] = v[j];

        v[j+1] = key;
    }
}

void Sorting::selectionSort(int * v, int n)
{
    // NON STABILE, IN-PLACE
    // CASO MIGLIORE: Ω(n^2), CASO MEDIO: Θ(n^2), CASO PEGGIORE: O(n^2)
    int i, j, min;
    for(i = 0; i < n-1; i++)
    {
        min = i;
        for(j = i+1; j < n; j++)
        {
            if(v[j] < v[min])
                min = j;
        }

        swap(v[i], v[min]);
    }
}

void Sorting::bubbleSort(int * v, int n)
{
    // STABILE, IN-PLACE
    // CASO MIGLIORE: Ω(n), CASO MEDIO: Θ(n^2), CASO PEGGIORE: O(n^2)
    bool sorted; int i;
    do
    {
        sorted = true;
        for(i = 0; i < n-1; i++)
        {
            if(v[i] > v[i+1])
            {
                swap(v[i], v[i+1]);
                sorted = false;
            }
        }
        n--;
    }while(!sorted);
}

void Sorting::_quickSort(int * v, int low, int high)
{
    // NON STABILE, "IN-PLACE"(In verità occupa O(n)/O(logn) spazio nello stack)
    // CASO MIGLIORE: Ω(n*logn), CASO MEDIO: Θ(n*logn), CASO PEGGIORE: O(n^2)
    if(low < high)
    {
        int mid = hoarePartition(v, low, high);
        _quickSort(v, low, mid);
        _quickSort(v, mid+1, high);
    }
}

void Sorting::_mergeSort(int * v, int low, int high)
{
    // STABILE, NON IN-PLACE
    // CASO MIGLIORE: Ω(n*logn), CASO MEDIO: Θ(n*logn), CASO PEGGIORE: O(n*logn)
    if(low < high)
    {
        int mid = low + (high-low)/2;
        _mergeSort(v, low, mid);
        _mergeSort(v, mid+1, high);
        merge(v, low, mid, high);
    }
}

void Sorting::bogoSort(int * v, int n)
{
    // NON STABILE, IN-PLACE
    // CASO MIGLIORE: Θ(n), CASO MEDIO: Θ(n*n!), CASO PEGGIORE: Θ(LOL)
    while(!is_sorted(v, n))
        random_shuffle(&v[0], &v[n]);
}



void Sorting::merge(int * v, int low, int mid, int high)
{
    // O(n)
    int * t = new int[high-low+1];
    int i = low, j = mid+1, k = 0;

    while(i <= mid && j <= high)
    {
        if(v[i] <= v[j])  // Funziona sia con <= che con <, con < però il merge non è stabile
            t[k++] = v[i++];
        else
            t[k++] = v[j++];
    }

    while(i <= mid)
        t[k++] = v[i++];

    while(j <= high)
        t[k++] = v[j++];

    memcpy(v+low, t, (high-low+1) * sizeof(t));
}


int Sorting::hoarePartition(int * v, int low, int high)
{
    // O(n)
    int i = low - 1;
    int j = high + 1;
    int pivot = v[low];
    while(true)
    {
        do i++; while(v[i] < pivot);
        do j--; while(v[j] > pivot);
        if(i < j) swap(v[i], v[j]);
        else return j;
    }
}

int Sorting::lomutoPartition(int * v, int low, int high)
{
    // O(n)
    int i = low - 1;
    for(int j = low;  j < high; j++)
        if(v[j] < v[high])
            swap(v[++i], v[j]);

    swap(v[i+1], v[high]);

    return i + 1;
}


void Sorting::swap(int & left, int & right)
{
    int temp = left;
    left = right;
    right = temp;
}

void Sorting::quickSort(int * v, int n)
{
    _quickSort(v, 0, n-1);
}

void Sorting::mergeSort(int * v, int n)
{
    _mergeSort(v, 0, n-1);
}

bool Sorting::is_sorted(int * v, int n)
{
    int i;
    for(i = 0; i < n-1 && v[i] <= v[i+1]; i++);
    return (i == n-1);
}
int* Sorting::randomArray(int size)
{
    int * v = new int[size];

    for(int i = 0; i < size; i++)
        v[i] = rand();

    return v;
}

int* Sorting::sortedArray(int size)
{
    int * v = new int[size];

    v[0] = (rand()%5)+1;

    for(int i = 1; i < size; i++)
        v[i] = v[i-1]+(rand()%5)+1;

    return v;
}

int* Sorting::revSortedArray(int size)
{
    int * v = new int[size];

    v[0] = 5*(size-1)+(rand()%size)+1;

    for(int i = 1; i < size; i++)
        v[i] = v[i-1]-(rand()%5)-1;

    return v;
}


int* Sorting::all0s(int size)
{
    return new int[size]();
}


void Sorting::printArray(int * v, int n)
{
    for(int i = 0; i < n; i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

void Sorting::test(int * v, int n, Sorting & s, void (Sorting::*f)(int*, int))
{
    auto begin = chrono::steady_clock::now();

    (s.*f)(v, n);

    auto end = chrono::steady_clock::now();

    cout << "Tempo impiegato = " <<  chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl;

    cout << (is_sorted(v, n) ? "Ordinato correttamente" : "Non ordinato") << endl;
}



