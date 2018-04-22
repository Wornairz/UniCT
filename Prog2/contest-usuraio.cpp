#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

void ordina(int* vett, unsigned short dim){
  for(int i=0; i<dim-1; i++){
    for(int j=i+1; j<dim; j++){
      if(vett[i]>vett[j]){
        int temp = vett[i];
        vett[i] = vett[j];
        vett[j] = temp;
      }
    }
  }
}

int mindist(int* vett, unsigned short n, unsigned short k){
  int mindist=1000000;
  for(int i=0; i<n-k+1; i++){
    int tmpdist = 0;
    for(int j=i+k-1; j>i; j--){
      tmpdist += vett[j]-vett[j-1];
    }
    if(tmpdist<mindist) mindist=tmpdist;
  }
  return mindist;
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	unsigned short n, k;
  int* vett;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n >> k;
    vett = new int[n];
		for(int i=0; i<n; i++){
      iss >> vett[i];
		}
    ordina(vett, n);
		outfile << mindist(vett, n, k) << "\n";
	}
	return 0;
}
