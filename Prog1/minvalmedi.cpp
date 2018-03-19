#include <iostream>

using namespace std;
//Data la matrice A[7][10] di float restituire l'indice di una riga il cui elemento massimo è
//strettamente minore dei valori medi della riga sovrastante e di quella sottostante o restituire il valore -1 se
//tale riga non esiste (non è possibile usare array ausiliari);

int main(){
    float A[7][10];
    for(int i=0;i<7;i++){
        for(int j=0;j<10;j++){
             if(i==0) A[i][j]=3;
             else if(i==1) A[i][j]=1;
             else if (i==2) A[i][j]=2;
             else A[i][j]=i-1;
        }
    }
    bool flag = false;
    for(int i=0;i<7;i++){
        float sopra = 0.0;
        float sotto = 0.0;
        float corrente = 0.0;
        for(int j=0;j<10;j++){
            corrente += A[i][j];
            if(i!=0) sopra += A[i-1][j];
            if(i!=9) sotto += A[i+1][j];
        }
        corrente/=10;
        sopra/=10;
        sotto/=10;
        if(corrente < sopra && corrente < sotto){
            flag = true;
            cout << "la riga e' la " << i << endl;
        }
    }
    if(!flag)
    {
        cout << "-1" << endl;
    }
    return 0;
}
