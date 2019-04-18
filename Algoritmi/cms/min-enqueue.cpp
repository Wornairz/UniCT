#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int cont = 0;

template <class T>
void enqueue_min_heap(T * array, T value, int heap_size){
	array[heap_size] = value;
	int parent = heap_size/2;
	while(parent>0 && array[heap_size]<array[parent]){
		swap(array[heap_size], array[parent]);
		heap_size = parent;
		parent = heap_size/2;
	}
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
			bool temp;
            for (int i = 1; i < n+1; i++) {
                iss >> temp;
                enqueue_min_heap(vett, temp, i);
            }
            for (int i = 1; i < n+1; i++) {
                outfile << vett[i] << " ";
            }
            outfile << "\n";
        }
        else if(tipo == "int") {
            int * vett = new int[n+1];
            int temp;
            for (int i = 1; i < n+1; i++) {
                iss >> temp;
                enqueue_min_heap(vett, temp, i);
            }
            for (int i = 1; i < n+1; i++) {
                outfile << vett[i] << " ";
            }
            outfile << "\n";
        }
        else if(tipo == "double") {
            double * vett = new double[n+1];
            double temp;
            for (int i = 1; i < n+1; i++) {
                iss >> temp;
                enqueue_min_heap(vett, temp, i);
            }
            for (int i = 1; i < n+1; i++) {
                outfile << vett[i] << " ";
            }
            outfile << "\n";
        }
        else if(tipo == "char") {
            char * vett = new char[n+1];
            char temp;
            for (int i = 1; i < n+1; i++) {
                iss >> temp;
                enqueue_min_heap(vett, temp, i);
            }
            for (int i = 1; i < n+1; i++) {
                outfile << vett[i] << " ";
            }
            outfile << "\n";
        }

    }
    return 0;
}
