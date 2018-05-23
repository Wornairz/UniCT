#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	int n, m, **mat, temp;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n;
		iss >> m;
		mat = new int*[n];
		for(int i=0;i<n;i++){
			mat[i] = new int[m];
			for(int j=0; j<m; j++){
                iss >> mat[i][j];
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0; j<m; j++){
                iss >> temp;
                mat[i][j] += temp;
                outfile << mat[i][j] << " ";
			}
		}
		outfile << "\n";
	}
	return 0;
}
