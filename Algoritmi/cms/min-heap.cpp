#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class T>
class MinHeap{
private:
	int heap_size, dim;
	T * array;
	
	void min_heapify(int index){
		if(index>heap_size) return;
		chiamate++;
		int left = index << 1;
		int right = (index << 1)+1;
		int minimo = index;
		if(left<=heap_size && array[left]<array[minimo])
			minimo = left;
		if(right<=heap_size && array[right]<array[minimo])
			minimo = right;
		if(minimo!=index){
			swap(array[index], array[minimo]);
			min_heapify(minimo);
		}
	}
	
	void swap(T & a, T & b){
		T temp = a;
		a = b;
		b = temp;
	}
	
public:
	int chiamate;
	
	MinHeap(int n){
		heap_size = chiamate = 0;
		array = new T[n];
		dim = n;
	}
	
	bool enqueue(T value){
		if(heap_size>=dim)
			return false;
		else{
			array[++heap_size] = value;
			int current = heap_size;
			int parent = current >> 1;
			while(parent>0 && array[current]<array[parent]){
				swap(array[parent], array[current]);
				current = parent;
				parent = current >> 1;
			}
			return true;
		}
	}
	
	T dequeue(){
		T min = array[1];
		array[1] = array[heap_size--];
		min_heapify(1);
		return min;
	}
	
	void stampa(ofstream & stream){
		for(int i=1; i<=heap_size; i++){
			stream << array[i] << " ";
		}
		stream << "\n";
	}
};

int main(){
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line, tipo, temp;
	int n;
	while(getline(input, line)){
		istringstream iss(line);
		iss >> tipo;
		iss >> n;
		if(tipo == "bool"){
			MinHeap<bool> heap = MinHeap<bool>(n);
			for(int i=0; i<n; i++){
				iss >> temp;
				if(temp == "extract")
					heap.dequeue();
				else{
					bool b;
					istringstream(temp.substr(2)) >> b;
					heap.enqueue(b);
				}
			}
			output << heap.chiamate << " ";
			heap.stampa(output);			
		}
		else if(tipo == "char"){
			MinHeap<char> heap = MinHeap<char>(n);
			for(int i=0; i<n; i++){
				iss >> temp;
				if(temp == "extract")
					heap.dequeue();
				else{
					heap.enqueue(temp[2]);
				}
			}
			output << heap.chiamate << " ";
			heap.stampa(output);	
		}
		else if(tipo == "int"){
			MinHeap<int> heap = MinHeap<int>(n);
			for(int i=0; i<n; i++){
				iss >> temp;
				if(temp == "extract")
					heap.dequeue();
				else{
					int num;
					istringstream(temp.substr(2)) >> num;
					heap.enqueue(num);
				}
			}
			output << heap.chiamate << " ";
			heap.stampa(output);	
		}
		else if(tipo == "double"){
			MinHeap<double> heap = MinHeap<double>(n);
			for(int i=0; i<n; i++){
				iss >> temp;
				if(temp == "extract")
					heap.dequeue();
				else{
					double d;
					istringstream(temp.substr(2)) >> d;
					heap.enqueue(d);
				}
			}
			output << heap.chiamate << " ";
			heap.stampa(output);	
		}
	}
	return 0;
}
