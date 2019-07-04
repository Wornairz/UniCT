#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void ordina(int *a, int n, int * b){
	//ordina per tempo di fine crescente
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			if(a[i]>a[j]){
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
				//spostiamo anche i relativi tempi di inizio
				temp = b[i];
				b[i] = b[j];
				b[j] = temp;
			}
		}
	}
}

int cardinalita(int *inizio, int *fine, int n){
	int card = 0;
	int lastfine = 0;
	for(int i=0; i<n; i++){
		if(inizio[i]>=lastfine){
			lastfine = fine[i];
			card++;
		}
	}
	return card;
}

int main(){
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line;
	int n;
	int * start,* end;
	for(int j=0; j<3; j++){
		//istringstream iss(line);
		input >> n;
		start = new int[n];
		end = new int[n];
		for(int i=0; i<n; i++){
			string temp;
			int inizio, fine;
			input >> temp;
			cout << temp << endl;
			istringstream(temp.substr(1)) >> inizio;
			istringstream(temp.substr(temp.find(",")+1, temp.find(")"))) >> fine;
			start[i] = inizio;
			end[i] = fine;
		}
		ordina(end, n, start);
		output << cardinalita(start, end, n) << endl;
	}
	return 0;
}
