#include <iostream>
#include <fstream>

using namespace std;

void sort(int *a, int N) {
	for (int i=0; i<N-1; i++) {
		for (int j=i+1; j<N; j++) {
			if (a[i] < a[j]) {
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}

int greedy_knapsack(int *a, int N, int P) {
	sort(a,N);
	int sum = 0; 
	for (int i=0; i<P; i++) {
		sum += a[i];
	}
	return sum; 
}

int main() {
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	
	int N, P; 
	
	while (!input.eof()) {
		input >> N;
		input >> P; 
		
		int a[N];
		for (int i=0; i<N; i++) 
			input >> a[i];
		
		output << greedy_knapsack(a, N, P) << endl;
	}
		
}
