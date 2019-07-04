#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

class Matrice {
public:
    int r, c;
    Matrice() {
        r = c = 0;
    }
    Matrice(int righe, int colonne) {
        r = righe;
        c = colonne;
    }
};

int matrix_chain_order(Matrice * p, int n) {
    int m[n][n];
    for(int i=0; i<n; i++) //caso banale quando la lunghezza della catena è 1
        m[i][i] = 0;  //riempiamo la diagonale principale di 0
        
    for(int l=2; l<=n; l++) { // lunghezza della catena, da 2 fino ad n matrici
        for(int i=0; i<=n-l; i++) { //indice sinistro, indica da quale matrice stiamo partendo - nella condizione della i va bene sia i<=n-l che i<n-l+1 usata dal libro
            int j = i + l - 1; // indice destro, indica a quale matrice vogliamo arrivare
            m[i][j] = INT_MAX; // settiamo al massimo valore possibile che verrà poi sostituito
            for(int k=i; k<j; k++){ //indice intermedio, cerchiamo tra tutte le possibili parentesizzazioni tra la matrice i e la matrice j quella ottima k in cui "spezzare" la catena
				int q = m[i][k] + m[k+1][j] + (p[i].r*p[k].c*p[j].c); //il costo della parentesizzazione in esame; dato "ricorsivamente" dal costo della moltiplicazione delle matrici tra i e k + quello tra k+1 e j + il costo per moltiplicare l'attuale soluzione
				if(q<m[i][j]) //se q è migliore del precendente valore calcolato...
					m[i][j] = q; //lo settiamo come nuovo valore migliore; alla fine avremo il valore ottimo
			}
        }
    }
    return m[0][n-1];
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string line, temp;
    Matrice * mat;
    int n;
    while(getline(input, line)) {
        istringstream iss(line);
        iss >> n;
        mat = new Matrice[n];
        for(int i=0; i<n; i++) {
            iss >> temp;
            istringstream(temp.substr(1, temp.find('x'))) >> mat[i].r;
            istringstream(temp.substr(temp.find('x')+1)) >> mat[i].c;
        }
        output << matrix_chain_order(mat, n) << "\n";
    }
    return 0;
}
