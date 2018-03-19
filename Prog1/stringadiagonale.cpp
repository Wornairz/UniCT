#include <iostream>
#include <string>
using namespace std;
// Data una matrice quadrata di stringhe, restituire una stringa ottenuta concatenando tutti gli ultimi
//caratteri delle stringhe presenti nella diagonale principale

int main(){
    int dim = 0;
    cout << "Inserisci dimensione matrice quadrata: ";
    cin >> dim;
    string m[dim][dim];
    string a = "";
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            cin >> m[i][j];
            if(i==j){
                a+=(m[i][j])[(m[i][j]).length()-1];
                //a+=(m[i][j]).at((m[i][j]).length()-1);
            }
        }
    }
    cout << a;
    return 0;
}
