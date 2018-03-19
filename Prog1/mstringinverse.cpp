#include <iostream>
#include <string>
using namespace std;

//data una matrice di stringhe di dimensione n x m restituire un booleano che indichi se esiste una colonna
// in cui siano presenti due stringhe contigue l'una inversa dell'altra


int main()
{
    int d1, d2 = 0;
    bool flag = false;
    cout << "inserisci il numero di righe della matrice: ";
    cin >> d1;
    cout << "inserisci il numero di colonne della matrice: ";
    cin >> d2;
    string m[d1][d2];
    for(int i=0;i<d1;i++){
    	for(int j=0;j<d2;j++){
    		cout << "Inserisci stringa: ";
    		cin >> m[i][j];
		}
	}
	cout << endl << endl;
    for(int i=0;i<d2;i++){
    	for(int j=0;j<d1-1;j++){
    		if((m[j][i]).length()==(m[j+1][i]).length()){
    			for(int c=0; c<(m[j][i]).length(); c++){
    				if((m[j][i])[c]==(m[j+1][i])[((m[j+1][i]).length()-c-1)]){
    					flag = true;
					} 
    				else flag = false;
				}
			}
			//cout << "le stringhe " << m[j][i] << " e " << m[j+1][i] << ((flag==true) ? " " : " non ")<< "sono inverse" << endl;
			cout << "Nella colonna " << i << " della matrice " << ((flag==true) ? "" : "non ") << "sono presenti stringhe inverse" << endl;
		}
	}
	return 0;
}

