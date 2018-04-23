#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

short check(short x, short y, short tempx, short tempy){
	return abs(x-tempx)+abs(y-tempy);
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	short n;
  string x, seq;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n >> x;
    //x to lower?
		for(int i=0; i<n; i++){
			iss >> seq;
      //seq to lower?
      if (seq.find(x) != string::npos) {
        outfile << seq << " ";
      }
		}
		outfile << "\n";
	}
	return 0;
}
