#include <iostream>
#include <fstream>

using namespace std;

int getMax(int *arr, int n){
    int max = 0;
    for(int i=0; i<n; i++)
        if(arr[i]>max)
            max = arr[i];
    return max;
}

int getMin(int *arr, int n){
    int min = getMax(arr, n);
    for(int i=0; i<n; i++)
        if(arr[i]<min)
            min = arr[i];
    return min;
}

int * variabilita(int *A, int n, int k){
    int * C = new int[k+1];
    for(int i=0; i<=k; i++)
        C[i] = 0;
    for(int i=0; i<n; i++)
        C[A[i]]++;
    for(int i=1; i<=k; i++)
        C[i] += C[i-1];
    return C;
}

int * counting_sort(int *A, int *C, int n){
    int * B = new int[n];
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
    string tipo, temp;
    int n;

    for(int j=0; j<100; j++){
        input >> tipo;
        input >> temp;
        n = stoi(temp);
        if(tipo == "int"){
            int * a = new int[n];
            for(int i=0; i<n; i++){
                input >> temp;
                a[i] = stoi(temp);
            }
            int k = getMax(a, n);
            int * c = variabilita(a, n, k);
            output << 0 << " ";
            for(int i=0; i<k; i++){
                if(c[i] != 0)
                    output << c[i] << " ";
            }
            int * b = counting_sort(a, c, n);
            for(int i=0; i<n; i++){
                output << b[i] << " ";
            }
            output << endl;
        }
        else if(tipo == "bool"){
            int *a = new int[n];
            for(int i=0; i<n; i++){
                input >> temp;
                a[i] = stoi(temp);
            }
            int k = getMax(a, n);
            int * c = variabilita(a, n, k);
            output << 0 << " ";
            output << c[0] << " ";
            int * b = counting_sort(a, c, n);
            for(int i=0; i<n; i++){
                output << b[i] << " ";
            }
            output << endl;
        }
        else if(tipo == "char"){
            int * a = new int[n];
            for(int i=0; i<n; i++){
                input >> temp;
                a[i] = temp[0];
            }
            int k = getMax(a, n);
            int * c = variabilita(a, n, k);
            output << c[0] << " ";
            for(int i=1; i<k; i++){
                if(c[i] != 0)
                    output << c[i] << " ";
            }
            int * b = counting_sort(a, c, n);
            for(int i=0; i<n; i++){
                output << (char) b[i] << " ";
            }
            output << endl;
        }
        else if(tipo == "double"){
            int * a = new int[n];
            for(int i=0; i<n; i++){
                input >> temp;
                double tempd = stod(temp);
                a[i] = tempd*10;
            }
            int k = getMax(a, n);
            int * c = variabilita(a, n, k);
            output << 0 << " ";
            for(int i=0; i<k; i++){
                if(c[i] != 0)
                    output << c[i] << " ";
            }
            int * b = counting_sort(a, c, n);
            for(int i=0; i<n; i++){
                output << (double) b[i]/10 << " ";
            }
            output << endl;
        }
    }
    return 0;
}