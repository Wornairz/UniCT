#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int LCS(string s1, int l1, string s2, int l2) {
    int c[l1+1][l2+1];

    //inizializziamo la matrice
    for(int i=0; i<=l1; i++)
        for(int j=0; j<=l2; j++)
            c[i][j] = 0;

    for(int i=1; i<=l1; i++) {
        for(int j=1; j<=l2; j++) {
            if(s1[i-1]==s2[j-1]) //se i due caratteri precedenti in considerazione sono uguali
                c[i][j] = c[i-1][j-1]+1; //aumentiamo il valore della matrice
            else if(c[i-1][j]>=c[i][j-1]) //se la strada a sinistra è migliore (più grande) di quella sopra
                c[i][j] = c[i-1][j]; //continuiamo con tale strada
            else
                c[i][j] = c[i][j-1]; //altrimenti la strada migliore è quella sopra
        }
    }
    return c[l1][l2];
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string line;
    string s1, s2;
    int l1, l2;
    while(getline(input, line)) {
        istringstream iss(line);
        iss >> l1;
        iss >> l2;
        iss >> s1;
        iss >> s2;
        output << LCS(s1, l1, s2, l2) << "\n";

    }
    return 0;
}
