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
	for(int i=0; i<=k; i++)
		C[i] = 0;
	for(int i=0; i<n; i++)
		C[A[i]]++;
	for(int i=0; i<=k; i++)
		C[i] += C[i-1];
}

int * counting_sort(int * A, int * C, int n){
	int * B = new int[n]; // output
	for(int i=n-1; i>=0; i--){
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
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
