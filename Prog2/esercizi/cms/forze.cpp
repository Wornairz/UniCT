#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void ordina(int* vett, int dim){
  for(int i=0; i<dim-1; i++){
    for(int j=i+1; j<dim; j++){
      if(vett[i]>vett[j]){
        //swap
        int temp = vett[i];
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
	unsigned short n, m;
  int* vett;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n >> m;
    vett = new int[n+m];
		for(int i=0; i<n+m; i++){
      iss >> vett[i];
		}
    ordina(vett, n+m);
		for(int i=0; i<n+m; i++){
  		outfile << vett[i] << " ";
		}
		outfile << "\n";
	}
	return 0;
}
