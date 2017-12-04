#include <iostream>
#include <string>
using namespace std;
bool check(int r, int c, short w, string **m);
//Scrivere un metodo che prenda come parametri formali una matrice A di stringhe ed uno short w,
//e restituisca in output un bool che indichi se esiste una riga di A in cui siano presenti almeno due stringhe in cui i primi
//w caratteri dell’una siano uguali agli ultimi w caratteri dell’altra (nello stesso ordine)

int main(){
    int r,c;
    short w;
    cout << "Inserisci il numero di righe: "; cin >> r;
    cout << "Inserisci il numero di colonne: "; cin >> c;
    cout << "Inserisci il numero w di caratteri da controllare: "; cin >> w;
    string **m;
    m = new string *[r];
    for(int i=0;i<r;i++){
        m[i] = new string[c];
        for(int j=0;j<c;j++){
            cin >> m[i][j];
        }
    }
    check(r,c,w,m);
    return 0;
}
bool check(int r, int c, short w, string **m){

    for(int i=0;i<r;i++){
        for(int j=0;j<c-1;j++){
            for(int g=j;g<c-1;g++){
                bool flag=false;
                for(int d=0;d<w;d++){
                        //cout << (m[i][g])[d]; cout << (m[i][g+1])[(m[i][g+1]).length()-w+d];
                    if((m[i][g])[d]==(m[i][g+1])[(m[i][g+1]).length()-w+d]){
                        flag=true;
                    }
                    else{
                        flag=false;
                        break;
                    }
                }
                if(flag){
                    cout << "Alla riga " << i << " ci sono stringhe che rispettano la consegna" << endl;
                }
            }
        }
    }
}
