#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

int ** c;

void print_LCS(int i, int j, string s, ofstream & stream) {
    if(i==0 || j==0)
        return;
    if(c[i-1][j-1] >= c[i-1][j] && c[i-1][j-1] >= c[i][j-1] && c[i-1][j-1]!=c[i][j]) {
        print_LCS(i-1, j-1, s, stream);
        if(c[i-1][j-1]!=c[i][j])
            stream << s[i-1];
    }
    else if(c[i-1][j] >= c[i][j-1])
        print_LCS(i-1, j, s, stream);
    else
        print_LCS(i, j-1, s, stream);
}

string print_LCS2(int l1, int l2, string s1, string s2){
	string lcs = "";
    int i = l1;
    int j = l2;
    while(i>0 && j>0) {
        if(s1[i-1]==s2[j-1]) {
            lcs += s1[i-1];
            i--;
            j--;
        }
        else if(c[i-1][j] > c[i][j-1])
            i--;
        else
            j--;
    }
    reverse(lcs.begin(), lcs.end());
    return lcs;
}

int LCS(string s1, int l1, string s2, int l2) {
    c = new int*[l1+1];
    for(int i=0; i<=l1; i++) {
        c[i] = new int[l2+1];
        for(int j=0; j<=l2; j++)
            c[i][j] = 0;
    }
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

        LCS(s1, l1, s2, l2);
        output << print_LCS2(l1, l2, s1, s2) << "\n";
    }
    return 0;
}
