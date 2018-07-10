#ifndef SORTING_H
#define SORTING_H

#include <chrono>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <math.h>

using namespace std;

class Sorting
{
    private:
        int lomutoPartition(int*, int, int);
        int hoarePartition(int*, int, int);
        void _quickSort(int*, int, int);
        void _mergeSort(int*, int, int);
        void merge(int*, int, int, int);
        void swap(int&, int&);
    public:
        Sorting(){srand(time(nullptr));};
        void insertionSort(int*, int);
        void selectionSort(int*, int);
        void bubbleSort(int*, int);
        void mergeSort(int*, int);
        void quickSort(int*, int);
        void bogoSort(int*, int);
        void printArray(int*, int);
        int* revSortedArray(int);
        int* sortedArray(int);
        int* randomArray(int);
        bool is_sorted(int*, int);
        int* all0s(int);
        void test(int*, int, Sorting&, void (Sorting::*f)(int*, int));
};









#endif // SORTING_H
