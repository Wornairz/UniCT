#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

short isdopp(int* vett, int cerc, short n){
  for(int i=0; i<n; i++){
      if(vett[i]==cerc) return true;
  }
  return false;
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	unsigned short n, dopp;
  int* vett;
	while(getline(infile, line)){
		istringstream iss(line);
    dopp=0;
		iss >> n;
    vett = new int[n];
		for(int i=0; i<n; i++){
      iss >> vett[i];
      if(isdopp(vett, vett[i], i)) dopp++;
		}
		outfile << dopp << "\n";
    dopp=0;
	}
	return 0;
}
