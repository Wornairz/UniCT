#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


short max(int mat[][100], int dim){
  short max=0;
  for(int i=0; i<dim; i++){
    for(int j=0; j<dim; j++){
      if(mat[i][j]>max) max = mat[i][j];
    }
  }
  return max;
}

void stampa(int mat[][100], int dim){
  cout << endl;
  for(int i=0; i<dim; i++){
    for(int j=0; j<dim; j++){
      cout << mat[i][j];
    }
    cout << endl;
  }
  cout << endl;
}
void azzera(int mat[][100], int dim){
  for(int i=0; i<dim; i++){
    for(int j=0; j<dim; j++){
      mat[i][j]=0;
    }
  }
}
int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	short n;
  int mat[100][100];
  azzera(mat, 100);
  short xi, yi, xf, yf;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n;
		for(int i=0; i<n; i++){
			iss >> xi >> yi >> xf >> yf;
      //cout << xi << " " << yi << " " << xf << " " << yf << " ";
      for(int i=xi; i<=xf; i++){
        for(int j=yi; j<=yf; j++){
          cout << "i=" << i << " j=" << j << endl;
          mat[i][j]++;
        }
      }
		}
		outfile << max(mat, 100) << "\n";
    azzera(mat, 100);
	}
	return 0;
}
