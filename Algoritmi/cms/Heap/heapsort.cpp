#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

template <class T>
class Heap {
private:
    int dim;
    int heapSize;
    int cont;
    T* array;

    void swap(int a, int b) {
        T temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }

    void max_heapify(int index) {
        if(index < 1 || index > heapSize)
            return;
        else
            cont++;

        int left = index << 1;
        int right = (index << 1)|1;
        int min = index;

        if(left <= heapSize && array[left]>array[min])
            min = left;
        if(right <= heapSize && array[right]>array[min])
            min = right;

        if(min!=index) {
            swap(index, min);
            max_heapify(min);
        }
    }

    T extract(){
		T val = array[1];
		swap(1, heapSize--);
		max_heapify(1);
		return val;
	}


public:
    Heap(int size) {
        dim = size;
        heapSize = 0;
        cont = 0;
        array = new T[dim+1];
    }

    void build(T* tarray) {

        for(int i=0; i<dim; i++) {
            array[i+1] = tarray[i];
        }

        heapSize = dim;

        for(int i=heapSize/2; i>0; i--) {
            max_heapify(i);
        }
    }

    void sort(T * array) {
		build(array);
		for(int i=1; i<=dim; i++){
			extract();
		}
    }

    void stampa(ofstream & output) {
        output << cont << " ";
        for(int i=1; i<=dim; i++) {
            output << array[i] << " ";
        }
        output << endl;
    }
};


int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string line, tipo;
    int n;

    while(getline(input, line)) {
        istringstream iss(line);
        iss >> tipo;
        iss >> n;
        if(tipo == "char") {
            Heap<char> heap(n);
            char * array = new char[n];
            for(int i=0; i<n; i++) {
                iss >> array[i];
            }
            heap.sort(array);
            heap.stampa(output);
        }
        else if(tipo == "int") {
            Heap<int> heap(n);
            int * array = new int[n];
            for(int i=0; i<n; i++) {
                iss >> array[i];
            }
            heap.sort(array);
            heap.stampa(output);
        }
        else if(tipo == "bool") {
            Heap<bool> heap(n);
            bool * array = new bool[n];
            for(int i=0; i<n; i++) {
                iss >> array[i];
            }
            heap.sort(array);
            heap.stampa(output);
        }
        else if(tipo == "double") {
            Heap<double> heap(n);
            double * array = new double[n];
            for(int i=0; i<n; i++) {
                iss >> array[i];
            }
            heap.sort(array);
            heap.stampa(output);
        }
    }

    return 0;
}
