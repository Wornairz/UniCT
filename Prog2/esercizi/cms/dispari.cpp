#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	int n, x;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n;
		for(int i=0;i<n;i++){
			iss >> x;
			if(x%2==1){
				outfile << x << " ";
			}
		}
		outfile << "\n";
	}
	return 0;
}
