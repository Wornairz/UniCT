#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void ordina(int *a, int n){
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			if(a[i]<a[j]){
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

int greeda(int *a, int n, int p){
	int sum = 0;
	int count = 0;
	for(int i=0; i<n; i++){
		if(count+1<=p){
			count++;
			sum+=a[i];			
		}
	}
	return sum;
}


int main(){
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line;
	int * array;
	int p, n;
	while(getline(input, line)){
		istringstream iss(line);
		iss >> n;
		iss >> p;
		array = new int[n];
		for(int i=0; i<n; i++)
			iss >> array[i];
		ordina(array, n);
		output << greeda(array, n, p) << "\n";
	}
	return 0;
}
