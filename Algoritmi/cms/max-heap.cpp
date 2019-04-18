#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class T>
class MaxHeap {
private:
    T * array;
    int dim, heap_size;

    void swap(T & a, T & b) {
        T temp = a;
        a = b;
        b = temp;
    }

public:
    int chiamate;

    MaxHeap(int dim) {
        this->dim = dim;
        array = new T[dim];
        heap_size = 0;
        chiamate = 0;
    }

    void max_heapify(int index) {
        if(index>heap_size) return;
        chiamate++;
        int left = index << 1;
        int right = (index << 1)+1;
        int massimo = index;
        if(left <= heap_size && array[left]>array[massimo])
            massimo = left;
        if(right<=heap_size && array[right]>array[massimo])
            massimo = right;
        if(massimo != index) {
            swap(array[index], array[massimo]);
            max_heapify(massimo);
        }
    }

    bool enqueue(T value) {
        if(heap_size+1<dim) {
            heap_size++;
            array[heap_size] = value;
            int parent = heap_size >> 1;
            int current = heap_size;
            while(parent>=1 && array[current]>array[parent]) {
                swap(array[current], array[parent]);
                current = parent;
                parent = current >> 1;
            }
            return true;
        }
        else return false;
    }

    T extract_max() {
        T max = array[1];
        array[1] = array[heap_size];
        heap_size--;
        max_heapify(1);
        return max;
    }

    void stampa(ofstream & stream) {
        for(int i=1; i<=heap_size; i++) {
            stream << array[i] << " ";
        }
    }

    void stampaTest() {
        for(int i=1; i<=heap_size; i++) {
            cout << array[i] << " ";
        }
        cout << "\n";
    }

};


int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string line, tipo, temp;
    int n;
    while(getline(input, line)) {
        istringstream iss(line);
        iss >> tipo;
        iss >> n;
        if(tipo == "bool") {
            MaxHeap<bool> heap = MaxHeap<bool>(n);
            for(int i=0; i<n; i++) {
                iss >> temp;
                if(temp == "extract") {
                    heap.extract_max();
                }
                else {
                    bool b;
                    istringstream(temp.substr(2)) >> b;
                    heap.enqueue(b);
                }
            }
            output << heap.chiamate << " ";
            heap.stampa(output);
            output << "\n";
        }
        else if(tipo == "double") {
            MaxHeap<double> heap = MaxHeap<double>(n);
            for(int i=0; i<n; i++) {
                iss >> temp;
                if(temp == "extract")
                    heap.extract_max();
                else {
                    double d;
                    istringstream(temp.substr(2)) >> d;
                    heap.enqueue(d);
                }
            }
            output << heap.chiamate << " ";
            heap.stampa(output);
            output << "\n";
        }
        else if(tipo == "char") {
            MaxHeap<char> heap = MaxHeap<char>(n);
            for(int i=0; i<n; i++) {
                iss >> temp;
                if(temp == "extract")
                    heap.extract_max();
                else {
                    char c = temp[2];
                    heap.enqueue(c);
                }
            }
            output << heap.chiamate << " ";
            heap.stampa(output);
            output << "\n";
        }
        else if(tipo == "int") {
            MaxHeap<int> heap = MaxHeap<int>(n);
            for(int i=0; i<n; i++) {
                iss >> temp;
                if(temp == "extract")
                    heap.extract_max();
                else {
                    temp = temp.substr(2);
                    int num;
                    istringstream(temp) >> num;
                    heap.enqueue(num);
                }
            }
            output << heap.chiamate << " ";
            heap.stampa(output);
            output << "\n";
        }
        else {
            cout << "errore nell'input" << endl;
            exit(1);
        }
    }
    return 0;
}
