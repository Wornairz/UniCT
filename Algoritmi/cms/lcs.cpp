#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int LCS(string s1, int l1, string s2, int l2) {
    int c[l1+1][l2+1];
    for(int i=0; i<=l1; i++)
        for(int j=0; j<=l2; j++)
            c[i][j] = 0;
    for(int i=1; i<=l1; i++) {
        for(int j=1; j<=l2; j++) {
            if(s1[i-1]==s2[j-1])
                c[i][j] = c[i-1][j-1]+1;
            else if(c[i-1][j]>=c[i][j-1])
                c[i][j] = c[i-1][j];
            else
                c[i][j] = c[i][j-1];
        }
    }
    return c[l1][l2];
}

int recursive_LCS(string s1, int l1, string s2, int l2, int **c) {
    if(c[l1][l2] != -1)
        return c[l1][l2];
    if(s1[l1] == s2[l2]) {
        c[l1][l2] = recursive_LCS(s1, l1-1, s2, l2-1, c)+1;
        return c[l1][l2];
    }
    else {
        if(recursive_LCS(s1, l1-1, s2, l2, c)>= recursive_LCS(s1, l1, s2, l2-1, c))
            return c[l1-1][l2];
        else
            return c[l1][l2-1];
    }

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
        int ** c;
        c = new int*[l1];
        for(int i=0; i<l1; i++) {
            c[i] = new int[l2];
            for(int j=0; j<l2; j++)
                c[i][j] = -1;
        }
        for(int i=0; i<l1; i++)
            c[i][0] = 0;
        for(int i=0; i<l2; i++)
            c[0][i] = 0;
        /*output << recursive_LCS(s1, l1-1, s2, l2-1, c) << "\n";
        for(int i=0; i<l1; i++){
        	for(int j=0; j<l2; j++)
        		cout << c[i][j] << " ";
        	cout << endl;
        } */
        output << LCS(s1, l1, s2, l2) << "\n";
    }
    return 0;
}
