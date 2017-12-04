#include <iostream>
#include <string>
using namespace std;

int main(){
    int dim;
    cin >> dim;
    string m[dim][dim];
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            cin >> m[i][j];
        }
    }
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            for(int c=j;c<dim-1;c++){
                string tmp1 = m[i][c].substr(0,3);
                string tmp2 = m[i][c+1].substr(m[i][c+1].length()-3,m[i][c+1].length());
                if(tmp1 == tmp2){
                    cout << "la riga " << i << " contiene due stringhe congruenti in ordine 3" << endl;
                }
            }
        }
    }
}
