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
	while(getline(input, line)){
		istringstream iss(line);
		iss >> n;
		start = new int[n];
		end = new int[n];
		for(int i=0; i<n; i++){
			string temp;
			int inizio, fine;
			iss >> temp;
			//cout << "temp1 = " << temp << " ";
			istringstream(temp.substr(1)) >> inizio;
			iss >> temp;
			//cout << "temp2 = " << temp << endl;
			istringstream(temp.substr(0, temp.find(")"))) >> fine;
			//cout << "inizio = " << inizio << " fine = " << fine << endl;
			start[i] = inizio;
			end[i] = fine;
		}
		ordina(end, n, start);
		/*for(int i=0; i<n; i++){
			cout << "(" << start[i] << " " << end[i] << ")" << " ";
		}
		cout << endl;*/
		output << cardinalita(start, end, n) << endl;
	}
	return 0;
}
