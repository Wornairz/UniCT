#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int fibonacci(int n){
	if(n==1 || n==2) return 1;
	else return fibonacci(n-1)+fibonacci(n-2);
}
int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	int n;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n;
		unsigned int tmp = fibonacci(n);
		outfile << tmp << "\n";
	}
	return 0;
}
