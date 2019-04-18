#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int cont = 0;

template <class T>
void max_heapify(T * array, int i, int heap_size) {
    int left = 2*i;
    int right = 2*i+1;
    int massimo = i;
    //cout << "i = " << array[i] << " l = " << array[left] << " r = " << array[right] << " ";
    if(left<heap_size && array[left]>array[massimo])
        massimo = left;
    if(right<heap_size && array[right]>array[massimo])
        massimo = right;
    //cout << "max = " << array[massimo] << "\n";
    if(massimo != i) {
        swap(array[massimo], array[i]);
        max_heapify(array, massimo, heap_size);
    }
    return;
}

template <class T>
static void build_max_heap(T * array, int n) {
    for(int i = n/2; i>0 ; i--)
        max_heapify(array, i, n);
    return;
}

template <class T>
void swap(T & a, T & b) {
    T & temp = a;
    a = b;
    b = temp;
}

int main() {
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    string line, tipo;
    int n;
    while (getline(infile, line)) {
		cout << "Riga: " << ++cont << "\n";
        istringstream iss(line);
        iss >> tipo;
        iss >> n;
        if(tipo == "bool") {
            bool * vett = new bool[n+1];

            for (int i = 1; i < n+1; i++) {
                iss >> vett[i];
            }
            build_max_heap(vett, n+1);
            for (int i = 1; i < n+1; i++) {
                outfile << vett[i] << " ";
            }
            outfile << "\n";
        }
        else if(tipo == "int") {
            int * vett = new int[n+1];
            for (int i = 1; i < n+1; i++) {
                iss >> vett[i];
            }
            build_max_heap(vett, n+1);
            for (int i = 1; i < n+1; i++) {
                outfile << vett[i] << " ";
            }
            outfile << "\n";
        }
        else if(tipo == "double") {
            double * vett = new double[n+1];
            for (int i = 1; i < n+1; i++) {
                iss >> vett[i];
            }
            build_max_heap(vett, n+1);
            for (int i = 1; i < n+1; i++) {
                outfile << vett[i] << " ";
            }
            outfile << "\n";
        }
        else if(tipo == "char") {
            char * vett = new char[n+1];
            for (int i = 1; i < n+1; i++) {
                iss >> vett[i];
            }
            build_max_heap(vett, n+1);
            for (int i = 1; i < n+1; i++) {
                outfile << vett[i] << " ";
            }
            outfile << "\n";
        }

    }
    return 0;
}
