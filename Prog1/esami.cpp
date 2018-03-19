#include <iostream>
#include <string>
using namespace std;

double esame03_02_2015_1(double **md, int n,int m);
string* esame03_02_2015_2(string ***mps, int n);
void es_orazio();
int main(){
    int n=4, m=5;
    string ***mps = new string**[n];
    for(int i=0;i<n;i++){
        mps[i] = new string*[m];
        for(int j=0; j<m; j++){
            mps[i][j] = new string("ci" + to_string(i) + "ao" );
            //cout << *mps[i][j] << endl;
        }
    }
    string **ms = new string*[n];
    for(int i=0;i<n;i++){
        ms[i] = new string[m];
        for(int j=0; j<m; j++){
            ms[i][j] = "ciao" + to_string(i) + to_string(j);
        }
    }
    int **mi = new int*[n];
    for(int i=0;i<n;i++){
        mi[i] = new int[m];
        for(int j=0; j<m; j++){
            mi[i][j] = i;
        }
    }
    double **md = new double*[n];
    for(int i=0;i<n;i++){
        md[i] = new double[m];
        for(int j=0; j<m; j++){
            md[i][j] = i-j;
        }
    }
}
void es_orazio(int **mi, n){
    //Data una matrice quadrata, stampare i valori contenuti in tutte le
    //diagonali parallele alla diagonale secondaria.
    for(int i=n-1;i>0;i--){
        for(int j=n-1;j>0;j--){

        }
    }
}
double esame03_02_2015_1(double **md, int n, int m){
    double min=1000000;
    int i1, i2;
    int temp;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            temp = md[i][2]-md[j][2];
            if(temp<0) temp = -temp;
            if(temp < min){
                min = temp;
                i1 = i;
                i2 = j;
            }
        }
    }
    return md[i1][2]*md[i2][2];
}
string* esame03_02_2015_2(string ***mps, int n){
    string* ptr = new string("");
    for(int i=0;i<n;i++){
        int j=n-1-i;
        int len = (*mps[i][j]).length();
        if(len%2==1){
            *ptr += (*mps[i][j])[(len/2)];
        }
    }
    return ptr;
}
