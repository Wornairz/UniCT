#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class T>
class Heap{
public:
	Heap(int size){
		dim = size;
		heapSize = count = 0;
		array = new T[size+1];
	}

	void sort(T * vett){
		build_min_heap(vett);
		for(int i=0; i<dim; i++){
			extract_min();
		}
	}

	void stampa(ofstream & output){
		output << count << " ";
		for(int i=1; i<=dim; i++){
			output << array[i] << " ";
		}
		output << "\n";
	}

private:
	int heapSize, dim, count;
	T * array;

	void min_heapify(int i){
		if(i < 1 || i>heapSize)
			return;
		count++;

		int left = i << 1;
		int right = (i << 1)|1;
		int min = i;

		if(left <= heapSize && array[left]<array[min])
			min = left;
		if(right <= heapSize && array[right]<array[min])
			min = right;

		if(min != i){
			swap(min, i);
			min_heapify(min);
		}
	}

	void build_min_heap(T * vett){
		for(int i=1; i<=dim; i++){
			array[i] = vett[i-1];
		}

		heapSize = dim;

		for(int i=heapSize/2; i>0; i--){
			min_heapify(i);
		}
	}

	T extract_min(){
		T val = array[1];
		swap(1, heapSize--);
		min_heapify(1);
		return val;
	}

	void swap(int a, int b){
		T val = array[a];
		array[a] = array[b];
		array[b] = val;
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
