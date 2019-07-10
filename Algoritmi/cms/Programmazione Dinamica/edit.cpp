#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int min_edit(string s1, string s2){
	//creazione matrice
	int ** m = new int*[s1.length()+1];
	for(int i=0; i<=s1.length(); i++){
		m[i] = new int[s2.length()+1];
	}

	//inizializzazione matrice
	for(int i=0; i<=s1.length(); i++)
		m[i][0] = i;
	for(int i=0; i<=s2.length(); i++)
		m[0][i] = i;

	for(int i=1; i<=s1.length(); i++){
		for(int j=1; j<=s2.length(); j++){
			if(s1[i-1] == s2[j-1])
				m[i][j] = m[i-1][j-1];
			else
				m[i][j] = min(m[i-1][j-1], min(m[i-1][j], m[i][j-1]))+1;
		}
	}
	return m[s1.length()][s2.length()];
}

int main(){
	ifstream input("input.txt");
	ofstream output("output.txt");
	string line, s1, s2;
	int l1, l2;
	while(getline(input, line)){
		istringstream iss(line);
		iss >> l1;
		iss >> l2;
		iss >> s1;
		iss >> s2;
		output << min_edit(s1, s2) << endl;
	}
}
