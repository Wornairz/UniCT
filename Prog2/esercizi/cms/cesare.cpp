#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	int n;
	char c;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n;
		for(int i=0;i<n;i++){
			iss >> c;
			c-=3;
			if(c<'a')
                c = 'z' - ('a' - c) + 1;
            outfile << c;
		}
		outfile << "\n";
	}
	return 0;
}
