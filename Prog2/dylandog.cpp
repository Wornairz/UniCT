#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	int n, x, z, temp;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n >> x;
		z = 0;
		for(int i=0;i<n;i++){
			iss >> temp;
			if(temp==x){
				z = i+1;
				break;
			}
		}
		outfile << z << "\n";
	}
	return 0;
}
