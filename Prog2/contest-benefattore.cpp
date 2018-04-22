#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int cassepeso(double* vett, unsigned short dim, double maxpeso, double& peso){
  peso=0;
  int ncasse=0;
  for(int i=0; i<dim; i++){
    if((vett[i]+peso)<=maxpeso){
      peso+=vett[i];
      ncasse++;
    }
  }
  return ncasse;
}

void ordina(double* vett, unsigned short dim){
  for(int i=0; i<dim-1; i++){
    for(int j=i+1; j<dim; j++){
      if(vett[i]>vett[j]){
        double temp = vett[i];
        vett[i] = vett[j];
        vett[j] = temp;
      }
    }
  }
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
  double maxpeso, peso;
	unsigned short n;
  double* vett;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> maxpeso >> n;
    vett = new double[n];
		for(int i=0; i<n; i++){
      iss >> vett[i];
		}
    ordina(vett, n);
		outfile << cassepeso(vett, n, maxpeso, peso) << " " << peso << "\n";
	}
	return 0;
}
