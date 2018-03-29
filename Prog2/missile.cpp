#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

short check(short x, short y, short tempx, short tempy){
	return sqrt((pow(tempx-x,2))+(pow(tempy-y,2)));
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	short n;
	short x, y;
	short tempx, tempy, bestx, besty;
	short best, att;
	while(getline(infile, line)){
		best = 1001;
		istringstream iss(line);
		iss >> n >> x >> y;
		for(int i=0; i<n; i++){
			iss >> tempx >> tempy;
			att = check(x, y, tempx, tempy);
			if(att<best){
				best = att;
				bestx = tempx;
				besty = tempy;
			}
		}
		outfile << bestx << " " << besty << "\n";
	}
	return 0;
}
