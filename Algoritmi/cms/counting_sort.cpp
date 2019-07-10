#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

int getMax(int *A, int n){
	int max = A[0];
	int min = A[0];
	for(int i=1; i<n; i++){
		if(A[i]>max)
			max = A[i];
		if(A[i]<min)
			min = A[i];
	}
	return max;
}

void variabilita(int * A, int n, int * C, int k){
	for(int i=0; i<=k; i++) //inizializza il vettore C che va da 0 a k (massimo valore dell'array A)
		C[i] = 0;
	for(int i=0; i<n; i++) //ad ogni posizione X del vettore C assegnamo il numero di valori uguali a X nell'array A
		C[A[i]]++; //es. se A[i] = 5 aumentiamo il valore di C[5] di un'unità
	for(int i=1; i<=k; i++) //per ogni numero dell'array C contiamo quanti sono i numeri minori o uguali ad esso
		C[i] += C[i-1]; //il numero di elementi <= di X è il numero di elementi X + il numero di elementi <= ad X-1
	//quindi in C[i] avremo il n° degli elementi <= i
}

int * counting_sort(int * A, int * C, int n){
	int * B = new int[n]; //array di output
	for(int i=n-1; i>=0; i--){ //andiamo dal valore più grande a quello più piccolo
		B[C[A[i]]-1] = A[i]; //posizioniamo il valore A[i] nella posizione indicata da C[A[i]]. Il -1 è per motivi di indici dell'array.
		C[A[i]]--; //quindi diminuiamo il numero di elementi <= di A[i] in modo che il prossimo inserimento di un elemento uguale ad A[i] sia nella posizione corretta (la precedente)
	}
	delete[] A;
	return B;
}

int main(){
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line;
	int n;
	int * array, * res;
	while(getline(input, line)){
		istringstream iss(line);
		iss >> n;
		array = new int[n];
		for(int i=0; i<n; i++){
			iss >> array[i];
		}
		int k = getMax(array, n);
		res = new int[k+1];
		variabilita(array, n, res, k);
		output << res[0] << " ";
		for(int i=1; i<k; i++){
			if(res[i] != 0)
				output << res[i] << " ";
		}
		res = counting_sort(array, res, n);
		for(int i=0; i<n; i++){
			output << res[i] << " ";
		}
		output << "\n";
	}
	
	return 0;
}
