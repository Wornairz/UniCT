#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

void ordina(int * a, int n){
	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			if(a[j]<a[i]){
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

int resto(int * monete, int n, int resto, int * m_usate){
	int * r = new int[resto+1];
	r[0] = 0;
	for(int i=1; i<=resto; i++){
		int q = INT_MAX;
		int tmp_q = q;
		int tmp_moneta = -1;
		for(int j=0; j<n; j++){
			if(i-monete[j]>=0 && r[i-monete[j]]!=INT_MAX){
				q = min(q, r[i-monete[j]]+1);
				if(tmp_q != q){
					tmp_q = q;
					tmp_moneta = monete[j];
				}
			}
		}
		r[i] = q;
		m_usate[i] = tmp_moneta;
	}
	return r[resto];
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string line;
    int r, n;
    int * monete;
    int * m_usate;
    while(getline(input, line)) {
        istringstream iss(line);
        iss >> r;
        iss >> n;
        monete = new int[n];
        for(int i=0; i<n; i++) {
            iss >> monete[i];
        }
		m_usate = new int[r+1];
		int t_m_usate = resto(monete, n, r, m_usate);
		output << t_m_usate << " ";
		int i=r;
		int * array = new int[t_m_usate];
		int cont = 0;
		while(i>0){
			array[cont++] = m_usate[i];
			i -= m_usate[i];
		}
		ordina(array, t_m_usate);
		for(int i=0; i<t_m_usate; i++){
			output << array[i] << " ";
		}
		output << "\n";
    }
    return 0;
}
