#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	int n;
    double temp, sum;
	while(getline(infile, line)){
		sum=0;
		istringstream iss(line);
		iss >> n;
		for(int i=0;i<n;i++){
			iss >> temp;
            sum+=temp;
		}
		sum= (sum*10);
		sum/=10;
		outfile << sum << "\n";
	}
	return 0;
}
