#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

double maxguadagno(double* vett, unsigned short n){
  double guadagno = 0;
  for(int i=0; i<n-1; i++){
    //double comprare = vett[i];
    for(int j=i+1; j<n; j++){
      if((vett[j]-vett[i])>guadagno) guadagno = vett[j]-vett[i];
    }
  }
  return guadagno;
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	unsigned short n;
  double* vett;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n;
    vett = new double[n];
		for(int i=0; i<n; i++){
      iss >> vett[i];
		}
		outfile << maxguadagno(vett, n) << "\n";
	}
	return 0;
}
