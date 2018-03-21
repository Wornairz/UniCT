#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool minore(string max, string str){
	if(max.length() < str.length()) return true;
	else if(max.length() == str.length()){
		for(int i=0; i<max.length(); i++){
			if(max[i]==str[i]) continue;
			else if(max[i]<str[i]) return true;
			else return false;
		}
	}
	return false;
}
int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	short n;
	string max, temp;
	while(getline(infile, line)){
		max= "0";
		istringstream iss(line);
		iss >> n;
		for(int i=0; i<n; i++){
			iss >> temp;
			if(minore(max, temp)) max = temp;
		}
		outfile << max << "\n";
	}
	return 0;
}
