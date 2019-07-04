#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

int resto(int * monete, int n, int resto){
	int * r = new int[resto+1];
	r[0] = 0; //caso banale resto 0
	for(int i=1; i<=resto; i++){ //cerchiamo la soluzione migliore per ogni possibile resto da tornare
		int q = INT_MAX; //placeholder che verrà sostituito sse è possibile tornare il resto
		for(int j=0; j<n; j++){ //scorre tutto l'array delle monete
			if(i-monete[j]>=0 && r[i-monete[j]]!=INT_MAX) //controllo per evitare che la moneta sia troppo grande E per evitare che il resto, dopo aver dato quella moneta, sia impossibile da dare
				q = min(q, r[i-monete[j]]+1); //si sceglie il minimo tra il precedente e l'attuale numero di monete da tornare
		}
		r[i] = q; //infine si setta il miglior risultato per l'attuale resto da tornare
	}
	return r[resto];
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string line;
    int r, n;
    int * monete;
    while(getline(input, line)) {
        istringstream iss(line);
        iss >> r;
        iss >> n;
        monete = new int[n];
        for(int i=0; i<n; i++) {
            iss >> monete[i];
        }
		output << resto(monete, n, r) << "\n";
    }
    return 0;
}
