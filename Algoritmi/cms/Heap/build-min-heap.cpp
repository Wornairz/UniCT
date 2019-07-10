#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int cont = 0;

template <class T>
void min_heapify(T * array, int i, int heap_size){
	int left = i*2;
	int right = i*2+1;
	int minimo = i;
	if(left<heap_size && array[left]<array[minimo])
		minimo = left;
	if(right<heap_size && array[right]<array[minimo])
		minimo = right;
	if(minimo != i){
		swap(array[minimo], array[i]);
		min_heapify(array, minimo, heap_size);
	}
	return;
}


template <class T>
void build_min_heap(T * array, int n){
	for(int i=n/2; i>0; i--)
		min_heapify(array, i, n);
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
            build_min_heap(vett, n+1);
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
            build_min_heap(vett, n+1);
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
            build_min_heap(vett, n+1);
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
            build_min_heap(vett, n+1);
            for (int i = 1; i < n+1; i++) {
                outfile << vett[i] << " ";
            }
            outfile << "\n";
        }

    }
    return 0;
}
